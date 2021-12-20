#include "GP_Timer1.h"

void GP_Timer1_INIT(void)
{
	SET_BIT(SYSCTL_RCGCTIMER_R,1); //Enable the timer0 clock
  CLEAR_BIT(TIMER1_CTL_R ,0);//Timer 1 is disabled
  TIMER1_CFG_R|=0X0; //Timer1 is 32 bit
  TIMER1_TAMR_R|=0x2;//Timer1	 is periodic
  SET_BIT(TIMER1_TAMR_R,4); //Counting is down
	SET_BIT(TIMER1_CTL_R ,1);  // The Timer freezes counting while the processor is halted by the debugger.
  SET_BIT(TIMER1_ICR_R,0);//Clear timer0's flag
  TIMER1_TAILR_R=0x00000000; //Clear the previous loaded value
	NVIC_PRI5_R |= (7<<13); //Interrupt priority of timer1A is 0
	SET_BIT(NVIC_EN0_R,21); //Enable Timer1A NVIC interrupt 
	SET_BIT(TIMER1_IMR_R ,0);  //Enable Timer module time is out interrupT
}

void GP_Timer1_Start(void)
{
	TIMER1_TAILR_R=16000000U-1U; //Loading the value that will achieve the wanted delay
  SET_BIT(TIMER1_CTL_R ,0); //Enable the timer and start count
}


