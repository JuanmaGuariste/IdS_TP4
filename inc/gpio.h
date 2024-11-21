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

#ifndef GPIO_H
#define GPIO_H

/**
 * @file gpio.h
 * @brief Declarations for the GPIO module.
 *
 * This file contains the declarations for the GPIO module, including functions,
 * data types, and macros for managing GPIO pins. It provides an interface
 * for creating, configuring, and controlling GPIO objects in an embedded system.
 *
 * @author Juan Manuel Guariste
 * @date 20/11/2024
 */

/* === Headers files inclusions ================================================================ */
#include <stdint.h>
#include <stdbool.h>

/* === Cabecera C++ ============================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =============================================================== */

/* === Public data type declarations =========================================================== */

/**
 * @brief Typedef for a pointer to a GPIO object.
 *
 * This typedef defines a pointer to a structure representing a GPIO object.
 */
typedef struct gpio_s * gpio_t;

/* === Public variable declarations ============================================================ */

/* === Public function declarations ============================================================ */

/**
 * @brief Creates a GPIO instance.
 *
 * This function initializes a structure to represent a GPIO, allocating
 * the required memory either dynamically or statically, depending on the configuration.
 *
 * @param port GPIO port number.
 * @param bit Pin number within the port.
 * @return gpio_t A reference to the created GPIO instance, or NULL if the creation fails.
 */
gpio_t gpioCreate(uint8_t port, uint8_t bit);

/**
 * @brief Configures the direction of a GPIO.
 *
 * This function sets whether a GPIO should operate as an input or an output.
 *
 * @param self GPIO instance to configure.
 * @param io `true` to configure as output, `false` to configure as input.
 */
void gpioSetDirection(gpio_t self, bool io);

/**
 * @brief Sets the logical state of a GPIO configured as output.
 *
 * This function changes the state of a GPIO to high or low,
 * provided it is configured as an output.
 *
 * @param self GPIO instance.
 * @param state `true` for high level, `false` for low level.
 */
void gpioSetState(gpio_t gpio, bool state);

/**
 * @brief Gets the logical state of a GPIO configured as input.
 *
 * This function reads the current state (high or low) of a GPIO configured as input.
 *
 * @param self GPIO instance.
 * @return `true` if the GPIO is at a high level, `false` if it is at a low level.
 */
bool gpioGetState(gpio_t gpio);

/* === End of documentation ==================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* GPIO_H */
