#include "UART_STDIO.h"
//
static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
#define BRC ((F_CPU/16/BAUD) - 1)

uint8_t myadd = 0xFB;	// Адрес устройства
char* subst = "SO2";
uint8_t cmd[10] = {0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18};


 void USARTinit(void)
 {		 
	UBRR0H = (unsigned char)(BRC>>8);
	UBRR0L = (unsigned char)(BRC);
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);
	//Set frame Format: 8bit data, 2 stop bits
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
	//DDRB |= (1<<PB5); //  pinMode(13,OUTPUT);
 //blink13(3); //ready indication
	 IDX=0;
	 done=0;
	 //sei();

	 stdout = &mystdout;
}
 

int uart_putchar(char c, FILE *stream)
{
   if (c == '\n')
   uart_putchar('\r', stream);
   loop_until_bit_is_set(UCSR0A, UDRE0);
   UDR0 = c;
   return 0;
}
/*
void clearStr(char* str)
{
        for(IT=0;IT<LEN;IT++)
                str[IT]=0;
}
*/
ISR(USART_RX_vect)
{
		//PORTD &= ~(1<<(PORTD2));	// Прием
		
        uint8_t bf= UDR0;
        if (bf != 0x00)
        {
	        bufferU[IDX]=bf;
	        // 			SOFT_UART_byte(bufferU[0]);
	        // 			SOFT_UART_byte(bufferU[1]);
	        // 			SOFT_UART_byte(bufferU[2]);
	        // 			SOFT_UART_byte(bufferU[3]);
	        IDX++;
        }
		
		if (bf == 0x23)
		{
			if (bufferU[1] == myadd)
				{
					_delay_us(1000);
					switch (bufferU[2])
					{
					case 0x10:
						check = 1;
						
						TakeConcentration();
						//if (check == 4)
						//{
							
							PORTD |= (1<<(PORTD4)); // Передача
							_delay_us(500);			// 400 мкс рабочий
							printf("%c%c%c, %s, %.3f, %s, %s, %s,%c",'@',myadd,bufferU[2],subst,mgStok,PPB,TEMP,HYDR,'#');
							check = 0;
							_delay_us(2000);			// 1 мл рабочий
							PORTD &= ~(1<<(PORTD4));	// Прием
							check = 1;
					//	}
						//else
						//{
						//	check = 1;
						//}
							
						
						
						break;
					case 0x11:
						PORTD |= (1<<(PORTD4)); // Передача
						_delay_us(500);			// 400 мкс рабочий	
						printf("%c%c%c%c",'@',myadd,bufferU[2],'#');
						check = 1;
						_delay_us(2000);			// 1 мл рабочий
						PORTD &= ~(1<<(PORTD4));	// Прием
						break;
					case 0x12:	printf("%c comand 0x12 ok%c",'@','#');
						break;
					default:	printf("comand not found*");
						break;	
					}
					
					/*_delay_us(1000);
					PORTD &= ~(1<<(PORTD4));	// Прием*/
				}
				
				//_delay_ms(10);
                IDX=0;
			
		}
		if (IDX == LEN)
		{
			IDX=0;
		}
		
		
        
		
}

