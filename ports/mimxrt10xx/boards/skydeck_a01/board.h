/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2020 Ha Thach for Adafruit Industries
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef BOARD_H_
#define BOARD_H_

// Size of on-board external flash
#define BOARD_FLASH_SIZE      (16*1024*1024)

//--------------------------------------------------------------------+
// LED
//--------------------------------------------------------------------+

// Green LED on GPIO_LPSR_08 (active low)
#define LED_PORT              BOARD_INITPINS_USER_LED_PERIPHERAL
#define LED_PIN               BOARD_INITPINS_USER_LED_CHANNEL
#define LED_STATE_ON          0

//--------------------------------------------------------------------+
// Neopixel
//--------------------------------------------------------------------+

#define NEOPIXEL_NUMBER       0

//--------------------------------------------------------------------+
// Button
//--------------------------------------------------------------------+

// No dedicated bootloader button - use double-tap reset
// #define BUTTON_PINMUX         IOMUXC_WAKEUP_DIG_GPIO13_IO00
// #define BUTTON_PORT           GPIO13
// #define BUTTON_PIN            0
// #define BUTTON_STATE_ACTIVE   0

//--------------------------------------------------------------------+
// USB UF2
//--------------------------------------------------------------------+

#define USB_VID           0xF055
#define USB_PID           0x9802
#define USB_MANUFACTURER  "PHYTEC"
#define USB_PRODUCT       "Skydeck A01"

// USB power enable
#define USB_PWR_PINMUX    IOMUXC_GPIO_AD_07_GPIO9_IO06
#define USB_PWR_PORT      GPIO9
#define USB_PWR_PIN       6

#define UF2_PRODUCT_NAME  USB_MANUFACTURER " " USB_PRODUCT
#define UF2_BOARD_ID      "SKYDECK-A01-v1"
#define UF2_VOLUME_LABEL  "SKYDECKBOOT"
#define UF2_INDEX_URL     "https://www.phytec.com/"

//--------------------------------------------------------------------+
// UART
//--------------------------------------------------------------------+

#define UART_DEV              LPUART1

#endif /* BOARD_H_ */
