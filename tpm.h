//******************************************
//FILE: tpm.h
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
#ifndef TPM_H_
#define TPM_H_

#include "global.h"
void tpm_busy_delay_ms(uint32_t);
void tpm_busy_delay_us(uint32_t);
void tpm_init();

#endif
