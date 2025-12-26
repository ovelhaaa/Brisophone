#ifndef __SSD1306_CONF_H__
#define __SSD1306_CONF_H__

// Choose interface
#define SSD1306_USE_I2C
// #define SSD1306_USE_SPI

// I2C Configuration
#define SSD1306_I2C_PORT        hi2c1
#define SSD1306_I2C_ADDR        (0x3C << 1)

// Mirror the screen if needed
// #define SSD1306_MIRROR_VERT
// #define SSD1306_MIRROR_HORIZ

// Set Inverse Color if needed
// #define SSD1306_INVERT_COLOR

// Include fonts that we need
#define SSD1306_INCLUDE_FONT_6x8
#define SSD1306_INCLUDE_FONT_7x10
#define SSD1306_INCLUDE_FONT_11x18
// #define SSD1306_INCLUDE_FONT_16x26

#endif /* __SSD1306_CONF_H__ */
