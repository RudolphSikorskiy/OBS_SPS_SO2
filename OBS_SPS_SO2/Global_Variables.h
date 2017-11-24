/*
 * Global_Variables.h
 *
 * Created: 20.10.2017 9:18:12
 *  Author: N
 */ 


#ifndef GLOBAL_VARIABLES_H_
#define GLOBAL_VARIABLES_H_
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SoftUART.h"
// Общие переменные для парсинга и вывода на 485 по запросу
// Буфер для парсинга
/*volatile*/ char Global_BUF[128];					// Буфер приема
//volatile char BUF[BufLEN];
#define A0 -10.0
#define X0 adc/1000
#define C0 327.09999996
//
#define A1 -16.57789614
#define X1 adc/1000
#define C1 541.99733688
//
// 2. Определения молярной массы для альтернативного пересчета
//
#define MOLAR 64.066 
//	46.0055		NO2
//	64.066		SO2
//	28.01		CO
//	34.0809		H2S
//	48			O3
// 3. Инициализация переменных для пакета от сенсора Spec Sensors
//
/*volatile*/ char* fromparse;
/*volatile*/ char* SN;
/*volatile*/ char* PPB;
/*volatile*/ char* TEMP;
/*volatile*/ char* HYDR;
/*volatile*/ char* ADCppb;
/*volatile*/ char* ADCtemp;
/*volatile*/ char* ADChydr;
/*volatile*/ char* HOUR;
/*volatile*/ char* MIN;
/*volatile*/ char* SEC;
/*volatile*/ char* Trash;
/*volatile*/ unsigned int trigger;
/*volatile*/ double mgStok;
/*volatile*/ double mgPrivat0;
/*volatile*/ double mgPrivat1;
/*volatile*/ signed long int ppb;
/*volatile*/ float ppm;
/*volatile*/ unsigned int tmp;
/*volatile*/ unsigned int adc;
/*volatile*/ unsigned int check;
char *ptr;

/*volatile*/ uint8_t OutStringPacket; 

void TakeConcentration(void);
void DataPackageFormation(char data[]);
#endif /* GLOBAL_VARIABLES_H_ */