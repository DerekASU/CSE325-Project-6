#include "adc.h"
#include "global.h"
#include "int.h"
#include "pit.h"
#include "pot.h"

//======================================================================================================================
// Private Macros
//======================================================================================================================

#define forever for(;;)

//======================================================================================================================
// Private Function Declarations
//======================================================================================================================

static void hw_init();
static void pit_callback();
static void run();
static void sw_init();

uint16_t curr_pot;
//======================================================================================================================
// Function Definitions
//======================================================================================================================

//----------------------------------------------------------------------------------------------------------------------
// FUNCTION: hw_init()
//
// DESCRIPTION
// Initializes the MKL46Z hardware peripherals we will be using.
//---------------------------------------------------------------------------------------------------------------------
void hw_init()
{
    // Mask all interrupts during hardware initialization.
    int_mask_all();

    sim_init();
    port_init();
    tpm_init();


    // Initialize PIT to generate interrupts at 1 Hz, calling pit_callback().
    pit_init(pit_timer_0, pit_freq_10_hz, pit_state_disabled, pit_callback);

    // Initialize ADC.
    adc_init();

    // Initialize the POT module.
    pot_init();

    // Unmask all interrupts.
    int_unmask_all();

    // Enable PIT0 to begin generating interrupts.
    pit_cfg_state(pit_timer_0, pit_state_enabled);
}

//----------------------------------------------------------------------------------------------------------------------
// FUNCTION: main()
//---------------------------------------------------------------------------------------------------------------------
int main()
{
    hw_init();
    sw_init();
    run();
}

//----------------------------------------------------------------------------------------------------------------------
// FUNCTION: run()
//
// DESCRIPTION
// Implements the main processing loop. We continuously read the state of the pot. When the state is < 100, the red
// LED is blinked at a frequency of 10 Hz. When the state is >= 100 and < 1000, the red LED is blinked at a frequency
// of 2 Hz. When the state is >= 1000, the red LED is blinked at a frequency of 1 Hz. We only change the PIT interrupt
// frequency when the state of the pot changes from one range to another.
//---------------------------------------------------------------------------------------------------------------------
static void run()
{
    forever {
        motor_speed(curr_pot);
    }
}

//----------------------------------------------------------------------------------------------------------------------
// FUNCTION: sw_init()
//
// DESCRIPTION
// Initialize any global variables.
//---------------------------------------------------------------------------------------------------------------------
static void sw_init()
{
}

//----------------------------------------------------------------------------------------------------------------------
// FUNCTION: pit_callback()
//
// DESCRIPTION
// This function is called by pit_isr() at the frequency we specified when we called pit_init() or when we changed the
// frequency by calling pit_cfg_freq(). We simply toggle the red LED.
//---------------------------------------------------------------------------------------------------------------------
static void pit_callback()
{
    //prev_pot = pot_get_prev_state();
    curr_pot = pot_get_curr_state();
}
