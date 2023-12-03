#include "API_mfrc522.h"
#include "API_mfrc522_port.h"

static const uint8_t READ_MASK = 0x80;
static const uint8_t WRITE_MASK = 0;

// Definiciones de algunos bits de registros utilizados
#define TxControlReg_Tx2RFEn				(1<<1)
#define TxControlReg_Tx1RFEn				1
#define ComIrqReg_RxIrq  					(1<<5)
#define ComIrqReg_TimerIrq					(1<<0)
#define FIFOLevelReg_FlushBuffer			0x80
#define BitFramingReg_StartSend				0x80
#define ComIrqReg_Set1						0x80

//registros definidos en sección 9.2 de la hoja de datos
typedef enum {
	//registros de comandos y estado
	CommandReg = 0x01,
	ComIEnReg = 0x02,
	DivIEnReg = 0x03,
	ComIrqReg = 0x04,
	DivIrqReg = 0x05,
	ErrorReg = 0x06,
	Status1Reg = 0x07,
	Status2Reg = 0x08,
	FIFODataReg = 0x09,
	FIFOLevelReg = 0x0A,
	WaterLevelReg = 0x0B,
	ControlReg = 0x0C,
	BitFramingReg = 0x0D,
	CollReg = 0x0E,

	//registros de comandos
	ModeReg = 0x11,
	TxModeReg = 0x12,
	RxModeReg = 0x13,
	TxControlReg = 0x14,
	TxASKReg = 0x15,
	TxSelReg = 0x16,
	RxSelReg = 0x17,
	RxThresholdReg = 0x18,
	DemodReg = 0x19,
	//
	//
	MfTxReg = 0x1C,
	MfRxReg = 0x1D,
	//
	SerialSpeedReg = 0x1F,

	//registros de configuracion
	CRCResultRegH = 0x21,
	CRCResultRegL = 0x22,
	//
	ModWidthReg = 0x24,
	//
	RFCfgReg = 0x26,
	GsNReg = 0x27,
	CWGsPReg = 0x28,
	ModGsPReg = 0x29,
	TModeReg = 0x2A,
	TPrescalerReg = 0x2B,
	TReloadRegH = 0x2C,
	TReloadRegL = 0x2D,
	TCounterValueRegH = 0x2E,
	TCounterValueRegL = 0x2F,

	//registros de prueba
	TestSel1Reg = 0x31,
	TestSel2Reg = 0x32,
	TestPinEnReg = 0x33,
	TestPinValueReg = 0x34,
	TestBusReg = 0x35,
	AutoTestReg = 0x36,
	VersionReg = 0x37,
	AnalogTestReg = 0x38,
	TestDAC1Reg = 0x39,
	TestDAC2Reg = 0x3A,
	TestADCReg = 0x3B
} registros_MFRC522_enum;

//comandos del MFRC522, sección 10.3 de la hoja de datos
typedef enum {
	Idle = 0x00,
	Mem = 0x01,
	GenerateRandomID = 0x02,
	CalcCRC = 0x03,
	Transmit = 0x04,
	NoCmdChange = 0x07,
	Receive = 0x08,
	Transceive = 0x0C,
	MFAuthent = 0x0E,
	SoftReset = 0x0F
} comandos_MFRC522_enum;

// Comandos a enviar a la tarjeta obtenidos de ISO/IEC 14443-3
typedef enum {
	CMD_REQA = 0x26, CMD_SEL_CL1 = 0x93
} comandos_tarjeta_enum;

static bool_t spiActivo = false;

static bool_t mfrc522_leerUID(uint8_t *uid);
static bool_t mfrc522_detectarTarjeta();
static bool_t mfrc522_leerBufferFIFO(uint8_t*);
static bool_t mfrc522_esperarRespuestaTarjeta();
static void mfrc522_enviarComandoTarjeta(uint8_t *comando, uint8_t largo,
		uint8_t txSize);
static void mfrc522_encenderAntena();

static void mfrc522_writeRegister(registros_MFRC522_enum, uint8_t);
static uint8_t mfrc522_readRegister(registros_MFRC522_enum);

void mfrc522_init() {
	spiActivo = portInit();

	if (!spiActivo)
		return;

	mfrc522_reset();

	// El módulo MFRC522 tiene un timer interno que puede ser utilizado para evitar
	// que una operación quede bloqueando el programa.
	// Se configura TModeReg = 0x80 para que el timer inicie automáticamente al finalizar una transmisión.
	mfrc522_writeRegister(TModeReg, 0x80);
	// Se configura el registro TPrescalerReg = 0xFF para una frecuencia de 26 kHz
	// y el valor de Reload en 0x0D = 13. Esto resulta en un timeout = 500 uS.
	mfrc522_writeRegister(TPrescalerReg, 0xFF);
	mfrc522_writeRegister(TReloadRegL, 0x0D);

	mfrc522_writeRegister(TxASKReg, 0x40);		// Configura modulación 100% ASK

	mfrc522_encenderAntena();			// Enciende la antena para transmitir
}

