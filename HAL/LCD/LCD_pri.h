/*
 * LCD_pri.h
 *
 *  Created on: Aug 22, 2022
 *      Author: hp
 */

#ifndef HAL_LCD_LCD_PRI_H_
#define HAL_LCD_LCD_PRI_H_

#define FOUR_BIT_MODE 1
#define EIGHT_BIT_MODE 0


/* Case of 4bit mode: HIGHEST_NIPPLE or LOWES_NIPPLE
 * Case of 8bit mode: N/A
 * */
#define HIGHEST_NIPPLE 1
#define LOWEST_NIPPLE  0

/*Available commands*/

#define CMD_CLR 1
#define CMD_RET_HOME 2


/*Increment cursor when writing to the LCD*/
#define CMD_ENTRY_MODE_INC  6

/*Decreament cursor when writing to the LCD*/
#define CMD_ENTRY_MODE_DEC  4

/*Display on, cursor off*/
#define CMD_DISPLAY_ON      12

/*Display off*/
#define CMD_DISPLAY_OFF     8

/*Eight bit mode, 2 lines, 5x7 dots*/
#define CMD_8BIT_MODE  56

/*Four bit mode, 2 lines, 5x7 dots*/
#define CMD_4BIT_MODE   40

/*You add the position (address) to this value*/
#define CMD_SET_CURSOR_POSITION 128

#define CMD_SHIFT_DISP_RIGHT 28

#define CMD_SHIFT_DISP_LEFT  24

#define CMD_CGRAM_ADDRESS    64

/*send a command to the LCD*/
static void LCD_vInstruction(u8 A_u8Ins_code);

/*send data to the LCD*/
static void LCD_vSendData(u8 A_u8Ch);


/*convert float to string*/
static void floatToString(f32 A_f32Num, u8 *A_u8Arr, u8 A_u8AfterDecimal);

/*convert integer to char*/
static u8 LCD_vConvIntToChar(u32 num);

/*Available patterns*/
static  u8 G_u8Pattern0[] = {0x04, 0x0E, 0x0E, 0x0E, 0x1F, 0x00, 0x04, 0x00};/*Space ship*/
static  u8 G_u8Pattern1[] = {0x00, 0x00, 0xA, 0x15, 0x11, 0xA, 0x04, 0x00};/*heart*/
static  u8 G_u8Pattern2[] = {0x0E,0x0E,0x04,0x04,0x1F,0x04,0x0A,0x0A};/*a man*/

static void LCD_vCreateCustomPattern(u8 *A_u8Pattern, u8 A_u8Loc);


#endif /* HAL_LCD_LCD_PRI_H_ */
