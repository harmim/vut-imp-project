/**
 * VUT FIT IMP project - heart rate measurement.
 *
 * @brief Main file, application entry point.
 * @author Dominik Harmim <xharmi00@stud.fit.vutbr.cz>
 */


#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "MK60D10.h"
#include "pin_mux.h"
#include "fsl_pit.h"
#include "fsl_clock.h"
#include "fsl_common.h"
#include "fsl_adc16.h"
#include "fsl_lptmr.h"
#include "display.h"
#include "sensor.h"


/**
 * MCGIRCLK clock frequency in Hz.
 */
static uint32_t mcg_clock_freq;


/**
 * Initializes Low Power Timer Driver (LPTMR).
 * LPTMR0 is used in sensor measurement.
 */
static void init_LPTMR(void)
{
	// enable MCGIRCLK
	CLOCK_SetInternalRefClkConfig(kMCG_IrclkEnable, kMCG_IrcSlow, 0);
	mcg_clock_freq = CLOCK_GetFreq(kCLOCK_McgInternalRefClk);
	CLOCK_EnableClock(kCLOCK_Lptmr0);

	lptmr_config_t config;
	LPTMR_GetDefaultConfig(&config);
	config.prescalerClockSource = kLPTMR_PrescalerClock_0; // set MCGIRCLK

	LPTMR_Init(LPTMR0, &config);

	// Clock source is MCGIRCLK which is 16b, 0xFFFF is maximum.
	static const uint32_t LPTMR0_period = 0xFFFF;
	LPTMR_SetTimerPeriod(LPTMR0, LPTMR0_period);
}


/**
 * PIT0 interrupt handler routine.
 * Displays next number on the LED display.
 */
void PIT0_IRQHandler(void)
{
	display_display_next_number();
	PIT_ClearStatusFlags(PIT, kPIT_Chnl_0, kPIT_TimerFlag);
}


/**
 * Initialization of Periodic Interrupt Timer Driver (PIT).
 * Sets timer for PIT0 which displays LCD display.
 */
static void init_PIT(void)
{
	CLOCK_EnableClock(kCLOCK_Pit0);

	pit_config_t config;
	PIT_GetDefaultConfig(&config);
	PIT_Init(PIT, &config);

	// set PIT0_IRQHandler as interrupt handler of PIT0, channel 0
	EnableIRQ(PIT0_IRQn);
	PIT_EnableInterrupts(PIT, kPIT_Chnl_0, kPIT_TimerInterruptEnable);

	const uint64_t PIT0_ch0_period =
		USEC_TO_COUNT(DISPLAY_REFRESH_IN_USEC, CLOCK_GetFreq(kCLOCK_BusClk));
	PIT_SetTimerPeriod(PIT, kPIT_Chnl_0, (uint32_t) PIT0_ch0_period);

	PIT_StartTimer(PIT, kPIT_Chnl_0);
}


/**
 * Initialization of Analog-to-Digital Converter Driver (ADC).
 * Sets ADC0 on channel 0 which reads signal from sensor.
 */
static void init_ADC16(void)
{
	CLOCK_EnableClock(kCLOCK_Adc0);

	adc16_config_t config;
	ADC16_GetDefaultConfig(&config);
	config.enableContinuousConversion = true;
#if defined(FSL_FEATURE_ADC16_MAX_RESOLUTION) \
	&& FSL_FEATURE_ADC16_MAX_RESOLUTION >= 16
	config.resolution = kADC16_Resolution16Bit;
#endif

	ADC16_Init(ADC0, &config);
	ADC16_EnableHardwareTrigger(ADC0, false);
	ADC16_SetHardwareAverage(ADC0, kADC16_HardwareAverageCount32);

#if defined(FSL_FEATURE_ADC16_HAS_CALIBRATION) \
	&& FSL_FEATURE_ADC16_HAS_CALIBRATION
	ADC16_DoAutoCalibration(ADC0);
#endif

	adc16_channel_config_t channel_config = {
		.channelNumber = 0,
		.enableInterruptOnConversionCompleted = false,
	};
#if defined(FSL_FEATURE_ADC16_HAS_DIFF_MODE) && FSL_FEATURE_ADC16_HAS_DIFF_MODE
	channel_config.enableDifferentialConversion = false;
#endif
	ADC16_SetChannelConfig(ADC0, 0, &channel_config);
}


/**
 * Initialization.
 */
static void init(void)
{
	BOARD_InitBootPins();
	init_LPTMR();
	init_PIT();
	init_ADC16();
}


/**
 * Main function, application entry point.
 *
 * @return EXIT_SUCCESS.
 */
int main(void)
{
	init();

	display_set_number(0);

	while (true)
	{
		display_set_number(sensor_get_heart_rate(mcg_clock_freq));
	}

	return EXIT_SUCCESS;
}
