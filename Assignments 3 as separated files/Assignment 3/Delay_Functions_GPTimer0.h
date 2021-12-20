

/**************Delay functions for the LCD*******************/


#ifndef __Delay__
#define __Delay__


#include "tm4c123gh6pm.h"
#include "registers_operations_macros.h"
void GPTimer0_Config();
void delay_us(int time);
void delay_ms(int time);



#endif