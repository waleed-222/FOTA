/*
 * LCD_cfg.h
 *
 *  Created on: Aug 22, 2022
 *      Author: hp
 */

#ifndef HAL_LCD_LCD_CFG_H_
#define HAL_LCD_LCD_CFG_H_

/*LCD_MODE:
 *
FOUR_BIT_MODE
EIGHT_BIT_MODE
*/

#define LCD_MODE FOUR_BIT_MODE

#define DATA_PORT PORTB_ID

#define RS_PORT   PORTA_ID
#define RS_PIN    PIN0_ID

#define RW_PORT  PORTA_ID
#define RW_PIN   PIN1_ID


#define EN_PORT   PORTA_ID
#define EN_PIN   PIN2_ID

/*Case of 4bit mode this is used*/
#define LCD_D4_ID PIN4_ID
#define LCD_D5_ID PIN5_ID
#define LCD_D6_ID PIN6_ID
#define LCD_D7_ID PIN7_ID


#endif /* HAL_LCD_LCD_CFG_H_ */
