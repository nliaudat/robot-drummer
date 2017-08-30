#ifdef USE_SOURCE_MIDI
#include "MIDI.h"
    MIDI_CREATE_DEFAULT_INSTANCE();
#endif


#ifdef USE_SOURCE_MIDI //cannot debug with midi enabled
  static const bool RELAYS_DEBUG_TXT = false;
#else
  static const bool RELAYS_DEBUG_TXT = false; //true only if needed
#endif

static const bool RELAYS_DEBUG_LED = false;

static const int OUT1 =12; //kick drum //bass
static const int OUT2 =11; //snare drum
static const int OUT3 =10; // open hi-hat pedal
static const int OUT4 =9; // hit hi-hat

static const int LED1 =5; 
static const int LED2 =6; 
static const int LED3 =7; 
 
static const int MAX1 =80; //time in millisecond before releasing the kick drum
static const int MAX2 =50;//70; //time in millisecond before releasing the snare drum
static const int MAX3 =90; //time in millisecond before releasing the hi-hat pedal (used only for note 44)
static const int MAX4 =40; //time in millisecond before releasing the hi-hat stick

static const int LED_MAX1 =300; //bass
static const int LED_MAX2 =200; //snare
static const int LED_MAX3 =100; // hi-hat

static const int MAX_ANTI_BURN =5000; // protect motor from burning if activated to long time, especially for hi-hat pedal (my actuator burns frequently :( )

long int hittime1; //millis() value when receiving the note of the kick drum
long int hittime2;
long int hittime3;
long int hittime4;

long int ledtime1; //millis() value when receiving the note of the kick drum
long int ledtime2;
long int ledtime3;

boolean hihatpedal = false; //true if hi-hat was opened by note 44
 
// void HandleNoteOff(byte channel, byte pitch, byte velocity) {
// Note off is currently not handled since the RELAYSs are released with a timeout
// }
 
// This function will be automatically calOUT when a NoteOn is received.
// It must be a void-returning function with the correct parameters,
// see documentation here:
// http://arduinomidilib.sourceforge.net/class_m_i_d_i___class.html

///////////////////////////////////////////////////////////////////// Handle Note (midi or pattern) /////////////////////
 
void HandleNoteOn(byte channel, byte pitch, byte velocity) { //used by midi or patterns source
 // Triggers related RELAYS when receives a Note On.
 // General Midi drumset mapping used:
 // 36 = C2 = Kick drum 1 // bass for me
 // 38 = D2 = Acoustic snare
 // 42 = F#2 = Close Hi-Hat
 // 44 = G#2 = Pedal Hi-Hat
 // 46 = A#2 = Open Hi-hat
 
switch (pitch){
case 36: //Kick drum
 digitalWrite(OUT1, 0); // Note velocity = 127 will set HIGH = 255
 digitalWrite(LED1, 0);
 hittime1 = millis();
 ledtime1 = hittime1;
 
           if(RELAYS_DEBUG_TXT){
              Serial.print("Kick drum : ");
              Serial.println(HIGH, DEC);
          }
          if(RELAYS_DEBUG_LED){
             digitalWrite(13, HIGH); 
          }
 break;
 
case 38: //Snare drum
 digitalWrite(OUT2, 0);
 digitalWrite(LED2, 0);
 hittime2 = millis();
 ledtime2 = hittime2;
 
            if(RELAYS_DEBUG_TXT){
              Serial.print("Snare drum: ");
              Serial.println(HIGH, DEC);
          }
          if(RELAYS_DEBUG_LED){
             digitalWrite(13, HIGH); 
          }
 break;
 
//Hi-Hat will be opened and left open when a "Open Hi-Hat" note is received. It will be closed as soon as a new "Close Hi-Hat" or "Pedal Hi-Hat" note is received.
 
case 42: //Close Hi-Hat
 digitalWrite(OUT3, 255); //if Hi-Hat was open, close it
 digitalWrite(OUT4, 0);
 digitalWrite(LED3, 0);
 hittime4 = millis();
 ledtime3 = hittime4;
 
             if(RELAYS_DEBUG_TXT){
              Serial.print("Close Hi-Hat: ");
              Serial.println(HIGH, DEC);
          }
          if(RELAYS_DEBUG_LED){
             digitalWrite(13, HIGH); 
          }
 break;
 
case 46: //Open Hi-Hat
 digitalWrite(OUT3, 0); //if Hi-Hat was close, open it
 digitalWrite(OUT4, 0);
 digitalWrite(LED3, 0);
 hittime4 = millis();
 ledtime3 = hittime4;
 
              if(RELAYS_DEBUG_TXT){
              Serial.print("Open Hi-Hat: ");
              Serial.println(HIGH, DEC);
          }
          if(RELAYS_DEBUG_LED){
             digitalWrite(13, HIGH); 
          }
 break;
 
case 44: //pedal
 digitalWrite(OUT3, 0);
 digitalWrite(LED3, 0);
 hittime3 = millis();
 hihatpedal = true;
              if(RELAYS_DEBUG_TXT){
              Serial.print("pedal : ");
              Serial.println(HIGH, DEC);
          }
          if(RELAYS_DEBUG_LED){
             digitalWrite(13, HIGH); 
          }
 break;
 
}
 // Try to keep your callbacks short (no delays ect) as the contrary would slow down the loop()
 // and have a bad impact on real-time performance.
}

