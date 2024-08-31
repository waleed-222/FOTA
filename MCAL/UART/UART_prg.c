/*
 * UART_prg.c
 *
 *  Created on: Sep 21, 2022
 *      Author: mostafa_ebrahim
 */

#include"../../LIB/STD_TYPES.h"
#include"../../LIB/BIT_MATH.h"
#include "../DIO/DIO_int.h"
#include "UART_reg.h"
#include "UART_pri.h"
#include "UART_cfg.h"
#include "UART_int.h"

#include "../../APP/Flashing_Manager/Flashing_Manger.h"

#define IDLE 0
#define RUNNING 1

u8 u8len;
u8 au8RxBuffer[255] ;

void UART_vInit(void)
{
u8 L_u8UCSRC=0;
SET_BIT(L_u8UCSRC,URSEL);
#if UART_SET_MODE==UART_ASYNC_MODE
		CLR_BIT(L_u8UCSRC,UMSEL);
#elif UART_SET_MODE==UART_SYNC_MODE
		SET_BIT(L_u8UCSRC,UMSEL);
#else
#warning "Invalid Mode of UART......"
#endif
#if UART_PARITY_MODE==UART_DISABLED_PARITY
		CLR_BIT(L_u8UCSRC,UPM0);
		CLR_BIT(L_u8UCSRC,UPM1);

#elif UART_PARITY_MODE==UART_EVEN_PARITY
		CLR_BIT(L_u8UCSRC,UPM0);
		SET_BIT(L_u8UCSSRC,UPM1);

#elif UART_PARITY_MODE== UART_ODD_PARITY
		SET_BIT(L_u8UCSSRC,UPM0);
		SET_BIT(L_u8UCSSRC,UPM1);
#else
#warning "Invalid Parity Mode of UART....."
#endif

#if	UART_STOP_BIT_SELECT==UART_ONE_STOP_BIT
		CLR_BIT(L_u8UCSRC,USBS);

#elif UART_STOP_BIT_SELECT==UART_TWO_STOP_BIT
		SET_BIT(L_u8UCSRC,USBS);

#else
#warning "Invalid Stop Bit Mode of UART....."
#endif

#if UART_CHAR_FRAME_SIZE == UART_5_BITS
		L_u8UCSRC&=UART_CHAR_SIZE_MASK;

#elif UART_CHAR_FRAME_SIZE==UART_6_BITS
		L_u8UCSRC&=UART_CHAR_SIZE_MASK;
		L_u8UCSRC|=UART_6_BITS;

#elif  UART_CHAR_FRAME_SIZE==UART_7_BITS
		L_u8UCSRC&=UART_CHAR_SIZE_MASK;
		L_u8UCSRC|=UART_7_BITS;

#elif  UART_CHAR_FRAME_SIZE==UART_8_BITS
		L_u8UCSRC&=UART_CHAR_SIZE_MASK;
		L_u8UCSRC|=UART_8_BITS;

#elif  UART_CHAR_FRAME_SIZE==UART_9_BITS
		L_u8UCSRC&=UART_CHAR_SIZE_MASK;
		L_u8UCSRC|=UART_8_BITS;
		SET_BIT(UCSRB,UCSZ2);


#else
#warning "Invalid Data Size Mode of UART....."
#endif

#if UART_CLK_PARITY== UART_CLK_PARITY_RISING_TX_FALIING_RX
		CLR_BIT(L_u8UCSRC,UCPOL);

#elif UART_CLK_PARITY==UART_CLK_PARITY_FALIING_TX_RISING_RX
		SET_BIT(L_u8UCSRC,UCPOL);

#else
#warning "Invalid Clock Polarity Mode of UART....."
#endif

	UCSRC=L_u8UCSRC;

#if  UART_RXC_INT_STATE==UART_INT_ENABLE
	SET_BIT(UCSRB,RXCIE);
#else
	CLR_BIT(UCSRB,RXCIE);
#endif

#if  UART_TXC_INT_STATE==UART_INT_ENABLE
	SET_BIT(UCSRB,TXCIE);
#else
	CLR_BIT(UCSRB,TXCIE);
#endif

#if UDRT_DRE_INT_STATE==UART_INT_ENABLE
	SET_BIT(UCSRB,UDRIE);
	#else
		CLR_BIT(UCSRB,UDRIE);
	#endif

	SET_BIT(UCSRB,RXEN);	/*Enable Receiver*/
	SET_BIT(UCSRB,TXEN);    /*Enable Transmitter*/

	UBBRL=51; /*equation BUD :BUD=f_cpu/(16*(UBR+1))*/

	DIO_vPinDir(PORTA_ID,PIN0_ID,DIR_INPUT); /*RX configure as Input*/
	DIO_vPinDir(PORTA_ID,PIN1_ID,DIR_OUTPUT);/*TX configure as Output*/
}


void UART_vSendData(u8 A_u8Data)
{
	while(GET_BIT(UCSRA,UDRE)==0);
	UDR=A_u8Data;
}
/*put your data
 * Busy wait until finish TCF or buffer empty
 * */
u8 UART_u8GetData(void)
{
	while (GET_BIT(UCSRA,RXC)==0);
	return UDR;
}
/*wait until receive flag is raised
 * return data from register UDR
 * */
void UART_vSend_String(u8* A_u8String)
{
u8 L_u8CountChar=0;
while(A_u8String[L_u8CountChar]!=ADDRESS_NULL)
{
	UART_vSendData(A_u8String[L_u8CountChar]);
	L_u8CountChar++;
}
UART_vSendData('\0');

}

/*receive string*/
void UART_vGet_String(u8* A_u8String)
{
	u8 L_u8CountChar=0;
	A_u8String[L_u8CountChar]=UART_u8GetData();
	while(A_u8String[L_u8CountChar]!=ADDRESS_NULL)
	{
		L_u8CountChar++;
		A_u8String[L_u8CountChar]=UART_u8GetData();
	}
	A_u8String[L_u8CountChar]='\0';
}
/*Get length and data from GUI*/
void UART_vidRxHandler(void)
{
	static u8 RxState = IDLE ;
		static u8 bufferIdx = 0 ;

		/*Check if a byte received*/
		if( (GET_BIT(UCSRA , 7)) == 1)
		{
			if(RxState == IDLE)
			{
				u8len = UDR ;
				RxState = RUNNING ;
			}
			else
			{
				au8RxBuffer[bufferIdx] = UDR ;
				bufferIdx ++ ;
				if(bufferIdx == u8len)
				{
					/*all data is received */
					bufferIdx = 0 ;
					RxState = IDLE ;
					/*call application callback*/
					flashing_vidRxNotification(au8RxBuffer , u8len) ;
				}
			}
			CLR_BIT(UCSRA , 7);
}
}

/*set callback to execute ISR related with RXC Event*/
void UART_vCallBack_RXC(void(*Fptr)(void))
{
	G_PTRF_UART_RXC=Fptr;
}

/*set callback to execute ISR related with TXC Event*/
void UART_vCallBack_TXC(void(*Fptr)(void))
{
	G_PTRF_UART_TXC=Fptr;
}

/*set callback to execute ISR related with UDRE Event*/
void UART_vCallBack_UDRE(void(*Fptr)(void))
{
	G_PTRF_UART_UDRE=Fptr;
}


/* Receiver Complete UART ISR*/
void __vector_13 (void)
{
	G_PTRF_UART_RXC();
}

/*Data Register Empty UART ISR*/
void __vector_14 (void)
{
	G_PTRF_UART_UDRE();
}

/* Transmitter Complete UAR ISR*/
void __vector_15 (void)
{
	G_PTRF_UART_TXC();
}





