/**
 * VUT FIT IMP project - heart rate measurement.
 *
 * original
 *
 * @brief LED display interface.
 * @author Dominik Harmim (xharmi00) <xharmi00@stud.fit.vutbr.cz>
 * @date 30.12.2018
 */


#ifndef DISPLAY_H
#define DISPLAY_H


#include <stdint.h>


/**
 * Display refresh period in us.
 * Frequency 60 Hz, 1 / 60 = 0.0166666 s = 16666 us,
 * for 4 digits = 16666 / 4 = 4166.
 */
static const uint64_t DISPLAY_REFRESH_IN_USEC = 4166;


/**
 * Displays next number on the LED display.
 */
void display_display_next_number(void);

/**
 * Sets number to be displayed on the LED display.
 *
 * @param number Number to be displayed on the LED display.
 */
void display_set_number(const unsigned int number);


#endif //DISPLAY_H
