#ifndef SOFTUART_H_
#define SOFTUART_H_

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Global_Variables.h"
#define CheckBit(reg,bit) (reg&(1<<bit)) //n=PIND&(1<<RX_PIN);

#define TX_PIN 3
#define RX_PIN 2
#define BTREIT 9600 //������� � 9600, ��� ������� ����� �������
#define MLN 1000000L //�������

void SOFT_UART_init();						// ������������� ����������� UART
void SOFT_UART_bit( char b);				// �������� ����
void SOFT_UART_byte( char a);				// �������� �����
void SOFT_UART_send( char *str);			// �������� ������
unsigned char SOFT_UART_read(void);			// ����� ������
char *OperationResponse(void);				// ������� �������� ������ �������



#endif /* SOFTUART_H_ */