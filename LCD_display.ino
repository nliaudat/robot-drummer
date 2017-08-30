/*
  LiquidCrystal Library for 1602 LCD with HD44780 controller
  Todo : see at http://playground.arduino.cc/Code/LcdBarGraph to study implementation
 */

// include the library code:
#include <LiquidCrystal.h>


// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(22,23,24,25,26,27);

//bool BPM_blink= false;

//char hit_history[15] = "              " ;
char H_hist[5] = "----" ;
char S_hist[5] = "----" ;
char B_hist[5] = "----" ;


//create custom at https://omerk.github.io/lcdchargen/
byte heart_empty[8] = {
  0b00000,
  0b01010,
  0b10101,
  0b10001,
  0b10001,
  0b01010,
  0b00100,
  0b00000
};


byte heart_full[8] = {
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000
};

byte music_note[8] = {
  0b00010,
  0b00011,
  0b00010,
  0b00010,
  0b01110,
  0b11110,
  0b01100,
  0b00000,
};



byte music_note_inverted[8] = {
  0b11101,
  0b11100,
  0b11101,
  0b11101,
  0b10001,
  0b00001,
  0b10011,
  0b11111
};

/*
byte heart_full_inverted[8] = {
  0b11111,
  0b11111,
  0b00100,
  0b00000,
  0b00000,
  0b00000,
  0b10001,
  0b11011
};
 */


///////////////////////////////////////////////////////////////////// Setup /////////////////////

void setup_lcd() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Ute Viel !");
  
    // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  //lcd.setCursor(0, 1);
  //lcd.print("Les Alienes");
  
  lcd.display();
  
  //we only have 8 locations 0-7 for custom char
  lcd.createChar (0, heart_empty); // load heart_empty to memory 0
  lcd.createChar (1, heart_full); // load heart_full to memory 1
  lcd.createChar (2, music_note); // load music_note to memory 2
  lcd.createChar (3, music_note_inverted); // load music_note to memory 3


  lcdSetupBPM();
  lcdSetupInstrument();

}


void lcdSetupBPM(){


//|___________o=120|
//|________________|


    lcd.setCursor(11, 0);
    //lcd.print(char(0)); 
     // why typecast? see: http://arduino.cc/forum/index.php?topic=74666.0
    lcd.write((uint8_t)0); //display an heart_empty  heart
    lcd.print("=");
    lcd.print(BPM);

}

void lcdSetupInstrument(){


//|paternname o=120|
//|HH:___SN:__BS:__|


    lcd.setCursor(0, 1);
    lcd.print("H---- S----B----");

}

///////////////////////////////////////////////////////////////////// Loop /////////////////////
void loop_lcd() {

}

///////////////////////////////////////////////////////////////////// Private Functions /////////////////////


///////////////////////////////////////////////////////////////////// Public Functions /////////////////////
void lcdRefreshBPM(){

    lcd.setCursor(13, 0);
    //lcd.print(char(0)); 
     // why typecast? see: http://arduino.cc/forum/index.php?topic=74666.0
    //lcd.write((uint8_t)0); //display an heart_empty heart
    //lcd.print("=");
    lcd.print(BPM);
    if(BPM < 100){
      lcd.setCursor(15, 0);
      lcd.print(" ");
    }

}



void lcdBlinkBPM(){

    

    BPM_blink = !BPM_blink;

      if(BPM_blink)
      {   
        lcd.setCursor(11, 0);
        lcd.write((uint8_t)1); //display a filled heart
        lcd.setCursor(12, 0);
        lcd.write((uint8_t)0); //display an empty heart
      }else{
        lcd.setCursor(11, 0);
        lcd.write((uint8_t)0); //display an empty heart
        lcd.setCursor(12, 0);
        lcd.write((uint8_t)1); //display a filled heart
      }

}


void lcdPrintPatternName(char* patname){

//|paternname o=120|
//|________________|
    lcd.setCursor(0, 0);
    lcd.print(patname);
    lcd.setCursor(10, 0); //clear last null char
    lcd.print(" ");
  
}


void lcdPrintInstrumentHit(char instrument, char hit){

//|paternname o=120|
//|HH:XO SN:X BS:X |
// H---- S---- B---
/*
    switch (instrument) {
            case 'H': //hi-hat
              lcd.setCursor(3, 1);
              break;
            case 'S': //snare
              lcd.setCursor(9, 1);
              break;
            case 'B': //bass
              lcd.setCursor(14, 1);
              break;
    }
        //if(hit != '-'){//do not print no note to avoid flickering 
          lcd.print(hit);
        //}
 */ 

 /*
      lcd.setCursor(0, 1);
      //memcpy(&xvals[1], &xvals[0], (width-1)*sizeof(*xvals));
      for(int i=1; i<16; i++) {
          hit_history[i-1] = hit_history[i];
      }

        if(hit == '-'){//do not print no note to avoid flickering 
            hit = ' ';
        }
        
      hit_history[15] = hit;

      lcd.print(hit_history);

 */     

//H---- S---- B----
//char H_hist[4] = "    " ;
//char S_hist[4] = "    " ;
//char B_hist[3] = "   " ;

    switch (instrument) {
            case 'H': //hi-hat
              lcd.setCursor(1, 1);
              for(int i=0; i<5; i++) {
                H_hist[i-1] = H_hist[i];
              }
              H_hist[4] = hit;
              lcd.print(H_hist);
              lcd.setCursor(6, 1); //clear last null char
              lcd.print("S");
              break;
            case 'S': //snare
              lcd.setCursor(7, 1);
              for(int i=0; i<5; i++) {
                S_hist[i-1] = S_hist[i];
              }
              S_hist[4] = hit;
              lcd.print(S_hist);
              lcd.setCursor(11, 1); //clear last null char
              lcd.print("B");
              break;
            case 'B': //bass
              lcd.setCursor(12, 1);
              for(int i=0; i<5; i++) {
                B_hist[i-1] = B_hist[i];
              }
              B_hist[4] = hit;
              lcd.print(B_hist);
              break;
    }
}


void lcdReset(){

    lcd.clear();
    lcd.noDisplay();

  lcdSetupBPM();
  lcdSetupInstrument();

  lcd.display();
  
}

/*
void to_lcd(char txt, bool line2, int pos) {

  lcd.print(txt);
  
}
*/


//http://arduino.stackexchange.com/questions/12034/passing-arguments-to-lcd-print-through-another-function

/*
#define lcdPositionPrint(row,col,content) \
    do { lcd.setCursor(row, col); lcd.print(content); } while (0)

*/
/*
#define lcdPrint(row,col,content) \
    do {LCD.print(content); } while (0)
*/


