/**
 * VUT FIT IMP project - heart rate measurement.
 *
 * @brief LED display implementation.
 * @author Dominik Harmim <xharmi00@stud.fit.vutbr.cz>
 */


#include <stdio.h>

#include "display.h"
#include "pin_mux.h"
#include "fsl_gpio.h"


/**
 * Writes value to the pin DISP_C1.
 */
#define SET_C1(_val) \
	GPIO_WritePinOutput( \
		BOARD_INITPINS_DISP_C1_GPIO, \
		BOARD_INITPINS_DISP_C1_PIN, \
		(uint8_t) (_val) \
	)

/**
 * Writes value to the pin DISP_C2.
 */
#define SET_C2(_val) \
	GPIO_WritePinOutput( \
		BOARD_INITPINS_DISP_C2_GPIO, \
		BOARD_INITPINS_DISP_C2_PIN, \
		(uint8_t) (_val) \
	)

/**
 * Writes value to the pin DISP_C3.
 */
#define SET_C3(_val) \
	GPIO_WritePinOutput( \
		BOARD_INITPINS_DISP_C3_GPIO, \
		BOARD_INITPINS_DISP_C3_PIN, \
		(uint8_t) (_val) \
	)

/**
 * Writes value to the pin DISP_C4.
 */
#define SET_C4(_val) \
	GPIO_WritePinOutput( \
		BOARD_INITPINS_DISP_C4_GPIO, \
		BOARD_INITPINS_DISP_C4_PIN, \
		(uint8_t) (_val) \
	)


/**
 * Displays digit 1 on the LED display.
 */
#define DISP_DIGIT_1() SET_C1(0)

/**
 * Displays digit 2 on the LED display.
 */
#define DISP_DIGIT_2() SET_C2(0)

/**
 * Displays digit 3 on the LED display.
 */
#define DISP_DIGIT_3() SET_C3(0)

/**
 * Displays digit 4 on the LED display.
 */
#define DISP_DIGIT_4() SET_C4(0)


/**
 * Writes value to the pin DISP_A.
 */
#define SET_SEG_A(_val) \
	GPIO_WritePinOutput( \
		BOARD_INITPINS_DISP_A_GPIO, \
		BOARD_INITPINS_DISP_A_PIN, \
		(uint8_t) (_val) \
	)

/**
 * Writes value to the pin DISP_B.
 */
#define SET_SEG_B(_val) \
	GPIO_WritePinOutput( \
		BOARD_INITPINS_DISP_B_GPIO, \
		BOARD_INITPINS_DISP_B_PIN, \
		(uint8_t) (_val) \
	)

/**
 * Writes value to the pin DISP_C.
 */
#define SET_SEG_C(_val) \
	GPIO_WritePinOutput( \
		BOARD_INITPINS_DISP_C_GPIO, \
		BOARD_INITPINS_DISP_C_PIN, \
		(uint8_t) (_val) \
	)

/**
 * Writes value to the pin DISP_D.
 */
#define SET_SEG_D(_val) \
	GPIO_WritePinOutput( \
		BOARD_INITPINS_DISP_D_GPIO, \
		BOARD_INITPINS_DISP_D_PIN, \
		(uint8_t) (_val) \
	)

/**
 * Writes value to the pin DISP_E.
 */
#define SET_SEG_E(_val) \
	GPIO_WritePinOutput( \
		BOARD_INITPINS_DISP_E_GPIO, \
		BOARD_INITPINS_DISP_E_PIN, \
		(uint8_t) (_val) \
	)

/**
 * Writes value to the pin DISP_F.
 */
#define SET_SEG_F(_val) \
	GPIO_WritePinOutput( \
		BOARD_INITPINS_DISP_F_GPIO, \
		BOARD_INITPINS_DISP_F_PIN, \
		(uint8_t) (_val) \
	)

/**
 * Writes value to the pin DISP_G.
 */
#define SET_SEG_G(_val) \
	GPIO_WritePinOutput( \
		BOARD_INITPINS_DISP_G_GPIO, \
		BOARD_INITPINS_DISP_G_PIN, \
		(uint8_t) (_val) \
	)


/**
 * Unsets all digits and all its segments.
 */
