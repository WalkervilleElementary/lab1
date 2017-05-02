#include <stdint.h>

/**
 * This program counts pulses on a digital input pin
 * and prints the frequency to the Serial port.
 */

//Implement the following functions for your board:
void init_counter();
void start_counter();
uint32_t end_counter(); //return value is the number of cycles on the input pin

#define TEST_FREQUENCY_GENERATOR

//Arduino Mega hardware timer counter implementation
#ifdef ARDUINO_AVR_MEGA2560
void init_counter() {
  //Don't want to generate a signal on a pin with this timer
  TCCR5A = 0;
  //Enable the timer overflow interrupt
  TIMSK5 = _BV(TOIE5);
  //Timer 5 uses pin 47 as an external input
  pinMode(47, INPUT);
}

//This interrupt runs everytime the counter overflows, giving 16 more bits to count with
//in count_upper
uint16_t count_overflow = 0;
ISR(TIMER5_OVF_vect) {
  count_overflow += 1;
}

void start_counter() {
  //Reset timer value
  TCNT5 = 0;
  count_overflow = 0;
  //Use digital pin 47 as the clock source, turning the timer into a counter of rising edges
  TCCR5B = _BV(CS52)|_BV(CS51)|_BV(CS50);
}

uint32_t end_counter() {
  //Disconnects all input sources to the timer
  TCCR5B = 0;
  //Return the timer value combined with the 16 overflow bits
  return (((uint32_t)count_overflow) << 16) | TCNT5;
}

//Uses timer 4 to generate an 8MHz signal on pin 6
#ifdef TEST_FREQUENCY_GENERATOR
void init_test_frequency_generator() {
  pinMode(6, OUTPUT);
  TCCR4A = _BV(COM4A0);
  TCCR4B = _BV(CS40);
  TCCR4B |= _BV(WGM42);
  OCR4A = 0;
  TCNT4 = 0;
}
#endif
#else
//TODO: Implement support for TINAH.
#endif

void setup() {
  pinMode(13, INPUT);
  Serial.begin(115200);
  #ifdef TEST_FREQUENCY_GENERATOR
  init_test_frequency_generator();
  #endif
  init_counter();
}

void loop() {
  start_counter();
  delay(1000);
  uint32_t count = end_counter();
  Serial.println(count);
}

