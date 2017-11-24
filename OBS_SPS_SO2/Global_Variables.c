#include "Global_Variables.h"



void DataPackageFormation(char data[])
{
	//USART_Transmit_str(data);
	//USART_Transmit('\r');
	char *pch = strtok (data,", "); //во втором параметре указаны разделители (пробел, запятая, точка)
	while (pch != NULL) //пока есть лексемы pch !== NULL а сейчас проверяем первые 4
	{	//		0		1	2	3	4		5		6	7	 8	 9	 10
		//111116010250, 13, 25, 51, 13143, 27064, 30330, 00, 03, 43, 30
		switch ( trigger )
		{
			//----------------------------//
			
			case 0:
			SN = pch;
			pch = strtok (NULL, ", ");
			trigger++;
			break;
			
			//----------------------------//
			
			case 1:
			PPB = pch;
			pch = strtok (NULL, ", ");
			trigger++;
			break;
			
			//----------------------------//
			
			case 2:
			TEMP = pch;
			pch = strtok (NULL, ", ");
			trigger++;
			break;
			
			//----------------------------//
			
			case 3:
			HYDR = pch;
			pch = strtok (NULL, ", ");
			trigger++;
			break;
			
			//----------------------------//
			
			case 4:
			ADCppb = pch;
			pch = strtok (NULL, ", ");
			trigger++;
			break;
			
			//----------------------------//
			
			case 5:
			ADCtemp = pch;
			pch = strtok (NULL, ", ");
			trigger++;
			break;
			
			//----------------------------//
			
			case 6:
			ADChydr = pch;
			pch = strtok (NULL, ", ");
			trigger++;
			break;
			
			//----------------------------//
			
			case 8:
			HOUR = pch;
			pch = strtok (NULL, ", ");
			trigger++;
			break;
			
			//----------------------------//
			
			case 9:
			MIN = pch;
			pch = strtok (NULL, ", ");
			trigger++;
			break;
			
			//----------------------------//
			
			case 10:
			SEC = pch;
			SEC[2]= '\0';
			//SEC[3]= '\0';
			pch = strtok (NULL, ", ");
			trigger++;
			break;
			
			//----------------------------//
			
			
			default:
			Trash = pch;
			pch = strtok (NULL, ", ");
			trigger++;
			break;
		}
		
	}
	trigger = 0;
	
	
}

//-----------------------------------------------------------------------//

int my_getnbr(char *str)
{
	int           result;
	int           puiss;

	result = 0;
	puiss = 1;
	while (('-' == (*str)) || ((*str) == '+'))
	{
		if (*str == '-')
		puiss = puiss * -1;
		str++;
	}
	while ((*str >= '0') && (*str <= '9'))
	{
		result = (result * 10) + ((*str) - '0');
		str++;
	}
	return (result * puiss);
}

//-----------------------------------------------------------------------//

void TakeConcentration(void)
{
	SOFT_UART_byte(0b00001101);			// Отправка Команды для получения стоки от SPS
	while(check == 3)
	{
		//asm("nop");
	}
	
	DataPackageFormation(Global_BUF);	// Секунда прошла Парсим фанные для вывода на 485
	
	if (PPB[0]=='-')					// если значение PPB с сенсора отрицательное то определяем его как 0
		ppb = 0;
	else
		//ppb= ppb+1000;
		ppb = strtol(PPB,&ptr,0);			// Перевод строки в целоцисленное без знаковое
	if (ADCppb[0]=='\0')
		adc = 0;						// Костыль, если напряжение на АЦП сенсора не пришло 0 то определяем его как 0
	else
		adc = strtol(ADCppb,&ptr,0);		// Перевод строки в целоцисленное без знаковое
	tmp = strtol(TEMP,&ptr,0);
	
	mgStok = MOLAR*0.000001*(ppb)/(8.314472*(tmp+273.15)/101325);
	check = 4;

}

