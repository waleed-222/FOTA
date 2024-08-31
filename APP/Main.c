/*
 * Main.c
 *
 *  Created on: Aug 29, 2024
 *      Author: Waleed Ebrahem Mohamed
 */

#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "../MCAL/DIO/DIO_int.h"
#include "../MCAL/UART/UART_int.h"

#include "avr/eeprom.h"

#include "Flashing_Manager/Flashing_Manger.h"


char eedata[] EEMEM = {0x00,0x00};
extern void APP_vidMoveIVT(u8 u8Section) ;

int main(void)
{
	u8 validAPP_Val, reqFromApp_Val;
		validAPP_Val = eeprom_read_byte (VALID_APP_ADDRESS);
		reqFromApp_Val = eeprom_read_byte (REQ_FROM_APP_ADDRESS);

		/*Starting of Program or there is no Valid program currently*/
		if ( (validAPP_Val != 1) | (reqFromApp_Val == 1))
		{
			/*for debugging*/
			DIO_vPinDir(PORTA_ID , PIN7_ID , DIR_OUTPUT);
			DIO_vSetPinVal(PORTA_ID , PIN7_ID , VAL_HIGH);


			UART_vInit();

	#if USE_INTERRUPT == 1
			/*Move Vector Table to boot loader section*/
			APP_vidMoveIVT(BLD_SECTION);
	#endif

			if(reqFromApp_Val == 1)
			{
				flashingMngr_vidHandleReqFromApp() ;
				/*clear application request*/
				eeprom_update_byte (REQ_FROM_APP_ADDRESS, 0);
			}

			while(1)
			{
			#if USE_INTERRUPT == 0
				UART_vidRxHandler();
			#endif
				flashingMngr_vidMainTask() ;
			}
		}
		else
		{
			/*Valid app, jump directly*/
			asm("jmp 0");
		}

		return 1 ;
	}

	extern void APP_vidMoveIVT(u8 u8Section)
	{
		/*Move Interrupt Vector table to Application [starting from 0]*/
		if(u8Section == APP_SECTION)
		{
			/* Enable change of interrupt vectors */
			GICR = (1<<IVCE);
			/* Move interrupts to Application section */
			CLR_BIT(GICR,IVSEL);
		}

		/*Move IVt to Bootloader [starting after end of app section]*/
		else
		{
			/* Enable change of interrupt vectors */
			GICR = (1<<IVCE);
			/* Move interrupts to boot Flash section */
			GICR = (1<<IVSEL);
		}
	}


