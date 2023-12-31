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

#include "mef_Plot3D.h"

/*==================[internal data declaration]==============================*/
static estMefPlot3D_enum estMefPlot3D = EST_ESPERANDO;
static int timerDelay = DELAY;

/*==================[internal functions declaration]=========================*/

static void mefPlot3D_enviaAcel() {
	uint8_t envioMje[15];
	int16_t accX,accY,accZ;
	//if (nBoard_Mma8451_isDataReady()){		//No es necesario
		//		accX= nBoard_Mma8451_getAcX();
		//		accY= nBoard_Mma8451_getAcY();
		//		accZ= nBoard_Mma8451_getAcZ();
		onBoard_Mma8451_getAcXYZ(&accX, &accY, &accZ);
		sprintf((char*)envioMje, "%d %d %d\n", (int)accX, (int)accY, (int)accZ);

	//}
		dataTransfer_EnvDMA_RecRingBuff_envDatos(envioMje, strlen((char*)envioMje));
}

/*==================[external functions declaration]=========================*/

void mefPlot3D_init() {
	mefPlot3D_reset();
}

void mefPlot3D_reset() {
	estMefPlot3D = EST_ESPERANDO;
	timerDelay = DELAY;
}

void mefPlot3D() {
	switch (estMefPlot3D) {
		case EST_ESPERANDO:
			if (timerDelay <= 0) {
				estMefPlot3D = EST_ENVIANDO;
			}
			break;

		case EST_ENVIANDO:
			if (onBoard_Mma8451_isDataReady()) {
				mefPlot3D_enviaAcel();
				mefPlot3D_reset();
			}
			break;
	}
}

void mefPlot3D_task1ms() {
	if (timerDelay > 0){
		timerDelay--;
	}
}
/*==================[end of file]============================================*/
