/*
 * LCD_int.h
 *
 *  Created on: Aug 22, 2022
 *      Author: hp
 */

#ifndef HAL_LCD_LCD_INT_H_
#define HAL_LCD_LCD_INT_H_
/*the Rows and Cols we have*/
 typedef enum
 {
ROW_ID0,
 ROW_ID1
 }Rows;
 typedef enum
 {
 COL_ID0  ,
 COL_ID1  ,
 COL_ID2  ,
 COL_ID3  ,
 COL_ID4  ,
 COL_ID5  ,
 COL_ID6  ,
 COL_ID7  ,
 COL_ID8  ,
 COL_ID9  ,
 COL_ID10 ,
 COL_ID11 ,
 COL_ID12 ,
 COL_ID13 ,
 COL_ID14 ,
 COL_ID15 ,
 }Cols;

 typedef enum {
 	SHIFT_LEFT,
 	SHIFT_RIGHT
 }Shift;

 typedef enum {
 	PATTERN0_ID,
 	PATTERN1_ID,
 	PATTERN2_ID,
 	PATTERN3_ID,
 	PATTERN4_ID,
 	PATTERN5_ID,
 	PATTERN6_ID,
 	PATTERN7_ID
 }Patterns;

#define NUMBER_OF_COLS 16
#define NUMBER_OF_ROWS 2


#define DISPLAY_DATA 1
#define INS_CODE 0
#define READ 1
#define WRITE 0



void LCD_vInit();
void LCD_vDispChar(u8 A_u8Ch);
void LCD_vDispStr(u8* A_u8Str);
void LCD_vDispNum(u32 A_u8Num);
void LCD_vCLR();
void LCD_vSetPos(u8 A_u8Row,u8 A_u8Col);
void LCD_vDispFloat(f32 A_f32Num);
void LCD_vReturnHome();
void LCD_vShiftDisp(u8 A_u8ShiftDir);
void LCD_vShiftCursor(u8 A_u8ShiftDir);
void LCD_vTurnOn();
void LCD_vTurnOff();
void LCD_vDispCustomChar(u8 A_u8PatternId, u8 A_u8Row, u8 A_u8Col);











#endif /* HAL_LCD_LCD_INT_H_ */
