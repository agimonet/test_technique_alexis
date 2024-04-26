/**
 * Copyright (c) 2019 eBikeLabs. All Rights Reserved.
 */

#include "file_template.h"
#include <stddef.h>

/**** Defines ****/

#define CONSTANT_MULTIPLIER 2.f /// Describe the constant; give the unit in parenthesis if necessary (no unit)

/**** Private functions prototypes ****/

/**
 * @brief Describe the function
 * @note Private functions start with an underscore
 */
static float _multiply(float a, float b);

/**** Public API ****/

void file_template_init(
    file_template_t *self,
    float period)
{
    self->_init.period = period;
    self->_init.initialized = true;
}

void file_template_update(
    file_template_t *self,
    float frequency)
{
    self->_frequency = frequency;
    self->result = _multiply(self->_frequency, self->_init.period);
}

/**** Private functions ****/

static float _multiply(float a, float b)
{
    return CONSTANT_MULTIPLIER * a * b;
}
