/*
 * UART_int.h
 *
 *  Created on: Sep 21, 2022
 *      Author: mostafa_ebrahim
 */

#ifndef MCAL_UART_UART_INT_H_
#define MCAL_UART_UART_INT_H_

void UART_vInit(void);
/*select bud rate 9600
 * disable parity
 * select 1 stop bit
 * Daata frame 8 bit
 * enable Transmit and receiver*/

void UART_vSendData(u8 A_u8Data);
/*put ur data
 * Busy wait until finish TCF or buffer empty
 * */
u8 UART_u8GetData(void);
/*wait until receive flag is raised
 * return data from register UDR
 * */
void UART_vSend_String(u8* A_u8String);

/*receive string*/
void UART_vGet_String(u8* A_u8String);

/*receive bytes fro GUI*/
void UART_vidRxHandler(void);

/*set callback to execute ISR related with RXC Event*/
void UART_vCallBack_RXC(void(*Fptr)(void));

/*set callback to execute ISR related with TXC Event*/
void UART_vCallBack_TXC(void(*Fptr)(void));

/*set callback to execute ISR related with UDRE Event*/
void UART_vCallBack_UDRE(void(*Fptr)(void));
#endif /* MCAL_UART_UART_INT_H_ */
