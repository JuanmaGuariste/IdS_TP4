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
 * @file gpio.c
 * @brief Implementation of the GPIO module functions.
 *
 * This file contains the definitions and implementations of the functions
 * for managing GPIO objects, including initialization, setting direction,
 * and controlling the state of GPIO pins.
 *
 * @author Juan Manuel Guariste
 * @date 20/11/2024
 */

/* === Headers files inclusions =============================================================== */

#include "gpio.h"
#include "hal.h"
#include <string.h>
#include <stddef.h>
#include <stdlib.h>

/* === Macros definitions ====================================================================== */

#ifndef GPIO_MAX_INSTANCES
#define GPIO_MAX_INSTANCES 10
#endif

#define USE_DYNAMIC_MEM

/* === Private data type declarations ========================================================== */

/* === Private variable declarations =========================================================== */

struct gpio_s {
    uint8_t port;
    uint8_t bit;
    bool output;
#ifndef USE_DYNAMIC_MEM
    bool used;
#endif
};

/* === Private function declarations =========================================================== */

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

#ifndef USE_DYNAMIC_MEM

/**
 * @brief Private function that creates a new GPIO instance using static memory.
 *
 * This function allocates a new GPIO object from a pool of statically defined instances.
 * It searches for an available instance in the pool and marks it as "used".
 *
 * @return Pointer to a `gpio_s` structure. Returns `NULL` if no instances are available.
 */
static gpio_t allocateInstance() {
    static struct gpio_s instances[GPIO_MAX_INSTANCES] = {0};

    gpio_t result = NULL;
    for (int index = 0; index < GPIO_MAX_INSTANCES; index++) {
        if (!instances[index].used) {
            result = &instances[index];
            result->used = true;
            break;
        }
    }
    return result;
}
#endif

/* === Public function implementation ========================================================== */

gpio_t gpioCreate(uint8_t port, uint8_t bit) {
#ifdef USE_DYNAMIC_MEM
    gpio_t self = malloc(sizeof(struct gpio_s));
#else
    gpio_t self = allocateInstance();
#endif
    if (self) {
        self->port = port;
        self->bit = bit;
        self->output = false;
    }
    return self;
}

void gpioSetDirection(gpio_t self, bool io) {
    self->output = io;
    hal_gpio_set_direction(self->port, self->bit, self->output);
}

void gpioSetState(gpio_t self, bool state) {
    if (self->output) {
        hal_gpio_set_output(self->port, self->bit, state);
    }
}

bool gpioGetState(gpio_t self) {
    return hal_gpio_get_input(self->port, self->bit);
}

/* === End of documentation ==================================================================== */