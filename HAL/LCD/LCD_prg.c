/*
 * LCD_prg.c
 *
 *  Created on: Aug 22, 2022
 *      Author: hp
 */
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO/DIO_int.h"
#include "LCD_pri.h"
#include "LCD_cfg.h"
#include "LCD_int.h"
#include<util/delay.h>

void LCD_vInit()
{
	_delay_ms(30); /*Specified in the data sheet to make a small delay before init*/

#if(LCD_MODE == EIGHT_BIT_MODE)
	/*Initialize the ports*/
	DIO_vPortDir(DATA_PORT, DIR_OUTPUT);
	DIO_vPinDir(EN_PORT, EN_PIN, DIR_OUTPUT);
	DIO_vPinDir(RW_PORT, RW_PIN, DIR_OUTPUT);
	DIO_vPinDir(RS_PORT, RS_PIN, DIR_OUTPUT);

	LCD_vInstruction(CMD_8BIT_MODE);/*Command to set 8bit mode, 2x16 lines, 5x7dots*/
	_delay_us(39);
	LCD_vInstruction(CMD_DISPLAY_ON);/*Command to set the display ON*/
	_delay_us(39);
	LCD_vInstruction(CMD_CLR);/*Command to clear display*/
	_delay_ms(1.53);
	LCD_vInstruction(CMD_ENTRY_MODE_INC);/*Command to increament cursor*/

#else /*4Bit mode*/
	DIO_vPinDir(EN_PORT, EN_PIN, DIR_OUTPUT);
	DIO_vPinDir(RW_PORT, RW_PIN, DIR_OUTPUT);
	DIO_vPinDir(RS_PORT, RS_PIN, DIR_OUTPUT);

	DIO_vPinDir(DATA_PORT, LCD_D4_ID, DIR_OUTPUT);
	DIO_vPinDir(DATA_PORT, LCD_D5_ID, DIR_OUTPUT);
	DIO_vPinDir(DATA_PORT, LCD_D6_ID, DIR_OUTPUT);
	DIO_vPinDir(DATA_PORT, LCD_D7_ID, DIR_OUTPUT);


	DIO_vSetPinVal(RS_PORT, RS_PIN, VAL_LOW);/*Choosing the instruction register*/
	DIO_vSetPinVal(RW_PORT, RW_PIN, VAL_LOW);/*Writing to the LCD*/
	DIO_vSetPinVal(EN_PORT, EN_PIN, VAL_HIGH);/*set the En high to make LCD read*/
	DIO_vSetPinVal(DATA_PORT, LCD_D4_ID, VAL_LOW);
	DIO_vSetPinVal(DATA_PORT, LCD_D5_ID, VAL_HIGH);
	DIO_vSetPinVal(DATA_PORT, LCD_D6_ID, VAL_LOW);
	DIO_vSetPinVal(DATA_PORT, LCD_D7_ID, VAL_LOW);
	DIO_vSetPinVal(EN_PORT,EN_PIN, VAL_LOW);/*set the En high to make LCD read*/

	LCD_vInstruction(CMD_4BIT_MODE);/*Command to set 4bit mode, 2x16 lines, 5x7dots*/
	_delay_us(39);
	LCD_vInstruction(CMD_DISPLAY_ON);/*Command to set the display ON*/
	_delay_us(39);
	LCD_vInstruction(CMD_CLR);/*Command to clear display*/
	_delay_ms(1.53);
	LCD_vInstruction(CMD_ENTRY_MODE_INC);/*Command to increament cursor*/
#endif

}

