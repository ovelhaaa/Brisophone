# Brisophone Porting Notes

## Overview
This document summarizes the changes made to port the Brisophone project to the STM32H743VIT6 (WeAct) board with SSD1306 Display and PCM5102 DAC.

## Pinout Mapping

| Function | Pin | Peripheral | Note |
| :--- | :--- | :--- | :--- |
| **I2S Audio** | | **SPI2** | Master TX, 48kHz, 16-bit |
| I2S_WS (LRCK) | PB12 | SPI2 | AF5 |
| I2S_CK (BCK) | PB13 | SPI2 | AF5 |
| I2S_SD (DIN) | PB15 | SPI2 | AF5 |
| **Display** | | **I2C1** | SSD1306 OLED (128x64) |
| I2C_SCL | PB6 | I2C1 | AF4, Pull-up |
| I2C_SDA | PB7 | I2C1 | AF4, Pull-up |
| **Buttons** | | **GPIO** | Active High (Internal Pull-down) |
| Button 1 | PD8 | GPIOD | Input |
| Button 2 | PD9 | GPIOD | Input |
| Button 3 | PD10 | GPIOD | Input |
| Button 4 | PD11 | GPIOD | Input |

## Clock Configuration
- **System Clock (SYSCLK):** 480 MHz
    - Source: HSE (25 MHz) -> PLL1.
    - Power Scale: VOS0 (Required for 480MHz).
- **Audio Clock:** ~12.288 MHz (Target for 256 * Fs)
    - Source: PLL2P.
    - Configuration: Fractional mode enabled on PLL2 to achieve precise frequency from 1MHz ref.
    - Exact Freq: ~12.2885 MHz.
    - I2S Prescaler: 8 (Linear). Bit Clock = 12.288 / 8 = 1.536 MHz = 48000 * 16 * 2.

## Memory Management
- **Audio Buffer:** Placed in **RAM_D2 (SRAM2)** using `__attribute__((section(".sram2")))`.
    - This ensures the DMA2 (or DMA1) can access the memory without bus contention from the CPU (D1).
- **Cache Coherency:** D-Cache maintenance (`SCB_CleanDCache_by_Addr`) is implemented in `audio.c` DMA callbacks to ensure data written by the CPU is visible to the DMA.

## Dependencies
- **SSD1306 Library:** Included in `lib/ssd1306`. Configured for I2C.
- **STM32Cube HAL:** Managed by PlatformIO.

## Hardware Notes
- **PCM5102:** Ensure SCK (system clock) pin of PCM5102 is tied to GND if using internal PLL mode (which typical modules do), or disconnected if not provided. The code generates BCK, WS, DOUT.
- **Levels:** STM32H7 is 3.3V logic.
