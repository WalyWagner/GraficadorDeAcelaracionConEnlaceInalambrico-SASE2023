/****************************************************************************************************
 *************************GRAFICADOR DE ACELERACIÓN CON ENLACE INALÁMBRICO***************************
 ***************************Simposio Argentino de Sistemas Embebidos 2023****************************
 ****************************************************************************************************
 ***************************************************************************WsS**********************
 *************************************************************************Copyright 2023*************
 ****************************************************************************************************
 * La documentación de este proyecto se acompaña en la carpeta raíz de mismo						*
 * Autor de la presente implementación: WALTER SEBASTIAN WAGNER               					 	*
 * Correo Electrónico: wagner@fceia.unr.edu.ar                           						 	*
 * Docente tutor: Ing. Gustavo Muro																	*
 * Correo Electrónico: gmuro@fceia.unr.edu.ar														*
 * Fecha última modificación: 31/07/2023                                         				 	*
 *                                                                       						 	*
 * Institución: UNIVERSIDAD NACIONAL DE ROSARIO                          							*
 * Dependencia: Facultad de Ciencias Exactas, Ingeniería y Agrimensura   							*
 * Escuela: Ingeniería Electrónica                                             						*
 * Departamento: Sistemas e Informática                                              				*
 * Cátedra: Sistemas Digitales 2                                                  					*
 * 																									*
 * Este código está protegido por los derechos de autor y copyright      							*
 * aplicables. Por favor, consulte el archivo ReadMe.txt que acompaña    							*
 * a este archivo para ver los términos de la licencia correspondiente.   							*
 * **************************************************************************************************
 * Se reconoce la participación de Martín Pissia como co-autor de la primera versión de este código	*
 ****************************************************************************************************/

#include <mef/mef_DeteccionTrama_ProcPeticion.h>

/*==================[internal data definitions]==========================*/
typedef union {
	struct {
		char initChar;
		char teamCode[2];
		char actionType;
		char actionCode[2];
	};
	char data[6];
}tramaData;

static void Acel();
static void Switch();
static void Leds();

/*==================[internal data declaration]==========================*/
uint8_t bufferEnv[32];
tramaData tramaRec;
bool ProcTrama_flag = false;

/*==================[internal function declarations]==========================*/
static void Leds() { 										//cuando se detecta accion sobre LED
	switch (tramaRec.actionCode[0]) {
		case '1':
			switch(tramaRec.actionCode[1]) {
				case 'E':
					onBoard_SwitchsAndLeds_setLed(BOARD_LED_ID_ROJO,BOARD_LED_MSG_ON);
					ProcTrama_flag = 1;
					break;

				case 'A':
					onBoard_SwitchsAndLeds_setLed(BOARD_LED_ID_ROJO,BOARD_LED_MSG_OFF);
					ProcTrama_flag = 1;
					break;

				case 'T':
					onBoard_SwitchsAndLeds_setLed(BOARD_LED_ID_ROJO,BOARD_LED_MSG_TOGGLE);
					ProcTrama_flag = 1;
					break;
			}
			break;

		case '2':
			switch (tramaRec.actionCode[1]) {
				case 'E':
					onBoard_SwitchsAndLeds_setLed(BOARD_LED_ID_VERDE,BOARD_LED_MSG_ON);
					ProcTrama_flag=1;
					break;

				case 'A':
					onBoard_SwitchsAndLeds_setLed(BOARD_LED_ID_VERDE,BOARD_LED_MSG_OFF);
					ProcTrama_flag=1;
					break;

				case 'T':
					onBoard_SwitchsAndLeds_setLed(BOARD_LED_ID_VERDE,BOARD_LED_MSG_TOGGLE);
					ProcTrama_flag=1;
					break;
			}
			break;
	}
	sprintf((char*)bufferEnv, "%s\n",tramaRec.data);
}

static void Switch() { 							//cuando se detecta lectura SW
	switch (tramaRec.actionCode[0]) {
		case '1':
			if (onBoard_SwitchsAndLeds_getSw(BOARD_SW_ID_1)) {
				sprintf((char*)bufferEnv, "%sP\n",tramaRec.data);
				ProcTrama_flag=1;
			} else {
				sprintf((char*)bufferEnv, "%sN\n",tramaRec.data);
				ProcTrama_flag=1;
			}
			break;

		case '3':
			if (onBoard_SwitchsAndLeds_getSw(BOARD_SW_ID_3)) {
				sprintf((char*)bufferEnv, "%sP\n",tramaRec.data);
				ProcTrama_flag=1;
			} else {
				sprintf((char*)bufferEnv, "%sN\n",tramaRec.data);
				ProcTrama_flag=1;
			}
			break;
	}
}

static void Acel() { 							//cuando se detecta medicion de la aceleracion
	if(tramaRec.actionCode[0] == '1') {

		int16_t accX,accY,accZ;

		if (onBoard_Mma8451_isDataReady()){
			//		accX= onBoard_Mma8451_getAcX();
			//		accY= onBoard_Mma8451_getAcY();
			//		accZ= onBoard_Mma8451_getAcZ();
			onBoard_Mma8451_getAcXYZ(&accX, &accY, &accZ);
			sprintf((char*)bufferEnv, "%s%+04d%+04d%+04d\n",tramaRec.data,(int)accX,(int)accY,(int)accZ);
			ProcTrama_flag = 1;
		}
	}
}

/*==================[external functions definition]==========================*/
uint8_t* mefDeteccionTrama_ProcPeticion_get_bufferEnv(){
	return bufferEnv;
}

bool mefDeteccionTrama_ProcPeticion_procPeticion(char *trama, int size) {
//ejecuta función segun periferico que deba intervenir
	strcpy(tramaRec.data, trama);
	tramaRec.data[size] = '\0';

	switch (tramaRec.actionType) {
		case '0':
			Leds();
			break;

		case '1':
			Switch();
			break;

		case '2':
			Acel();
			break;
	}
	return ProcTrama_flag;		//verdadero si una trama logro ser procesada
}
/*==================[end of file]============================================*/
