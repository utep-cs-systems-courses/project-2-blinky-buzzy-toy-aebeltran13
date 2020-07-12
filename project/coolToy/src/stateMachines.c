#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"

void red_then_green(){
  static char state = 0;

  switch(state){
  case 0:
    red_on = 1;
    green_on = 0;
    state = 1;
    leds_changed = 1;
    led_update();
    break;
  case 1:
    red_on = 0;
    green_on = 1;
    state = 2;
    leds_changed = 1;
    led_update();
    break;
  case 2:
    green_on = 0;
    state = 3;
    leds_changed = 1;
    led_update();
    break;
  case 3:
    red_on = 1;
    green_on = 0;
    state = 0;
    leds_changed = 1;
    led_update();
    break;
  }
}

void toggle_on(){
  red_on = 1;
  green_on = 1;
  leds_changed = 1;
  led_update();
}

void toggle_off(){
  red_on = 0;
  green_on = 0;
  leds_changed = 1;
  led_update();
}

void song(){
  float a = 220;
  float mC = 65.41;
  float d = 146.83;
  float mD = 73.42;
  float e = 164.81;
  float mF = 87.31;
  float g = 196;
  float mG = 98;

  float notes[30] = {mF,0,a,mC,0,0,a,0,mF,d,d,d,0,0,0,0,mF,a,mC,0,a,0,mF,e,0,mD,d};
  for(int i = 0; i < 30; i++){
    if(i % 2 == 0){
      toggle_on();
    }else{
      toggle_off();
    }
    buzzer_set_period(notes[i]);
    __delay_cycles(2500000);
  }
  buzzer_set_period(0);
}












