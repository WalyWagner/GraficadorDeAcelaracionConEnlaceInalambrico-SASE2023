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
 ****************************************************************************************************/

#include "procPeticion.h"

/*==================[internal data definitions]==========================*/
uint8_t bufferEnv[32];
tramaData tramaRec;
bool ProcTrama_flag = false;


/*==================[external functions definition]==========================*/
uint8_t* get_bufferEnv(){
	return bufferEnv;
}

bool procPeticion(char *trama, int size) { //ejecuta función segun periferico que deba intervenir
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

/*==================[internal function definitions]==========================*/
void Leds() { 										//cuando se detecta accion sobre LED
	switch (tramaRec.actionCode[0]) {
		case '1':
			switch(tramaRec.actionCode[1]) {
				case 'E':
					board_setLed(BOARD_LED_ID_ROJO,BOARD_LED_MSG_ON);
					ProcTrama_flag = 1;
					break;

				case 'A':
					board_setLed(BOARD_LED_ID_ROJO,BOARD_LED_MSG_OFF);
					ProcTrama_flag = 1;
					break;

				case 'T':
					board_setLed(BOARD_LED_ID_ROJO,BOARD_LED_MSG_TOGGLE);
					ProcTrama_flag = 1;
					break;
			}
			break;

		case '2':
			switch (tramaRec.actionCode[1]) {
				case 'E':
					board_setLed(BOARD_LED_ID_VERDE,BOARD_LED_MSG_ON);
					ProcTrama_flag=1;
					break;

				case 'A':
					board_setLed(BOARD_LED_ID_VERDE,BOARD_LED_MSG_OFF);
					ProcTrama_flag=1;
					break;

				case 'T':
					board_setLed(BOARD_LED_ID_VERDE,BOARD_LED_MSG_TOGGLE);
					ProcTrama_flag=1;
					break;
			}
			break;
	}
	sprintf((char*)bufferEnv, "%s\n",tramaRec.data);
}

void Switch() { 							//cuando se detecta lectura SW
	switch (tramaRec.actionCode[0]) {
		case '1':
			if (board_getSw(BOARD_SW_ID_1)) {
				sprintf((char*)bufferEnv, "%sP\n",tramaRec.data);
				ProcTrama_flag=1;
			} else {
				sprintf((char*)bufferEnv, "%sN\n",tramaRec.data);
				ProcTrama_flag=1;
			}
			break;

		case '3':
			if (board_getSw(BOARD_SW_ID_3)) {
				sprintf((char*)bufferEnv, "%sP\n",tramaRec.data);
				ProcTrama_flag=1;
			} else {
				sprintf((char*)bufferEnv, "%sN\n",tramaRec.data);
				ProcTrama_flag=1;
			}
			break;
	}
}

void Acel() { 							//cuando se detecta medicion de la aceleracion
	if(tramaRec.actionCode[0] == '1') {

		int16_t accX,accY,accZ;

		if (mma8451_isDataReady()){
			//		accX= mma8451_getAcX();
			//		accY= mma8451_getAcY();
			//		accZ= mma8451_getAcZ();
			mma8451_getAcXYZ(&accX, &accY, &accZ);
			sprintf((char*)bufferEnv, "%s%+04d%+04d%+04d\n",tramaRec.data,(int)accX,(int)accY,(int)accZ);
			ProcTrama_flag = 1;
		}
	}
}

/*==================[end of file]============================================*/