void LCD_vSendData(u8 A_u8Data)
{
	DIO_vSetPinVal(EN_PORT, EN_PIN, VAL_HIGH);/*set the En high to make LCD read*/
		DIO_vSetPinVal(RS_PORT, RS_PIN, VAL_HIGH);/*Choosing the data register*/
		DIO_vSetPinVal(RW_PORT, RW_PIN, VAL_LOW);/*Writing to the LCD*/
		#if(LCD_MODE == EIGHT_BIT_MODE)
			DIO_vSetPortVal(DATA_PORT, A_u8Data); /*write the data*/
			DIO_vSetPinVal(EN_PORT, EN_PIN, VAL_LOW);/*Falling edge to perform the instruction*/
			_delay_us(5);
		#else
			/*In 4Bit mode we send the higher nibble first then the lower nibble*/

			/*Sending the higher nibble*/
			DIO_vSetPinVal(DATA_PORT, LCD_D4_ID, GET_BIT(A_u8Data, PIN4_ID));
			DIO_vSetPinVal(DATA_PORT, LCD_D5_ID, GET_BIT(A_u8Data, PIN5_ID));
			DIO_vSetPinVal(DATA_PORT, LCD_D6_ID, GET_BIT(A_u8Data, PIN6_ID));
			DIO_vSetPinVal(DATA_PORT, LCD_D7_ID, GET_BIT(A_u8Data, PIN7_ID));
			DIO_vSetPinVal(EN_PORT, EN_PIN, VAL_LOW);/*Falling edge to perform the instruction*/


			/*Sending the lower nibble*/
			DIO_vSetPinVal(EN_PORT, EN_PIN, VAL_HIGH);/*set the En high to make LCD read*/
			DIO_vSetPinVal(DATA_PORT, LCD_D4_ID, GET_BIT(A_u8Data, PIN0_ID));
			DIO_vSetPinVal(DATA_PORT, LCD_D5_ID, GET_BIT(A_u8Data, PIN1_ID));
			DIO_vSetPinVal(DATA_PORT, LCD_D6_ID, GET_BIT(A_u8Data, PIN2_ID));
			DIO_vSetPinVal(DATA_PORT, LCD_D7_ID, GET_BIT(A_u8Data, PIN3_ID));
			DIO_vSetPinVal(EN_PORT, EN_PIN, VAL_LOW);/*Falling edge to perform the instruction*/

			_delay_us(10);
		#endif
}
void LCD_vDispChar(u8 A_u8Ch)
{
	LCD_vSendData(A_u8Ch);



}
void LCD_vDispStr(u8* A_u8Str)
{ u8 i=0;

		for(;A_u8Str[i]!='\0';i++)
		LCD_vDispChar(A_u8Str[i]);

}

void LCD_vDispNum(u32 A_u8Num)
{u8 arr[10],i=0;

	for(;A_u8Num>0;i++)
	{
		arr[i]=LCD_vConvIntToChar(A_u8Num%10);

		A_u8Num/=10;
	}

	for(;i>0;i--)
		LCD_vSendData(arr[i-1]);

}
void LCD_vCLR()
{
	LCD_vInstruction(CMD_CLR);
	_delay_ms(1.53);

}
void LCD_vSetPos(u8 A_u8Row,u8 A_u8Col)
{
	u8 L_u8FirstRow = 0x00, L_u8SecondRow = 0x40;
	switch(A_u8Row){
		case ROW_ID0: LCD_vInstruction(CMD_SET_CURSOR_POSITION + L_u8FirstRow + A_u8Col); break;
		case ROW_ID1: LCD_vInstruction(CMD_SET_CURSOR_POSITION + L_u8SecondRow + A_u8Col); break;

	}

}

void LCD_vInstruction(u8 A_u8Cmd)
{
	DIO_vSetPinVal(RS_PORT, RS_PIN, VAL_LOW);/*Choosing the instruction register*/
			DIO_vSetPinVal(RW_PORT, RW_PIN, VAL_LOW);/*Writing to the LCD*/
			DIO_vSetPinVal(EN_PORT, EN_PIN, VAL_HIGH);/*set the En high to make LCD read*/
	#if (LCD_MODE== EIGHT_BIT_MODE)
			DIO_vSetPortVal(DATA_PORT, A_u8Cmd); /*write the command*/
					DIO_vSetPinVal(EN_PORT, EN_PIN, VAL_LOW);/*Falling edge to perform the instruction*/
				#else /*Four bit mode*/
					/*In 4Bit mode we send the higher nibble first then the lower nibble*/

					/*Sending the higher nibble*/
					DIO_vSetPinVal(DATA_PORT, LCD_D4_ID, GET_BIT(A_u8Cmd, PIN4_ID));
					DIO_vSetPinVal(DATA_PORT, LCD_D5_ID, GET_BIT(A_u8Cmd, PIN5_ID));
					DIO_vSetPinVal(DATA_PORT, LCD_D6_ID, GET_BIT(A_u8Cmd, PIN6_ID));
					DIO_vSetPinVal(DATA_PORT, LCD_D7_ID, GET_BIT(A_u8Cmd, PIN7_ID));
					DIO_vSetPinVal(EN_PORT, EN_PIN, VAL_LOW);/*Falling edge to perform the instruction*/


					/*Sending the lower nibble*/
					DIO_vSetPinVal(EN_PORT,EN_PIN, VAL_HIGH);/*set the En high to make LCD read*/
					DIO_vSetPinVal(DATA_PORT, LCD_D4_ID, GET_BIT(A_u8Cmd, PIN0_ID));
					DIO_vSetPinVal(DATA_PORT, LCD_D5_ID, GET_BIT(A_u8Cmd, PIN1_ID));
					DIO_vSetPinVal(DATA_PORT, LCD_D6_ID, GET_BIT(A_u8Cmd, PIN2_ID));
					DIO_vSetPinVal(DATA_PORT, LCD_D7_ID, GET_BIT(A_u8Cmd, PIN3_ID));
					DIO_vSetPinVal(EN_PORT, EN_PIN, VAL_LOW);/*Falling edge to perform the instruction*/

				#endif

}

