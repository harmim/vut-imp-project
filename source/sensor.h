/**
 * VUT FIT IMP project - heart rate measurement.
 *
 * original
 *
 * @brief Heart rate sensor interface.
 * @author Dominik Harmim (xharmi00) <xharmi00@stud.fit.vutbr.cz>
 * @date 30.12.2018
 */


#ifndef SENSOR_H
#define SENSOR_H


#include <stdint.h>


/**
 * Measures heart rate per minute by sensor.
 *
 * @param mcg_clock_freq MCGIRCLK clock frequency in Hz.
 * @return Heart rate per minute measured by sensor.
 */
const unsigned int sensor_get_heart_rate(const uint32_t mcg_clock_freq);


#endif //SENSOR_H
