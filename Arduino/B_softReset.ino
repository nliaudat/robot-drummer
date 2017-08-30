/*
// http://www.codeproject.com/Articles/1012319/Arduino-Software-Reset
// 
*/


#include <avr/wdt.h>

/*
 //do not work with mega ...
void softwareReset( uint8_t prescaller) {
  // start watchdog with the provided prescaller
  wdt_enable( prescaller);
  // wait for the prescaller time to expire
  // without sending the reset signal by using
  // the wdt_reset() method
  while(1) {}
}
*/

void softwareReset( unsigned long delayMillis) {
  uint32_t resetTime = millis() + delayMillis;
  while ( resetTime > millis()) { 
    /* wait and do nothing until the required delay expires... */
  }
  // jump to the start of the program
  asm volatile ( "jmp 0");  
}

// usage : 
  // restart in 60 milliseconds
  //softwareReset( WDTO_60MS);


