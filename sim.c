//******************************************
//FILE: sim.c
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
#include "sim.h"

void sim_init(){
    // Enable clock gates to ports A-E.
    SIM_SCGC5 |= 0b11111 << 9;

    // Enable the clock gate to ADC0.
    SIM_SCGC6 |= 1 << 27;
    
    // Enable the clock gate to TPM0.
    SIM_SCGC6 |= 1 << 24;

    // Enable the clock gate to PIT.
    SIM_SCGC6 |= 1 << 23;
    
    // Configure the TPM reference clock to be 4 MHz MCGIRCLK. TPM0_SC[PS] is initialized to 0b010 (2 decimal) so the
    // TPM counter clock frequency will be 4 MHz / 2^2 = 1 MHz. This configures the TPM counter clock period to be 1 us.
    SIM_SOPT2 |= 0b11 << 24;
}
