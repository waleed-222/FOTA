/*
 * UART_pri.h
 *
 *  Created on: Sep 21, 2022
 *      Author: mostafa_ebrahim
 */

#ifndef MCAL_UART_UART_PRI_H_
#define MCAL_UART_UART_PRI_H_

/*options of modes*/
#define UART_ASYNC_MODE    0
#define UART_SYNC_MODE     1


/*options of stop bit*/
#define UART_ONE_STOP_BIT 0
#define UART_TWO_STOP_BIT 1

/*options of Party mode Options*/
 #define UART_DISABLED_PARITY     0
 #define UART_ODD_PARITY          1
 #define UART_EVEN_PARITY         2


/*options of character size*/
#define UART_5_BITS    0
#define UART_6_BITS    2
#define UART_7_BITS    4
#define UART_8_BITS    6
#define UART_9_BITS    14

/*Mask for select size of Data*/
#define UART_CHAR_SIZE_MASK 249

/*Clock parity options*/
#define UART_CLK_PARITY_RISING_TX_FALIING_RX 0
#define UART_CLK_PARITY_FALIING_TX_RISING_RX 1

/*options of UART INT*/
#define UART_INT_DISABLE 0
#define UART_INT_ENABLE 1

/*ISR UART*/
void __vector_13 (void) __attribute__((signal)); /*RXC UART*/
void __vector_14 (void) __attribute__((signal)); /*UDRE UART*/
void __vector_15 (void) __attribute__((signal)); /*TXC UART*/

/*Pointer to function*/
void (*G_PTRF_UART_RXC)(void) =ADDRESS_NULL;
void (*G_PTRF_UART_UDRE)(void) = ADDRESS_NULL;
void (*G_PTRF_UART_TXC)(void) =ADDRESS_NULL;


#endif /* MCAL_UART_UART_PRI_H_ */
