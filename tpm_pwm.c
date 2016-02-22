//******************************************
//FILE: tpm_pwm.c
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
#include "tpm_pwm.h"

void tpm_pwm_init(){
    // Write any value to TPM0_CNT to reset the TPM counter to 0.
    TPM0_CNT = 0;
    
    // Configure the period of the PWM signal to be 40 us (so the PWM signal frequency will be 25k Hz).
    TPM0_MOD = 40 - 1;
    
    // Configure TPM0 channel 0 for Edge-Aligned PWM mode with high polarity, i.e., the PWM signal will
    // start high and will change to low at a time determined by the value of TPM0_C0V. For edge-triggered up-counting
    // PWM mode, TPM0_SC[CPWMS] must be 0, TPM0_C0SC[MSB:MSA] must be 0b10, and TPM0_C0SC[ELSB:ELSA] must be 0b10.
    // CHIE is cleared to 0 to disable channel interrupts.
    TPM0_C0SC = 0b00101000;
    
}

void tpm_pwm_duty(int n){
	TPM0_C0V = ((TPM0_MOD + 1) * n) / 100;
}