#define UNSET_ALL_DIGITS() \
	SET_C1(1), SET_C2(1), SET_C3(1), SET_C4(1), SET_SEG_A(0), SET_SEG_B(0), \
	SET_SEG_C(0), SET_SEG_D(0), SET_SEG_E(0), SET_SEG_F(0), SET_SEG_G(0)


/**
 * Displays digit 0 on the LED display.
 */
#define SET_DIGIT_0() \
	SET_SEG_A(1), SET_SEG_B(1), SET_SEG_C(1), SET_SEG_D(1), SET_SEG_E(1), \
	SET_SEG_F(1)

/**
 * Displays digit 1 on the LED display.
 */
#define SET_DIGIT_1() SET_SEG_B(1), SET_SEG_C(1)

/**
 * Displays digit 2 on the LED display.
 */
#define SET_DIGIT_2() \
	SET_SEG_A(1), SET_SEG_B(1), SET_SEG_D(1), SET_SEG_E(1), SET_SEG_G(1)

/**
 * Displays digit 3 on the LED display.
 */
#define SET_DIGIT_3() \
	SET_SEG_A(1), SET_SEG_B(1), SET_SEG_C(1), SET_SEG_D(1), SET_SEG_G(1)

/**
 * Displays digit 4 on the LED display.
 */
#define SET_DIGIT_4() SET_SEG_B(1), SET_SEG_C(1), SET_SEG_F(1), SET_SEG_G(1)

/**
 * Displays digit 5 on the LED display.
 */
#define SET_DIGIT_5() \
	SET_SEG_A(1), SET_SEG_C(1), SET_SEG_D(1), SET_SEG_F(1), SET_SEG_G(1)

/**
 * Displays digit 6 on the LED display.
 */
#define SET_DIGIT_6() \
	SET_SEG_A(1), SET_SEG_C(1), SET_SEG_D(1), SET_SEG_E(1), SET_SEG_F(1), \
	SET_SEG_G(1)

/**
 * Displays digit 7 on the LED display.
 */
#define SET_DIGIT_7() SET_SEG_A(1), SET_SEG_B(1), SET_SEG_C(1)

/**
 * Displays digit 8 on the LED display.
 */
#define SET_DIGIT_8() \
	SET_SEG_A(1), SET_SEG_B(1), SET_SEG_C(1), SET_SEG_D(1), SET_SEG_E(1), \
	SET_SEG_F(1), SET_SEG_G(1)

/**
 * Displays digit 9 on the LED display.
 */
#define SET_DIGIT_9() \
	SET_SEG_A(1), SET_SEG_B(1), SET_SEG_C(1), SET_SEG_D(1), SET_SEG_F(1), \
	SET_SEG_G(1)

/**
 * Size of the number_str array.
 * 5 because there is 4 digits characters and '\0' character.
 */
#define NUMBER_STR_SIZE 5


/**
 * Number to be displayed on the LED display, in string format.
 */
static char number_str[NUMBER_STR_SIZE];


void display_display_next_number(void)
{
	static size_t number_index = NUMBER_STR_SIZE - 2;

	if (++number_index == NUMBER_STR_SIZE - 1)
	{
		number_index = 0;
	}

	UNSET_ALL_DIGITS();

	switch (number_index)
	{
		case 0:
			DISP_DIGIT_1();
			break;

		case 1:
			DISP_DIGIT_2();
			break;

		case 2:
			DISP_DIGIT_3();
			break;

		case 3:
			DISP_DIGIT_4();
			break;

		default:
			return;
	}

	switch (number_str[number_index])
	{
		case '0':
			SET_DIGIT_0();
			break;

		case '1':
			SET_DIGIT_1();
			break;

		case '2':
			SET_DIGIT_2();
			break;

		case '3':
			SET_DIGIT_3();
			break;

		case '4':
			SET_DIGIT_4();
			break;

		case '5':
			SET_DIGIT_5();
			break;

		case '6':
			SET_DIGIT_6();
			break;

		case '7':
			SET_DIGIT_7();
			break;

		case '8':
			SET_DIGIT_8();
			break;

		case '9':
			SET_DIGIT_9();
			break;

		default:
			return;
	}
}


void display_set_number(const unsigned int number)
{
	sprintf(number_str, "% *u", NUMBER_STR_SIZE - 1, number);
}
