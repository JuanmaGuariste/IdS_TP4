/************************************************************************************************
Copyright (c) 2023, Juan Manuel Guariste <juanmaguariste@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial
portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES
OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

SPDX-License-Identifier: MIT
*************************************************************************************************/

/**
 * @file main.c
 * @brief Definition of the main function of the program.
 *
 * This file contains the implementation of the main entry point for the program.
 * It initializes the necessary hardware and manages the main application loop
 * to handle GPIO functionality, such as controlling an LED based on button input.
 *
 * @author Juan Manuel Guariste
 * @date 20/11/2024
 */

/* === Headers files inclusions =============================================================== */

#include "main.h"
#include "gpio.h"

/* === Macros definitions ====================================================================== */

#define RED_LED_PORT 1
#define RED_LED_BIT  7
#define BUTTON_PORT  2
#define BUTTON_BIT   3

/* === Private data type declarations ========================================================== */

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

/* === Public function implementation ========================================================== */

int main(void) {
    gpio_t led_rojo;
    gpio_t button;

    led_rojo = gpioCreate(RED_LED_PORT, RED_LED_BIT);
    button = gpioCreate(BUTTON_PORT, BUTTON_BIT);

    gpioSetDirection(led_rojo, true);
    gpioSetState(led_rojo, false);
    gpioSetDirection(button, false);

    while (1) {
        if (gpioGetState(button)) {
            gpioSetState(led_rojo, true);
        } else {
            gpioSetState(led_rojo, false);
        }
    }
    return 0;
}

/* === End of documentation ==================================================================== */
