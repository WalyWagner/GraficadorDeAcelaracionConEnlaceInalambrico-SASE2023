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

#include <mef/mef_Modo.h>

/*==================[internal data definition]==========================*/
static estMefModo_enum est_MefModo;
int8_t contTim300ms = 300;		//Contador para 300ms
int16_t contTim1000ms = 1000;	//Contador para 1 segundo
uint8_t cont_SW_ID_1_Ev = 0;	//Contador para eventos de SW1 -> Se usa para cambiar de modo PLOT3D a MASTER
bool SASE = true;				//Bandera para alternar entre los mensajes SASE Y 2023 en el OLED

/*==================[external functions definition]==========================*/
void mefModo_init() {
	/* Inicializacion estado de la MEF */
	est_MefModo = EST_DETECCION_TRAMA;
	mefDeteccionTrama_init();
	mefPlot3D_init();

	/*Inicialización de gráficas en displays -> Se debería realizar en una subrutina image_Init()
	 * Se muestra un Título "|ACELEROMETRO SD2|" y una imagen conformada por un circulo y dos rectángulos
	 * En su interior de imprimirá el módulo de la aceleración cada 300ms
	 * Por otra parte se muestra "SASE" - "2023" alternadamente cada medio segundo en el OLED
	 * */
	oled_fillRect(40, 20, 40+48, 20+30, OLED_COLOR_WHITE);				//Rectangulo exterior
	oled_fillRect(40+4, 20+4, 40+48-4, 20+30-4, OLED_COLOR_BLACK);		//Rectangulo interior
	oled_circle(64, 35, 30, OLED_COLOR_WHITE);							//Circulo
	oled_putString(88, 55, (uint8_t *) "Master", OLED_COLOR_WHITE, OLED_COLOR_BLACK);				//Msj OLED
	oled_putString(14, 0, (uint8_t *) "|ACELEROMETRO SD2|", OLED_COLOR_BLACK, OLED_COLOR_WHITE);	//Msj OLED
	SegLCD_DisplayHex(0x5A5E);											//Msj LCD
}

void mefModo() {
	switch (est_MefModo) {
		case EST_DETECCION_TRAMA:
			mefDeteccionTrama();
			if (board_getSw(BOARD_SW_ID_1) && board_getSw(BOARD_SW_ID_3)) {
				mefPlot3D_reset();
				est_MefModo = EST_PLOT_3D;
				oled_putString(88, 55, (uint8_t *) "Plot3D", OLED_COLOR_WHITE, OLED_COLOR_BLACK);
			}
			break;

		case EST_PLOT_3D:
			mefPlot3D();
			if (key_getPressEv(BOARD_SW_ID_1)){
				cont_SW_ID_1_Ev++;
			}
			if (cont_SW_ID_1_Ev >= 3) {
				cont_SW_ID_1_Ev = 0;
				mefDeteccionTrama_reset();
				est_MefModo = EST_DETECCION_TRAMA;
				oled_putString(88, 55, (uint8_t *) "Master", OLED_COLOR_WHITE, OLED_COLOR_BLACK);
			}
			break;
	}
}

void mefModo_task1ms() {
	contTim300ms--;contTim1000ms--;

	if (est_MefModo == EST_PLOT_3D) {
		mefPlot3D_task1ms();
	}
	if (contTim300ms<=0){
		contTim300ms=300;
		int16_t accX, accY, accZ;
		mma8451_getAcXYZ(&accX, &accY, &accZ);
		int accMod = sqrt (accX*accX+accY*accY+accZ*accZ);

		char virtual_value[6];
		sprintf((char *)virtual_value,"%dcg\n",(int) accMod);
		oled_putString(48, 32, (uint8_t *) virtual_value, OLED_COLOR_WHITE, OLED_COLOR_BLACK);
	if (contTim1000ms<=0){
		contTim1000ms=1000;
		if (SASE){
			SegLCD_DisplayDecimal(2023);
			SASE=false;
		}  else{
			SegLCD_DisplayHex(0x5A5E);
			SASE=true;
		}
	}
}
}
/*==================[end of file]============================================*/