u8 LCD_vConvIntToChar(u32 A_u32Num)
{u8 temp;
	switch(A_u32Num)
	{
	case 0:temp='0';break;
	case 1:temp='1';break;
	case 2:temp='2';break;
	case 3:temp='3';break;
	case 4:temp='4';break;
	case 5:temp='5';break;
	case 6:temp='6';break;
	case 7:temp='7';break;
	case 8:temp='8';break;
	case 9:temp='9';break;

	}
	return temp;
}


void LCD_vDispFloat(f32 A_f32Num)
{
	u8 L_u8Arr[10]={};
	floatToString(A_f32Num, L_u8Arr, 3);
	LCD_vDispStr(L_u8Arr);
}
void LCD_vReturnHome()
{
	LCD_vInstruction(CMD_RET_HOME);
}
void LCD_vShiftDisp(u8 A_u8ShiftDir)
{
	switch(A_u8ShiftDir){
			case SHIFT_LEFT:  LCD_vInstruction(CMD_SHIFT_DISP_LEFT); break;
			case SHIFT_RIGHT: LCD_vInstruction(CMD_SHIFT_DISP_RIGHT); break;
}
}

void floatToString(f32 A_f32Num, u8 *A_u8Arr, u8 A_u8AfterDecimal)
{
		u32 L_u32IntPart = (u32) A_f32Num;
			f32 L_f32FloatPart = A_f32Num - (f32)L_u32IntPart;

			u8 i=0;

				for(;L_u32IntPart>0;i++)
				{
					A_u8Arr[i]=LCD_vConvIntToChar(L_u32IntPart%10);

					L_u32IntPart/=10;
				}
				A_u8Arr[i]= '.';
				i++;
				L_f32FloatPart*=10;
				u32 L_u32Temp=L_f32FloatPart;
				for(;L_u32Temp!=0;i++)
				{
					A_u8Arr[i]=LCD_vConvIntToChar(L_u32Temp%10);
					L_f32FloatPart-=L_u32Temp;
					L_f32FloatPart*=10;
					L_u32Temp=L_f32FloatPart;


			    }
}
void LCD_vShiftCursor(u8 A_u8ShiftDir)
{

}
void LCD_vTurnOn()
{
	LCD_vInstruction(CMD_DISPLAY_ON);
}
void LCD_vTurnOff()
{
	LCD_vInstruction(CMD_DISPLAY_OFF);
}
/* Creating a custom patterns
 * we multiply by 8 as we have 8 locations (5x8 dots, 8 rows) for each cell (only can create 8 patterns)
 * */

static void LCD_vCreateCustomPattern(u8 *A_u8Pattern, u8 A_u8Loc)
{
	LCD_vInstruction(CMD_CGRAM_ADDRESS + A_u8Loc*8);
	_delay_us(45);
	for(u8 i=0; i<8; i++)
	{
		LCD_vSendData(A_u8Pattern[i]);
	}
}

void LCD_vDispCustomChar(u8 A_u8PatternId, u8 A_u8Row, u8 A_u8Col)
{
	switch(A_u8PatternId){

		case PATTERN0_ID: LCD_vCreateCustomPattern(G_u8Pattern0, 0); LCD_vSetPos(A_u8Row, A_u8Col);LCD_vSendData(0); break;
		case PATTERN1_ID: LCD_vCreateCustomPattern(G_u8Pattern1, 1); LCD_vSetPos(A_u8Row, A_u8Col);LCD_vSendData(1); break;
		case PATTERN2_ID: LCD_vCreateCustomPattern(G_u8Pattern2, 2); LCD_vSetPos(A_u8Row, A_u8Col);LCD_vSendData(2); break;
		/*
		case PATTERN3_ID: LCD_vCreateCustomPattern(G_u8Pattern3, 3); LCD_vSetPos(A_u8Row, A_u8Col);LCD_vSendData(0); break;
		case PATTERN4_ID: LCD_vCreateCustomPattern(G_u8Pattern4, 4); LCD_vSetPos(A_u8Row, A_u8Col);LCD_vSendData(0); break;
		case PATTERN5_ID: LCD_vCreateCustomPattern(G_u8Pattern5, 5); LCD_vSetPos(A_u8Row, A_u8Col);LCD_vSendData(0); break;
		case PATTERN6_ID: LCD_vCreateCustomPattern(G_u8Pattern6, 6); LCD_vSetPos(A_u8Row, A_u8Col);LCD_vSendData(0); break;
		case PATTERN7_ID: LCD_vCreateCustomPattern(G_u8Pattern7, 7); LCD_vSetPos(A_u8Row, A_u8Col);LCD_vSendData(0); break;
		*/
	}
}

