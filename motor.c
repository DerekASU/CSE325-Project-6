//******************************************
//FILE: motor.c
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
#include "motor.h"


void motor_speed(uint16_t curr_pot){
		if (curr_pot < 1500) {
        	TPM0_C0SC &= ~(0b1111 << 2);  // Disables only TPM0_CH0
        } else if (curr_pot < 4001) {
        	TPM0_C0SC |= 0b1010 << 2;  // Enables TPM0_CH0
        	tpm_pwm_duty(100);
        	tpm_busy_delay_ms(1);
        	tpm_pwm_duty(50);
        } else {
        	TPM0_C0SC |= 0b1010 << 2;  // Enables TPM0_CH0
            tpm_pwm_duty(100);
        }
    }
