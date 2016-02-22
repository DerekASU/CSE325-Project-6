//******************************************
//FILE: pot.h
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
#ifndef POT_H_
#define POT_H_

#include "global.h"

uint16_t pot_get_curr_state();
uint16_t pot_get_prev_state();
void pot_init();


#endif
