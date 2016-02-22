//******************************************
//FILE: port.c
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
#include "port.h"

void port_init()
{
    // Configure PTC1 for the TPM0 channel 0 PWM function (ALT4).
    PORTC_PCR1 = (0b100 << 8);
    
    PORTC_PCR2 = 0;
}
