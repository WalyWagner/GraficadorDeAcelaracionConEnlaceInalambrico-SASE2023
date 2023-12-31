/*****************************************************************************
 *   oled.h:  Header file for SSD1306 OLED Display
 *
 *   Copyright 2009, Embedded Artists AB
 *   Copyright 2023, DSI FCEIA UNR - Sistemas Digitales 2
 *    DSI: http://www.dsi.fceia.unr.edu.ar/
 *   Copyright 2023, Guido Cicconi
 *   Copyright 2023, Walter Wagner
 *   All rights reserved.
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
 *
 */
#ifndef offBoard_oledDriver_H
#define offBoard_oledDriver_H

/*==================[inclusions]=============================================*/
#include <stdint.h>

/*==================[cplusplus]==============================================*/
#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/
typedef enum
{
    OLED_COLOR_BLACK = 0,
    OLED_COLOR_WHITE
} oled_color_t;

#define OLED_DISPLAY_WIDTH  128
#define OLED_DISPLAY_HEIGHT 64


/*==================[external functions definition]==========================*/
void offBoard_oledDriver_Init (void);
void offBoard_oledDriver_putPixel(uint8_t x, uint8_t y, oled_color_t color);
void offBoard_oledDriver_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, oled_color_t color);
void offBoard_oledDriver_circle(uint8_t x0, uint8_t y0, uint8_t r, oled_color_t color);
void offBoard_oledDriver_rect(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, oled_color_t color);
void offBoard_oledDriver_fillRect(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, oled_color_t color);
void offBoard_oledDriver_clearScreen(oled_color_t color);
void offBoard_oledDriver_putString(uint8_t x, uint8_t y, uint8_t *pStr, oled_color_t fb, oled_color_t bg);
uint8_t offBoard_oledDriver_putChar(uint8_t x, uint8_t y, uint8_t ch, oled_color_t fb, oled_color_t bg);
void offBoard_oledDriver_setContrast(uint8_t contrast);

/*==================[cplusplus]==============================================*/
#ifdef __cplusplus
}
#endif

#endif /* offBoard_oledDriver_H */
