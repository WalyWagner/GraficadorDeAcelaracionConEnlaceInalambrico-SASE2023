/* Copyright 2017, DSI FCEIA UNR - Sistemas Digitales 2
 *    DSI: http://www.dsi.fceia.unr.edu.ar/
 * Copyright 2017, Diego Alegrechi
 * Copyright 2017, Gustavo Muro
 * Copyright 2023, Walter Wagner => wagner@fceia.unr.edu.ar
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/*==================[inclusions]=============================================*/
#include <onBoard/onBoard_Mma8451.h>

/*==================[internal data declaration]==============================*/
static bool dataReadyFlag = false;
static int16_t readX, readY, readZ;

/*==================[internal functions declaration]=========================*/
static uint8_t onBoard_Mma8451_read_reg(uint8_t addr)
{
	i2c_master_transfer_t masterXfer;
    uint8_t ret;

	memset(&masterXfer, 0, sizeof(masterXfer));    // pone todo en cero (sizeof())
	masterXfer.slaveAddress = MMA8451_I2C_ADDRESS;
	masterXfer.direction = kI2C_Read;
	masterXfer.subaddress = addr;
	masterXfer.subaddressSize = 1;
	masterXfer.data = &ret;
	masterXfer.dataSize = 1;
	masterXfer.flags = kI2C_TransferDefaultFlag;

	I2C_MasterTransferBlocking(I2C0, &masterXfer);

	return ret;
}

static void onBoard_Mma8451_read_multyReg(uint8_t addr, uint8_t *buff, uint8_t size){
//Es más óptimo, si se desean leer los 3 ejes inciar una sola vez la comunicación
//Aprovechando que los registros donde se almacenan las lecturas son contiguos

	i2c_master_transfer_t masterXfer;

	memset(&masterXfer, 0, sizeof(masterXfer));
	masterXfer.slaveAddress = MMA8451_I2C_ADDRESS;
	masterXfer.direction = kI2C_Read;
	masterXfer.subaddress = addr;
	masterXfer.subaddressSize = 1;
	masterXfer.data = buff;
	masterXfer.dataSize = size;
	masterXfer.flags = kI2C_TransferDefaultFlag;

	I2C_MasterTransferBlocking(I2C0, &masterXfer);
}

static void onBoard_Mma8451_write_reg(uint8_t addr, uint8_t data)
{
	i2c_master_transfer_t masterXfer;

    memset(&masterXfer, 0, sizeof(masterXfer));

    masterXfer.slaveAddress = MMA8451_I2C_ADDRESS;
	masterXfer.direction = kI2C_Write;
	masterXfer.subaddress = addr;
	masterXfer.subaddressSize = 1;
	masterXfer.data = &data;
	masterXfer.dataSize = 1;
	masterXfer.flags = kI2C_TransferDefaultFlag;

    I2C_MasterTransferBlocking(I2C0, &masterXfer);
}

static void onBoard_Mma8451_configPort_Init(void)
{
	const port_pin_config_t port_int1_config = {
			/* Internal pull-up/down resistor is disabled */
		.pullSelect = kPORT_PullDisable,
		/* Slow slew rate is configured */
		.slewRate = kPORT_SlowSlewRate,
		/* Passive filter is disabled */
		.passiveFilterEnable = kPORT_PassiveFilterDisable,
		/* Low drive strength is configured */
		.driveStrength = kPORT_LowDriveStrength,
		/* Pin is configured as PTC3 */
		.mux = kPORT_MuxAsGpio,
	};
	const gpio_pin_config_t gpio_int1_config = {
		.pinDirection = kGPIO_DigitalInput,
		.outputLogic = 0U
	};

	PORT_SetPinConfig(INT1_PORT, INT1_PIN, &port_int1_config);
	GPIO_PinInit(INT1_GPIO, INT1_PIN, &gpio_int1_config);

	/* Interrupt polarity active high, or active low. Default value: 0.
	   0: Active low; 1: Active high. VER REGISTRO CTRL_REG3 */
	PORT_SetPinInterruptConfig(INT1_PORT, INT1_PIN, kPORT_InterruptLogicZero);

	NVIC_EnableIRQ(PORTC_PORTD_IRQn);
	NVIC_SetPriority(PORTC_PORTD_IRQn, 0);
}

