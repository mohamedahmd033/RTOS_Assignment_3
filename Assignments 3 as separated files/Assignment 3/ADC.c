#include "ADC.h"
#include "Delay_Functions_GPTimer0.h"

void ADC_INIT(void)
{
	SYSCTL_RCGC0_R |= 0x00010000ul; 	// Activate ADC0, bit 16 of RCGC register
	delay_ms(1);			// Allow time for clock to be enabled
	SYSCTL_RCGC0_R &= ~0x00000300ul;	// Configure the sampling rate default value of 125k, bits 15-12
	ADC0_SSPRI_R &= ~0xF000ul;					// Set priority of sequencer 3 the hights one; zeros at bits 15-12
	ADC0_ACTSS_R &= ~0x8ul;						// Disable sequencer 3 during configuratuion
	ADC0_EMUX_R &= ~0xF000ul;					// Make sequencer 3 triggered software/start; 0x0 at bits 3-0
	ADC0_SSMUX3_R = 0x0ul;						// Get input from channel 0
	ADC0_SSCTL3_R |= 0x0Eul;					// Enable temperature measurment, set flag on EOC at the first sample
	ADC0_ACTSS_R |=0x8ul;							// Enable ADC0 sequencer 3
}