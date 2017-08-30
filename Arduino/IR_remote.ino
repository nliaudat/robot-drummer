/*
  http://arduino.stackexchange.com/questions/3926/using-vs1838b-with-arduino
"Removing the files - libraries\RobotIRremote\IRremoteTools.cpp and libraries\RobotIRremote\IRremoteTools.h solved the problem.
*/

#include "IRremote.h"


#ifdef USE_SOURCE_MIDI //cannot debug with midi enabled
  static const bool IR_DEBUG = false;
#else
  static const bool IR_DEBUG = false; //true only if needed
#endif


int receiver_PIN = 2; 


IRrecv irrecv(receiver_PIN);           // create instance of 'irrecv'
decode_results results;            // create instance of 'decode_results'

static const int MIN_BPM = 20; //cannot be 0, use as divider in pattern : INTERVAL = (60000/BPM)/(PATTERN_TEMPO);
static const int MAX_BPM = 200; 
static const int STEP_BPM = 5; 

///////////////////////////////////////////////////////////////////// Setup /////////////////////

void setup_IR(){
  if(IR_DEBUG){
    Serial.println("IR Receiver Raw Data + Button Decode Test");
  }
  
  irrecv.enableIRIn(); // Start the receiver

}

///////////////////////////////////////////////////////////////////// Loop /////////////////////
void loop_IR(){
  if (irrecv.decode(&results)) // have we received an IR signal?
  {
//    Serial.println(results.value, HEX);  UN Comment to see raw values
    translateIR(); 
    irrecv.resume(); // receive the next value
  }  
}

///////////////////////////////////////////////////////////////////// Private Functions /////////////////////
void translateIR(){ // takes action based on IR code received

// describing Car MP3 IR codes 



  switch(results.value){

  case 0xFFA25D: 
    if(IR_DEBUG){ 
      Serial.println("power off/on"); 
    }
    softwareReset( WDTO_60MS);
    break;

  case 0xFF629D:  
    if(IR_DEBUG){
      Serial.println("mode"); 
    }
    break;

  case 0xFFE21D:  
    if(IR_DEBUG){
    Serial.println("Mute sound"); 
    }
    break;

  case 0xFF22DD:  
    if(IR_DEBUG){
      Serial.println("Play/Pause"); 
    }
    #ifdef USE_SOURCE_PATTERN
    
      if(PAUSE_PATTERN == true){
        lcdPrintPatternName((char *)"PAUSED    "); //char * avoid deprecated conversion from string constant to ‘char*’` warnings in GCC
        lcdPrintInstrumentHit('H', ' ');
        lcdPrintInstrumentHit('S', ' ');
        lcdPrintInstrumentHit('B', ' ');
        CloseAllRelay(); //prevent burning
      }else{
        switch_pattern(CURRENT_PATTERN, true);
      }
      PAUSE_PATTERN = !PAUSE_PATTERN;

    #endif
    break;

  case 0xFF02FD:  
    if(IR_DEBUG){
      Serial.println("Previous"); 
    }
    #ifdef USE_SOURCE_PATTERN
      if(CURRENT_PATTERN > 1){
        CURRENT_PATTERN --;
      }else{
        CURRENT_PATTERN = MAX_PATTERN_NUM;
      }
      //switch_pattern(CURRENT_PATTERN);  //immediately
      PATTERN_CHANGE = CURRENT_PATTERN; //will change pattern at next end of measure
      switch_pattern(CURRENT_PATTERN, false); //next measure, but display "-> pattername"
      //set info to lcd
      
    #endif
    break;

  case 0xFFC23D:
    if(IR_DEBUG){
      Serial.println("Next"); 
    }
     #ifdef USE_SOURCE_PATTERN
      if(CURRENT_PATTERN < MAX_PATTERN_NUM){
        CURRENT_PATTERN ++;
      }else{
        CURRENT_PATTERN = 1;
      }
      //switch_pattern(CURRENT_PATTERN); //immediately
      PATTERN_CHANGE = CURRENT_PATTERN; //will change pattern at next end of measure
      switch_pattern(CURRENT_PATTERN, false); //next measure, but display "-> pattername"
    #endif
    break;

  case 0xFFE01F:  
    if(IR_DEBUG){
      Serial.println("EQ"); 
    }
     #ifdef USE_SOURCE_PATTERN
      switch_pattern(0, true);//test pattern
      //PATTERN_CHANGE = CURRENT_PATTERN; //will not work, cause routine discare PATTERN_CHANGE = 0
    #endif
    break;

  case 0xFFA857: 
    if(IR_DEBUG){ 
      Serial.println("VOL -"); 
    }
    #ifdef USE_SOURCE_PATTERN
    //decrease BPM
    IR_refresh_BPM(false);
    #endif
    break;

  case 0xFF906F:  
    if(IR_DEBUG){
    Serial.println("VOL +"); 
    }
    #ifdef USE_SOURCE_PATTERN
    //increase BPM
    IR_refresh_BPM(true);
    #endif
    break;

  case 0xFF6897:  
    if(IR_DEBUG){
    Serial.println(" 0"); 
    }
    break;

  case 0xFF9867:  
    if(IR_DEBUG){
    Serial.println("Repeat"); 
    }
    #ifdef USE_SOURCE_PATTERN
    //reset lcd display
    lcdReset();
    #endif
    break;

  case 0xFFB04F:  
    if(IR_DEBUG){
    Serial.println(" u/sd"); 
    }
    break;

  case 0xFF30CF:  
    if(IR_DEBUG){
    Serial.println(" 1"); 
    }
    break;

  case 0xFF18E7:  
    if(IR_DEBUG){
    Serial.println(" 2"); 
    }
    break;

  case 0xFF7A85:  
    if(IR_DEBUG){
    Serial.println(" 3"); 
    }
    break;

  case 0xFF10EF:  
    if(IR_DEBUG){
    Serial.println(" 4"); 
    }
    break;

  case 0xFF38C7:  
    if(IR_DEBUG){
    Serial.println(" 5"); 
    }
    break;

  case 0xFF5AA5:  
    if(IR_DEBUG){
    Serial.println(" 6"); 
    }
    break;

  case 0xFF42BD:  
    if(IR_DEBUG){
    Serial.println(" 7"); 
    }
    break;

  case 0xFF4AB5:  
    if(IR_DEBUG){
    Serial.println(" 8"); 
    }
    break;

  case 0xFF52AD:  
    if(IR_DEBUG){
    Serial.println(" 9"); 
    }
    break;

 //FFFFFF is a the normal repeat command, you'll get a stream of them if you hold down a button.
 // in my case that's 4294967295
   case 4294967295:  
     if(IR_DEBUG){
    Serial.println("one more time :)"); 
     }
    break;
    
  default: 
    if(IR_DEBUG){
    Serial.print("not understood : ");
    Serial.println(results.value);
    }
    

  }

  //delay(500);


} //END translateIR

///////////////////////////////////////////////////////////////////// Public Functions /////////////////////

void IR_refresh_BPM(bool inc){ //else dec ...


      if(inc){ //increase one step
        if(BPM + STEP_BPM <= MAX_BPM){
            BPM += STEP_BPM;
        } 
      }else{
        if(BPM - STEP_BPM >= MIN_BPM){
            BPM -= STEP_BPM;
        }
      }

      
      lcdRefreshBPM();
      patternRefreshBPM();
  
}


