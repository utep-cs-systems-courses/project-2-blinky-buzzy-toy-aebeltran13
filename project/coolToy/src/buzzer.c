#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
#include "led.h"

void buzzer_init()
{
    /* 
       Direct timer A output "TA0.1" to P2.6.  
        According to table 21 from data sheet:
          P2SEL2.6, P2SEL2.7, anmd P2SEL.7 must be zero
          P2SEL.6 must be 1
        Also: P2.6 direction must be output
    */
    timerAUpmode();		/* used to drive speaker */
    P2SEL2 &= ~(BIT6 | BIT7);
    P2SEL &= ~BIT7; 
    P2SEL |= BIT6;
    P2DIR = BIT6;		/* enable output to speaker (P2.6) */
}

void buzzer_set_period(short cycles) /* buzzer clock = 2MHz.  (period of 1k results in 2kHz tone) */
{
  CCR0 = cycles; 
  CCR1 = cycles >> 1;		/* one half cycle */
}

void song(){
  float a = 2200;
  float mC = 650.41;
  float d = 1460.83;
  float mD = 730.42;
  float e = 1640.81;
  float mF = 870.31;
  float g = 1960;
  float mG = 980;

  float notes[30] = {mF,0,a,mC,0,0,a,0,mF,d,d,d,0,0,0,0,mF,a,mC,0,a,0,mF,e,0,mD,d};
  for(int i = 0; i < 30; i++){
    buzzer_set_period(notes[i]);
    __delay_cycles(2500000);
  }
  buzzer_set_period(0);
}

void siren_song(){
  for(int i = 0; i<30; i++){
    if(i % 2 == 0){
      buzzer_set_period(2000);
      toggle_on();
    }else{
      buzzer_set_period(1000);
      toggle_off();
    }
    __delay_cycles(2500000);
  }
  buzzer_set_period(0);
}
