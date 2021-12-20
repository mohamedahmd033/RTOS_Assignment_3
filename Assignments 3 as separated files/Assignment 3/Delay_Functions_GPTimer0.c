#include "Delay_Functions_GPTimer0.h"


unsigned int MC_CLOCK =16000000;
void GPTimer0_Config()
{
  SET_BIT(SYSCTL_RCGCTIMER_R,0); //Enable the timer0 clock
  CLEAR_BIT(TIMER0_CTL_R ,0);//Timer 0 is disabled
  TIMER0_CFG_R|=0X0; //Timer0 is 32 bit
  TIMER0_TAMR_R|=0x1;//Timer0 is one shot
  SET_BIT(TIMER0_TAMR_R,4); //Counting is down
  SET_BIT(TIMER0_ICR_R,0);//Clear timer0's flag
  TIMER0_TAILR_R=0x00000000; //Clear the previous loaded value
}

void delay_us( int time)
{
  GPTimer0_Config();
  unsigned long num_of_counts=time*(MC_CLOCK/1000000);//Calculating the needed counts to make the wanted delay
  TIMER0_TAILR_R=num_of_counts; //Loading the value that will achieve the wanted delay
  SET_BIT(TIMER0_CTL_R ,0); //Enable the timer and start count
  while(!((TIMER0_RIS_R)&(1<<0))); //Stay till making the wanted delay
	CLEAR_BIT(SYSCTL_RCGCTIMER_R,0); //Disable timer0 clock

}

void delay_ms(int time)
{
   GPTimer0_Config();
   unsigned long num_of_counts=time*(MC_CLOCK/1000);//Calculating the needed counts to make the wanted delay
  TIMER0_TAILR_R=num_of_counts; //Loading the value that will achieve the wanted delay
  SET_BIT(TIMER0_CTL_R ,0); //Enable the timer and start count
  while(!((TIMER0_RIS_R)&(1<<0))); //Stay till making the wanted delay
	CLEAR_BIT(SYSCTL_RCGCTIMER_R,0); //Disable timer0 clock
    
}


void systick_delay_ms(unsigned int time) //delay in ms with maximum delay is ((16777216/MC_CLOCK)*1000) ms
{
  unsigned int maximum_delay=((16777216/MC_CLOCK)*1000);
  if(time>maximum_delay)
  {
    while(1);
  }
  NVIC_ST_CTRL_R&=~(1<<0); //disable the timer to make configrations
  NVIC_ST_RELOAD_R=0;
  NVIC_ST_RELOAD_R=(time*(MC_CLOCK/1000)-1);//reload the value which will make the delay which is maximum 1000ms
  NVIC_ST_CURRENT_R=0x000000; //reset the flag bit and the current value register
  NVIC_ST_CTRL_R&=~(1<<1);//no intrupt
  NVIC_ST_CTRL_R|=(1<<2)|(1<<0);//enable the clock soucre and enable the clock
  while(!(NVIC_ST_CTRL_R&(1<<16)));//looping till the flag be 1;
  NVIC_ST_CTRL_R&=~(1<<0); //disable the timer to make configrations


}


