/**
 ******************************************************************************
 * File Name          : bargraph.c
 * Date               :
 * Author				: Xavier Halgand
 * Description        : Adapted for SSD1306 Display
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/

#include "bargraph.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include <stdio.h>

// Visualizer State
static uint16_t bg_value = 0;

void bargraphInit(void)
{
    // SSD1306 Initialization is done in main.c
    // We just reset internal state
    bg_value = 0;
}

void bargraphWrite(uint16_t data)
{
    // Store the value to be displayed (0-10 roughly, or bitmask)
    bg_value = data;
}

/*  bargraphUpdate() is called periodically */
void bargraphUpdate(void)
{
    // Draw a simple bar or visualization on the OLED
    // Assuming 10 "LEDs" equivalent

    ssd1306_Fill(Black);

    char buf[16];
    snprintf(buf, sizeof(buf), "Brisophone H7");
    ssd1306_SetCursor(2, 0);
    ssd1306_WriteString(buf, Font_7x10, White);

    // Draw 10 boxes for the bargraph
    // x start: 10, width 10, gap 2.

    for(int i=0; i<10; i++) {
        uint8_t x = 4 + (i * 12);
        uint8_t y = 20;
        uint8_t w = 10;
        uint8_t h = 30;

        // Check if bit 'i' is set
        if (bg_value & (1 << i)) {
            ssd1306_FillRectangle(x, y, x+w, y+h, White);
        } else {
            ssd1306_DrawRectangle(x, y, x+w, y+h, White);
        }
    }

    ssd1306_UpdateScreen();
}