void mfrc522_reset() {
	mfrc522_writeRegister(CommandReg, SoftReset);
}

static void mfrc522_encenderAntena() {
	const uint8_t valor_deseado = TxControlReg_Tx1RFEn | TxControlReg_Tx2RFEn;

	uint8_t valor_registro = mfrc522_readRegister(TxControlReg);
	if (valor_deseado != (valor_registro & valor_deseado))
		mfrc522_writeRegister(TxControlReg, valor_registro | valor_deseado);
}

bool_t mfrc522_leerUIDTarjeta(uint8_t *uid) {
	bool_t estado = false;
	bool_t tarjetaDetectada = mfrc522_detectarTarjeta();//enviar comando tarjeta
	if (tarjetaDetectada)
		return mfrc522_leerUID(uid);		// si tarjeta presente, leer uid

	return estado;
}

static bool_t mfrc522_detectarTarjeta() {
	const uint8_t cmd = CMD_REQA;
	mfrc522_enviarComandoTarjeta(&cmd, 1, 7);
	bool_t respuestaRecibida = mfrc522_esperarRespuestaTarjeta();
	return respuestaRecibida;

}

static bool_t mfrc522_leerUID(uint8_t *uid) {
	uint8_t cmdBuffer[2];
	cmdBuffer[0] = CMD_SEL_CL1;
	cmdBuffer[1] = 0x20;
	uint8_t responseBuffer[7];

	mfrc522_enviarComandoTarjeta(cmdBuffer, sizeof(cmdBuffer), 0);

	bool_t respuestaRecibida = mfrc522_esperarRespuestaTarjeta();
	if (!respuestaRecibida)
		return respuestaRecibida;

	bool_t lecturaUid = mfrc522_leerBufferFIFO(responseBuffer);

	if (lecturaUid) {
		for (uint8_t i = 0; i < 4; i++) {
			uid[i] = responseBuffer[i];
		}
	}

	return lecturaUid;
}

static void mfrc522_enviarComandoTarjeta(uint8_t *comando, uint8_t largo,
		uint8_t txSize) {
	mfrc522_writeRegister(CommandReg, Idle);

	// Para resetear los bits de interrupciones
	// en el registro ComIrqReg.
	uint8_t valor_ComIrqReg = mfrc522_readRegister(ComIrqReg);
	mfrc522_writeRegister(ComIrqReg, valor_ComIrqReg & (~ComIrqReg_Set1));

	mfrc522_writeRegister(FIFOLevelReg, FIFOLevelReg_FlushBuffer);
	for (uint8_t i = 0; i < largo; i++) {
		mfrc522_writeRegister(FIFODataReg, *(comando + i));
	}

	mfrc522_writeRegister(CommandReg, Transceive);

	// Iniciar la transmisión e indica que se transmiten solo txSize bits.
	// txSize = 0 indica que se transmiten 8 bits.
	mfrc522_writeRegister(BitFramingReg, BitFramingReg_StartSend | txSize);
}

static bool_t mfrc522_esperarRespuestaTarjeta() {
	bool_t respuestaRecibida = false;
	while (!respuestaRecibida) {
		uint8_t irqReg = mfrc522_readRegister(ComIrqReg);
		if (irqReg & ComIrqReg_TimerIrq)		//ver si ocurre un timeout
			break;
		if (irqReg & ComIrqReg_RxIrq)	//si se recibe una respuesta
			respuestaRecibida = true;
	}
	return respuestaRecibida;
}

static bool_t mfrc522_leerBufferFIFO(uint8_t *response) {
	uint8_t n = mfrc522_readRegister(FIFOLevelReg);
	if (n == 0)
		return false;
	for (uint8_t i = 0; i < n; i++) {
		response[i] = mfrc522_readRegister(FIFODataReg);
	}
	return true;
}

static void mfrc522_writeRegister(registros_MFRC522_enum reg, uint8_t data) {
	uint8_t reg_addr = WRITE_MASK | reg << 1;
	spiWrite(reg_addr, &data, 1);
}

static uint8_t mfrc522_readRegister(registros_MFRC522_enum reg) {
	uint8_t rxBuffer = 0;
	uint8_t reg_addr = READ_MASK | reg << 1;
	spiRead(reg_addr, &rxBuffer, 1);
	return rxBuffer;
}
