/**
 * Copyright (c) 2019 eBikeLabs. All Rights Reserved.
 * @defgroup NameFile Name file
 * @brief Describe briefly the purpose of the group of modules
 * @{
 * @file
 * @brief Describe briefly the purpose of the module
 */

#pragma once

#include <stdbool.h>
#include <stdint.h>

/**** Typedefs ****/

/**
 * @brief Describe the structure file_template_t
 */
typedef struct
{
    struct file_template_handle_init
    {
        float period;     /// Describe the attribute; give the unit in parenthesis if necessary (s)
        bool initialized; /// Becomes true after the module is initialized
    } _init;

    float _frequency; /// This is a private attribute (Hz)

    /// Outputs
    float result; /// This is a public attribute (no unit)
} file_template_t;

/**** Public API ****/

/**
 * @brief Describe the function
 * @note Public functions start with the name of the module
 */
void file_template_init(
    file_template_t *self, /// We refer to the module structures as self
    float period           /// Describe the parameter; give the unit in parenthesis if necessary (s)
);

/**
 * @brief Describe the function
 * @note Public functions start with the name of the module
 */
void file_template_update(
    file_template_t *self, /// We refer to the module structures as self
    float frequency        /// Describe the parameter; give the unit in parenthesis if necessary (s)
);
