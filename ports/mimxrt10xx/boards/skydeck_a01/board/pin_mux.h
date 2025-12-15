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

#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Calls initialization functions.
 */
void BOARD_InitBootPins(void);

/* GPIO_LPSR_08 - Green LED (active low) */
#define BOARD_INITPINS_USER_LED_PERIPHERAL                                GPIO12   /*!< Peripheral name */
#define BOARD_INITPINS_USER_LED_SIGNAL                                   gpio_io   /*!< Signal name */
#define BOARD_INITPINS_USER_LED_CHANNEL                                       8U   /*!< Signal channel */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_USER_LED_GPIO                                      GPIO12   /*!< GPIO peripheral base pointer */
#define BOARD_INITPINS_USER_LED_GPIO_PIN                                      8U   /*!< GPIO pin number */
#define BOARD_INITPINS_USER_LED_GPIO_PIN_MASK                         (1U << 8U)   /*!< GPIO pin mask */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 */
void BOARD_InitPins(void);

/*!
 * @brief Configures LPUART1 pins for debug console.
 */
void BOARD_InitDEBUG_UARTPins(void);

#if defined(__cplusplus)
}
#endif

#endif /* _PIN_MUX_H_ */
