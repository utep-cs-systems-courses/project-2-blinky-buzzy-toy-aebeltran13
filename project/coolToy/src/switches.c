#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "stateMachines.h"

char SW1_state_down,SW2_state_down,SW3_state_down,SW4_state_down;
char switch_state_changed; /* effectively boolean */

static char 
switch_update_interrupt_sense()
{
  char p2val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);	/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);	/* if switch down, sense up */
  return p2val;
}

void 
switch_init()			/* setup switch */
{  
  P2REN |= SWITCHES;		/* enables resistors for switches */
  P2IE |= SWITCHES;		/* enable interrupts from switches */
  P2OUT |= SWITCHES;		/* pull-ups for switches */
  P2DIR &= ~SWITCHES;		/* set switches' bits for input */
  switch_update_interrupt_sense();
  switch_interrupt_handler();
}

void
switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense();
  SW1_state_down = (p2val & SW1) ? 0 : SW1; /* 0 when SW1 is up */
  SW2_state_down = (p2val & SW2) ? 0 : SW2; /* 0 when SW2 is up */
  SW3_state_down = (p2val & SW3) ? 0 : SW3; /* 0 when SW3 is up */
  SW4_state_down = (p2val & SW4) ? 0 : SW4; /* 0 when SW4 is up */
  
  if(SW1_state_down){
    toggle_on();
  }
  if(SW2_state_down){
    red_then_green();
  }
  if(SW3_state_down){
    song();
  }
  if(SW4_state_down){
    /* led_siren();
       siren_song();*/
  }
}
