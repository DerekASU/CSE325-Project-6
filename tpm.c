//******************************************
//FILE: tpm.c
//
// DESCRIPTION
//
// AUTHOR
// Jialiang Liu (jliu174@asu.edu)
// Derek Janzen (djanzen@asu.edu)
//CSE 325 Embedded System 2015 Fall
// Electrical Engineering
// Arizona State University
//*****************************************
#include "tpm.h"

void tpm_init(){
    // Initialize TPM0_SC. We: (1) disable the TPM0 counter by writing 0b00 to TPM0_SC[CMOD] (we will write 0b01 later
    // to enable the counter to begin up counting); (2) DMA is disabled; (3) timer overflow interrupts are disabled;
    // (4) the TPM counter will be an up counter; (5) the prescale divider value is 2^2; this makes the TPM clock
    // period 1 us.
    TPM0_SC = 0x00000002;
    
    
    // Write all 0's to TPM0_CONF. Specifically, CROT = 0 because we are not using an external trigger; CSOO = 0 to
    // force the counter to continue counting on timer overflow; CSOT = 0 to cause the TPM counter to start counting
    // as soon as it is enabled by writing 0b01 to TPM0_SC[CMOD]; DBGMODE = 0b00 to pause the TPM counter when the
    // debugger is halted; and DOZEEN = 0 to cause the TPM counter to continue counting if the processor changes to
    // doze mode.
    TPM0_CONF = 0x00000000;
    
    tpm_pwm_init();
    
    // We have completed the initialization of TPM0. Note that is has been disabled from counting this entire time. To
    // start the generation of the PWM signals, we need to write 0b01 to TPM0_SC[CMOD].
    TPM0_SC |= 0b01 << 3;
}

void tpm_busy_delay_us(uint32_t  p_delay_us)
{
	SIM_SCGC6 |=0b1 << 24 ;
	SIM_SOPT2 |= SIM_SOPT2_TPMSRC(0b11);
	TPM0_SC |= 0b1 << 7;
	TPM0_SC &= ~(0b11 < 3);
	// TPM0_MOD = TPM_SC_CMOD(0b00);
	TPM0_SC |= (0b10);
	TPM0_CNT |= TPM_CNT_COUNT(0b0);
	TPM0_MOD = p_delay_us-1;
	TPM0_CONF &= ~(0b1 << 17);
	TPM0_CONF &= ~(0b1 << 16);
	TPM0_SC |= TPM_SC_CMOD(0b01);
	// TPM0_SC |= TPM_SC_PS(0b001);
	while (~TPM0_SC & TPM_SC_TOF_MASK) {}
	TPM0_SC |= 0b1 << 7;
} 


void tpm_busy_delay_ms(uint32_t p_delay_ms)
{
	uint32_t i;
	for(i=0; i < p_delay_ms; i++){
		tpm_busy_delay_us(1000);
	}
}
