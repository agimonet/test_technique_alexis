/**
 * Copyright (c) 2019 eBikeLabs. All Rights Reserved.
 */

#pragma once

/**** Public API ****/

/**
 * @brief Called to initialize the pedaling state machine
 */

void pedaling_mgt_init(void);

/**
 * @brief Return current pedaling speed in RPM
 */
float get_pedaling_speed(void);

/**
 * @brief Return average current pedaling speed in RPM
 */
float get_average_pedaling_speed(void);

/**
 * @brief Callback when a magnet passes in front of the pedaling sensor
 */
void new_magnet_cb(void);
