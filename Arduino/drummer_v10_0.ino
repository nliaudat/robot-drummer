/*
// *****************************************************************************
//                              robotic drummer
// *****************************************************************************
// 
// Nicolas Liaudat - 2015 - nliaudat[at]gmail(pt)com
//
// Got inspiration from : 
// https://vitomakes.wordpress.com/2013/11/22/deep-inside-the-fork-o-drumbot/
// http://blog.stef.be/drummerbot
// http://www.instructables.com/id/Arduino-Controlled-Robotic-Drum/?ALLSTEPS
// http://www.instructables.com/id/Make-a-Beat-using-Solenoids/?ALLSTEPS
// http://makezine.com/projects/make-robotic-drum-using-arduino-uno/
// http://nrqm.ca/robot-drummer/
//
*/

// can use midi serial source OR/AND preloaded patterns
//#define USE_SOURCE_MIDI
#define USE_SOURCE_PATTERN

      

      //When using the Arduino board with midi in, it’s necessary to set the baudrate to the midi standard of 31250. 
      //Unfortunately, this is a non-default baudrate so the Arduino Serial Monitor cannot display this serial data

#ifdef USE_SOURCE_MIDI //cannot debug with midi enabled
  static const bool MAIN_DEBUG = false;
#else
  static const bool MAIN_DEBUG = true; //if needed
#endif

#ifdef USE_SOURCE_PATTERN
  volatile bool PAUSE_PATTERN = false; //midi running
  //const int PATTERN[6]={1,2,3,4,5,99}; //used in switch_pattern(int num){
  volatile int CURRENT_PATTERN;
  const int MAX_PATTERN_NUM = 25; //not include template num 0
  volatile int BPM = 120;
  volatile bool BPM_blink= false;
#endif

///////////////////////////////////////////////////////////////////// Setup /////////////////////
void setup() {

   if(MAIN_DEBUG){

//#ifdef USE_SOURCE_MIDI
//        
//        Serial.println("MIDI Input : enabled");
//#else
//        Serial.println("MIDI Input : disabled");
//#endif

#ifdef USE_SOURCE_PATTERN
    #ifndef USE_SOURCE_MIDI
            Serial.begin(38400); // 31250 for midi, 38400 for serial debug
              while (!Serial) {
                ; // wait for serial port to connect. Needed for native USB port only
              }
    #endif
        Serial.println("main debug :");
        Serial.println("onboard PATTERNS : enabled");
#else
        Serial.println("onboard PATTERNS : disabled");
#endif
      
   }
  //Serial.begin(9600); 

#ifdef USE_SOURCE_PATTERN
    setup_drum_pattern();
#endif

  //setup_solenoid(); // pattern and midi read if defined
  setup_RELAYS();
  setup_lcd();
  setup_IR();
  //setup_ledstrip();
}

///////////////////////////////////////////////////////////////////// Loop /////////////////////
void loop() {

#ifdef USE_SOURCE_PATTERN
       if(PAUSE_PATTERN == true){
          loop_pattern();
          //loop_potentiometer_bpm();
       }//else{
        //loop_potentiometer_pattern();
       //}
#endif

     //loop_solenoid();
     loop_RELAYS();
     loop_IR();
     
     //loop_analog_buttons();

     
  

}



