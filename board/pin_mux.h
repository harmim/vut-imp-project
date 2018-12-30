/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_

/*!
 * @addtogroup pin_mux
 * @{
 */

/***********************************************************************************************************************
 * API
 **********************************************************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Calls initialization functions.
 *
 */
void BOARD_InitBootPins(void);

/*! @name PORTD8 (coord C9), DISP_C1
  @{ */
#define BOARD_INITPINS_DISP_C1_GPIO GPIOD /*!<@brief GPIO device name: GPIOD */
#define BOARD_INITPINS_DISP_C1_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_INITPINS_DISP_C1_PIN 8U     /*!<@brief PORTD pin index: 8 */
                                          /* @} */

/*! @name PORTD9 (coord B9), DISP_C4
  @{ */
#define BOARD_INITPINS_DISP_C4_GPIO GPIOD /*!<@brief GPIO device name: GPIOD */
#define BOARD_INITPINS_DISP_C4_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_INITPINS_DISP_C4_PIN 9U     /*!<@brief PORTD pin index: 9 */
                                          /* @} */

/*! @name PORTD12 (coord B1), DISP_C3
  @{ */
#define BOARD_INITPINS_DISP_C3_GPIO GPIOD /*!<@brief GPIO device name: GPIOD */
#define BOARD_INITPINS_DISP_C3_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_INITPINS_DISP_C3_PIN 12U    /*!<@brief PORTD pin index: 12 */
                                          /* @} */

/*! @name PORTD13 (coord C3), DISP_C2
  @{ */
#define BOARD_INITPINS_DISP_C2_GPIO GPIOD /*!<@brief GPIO device name: GPIOD */
#define BOARD_INITPINS_DISP_C2_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_INITPINS_DISP_C2_PIN 13U    /*!<@brief PORTD pin index: 13 */
                                          /* @} */

/*! @name PORTA10 (coord M9), DISP_D
  @{ */
#define BOARD_INITPINS_DISP_D_GPIO GPIOA /*!<@brief GPIO device name: GPIOA */
#define BOARD_INITPINS_DISP_D_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_INITPINS_DISP_D_PIN 10U    /*!<@brief PORTA pin index: 10 */
                                         /* @} */

/*! @name PORTA6 (coord J7), DISP_E
  @{ */
#define BOARD_INITPINS_DISP_E_GPIO GPIOA /*!<@brief GPIO device name: GPIOA */
#define BOARD_INITPINS_DISP_E_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_INITPINS_DISP_E_PIN 6U     /*!<@brief PORTA pin index: 6 */
                                         /* @} */

/*! @name PORTA11 (coord L9), DISP_A
  @{ */
#define BOARD_INITPINS_DISP_A_GPIO GPIOA /*!<@brief GPIO device name: GPIOA */
#define BOARD_INITPINS_DISP_A_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_INITPINS_DISP_A_PIN 11U    /*!<@brief PORTA pin index: 11 */
                                         /* @} */

/*! @name PORTA7 (coord J8), DISP_F
  @{ */
#define BOARD_INITPINS_DISP_F_GPIO GPIOA /*!<@brief GPIO device name: GPIOA */
#define BOARD_INITPINS_DISP_F_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_INITPINS_DISP_F_PIN 7U     /*!<@brief PORTA pin index: 7 */
                                         /* @} */

/*! @name PORTA9 (coord L8), DISP_B
  @{ */
#define BOARD_INITPINS_DISP_B_GPIO GPIOA /*!<@brief GPIO device name: GPIOA */
#define BOARD_INITPINS_DISP_B_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_INITPINS_DISP_B_PIN 9U     /*!<@brief PORTA pin index: 9 */
                                         /* @} */

/*! @name PORTD14 (coord C2), DISP_C
  @{ */
#define BOARD_INITPINS_DISP_C_GPIO GPIOD /*!<@brief GPIO device name: GPIOD */
#define BOARD_INITPINS_DISP_C_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_INITPINS_DISP_C_PIN 14U    /*!<@brief PORTD pin index: 14 */
                                         /* @} */

/*! @name PORTD15 (coord C1), DISP_G
  @{ */
#define BOARD_INITPINS_DISP_G_GPIO GPIOD /*!<@brief GPIO device name: GPIOD */
#define BOARD_INITPINS_DISP_G_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_INITPINS_DISP_G_PIN 15U    /*!<@brief PORTD pin index: 15 */
                                         /* @} */

/*! @name ADC0_DP0 (coord L1), SENSOR
  @{ */
/* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPins(void);

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* _PIN_MUX_H_ */

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/