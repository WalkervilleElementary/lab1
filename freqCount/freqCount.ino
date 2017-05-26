#include <phys253.h>
#include <avr/interrupt.h>
#include <LiquidCrystal.h>

#include <stdint.h>

/**
 * This program counts pulses on a digital input pin
 * and prints the frequency to the Serial port.
 */
/*
//Implement the following functions for your board:
void init_counter();
void start_counter();
uint32_t end_counter(); //return value is the number of cycles on the input pin

volatile unsigned int count = 0;

void init_counter() {
  count = 0;
}

*/
/*
void enableExternalInterrupt(unsigned int INTX, unsigned int mode)
{
  if (INTX > 3 || mode > 3 || mode == 1) return;
  cli();
  // Allow pin to trigger interrupts       
  EIMSK |= (1 << INTX);
  // Clear the interrupt configuration bits
  EICRA &= ~(1 << (INTX*2+0));
  EICRA &= ~(1 << (INTX*2+1));
  // Set new interrupt configuration bits   
  EICRA |= mode << (INTX*2);
  sei();
}

void disableExternalInterrupt(unsigned int INTX)
{
  if (INTX > 3) return;
  EIMSK &= ~(1 << INTX);
}

ISR(INT2_vect) {++count;};


void start_counter() {
  count = 0;
  enableExternalInterrupt(0, RISING);
}


uint32_t end_counter() {
  disableExternalInterrupt(0);
  return count;
}
*/
void setup() {
  #include<phys253setup.txt>

  Serial.begin(9600);
  //init_counter();
}

void loop() {
  unsigned long count = 0;
  bool mode = true;
  unsigned long start = millis();
  while(millis() - 1000 < start) {
    if (digitalRead(0)) {
      if (mode) {
        count++;
        mode = false;
      }
    } else {
      mode = true;
    }
  }
  
  LCD.clear();
  LCD.home();
  LCD.setCursor(0,0);
  LCD.print(count);

  
}
