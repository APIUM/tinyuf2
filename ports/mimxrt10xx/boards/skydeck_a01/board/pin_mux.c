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

#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "fsl_gpio.h"
#include "pin_mux.h"

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitBootPins
 * Description   : Calls initialization functions.
 *
 * END ****************************************************************************************************************/
void BOARD_InitBootPins(void) {
    BOARD_InitPins();
}

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitPins(void) {
    CLOCK_EnableClock(kCLOCK_Iomuxc);           /* LPCG on: LPCG is ON. */
    CLOCK_EnableClock(kCLOCK_Iomuxc_Lpsr);      /* Enable LPSR IOMUXC clock for GPIO_LPSR pins */

    /* GPIO configuration of USER_LED on GPIO_LPSR_08 (active low, start with LED off) */
    gpio_pin_config_t USER_LED_config = {
        .direction = kGPIO_DigitalOutput,
        .outputLogic = 1U,                      /* Start high (LED off, active low) */
        .interruptMode = kGPIO_NoIntmode
    };
    /* Initialize GPIO functionality on GPIO_LPSR_08 */
    GPIO_PinInit(GPIO12, 8U, &USER_LED_config);

    IOMUXC_SetPinMux(
        IOMUXC_GPIO_LPSR_08_GPIO12_IO08,        /* GPIO_LPSR_08 is configured as GPIO12_IO08 */
        0U);                                    /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_LPSR_08_GPIO12_IO08,        /* GPIO_LPSR_08 PAD functional properties : */
        0x02U);                                 /* Slew Rate Field: Fast Slew Rate
                                                   Drive Strength Field: high drive strength
                                                   Pull / Keep Select Field: Pull Disable
                                                   Pull Up / Down Config. Field: Weak pull down
                                                   Open Drain Field: Disabled */
}

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitDEBUG_UARTPins
 * Description   : Configures LPUART1 pins for debug console.
 *
 * END ****************************************************************************************************************/
void BOARD_InitDEBUG_UARTPins(void) {
    CLOCK_EnableClock(kCLOCK_Iomuxc);           /* LPCG on: LPCG is ON. */

    IOMUXC_SetPinMux(
        IOMUXC_GPIO_AD_24_LPUART1_TXD,          /* GPIO_AD_24 is configured as LPUART1_TXD */
        0U);                                    /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_AD_25_LPUART1_RXD,          /* GPIO_AD_25 is configured as LPUART1_RXD */
        0U);                                    /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_AD_24_LPUART1_TXD,          /* GPIO_AD_24 PAD functional properties : */
        0x03U);                                 /* Slew Rate Field: Slow Slew Rate
                                                   Drive Strength Field: high drive strength
                                                   Pull / Keep Select Field: Pull Disable
                                                   Pull Up / Down Config. Field: Weak pull down
                                                   Open Drain Field: Disabled */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_AD_25_LPUART1_RXD,          /* GPIO_AD_25 PAD functional properties : */
        0x03U);                                 /* Slew Rate Field: Slow Slew Rate
                                                   Drive Strength Field: high drive strength
                                                   Pull / Keep Select Field: Pull Disable
                                                   Pull Up / Down Config. Field: Weak pull down
                                                   Open Drain Field: Disabled */
}
