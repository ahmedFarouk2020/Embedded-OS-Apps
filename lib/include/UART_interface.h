/*********************************************************/
/* author  : Farouk                                      */
/* Version : v01                                         */
/* Date    : Sept 19 2020                                */
/*********************************************************/

#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H

/* set configurations of UART */
void MUART_voidInit(void);
/* transmit a bulk of data */
void MUART_voidTransmit(u8* copy_u8Arr);
/* get Transmit integer data by UART */
void MUART_voidTransmitInt(u32 data);
char MUART_u8Receive(void);







#endif