///////////////////////////////////////////////////////////////////// Setup /////////////////////
void setup_RELAYS() {

   if(RELAYS_DEBUG_TXT){
      Serial.println("RELAYS debug :");
   }
   if(RELAYS_DEBUG_LED){
      pinMode(13, OUTPUT);
   }
  
#ifdef USE_SOURCE_MIDI
 // Initiate MIDI communications, listen to all channels
MIDI.begin(MIDI_CHANNEL_OMNI);
#endif


pinMode(OUT1, OUTPUT);
pinMode(OUT2, OUTPUT);
pinMode(OUT3, OUTPUT);
pinMode(OUT4, OUTPUT);

pinMode(LED1, OUTPUT);
pinMode(LED2, OUTPUT);
pinMode(LED3, OUTPUT);

  CloseAllRelay();


#ifdef USE_SOURCE_MIDI 
 // Connect the HandleNoteOn function to the library, so it is calOUT upon reception of a NoteOn.
 MIDI.setHandleNoteOn(HandleNoteOn); // Put only the name of the function
// MIDI.setHandleNoteOff(HandleNoteOff);
#endif

}


///////////////////////////////////////////////////////////////////// Loop /////////////////////
void loop_RELAYS() {
  
#ifdef USE_SOURCE_MIDI 
  if (MIDI.check() == true){
       if(RELAYS_DEBUG_TXT){
          Serial.println("midi available - pause pattern mode");
       }
    PAUSE_PATTERN = true;
  }else{
       if(RELAYS_DEBUG_TXT){
          Serial.println("midi unavailable - enable pattern mode");
       }
    //PAUSE_PATTERN = false; //set in IR
  }
 // Call MIDI.read the fastest you can for real-time performance.
 MIDI.read();
#endif

long int curtime = millis();
 ////////////////////////
//process actuators
///////////////////////

 // reset the coils after related timeouts
 if (curtime >= (hittime1 + MAX1)) {
 digitalWrite(OUT1, 255);
       if(RELAYS_DEBUG_LED){
          digitalWrite(13, LOW); 
       }
 }
 if (curtime >= (hittime2 + MAX2)) {
 digitalWrite(OUT2, 255);
        if(RELAYS_DEBUG_LED){
          digitalWrite(13, LOW); 
       }
 }
 if (hihatpedal && curtime >= (hittime3 + MAX3)) { //close pedal by timeout only if it was triggered by note 44
 digitalWrite(OUT3, 255);
 hihatpedal = false;
 }
 if (curtime >= (hittime4 + MAX4)) {
 digitalWrite(OUT4, 255);
 }

////////////////////////
// Prevent actuator from burning :)
///////////////////////
//MAX_ANTI_BURN

 if (curtime >= (hittime1 + MAX_ANTI_BURN)) {
 digitalWrite(OUT1, 255);
       if(RELAYS_DEBUG_LED){
          digitalWrite(13, LOW); 
       }
 }
 if (curtime >= (hittime2 + MAX_ANTI_BURN)) {
 digitalWrite(OUT2, 255);
        if(RELAYS_DEBUG_LED){
          digitalWrite(13, LOW); 
       }
 }
 if (hihatpedal && curtime >= (hittime3 + MAX_ANTI_BURN)) {
 digitalWrite(OUT3, 255);
 hihatpedal = false;
 }
 if (curtime >= (hittime4 + MAX_ANTI_BURN)) {
 digitalWrite(OUT4, 255);
 }
 
////////////////////////
//process led strip
///////////////////////

 // reset the coils after related timeouts
 if (curtime >= (ledtime1 + LED_MAX1)) {
 digitalWrite(LED1, 255);
       if(RELAYS_DEBUG_LED){
          digitalWrite(13, LOW); 
       }
 }
 if (curtime >= (ledtime2 + LED_MAX2)) {
 digitalWrite(LED2, 255);
        if(RELAYS_DEBUG_LED){
          digitalWrite(13, LOW); 
       }
 }
 if (curtime >= (ledtime3 + LED_MAX3)) { 
 digitalWrite(LED3, 255);
 }
 
}

void CloseAllRelay(){
  //set all closed
digitalWrite(OUT1, 255);
digitalWrite(OUT2, 255);
digitalWrite(OUT3, 255);
digitalWrite(OUT4, 255);

digitalWrite(LED1, 255);
digitalWrite(LED2, 255);
digitalWrite(LED3, 255);
}


