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
#include <onBoard_KL46/SD2_SwitchsAndLeds.h>

/*==================[internal data declaration]==============================*/
static const board_gpioInfo_type board_gpioLeds[] =
{
    {PORTE, GPIOE, 29},     /* LED ROJO */
    {PORTD, GPIOD, 5},      /* LED VERDE */
};

static const board_gpioInfo_type board_gpioSw[] =
{
    {PORTC, GPIOC, 3},      /* SW1 */
    {PORTC, GPIOC, 12},     /* SW3 */
};

/*==================[internal data declaration]==============================*/
static estPul_enum estSW[BOARD_SW_ID_TOTAL];
static bool eventSW[BOARD_SW_ID_TOTAL];

/*==================[external functions definition]==========================*/
void SwitchsAndLeds_init(void){
    	int32_t i;
    	gpio_pin_config_t gpio_led_config =
    	{
    		.outputLogic = 1,
    		.pinDirection = kGPIO_DigitalOutput,
    	};
    	gpio_pin_config_t gpio_sw_config = {
    		.outputLogic = 0U,
    		.pinDirection = kGPIO_DigitalInput
    	};


    	const port_pin_config_t port_led_config = {
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

    	const port_pin_config_t port_sw_config = {
    		/* Internal pull-up resistor is enabled */
    		.pullSelect = kPORT_PullUp,
    		/* Fast slew rate is configured */
    		.slewRate = kPORT_FastSlewRate,
    		/* Passive filter is disabled */
    		.passiveFilterEnable = kPORT_PassiveFilterDisable,
    		/* Low drive strength is configured */
    		.driveStrength = kPORT_LowDriveStrength,
    		/* Pin is configured as PTC3 */
    		.mux = kPORT_MuxAsGpio,
    	};


    	CLOCK_EnableClock(kCLOCK_PortA);
    	CLOCK_EnableClock(kCLOCK_PortB);
    	CLOCK_EnableClock(kCLOCK_PortC);
    	CLOCK_EnableClock(kCLOCK_PortD);
    	CLOCK_EnableClock(kCLOCK_PortE);

    	/* Inicialización de leds */
    	for (i = 0 ; i < BOARD_LED_ID_TOTAL ; i++)
    	{
    		PORT_SetPinConfig(board_gpioLeds[i].port, board_gpioLeds[i].pin, &port_led_config);
    		GPIO_PinInit(board_gpioLeds[i].gpio, board_gpioLeds[i].pin, &gpio_led_config);
    	}

    	/* Inicialización de SWs */
    	for (i = 0 ; i < BOARD_SW_ID_TOTAL; i++)
    	{
    		PORT_SetPinConfig(board_gpioSw[i].port, board_gpioSw[i].pin, &port_sw_config);
    		GPIO_PinInit(board_gpioSw[i].gpio, board_gpioSw[i].pin, &gpio_sw_config);
    	}

    	/* Inicilización de los pines PTA16 y PTA17 como GPIO*/
    	PORT_SetPinConfig(PORTA, 16, &port_led_config);
    	GPIO_PinInit(GPIOA, 16, &gpio_led_config);

    	PORT_SetPinConfig(PORTA, 17, &port_led_config);
    	GPIO_PinInit(GPIOA, 17, &gpio_led_config);

    	key_init();

}

void board_setLed(board_ledId_enum id, board_ledMsg_enum msg){
    switch (msg)
    {
        case BOARD_LED_MSG_OFF:
        	GPIO_PortSet(board_gpioLeds[id].gpio, 1<<board_gpioLeds[id].pin);
            break;

        case BOARD_LED_MSG_ON:
        	GPIO_PortClear(board_gpioLeds[id].gpio, 1<<board_gpioLeds[id].pin);
            break;

        case BOARD_LED_MSG_TOGGLE:
        	GPIO_PortToggle(board_gpioLeds[id].gpio, 1<<board_gpioLeds[id].pin);
            break;

        default:
            break;
    }
}

bool board_getSw(board_swId_enum id){
    return !GPIO_ReadPinInput(board_gpioSw[id].gpio, board_gpioSw[id].pin);
}


/* Todas las subrutinas key_... se utilizan emulando una MEF
 * Sirven para detectar eventos en los Switches y no que esté pulsado en un momento particular
 */
void key_init(void){
    for (int32_t i = 0 ; i < BOARD_SW_ID_TOTAL ; i++)
    {
        estSW[i] = ESPERANDO_ACTIVACION;
        eventSW[i] = 0;
    }
}

bool key_getPressEv(board_swId_enum id){
    bool ret = false;

    if (eventSW[id])
    {
        eventSW[id] = 0;
        ret = true;
    }

    return ret;
}

void key_periodicTask1ms(void){
    for (int32_t i = 0 ; i < BOARD_SW_ID_TOTAL ; i++)
    {
        switch (estSW[i])
        {
            case ESPERANDO_ACTIVACION:
                if (board_getSw(i))
                {
                    eventSW[i] = 1;
                    estSW[i] = ESPERANDO_DESACTIVACION;
                }
                break;

            case ESPERANDO_DESACTIVACION:
                if (!board_getSw(i))
                {
                    estSW[i] = ESPERANDO_ACTIVACION;
                }
                break;

            default:
                estSW[i] = ESPERANDO_ACTIVACION;
                break;
        }
    }
}

/*==================[end of file]============================================*/
