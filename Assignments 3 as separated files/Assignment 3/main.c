

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"


/* Stellaris library includes. */
#include "hw_types.h"
#include "hw_memmap.h"
#include "hw_sysctl.h"


/*my Created Files*/
#include "ADC.h"
#include "LCD.h"
#include "GP_Timer1.h"
#include "toStringConverter.h"


#define num_of_digits_before 3
#define num_of_digits_after 2



/*Global Variables*/
float temperature;
unsigned long long Interrupt_Execution_Count=0;
unsigned long long ADC_Task_Execution_Count=0;
unsigned long long LCD_Task_Execution_Count=0;

xSemaphoreHandle xBinarySemaphoreReadTemperature;
xSemaphoreHandle xBinarySemaphoreDisplayTemperature;

/*Functions Prototypes*/
void vGetTemperature( void *pvParameters );
void vDisplayTemperature( void *pvParameters );

/*-----------------------------------------------------------*/





/*********************************************  TIMER1A_Handler  ************************************************************/
/*Timer0 Exception Handler*/
void TIMER1A_Handler(void)
{
	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
	xSemaphoreGiveFromISR( xBinarySemaphoreReadTemperature, &xHigherPriorityTaskWoken ); //Unblocking vGetTemperature Task
	
	SET_BIT(TIMER1_ICR_R,0); //Clear the Interrupt flag
	
	Interrupt_Execution_Count++; //Just a counter show that how many time this interrupt excuted
	
	portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
}

/**********************************************************************************************************************************/





/*********************************************  vGetTemperature Task  ************************************************************/
void vGetTemperature( void *pvParameters )
{
	/*
		This Task Waits for an interrupt from timer1 which happen every second to unlock it/
		then, it gets the internal temperature from the ADC, calculates it and store it in temperature variable/
		after that, it unlocks the lcd displaying task.
	*/
	
	unsigned long ADC_output;
	
	xSemaphoreTake( xBinarySemaphoreReadTemperature, 0 );
		for(;;)
	{
		ADC0_PSSI_R |= 0X8; // Initialize SS3
		while((ADC0_RIS_R & 0X8) == 0); // Loop till conversion is done
		
		ADC_output = ADC0_SSFIFO3_R & 0xFFF; // Read temperature ADC output
		temperature = 147.5 - ( (247.5 * ADC_output) / 4096); // Convert the ADC output to a temperature in degrees
		
		ADC_Task_Execution_Count++; //Just a counter show that how many times this task executed
		
		xSemaphoreGive( xBinarySemaphoreDisplayTemperature);// unblock LCD display task which is lower priority
		
		xSemaphoreTake( xBinarySemaphoreReadTemperature, portMAX_DELAY ); // block till 1 second is passed
																																			// Timer will unblock this task after 1 second periodically
	}
}
/**********************************************************************************************************************************/






/*********************************************  vDisplayTemperature Task  ************************************************************/
void vDisplayTemperature( void *pvParameters )
{
		/*
		This Task Waits for the GetTemperature Task to unlock it/
		then, it transforms the float variable "temperature" to be a string "LCD_temperature"/
		then, it clears the LCD and prints the new temperature on it/
		finally, it blocks again till a new unlock arrive from GetTemperature Task
	*/
	
	char LCD_temperature[num_of_digits_before + num_of_digits_after+1]; 
	
	xSemaphoreTake( xBinarySemaphoreDisplayTemperature, 0 );
	for(;;)
	{
		//Convert Temperature Float variable to a String stored in "LCD_temperature" variable
		ftoa((float)temperature,LCD_temperature, num_of_digits_after); 
		
		/*Critical Section:
		to not update the temperature while the it is being writing on the LCD*/
		__asm("CPSID  I");
		
		LCD_clearScreen(); //Clear the LCD
		LCD_displayString(LCD_temperature); //Display the new Temperature Value
		
		__asm("CPSIE  I");
		/*Critical Section End*/
		
		LCD_Task_Execution_Count++; //Just a counter show that how many times this task executed
		
		xSemaphoreTake( xBinarySemaphoreDisplayTemperature, portMAX_DELAY ); //block till a new temperature read is excuted 
	}
}
/**********************************************************************************************************************************/




int main( void )
{
	
	vSemaphoreCreateBinary( xBinarySemaphoreReadTemperature );
	vSemaphoreCreateBinary( xBinarySemaphoreDisplayTemperature );
	
	ADC_INIT();
	LCD_init();
	GP_Timer1_INIT();

	xTaskCreate( vGetTemperature, "GetTemperature", 240, NULL, 2 , NULL );
	xTaskCreate( vDisplayTemperature, "DisplayTemperature", 240, NULL, 1 , NULL );
	GP_Timer1_Start();
	vTaskStartScheduler();

	for(;;){}

}
/*-----------------------------------------------------------*/














/*-----------------------------------------------------------*/

void vApplicationMallocFailedHook( void )
{
	/* This function will only be called if an API call to create a task, queue
	or semaphore fails because there is too little heap RAM remaining - and
	configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h. */
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( xTaskHandle *pxTask, signed char *pcTaskName )
{
	/* This function will only be called if a task overflows its stack.  Note
	that stack overflow checking does slow down the context switch
	implementation and will only be performed if configCHECK_FOR_STACK_OVERFLOW
	is set to either 1 or 2 in FreeRTOSConfig.h. */
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
	/* This example does not use the idle hook to perform any processing.  The
	idle hook will only be called if configUSE_IDLE_HOOK is set to 1 in 
	FreeRTOSConfig.h. */
}
/*-----------------------------------------------------------*/

void vApplicationTickHook( void )
{
	/* This example does not use the tick hook to perform any processing.   The
	tick hook will only be called if configUSE_TICK_HOOK is set to 1 in
	FreeRTOSConfig.h. */
}









