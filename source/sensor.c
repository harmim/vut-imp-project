/**
 * VUT FIT IMP project - heart rate measurement.
 *
 * @brief Heart rate sensor implementation.
 * @author Dominik Harmim <xharmi00@stud.fit.vutbr.cz>
 */


#include <stdbool.h>

#include "sensor.h"
#include "MK60D10.h"
#include "fsl_common.h"
#include "fsl_lptmr.h"
#include "fsl_adc16.h"


/**
 * Size of array of heart rates.
 */
#define HEART_RATES_SIZE 5

/**
 * Size of array of heart rates averages.
 */
#define HEART_RATES_AVG_SIZE 30


/**
 * Reads signal from heart rate sensor.
 *
 * @return Signal from heart rate sensor.
 */
static uint32_t read_signal(void)
{
	bool wait = true;
	while (wait)
	{
		const uint32_t status_flags = ADC16_GetChannelStatusFlags(ADC0, 0);
		wait = !(status_flags & kADC16_ChannelConversionDoneFlag);
	}

	return ADC16_GetChannelConversionValue(ADC0, 0);
}


/**
 * Low-pass filter.
 *
 * @param x Input signal.
 * @param time_interval Time interval between measurements in us.
 * @return Filtered signal.
 */
static float low_pass_filter(const float x, const float time_interval)
{
	// 1 / (2 * PI * f), f = 3 Hz
	// time is in us: 1 / (2 * PI * (3 / 1000000)) = 53051.6477
	static const float time_constant = 53051.6477;
	static float y_prev = 0.0;
	static bool x0 = true;
	float y, a;

	a = time_interval / (time_constant + time_interval);

	if (x0)
	{
		x0 = false;
		y = x * a;

		y_prev = y;

		return y;
	}

	y = a * x + (1.0 - a) * y_prev;

	y_prev = y;

	return y;
}


/**
 * High-pass filter.
 *
 * @param x Input signal.
 * @param time_interval Time interval between measurements in us.
 * @return Filtered signal.
 */
static float high_pass_filter(const float x, const float time_interval)
{
	// 1 / (2 * PI * f), f = 1 Hz
	// time is in us: 1 / (2 * PI * (1 / 1000000)) = 159154.9431
	static const float time_constant = 159154.9431;
	static float x_prev = 0.0, y_prev = 0.0;
	static bool x0 = true;
	float y, a;

	if (x0)
	{
		x0 = false;
		y = x;

		x_prev = x;
		y_prev = y;

		return y;
	}

	a = time_constant / (time_constant + time_interval);
	y = a * y_prev + a * (x - x_prev);

	x_prev = x;
	y_prev = y;

	return y;
}


/**
 * Pushes float value into end of the array and shifts the rest of the
 * array left.
 *
 * @param array The array where the value will be pushed.
 * @param size Size of the array.
 * @param value Value to be pushed.
 */
void f_array_push(float *const array, const size_t size, const float value)
{
	for (size_t i = 0; i < size; i++)
	{
		if (i == size - 1)
		{
			array[i] = value;
		}
		else
		{
			array[i] = array[i + 1];
		}
	}
}


/**
 * Calculates average value of non-zero array values.
 *
 * @param array The array for calculating the average.
 * @param size Size of the array.
 * @return Average of non-zero values in the input array.
 */
float f_array_average(const float *const array, const size_t size)
{
	float sum = 0.0;
	size_t count = 0;

	for (size_t i = 0; i < size; i++)
	{
		if (array[i] != 0.0)
		{
			sum += array[i];
			count++;
		}
	}

	return sum / count;
}


/**
 * Sets all values of the input array to zero.
 *
 * @param array The array which will be cleaned.
 * @param size Size of the array.
 */
void f_array_clean(float *const array, const size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		array[i] = 0.0;
	}
}


const unsigned int sensor_get_heart_rate(const uint32_t mcg_clock_freq)
{
	// Static declarations. These variables depends on previous measurements.

	static unsigned int heart_rate = 0;

	static float
		heart_rates[HEART_RATES_SIZE] = {0.0},
		heart_rates_avg[HEART_RATES_AVG_SIZE] = {0.0};
	static size_t heart_rate_index = 0; // index to heart_rates array

	static bool measurement_started = false;
	static uint64_t measurement_time = 0;

	static float signal_maximum = 0.0;
	static bool signal_riseing = false;

	const uint32_t signal = read_signal();
	// time interval between measurements in us
	const uint64_t time_interval = COUNT_TO_USEC(
		(uint64_t) LPTMR_GetCurrentTimerCount(LPTMR0),
		mcg_clock_freq
	);
	measurement_time += time_interval;

	// reset LPTMR timer
	LPTMR_StopTimer(LPTMR0);
	LPTMR_StartTimer(LPTMR0);

	float y = (float) signal; // filtered signal
	y = low_pass_filter(y, (float) time_interval);
	y = high_pass_filter(y, (float) time_interval);

	bool beat = false;
	if (signal_riseing)
	{
		// ignore signal value below no_measurement_limit
		static const float no_measurement_limit = 8.0;
		if (y > no_measurement_limit && y > signal_maximum)
		{
			signal_maximum = y;
		}
		else if (signal_maximum != 0.0)
		{
			signal_riseing = false;
			beat = true;
		}
	}
	else if (y <= 0.0)
	{
		signal_maximum = 0.0;
		signal_riseing = true;
	}

	if (beat)
	{
		if (measurement_started && measurement_time != 0)
		{
			static const float rate_calabration_constant = 35.0;
			const float rate =
				60.0
				/ ((float) measurement_time / 1000000.0)
				- rate_calabration_constant;

			// ignore rate, rate_down_limit > rate > rate_up_limit
			static const float
				rate_down_limit = 30.0,
				rate_up_limit = 210.0;
			if (rate > rate_down_limit && rate < rate_up_limit)
			{
				// push rate to heart_rates array
				f_array_push(heart_rates, HEART_RATES_SIZE, rate);
				heart_rate_index++;
			}
		}

		measurement_time = 0;
		measurement_started = true;
	}

	// reset measurement after 2.5 s without beep
	static const uint64_t max_time_between_measurements = 2500000;
	if (measurement_time > max_time_between_measurements)
	{
		measurement_started = false;
		heart_rate_index = 0;
		heart_rate = 0;
		f_array_clean(heart_rates, HEART_RATES_SIZE);
		f_array_clean(heart_rates_avg, HEART_RATES_AVG_SIZE);
	}

	// If heart_rates is full, return average heart rate.
	if (heart_rate_index == HEART_RATES_SIZE)
	{
		heart_rate_index = 0;
		float heart_rate_avg = f_array_average(heart_rates, HEART_RATES_SIZE);
		f_array_clean(heart_rates, HEART_RATES_SIZE);
		f_array_push(heart_rates_avg, HEART_RATES_AVG_SIZE, heart_rate_avg);

		heart_rate = (unsigned int) f_array_average(
			heart_rates_avg, HEART_RATES_AVG_SIZE
		);
	}

	return heart_rate;
}