/*==================[external functions definition]==========================*/
void onBoard_Mma8451_Init(void)
{
    CTRL_REG1_t ctrl_reg1;
    CTRL_REG4_t ctrl_reg4;
    CTRL_REG5_t ctrl_reg5;

	ctrl_reg4.INT_EN_DRDY = 1;
	ctrl_reg4.INT_EN_FF_MT = 0;
	ctrl_reg4.INT_EN_PULSE = 0;
	ctrl_reg4.INT_EN_LNDPRT = 0;
	ctrl_reg4.INT_EN_TRANS = 0;
	ctrl_reg4.INT_EN_FIFO = 0;
	ctrl_reg4.INT_EN_ASLP = 0;

	onBoard_Mma8451_write_reg(CTRL_REG4_ADDRESS, ctrl_reg4.data);

	ctrl_reg5.INT_CFG_DRDY = 1;
	ctrl_reg5.INT_CFG_FF_MT = 0;
	ctrl_reg5.INT_CFG_PULSE = 0;
	ctrl_reg5.INT_CFG_LNDPRT = 0;
	ctrl_reg5.INT_CFG_TRANS = 0;
	ctrl_reg5.INT_CFG_FIFO = 0;
	ctrl_reg5.INT_CFG_ASLP = 0;

	onBoard_Mma8451_write_reg(CTRL_REG5_ADDRESS, ctrl_reg5.data);


	ctrl_reg1.ACTIVE = 1;
	ctrl_reg1.F_READ = 0;
	ctrl_reg1.LNOISE = 1;
	ctrl_reg1.DR = 0B101;
	ctrl_reg1.ASLP_RATE = 0B00;

    onBoard_Mma8451_write_reg(CTRL_REG1_ADDRESS, ctrl_reg1.data);

    onBoard_Mma8451_configPort_Init();
}

void onBoard_Mma8451_setDataRate(DR_enum rate)
{
    CTRL_REG1_t ctr_reg1;
    bool estAct;

    /* antes de modificar data rate es necesario poner ACTIVE = 0 */
    ctr_reg1.data = onBoard_Mma8451_read_reg(CTRL_REG1_ADDRESS);

    /* guarda valor que tiene ACTIVE y luego pone a cero */
    estAct = ctr_reg1.ACTIVE;
    ctr_reg1.ACTIVE = 0;

	onBoard_Mma8451_write_reg(CTRL_REG1_ADDRESS, ctr_reg1.data);

	/* actualiza DR y en la misma escritura va a restaurar ACTIVE */
	ctr_reg1.DR = rate;
	ctr_reg1.ACTIVE = estAct;

	onBoard_Mma8451_write_reg(CTRL_REG1_ADDRESS, ctr_reg1.data);


}

bool onBoard_Mma8451_isDataReady(void){
	if (dataReadyFlag) {
		dataReadyFlag = false;
		return true;
	}
	return false;
}

int16_t onBoard_Mma8451_getAcX(void){
	return (int16_t)(((int32_t)readX * 100) / (int32_t)4096);
}

int16_t onBoard_Mma8451_getAcY(void){
	return (int16_t)(((int32_t)readY * 100) / (int32_t)4096);
}

int16_t onBoard_Mma8451_getAcZ(void){
	return (int16_t)(((int32_t)readZ * 100) / (int32_t)4096);
}

void onBoard_Mma8451_getAcXYZ(int16_t *X, int16_t *Y, int16_t *Z){
	*X = (int16_t)(((int32_t)readX * 100) / (int32_t)4096);
	*Y = (int16_t)(((int32_t)readY * 100) / (int32_t)4096);
	*Z = (int16_t)(((int32_t)readZ * 100) / (int32_t)4096);
}


void PORTC_PORTD_IRQHandler(void){

    INT_SOURCE_t intSource;

    intSource.data = onBoard_Mma8451_read_reg(INT_SOURCE_ADDRESS);

    if (intSource.SRC_DRDY){
    	uint8_t bufAcc[6];
    	int16_t readG;

    	onBoard_Mma8451_read_multyReg(0x01, bufAcc, sizeof(bufAcc));

    	readG   = (int16_t)bufAcc[0] << 8;
    	readG  |= (int16_t)bufAcc[1];
    	readX = readG >> 2;

    	readG   = (int16_t)bufAcc[2] << 8;
    	readG  |= (int16_t)bufAcc[3];
    	readY = readG >> 2;

    	readG   = (int16_t)bufAcc[4] << 8;
    	readG  |= (int16_t)bufAcc[5];
    	readZ = readG >> 2;

    	dataReadyFlag = true;
    }

    PORT_ClearPinsInterruptFlags(INT1_PORT, 1<<INT1_PIN);
}
/*==================[end of file]============================================*/
