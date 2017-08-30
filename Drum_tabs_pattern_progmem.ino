/*
  // http://www.drumtabs.org/
  // ### Editors
  // http://domoritz.de/drummy/
  // http://whatang.org/
  //
  //
  // ### Samples
  // http://www.911tabs.com
  // http://drumbum.com/drumtabs/
  // http://www.911tabs.com/link/?6671161
*/

/*

  //http://www.cygnusproductions.com/rtp/drums/dtab_explanation.txt

  ## simple
  B = Bass-Drum
  S = Snare-Drum
  H = Hi-Hat
  C = Cymbal
  T = Tom

  ##
  HH|=Hi-Hat SN|=Snare
  BS|=Bass   FT|=Floor Tom
  T1|=Tom 1  C1|=Crash 1

  Cymbal              Hi-Hat           Snare
  C = crash           X = closed       X = hit
  R = ride            O = open         R = rimshot
  B = bell of ride    H = half-open    F = flam
  S = splash          P = with pedal   S = side stick
  T = china (trash)



*/



#ifdef USE_SOURCE_PATTERN



unsigned long INTERVAL = 0;

#ifdef USE_SOURCE_MIDI //cannot debug with midi enabled
static const bool PATTERN_DEBUG = false;
#else
static const bool PATTERN_DEBUG = false; //if needed
#endif



unsigned long previousMillis = 0;
unsigned long currentMillis ;

/// Store data in flash (program) memory instead of SRAM
// https://www.arduino.cc/en/Reference/PROGMEM

#include <avr/pgmspace.h>

//char * drumcode[7] = {"-", //nothing
//                      "|", //end of measure
//                      "x", //hit (snare or closed hi-hat)
//                      "o", //hit on open hi-hat
//                      "h", //hit on 1/2 open hi-hat
//                      "p", //hi-hat pedal
//                      "f"};// hit with 2 hands (considered as simple hit
//
//
//                       MAJ letter are for loud, min are for normal


static const int LOUD = 127;
static const int QUIET = 70;


//const static char PROGMEM pattern_null[6][19] ={ //6 params, 16 tempo char + 2 delimiter + 1 null terminator = 19
//   "|----------------|", //HH : hit-hat
//   "|----------------|", //SN : snare
//   "|----------------|", //BS : bass
// // |1eta2eta3eta4eta|
//   "Empty", //name max 10 chars
//   "4"//tempo : 4:4
//};

const static char PROGMEM pattern_0[6][53] = { //test pattern
  "|x---x---X---X---|o---o---O---O---|p---p---P---P---|", //HH
  "|o---o---O---O---|o-o-o-O-O-OoOoOo|o---o---O---O---|", //SN
  "|o---o---O---O---|o-o-o-O-O-OoOoOo|o---o---O---O---|", //BS
// |1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|
  "Test      ", //name max 10 chars
  "4" //tempo
};

const static char PROGMEM pattern_1[6][19] = {
  "|x-x-x-x-x-x-x-x-|", //HH
  "|----o-------o---|", //SN
  "|o-------o-o-----|", //BS
// |1eta2eta3eta4eta|
  "4:4 [1] 1m", //name
//"1234567890"
  "4" //tempo
};

const static char PROGMEM pattern_2[6][36] = {
  "|--x-x-x-x-x-x-x-|x-x-x-x-x-x-x-x-|", //HH
  "|----o-------o---|----o-o-----o---|", //SN
  "|o-------o-o---o-|--o-----o-o-----|", //BS
// |1eta2eta3eta4eta|1eta2eta3eta4eta|
  "4:4 [2] 2m", //name
//"1234567890"
  "4" //tempo
};


const static char PROGMEM pattern_3[6][36] = { //4:4
  "|x-x-x-x-x-x-x-x-|x-x-x-x-x-x-x-o-|", //HH
  "|----o-------o---|----o-------o---|", //SN
  "|o-o-----o-o---o-|o-o-----o-o-----|", //BS
// |1eta2eta3eta4eta|1eta2eta3eta4eta|
  "4:4 [3] 2m", //name
//"1234567890"
  "4" //tempo
};

const static char PROGMEM pattern_4[6][70] = { //4:4
  "|--x-x-x-x-x-x-x-|x-x-x-x-x-x-x-o-|--x-x-x-x-x-x-x-|x-x-x-x-x-x-x-o-|", //HH
  "|----o-------o---|----o-------o---|----o--o----o---|----o---o---o---|", //SN
  "|o-----o-o-----o-|o-----o-o-o-----|o-o-----o-o-----|o-o---o---o---o-|", //BS
// |1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|
  "4:4 [4] 4m", //name
//"1234567890"
  "4" //tempo
};



const static char PROGMEM pattern_5[6][70] = { //4:4
  "|--x-x-x-x-x-x-x-|x-x-x-x-x-x-x-x-|x-x-x-x-x-x-x-x-|x-x-x-x-x-x-o--P|", //HH
  "|----o-------o---|----o-------o---|----o-------o---|----o-------o---|", //SN
  "|o-o---o---o---o-|--o-----o-o-----|o-o---o---o---o-|--o-----o-o-----|", //BS
// |1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|
  "4:4 [5] 4m", //name
//"1234567890"
  "4" //tempo
};


const static char PROGMEM pattern_6[6][36] = { //4:4
  "|----X---X---X---|X---X---X---X---|", //HH
  "|----o-------o---|----o-------o---|", //SN
  "|o-o---o-o-o---o-|o-o---o-o-o-----|", //BS
// |1eta2eta3eta4eta|1eta2eta3eta4eta|
  "4:4 [6] 2m", //name
//"1234567890"
  "4" //tempo
};


const static char PROGMEM pattern_7[6][19] = { //4:4
  "|X---o---X---o---|", //HH
  "|----o--o-o--o---|", //SN
  "|o--o----o-oo--o-|", //BS
// |1eta2eta3eta4eta|
  "4:4 [7] 1m", //name
//"1234567890"
  "4" //tempo
};

const static char PROGMEM pattern_8[6][19] = { //4:4
  "|X---X---X---X---|", //HH
  "|----o---o---o---|", //SN
  "|o--o---o-o-o--o-|", //BS
// |1eta2eta3eta4eta|
  "4:4 [8] 1m", //name
//"1234567890"
  "4" //tempo
};


const static char PROGMEM pattern_9[6][70] = { //4:4
  "|--X-X-X-X-X-X-X-|X-X-X-X-X-X-X-X-|X-X-X-X-XXX-X-XX|XXXXX-X-XXX-X---|", //HH
  "|------O-----O---|------O-----O--O|------O-----O---|------O-----O-OO|", //SN
  "|O----O-----O----|O----O-----O----|O----O-----O----|O----O-----O-O--|", //BS
// |1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|
  "4:4 [9] 4m", //name
//"1234567890"
  "4" //tempo
};


//Rage Against the Machine : Fistful of Steel
const static char PROGMEM pattern_10[6][70] = { //4:4
  "|x-O---x-x-O-x-O-|x-O-x-x-x-O-x-O-|x-O-x-x-x-O-x-O-|x-x-x-x-x-O-x-O-|", //HH
  "|----o----o--o---|----o----o--o---|----o----o--o---|----o--o----o---|", //SN
  "|o---------o---o-|oo--------o---o-|o---------o---o-|oo-o------o---o-|", //BS
// |1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|
  "4:4 [10]4m", //name
//"1234567890"
  "4" //tempo
};


//Rage Against the Machine : Fistful of Steel
const static char PROGMEM pattern_11[6][70] = { //4:4
  "|x-x-x-x-x-x-x-x-|x-x-x-x-x-x-x-x-|x-x-x-x-x-x-x-x-|x-x-x-x-x-x-x-x-|", //HH
  "|----o-------o---|--o-o-------o---|----o-------o---|--o-o----o--o---|", //SN
  "|o-o---oo--o-----|o-----oo--o-----|o-o---oo--o-----|o-----oo--oo--o-|", //BS
// |1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|
  "4:4 [11]4m", //name
//"1234567890"
  "4" //tempo
};

//Rage Against the Machine : Fistful of Steel
const static char PROGMEM pattern_12[6][70] = { //4:4
  "|--x-x-x-x-x-x-x-|--x-x-x-x-x-x-x-|--x-x-x-x-x-x-x-|--x-x-x-x-x-x-x-|", //HH
  "|----o-------o---|----o---oo--oo--|----o-------o---|----o---oo--oo--|", //SN
  "|--o--o--o--o---o|--o--o-o---o---o|--o--o--o--o---o|--o--o-o---o---o|", //BS
// |1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|
  "4:4 [12]4m", //name
//"1234567890"
  "4" //tempo
};


// Rage Against the Machine : Township Rebellion
const static char PROGMEM pattern_13[6][19] = { //4:4
  "|--o-------o---o-|", //HH
  "|----s-------s---|", //SN
  "|o--o--o---o--o--|", //BS
// |1eta2eta3eta4eta|
  "4:4 [13]1m", //name
//"1234567890"
  "4" //tempo
};


// Rage Against the Machine : Township Rebellion
const static char PROGMEM pattern_14[6][53] = { //4:4
  "|----x---x---x---|x---x---x---x---|x---------------|", //HH
  "|--------o-------|--------o-------|--------o-------|", //SN
  "|o---o-----------|o---o-----------|o---o-----o-o---|", //BS
// |1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|
  "4:4 [14]3m", //name
//"1234567890"
  "4" //tempo
};

// Rage Against the Machine : Township Rebellion
const static char PROGMEM pattern_15[6][36] = { //4:4
  "|------o---------|--o-------o---o-|", //HH
  "|----o-------o---|----o-------o---|", //SN
  "|o--o--o---o--o--|o--o--o---o--o--|", //BS
// |1eta2eta3eta4eta|1eta2eta3eta4eta|
  "4:4 [15]2m", //name
//"1234567890"
  "4" //tempo
};


// Rage Against the Machine : Township Rebellion
const static char PROGMEM pattern_16[6][36] = { //4:4
  "|--o-------X---o-|O-----O--xO---oo|", //HH
  "|----o-------o---|----o-------o---|", //SN
  "|o--o--o---o--o--|o--o--o---o--o--|", //BS
// |1eta2eta3eta4eta|1eta2eta3eta4eta|
  "4:4 [16]2m", //name
//"1234567890"
  "4" //tempo
};

// Rage Against the Machine : Township Rebellion
const static char PROGMEM pattern_17[6][36] = { //4:4
  "|--x-x-x-x-x-x-x-|x-x-x-x-x-x-----|", //HH
  "|----o-------o---|----o-------o---|", //SN
  "|o--o--oo--------|o--o--oo---o--o-|", //BS
// |1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|
  "4:4 [17]2m", //name
//"1234567890"
  "4" //tempo
};

// Rage Against the Machine : Township Rebellion
const static char PROGMEM pattern_18[6][70] = { //4:4
  "|x-x-x-x-x-x-x-O-|x-x-x-x-x-x-x-O-|x-x-x-x-x-x-x-x-|x-x-x-x-x-x-x-O-|", //HH
  "|-o--o--o-o--o--o|-o--o----o--o---|-o--o--o-o--o--o|-o--o----o--o---|", //SN
  "|o--o--o---oo--o-|o--o--oo---o--o-|o--o--o---oo--o-|o--o--oo---o--o-|", //BS
// |1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|
  "4:4 [18]4m", //name
//"1234567890"
  "4" //tempo
};

// Rage Against the Machine : Township Rebellion
const static char PROGMEM pattern_19[6][70] = { //4:4
  "|--x-x-x-x-x-x-x-|x-x-x-x-x-x-----|--x-x-x-x-x-x-x-|x-x-x-x-x---x---|", //HH
  "|----o-------o---|----o-------o---|----o-------o---|----o-------o---|", //SN
  "|o-o-----o-o-----|o-o-----o-o--o--|o-o-----o-o-----|o-o-----o-o--oo-|", //BS
// |1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|
  "4:4 [19]4m", //name
//"1234567890"
  "4" //tempo
};


// Rage Against the Machine : Freedom
const static char PROGMEM pattern_20[6][36] = { //4:4
  "|--x-x---x-x-x-x-|--x-x-----------|", //HH
  "|o--o--o--o--o---|o--o--o-----ooo-|", //SN
  "|--o--o----oo--o-|--o--o---------o|", //BS
// |1eta2eta3eta4eta|1eta2eta3eta4eta|
  "4:4 [20]2m", //name
//"1234567890"
  "4" //tempo
};



// Rage Against the Machine : Settle For Nothing
const static char PROGMEM pattern_21[6][70] = { //4:4
  "|--x-x-x---x-x-x-|--x-x-x-x-x-x-x-|--x---x---x---x-|--x---x-x-x-x-x-|", //HH
  "|----o-------o---|----o---o---o---|o---o---o---o---|o---o-------o---|", //SN
  "|o-o-----o-o-----|o-o----o--oo--o-|o-oo--o-o-oo--o-|o-o----o--oo--o-|", //BS
// |1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|
  "4:4 [21]4m", //name
//"1234567890"
  "4" //tempo
};


const static char PROGMEM pattern_22[6][480] = { //4:4
  "|--x-x-x-x-x-x-x-|x-x-x-x-x-------|--x-x-x-x-x-x-x-|x-x-x-x-x-------|x---x---x---x---|--x-X-X-x-x-X-X-|x-x-X-X-x-x-X---|--x-X-X-x-x-X-X-|x-x-X-X-xxxxxxxx|--x-X-X-x-x-X-X-|x-x-X-X-x-x-X---|--x-X-X-x-x-X-X-|x-x-X-X-XXXXXXXX|--x-X-X-x-x-X-X-|x-x-X-X-x-x-X---|--x-X-X-x-x-X-X-|x-x-X-X-x---x---|x-x-x-x-x-------|--x-x-x-x-x-x-x-|x-x-x-x-x-x-----|--x-x-x-x-x-x-x-|x-x-x-x---------|--x-x-x-x-x-x-x-|x-x-x-x-x-x-----|--x-x-x-x-x-x-x-|x-x-x-x-x-x-x-x-|x-x-x-x-x-------|----------------|", //HH
  "|----o-------o---|----o-------o---|----o-------o---|----o-----------|--------------O-|----o-------o---|----o-------o---|----o-------o---|----o-------o---|----o-------o---|----o-------o---|----o-------o---|----o---o--o--o-|----o-------o---|----o-------o---|----o-------o---|----o-----------|----o-------o---|----o-------o---|----o-------o---|----o-------o---|----o---o-----o-|----o-------o---|----o-------o---|----o-------o---|----o-------o-o-|----o-------o---|----o-----------|", //SN
  "|o-o---oo-oo-----|o-o---oo-oo-o-o-|o-o---oo-oo-----|o-o---oo-oo-----|----------------|o-o-----oo-o----|o-o-----oo-o-o-o|o-o-----oo-o----|o-o-----oooo-ooo|o-o-----oo-o----|o-o-----oo-o-o-o|o-o-----oo-o----|o-o------oo-oo-o|o-o-----oo-o----|o-o-----oo-o-o-o|o-o-----oo-o----|o-o-------------|o-o---oo-oo-o-o-|o-------ooo-----|o--o----oo---ooo|o--o----ooo-----|o--o----o-------|o-------ooo-----|o--o----oo---ooo|o--o----ooo-----|o--o----oo-o-o-o|o-o---oo-oo-o-o-|--o-o-o---------|", //BS
// |1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|
  "RATM[1]28m", //name
//"1234567890"
  "4" //tempo
};

/*
//bad
//Rage Against the Machine : Settle For Nothing
const static char PROGMEM pattern_23[6][206] = { //4:4
  "|----x-------x---|----------------|----x-------x---|x---------------|----x---x---x---|x---------x-x-x-|----x-------x---|----x-------x---|----x---x---x---|x---------x-x-x-|----x-------x---|----x---x------X|", //HH
  "|--------o-------|o---------o-o---|--------o-------|o---------o-o---|----o-------o---|o---------------|--------o-------|--------o---o---|----o-------o---|o---------------|--------o-------|--------o-ooooo-|", //SN
  "|o-o-o-o-------o-|--o-o-o-o-----o-|o-o-o-o-------o-|--o-o-o-o-----o-|o-o---o-o-----o-|--o-o-o-o-----o-|o-o-o-o-------o-|o-o---o-------o-|o-o---o-o-----o-|--o-o-o-o-----o-|o-o-o-o-------o-|o-o-o-o---------|", //BS
// |1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|
  "RATM[2]12m", //name
//"1234567890"
  "4" //tempo
};
*/

//Rage Against the Machine :Take the Power Back
const static char PROGMEM pattern_23[6][240] = { //4:4
  "|--x-x-x-x-x-x-x-|x-x-x-x-x-x-x-x-|x-x-x-x-x-x-x-x-|x-x-x-x-x-x-x-x-|x-x-x-x-x-x-x-x-|--x-x-x-x-x-x-x-|x-x-x-x-x-x-x-x-|x-x-x-x-x-x-x-x-|--x-x-x-x-x-x-x-|x-x-x-x-x-x-x-x-|x-x----X----x---|----------------|----------------|------------x-o-|", //HH
  "|----o-------o---|----o-------o---|----o--o----o---|----o-------o---|----o---o--o--o-|----o-------o---|----o-------o---|----o--o----o---|----o-------o---|----o-------o---|----o-o---------|----o-------o---|----o-------o-oo|----o-----------|", //SN
  "|o-o----o--o--o--|o-o----o--o--o--|o-o-------o--o--|o-o----o--o--o--|o-o----o--o--o--|o-o----o--o--o--|o-o----o--o--o--|o-o-------o--o--|o-o----o--o--o--|o-o----o--o--o--|o-o----o--------|o-o---o-o--o--o-|o-o---oo-o-o----|o-o---o-o-------|", //BS
// |1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|
  "RATM[2]14m", //name
//"1234567890"
  "4" //tempo
};

/*
const static char PROGMEM pattern_25[6][28] = { //4:3 : 2x12 tempo char + 3 delimiter + 1 null terminator = 28
  "|--x-x---x-x-|--x-x-x-x-x-|", //HH
  "|------o-----|------------|", //SN
  "|o-----------|o-----o-----|", //BS
// |1eta2eta3eta|1eta2eta3eta|
  "4:3 [1] 2m", //name
//"1234567890"
  "3" //tempo
};

const static char PROGMEM pattern_26[6][54] = { //4:3
  "|--x-x-x-x-x-|x-x-x-x-x---|--x-x-x-x-x-|--x-x-x-x-x-|", //HH
  "|------o-----|------o-----|------o-----|------o-----|", //SN
  "|o-----------|o---------o-|o-----------|o-----------|", //BS
// |1eta2eta3eta|1eta2eta3eta|1eta2eta3eta|1eta2eta3eta|
  "4:3 [2] 4m", //name
//"1234567890"
  "3" //tempo
};


const static char PROGMEM pattern_27[6][67] = { //4:3
  "|--x-x---x-x-|--x-x-x-x-x-|--x-x---x-x-|--x-x-x-x-x-|--x-x---x-x-|", //HH
  "|------o-----|------------|------o-----|------------|------o-----|", //SN
  "|o-----------|o-----o-----|o-----------|o-----o-----|o-----------|", //BS
// |1eta2eta3eta|1eta2eta3eta|1eta2eta3eta|1eta2eta3eta|1eta2eta3eta|
  "4:3 [3] 5m", //name
//"1234567890"
  "3" //tempo
};

// Rage Against the Machine :Bullet in the Head  //170 BPM
const static char PROGMEM pattern_28[6][43] = { //4:10
  "|x----x----x----x----x----x----x----x----|", //HH
  "|----------o------------o------o---------|", //SN
  "|o----o---------o---------o--------------|", //BS
// |1eta2eta3eta4eta5eta6eta7eta8eta9eta0eta|
  "4:10 [1]1m", //name
//"1234567890"
  "100" //tempo
};

// Rage Against the Machine :Bullet in the Head  //170 BPM
const static char PROGMEM pattern_29[6][84] = { //4:10
  "|-------x---x---------x---x--------------|-------x--------x------x---x---x-------X|", //HH
  "|-o--o--------o-----o---o---o---o--------|-o--o-----o--o-------o---o---o----o-----|", //SN
  "|-------o---o---------o---o---------o----|-------o--------o------o---o---o-------o|", //BS
// |1eta2eta3eta4eta5eta6eta7eta8eta9eta0eta|1eta2eta3eta4eta5eta6eta7eta8eta9eta0eta|
  "4:10 [2]2m", //name
//"1234567890"
  "100" //tempo
};
*/

const static char PROGMEM pattern_24[6][138] = { //4:4
  "|--x-X-X-x-x-X-X-|x-O-X-X-x-x-X---|--x-X-X-x-x-O-X-|x-x-X-X-xxxxxxxx|--O-X-X-x-x-X-X-|x-x-X-X-x-x-O--X|--x-X-X-x-x-X-X-|x-x-X-X-O-X--X-X|", //HH
  "|-o--o--o--o-o--o|o---o--o--o-o---|----o-------o---|----o---o---o---|----o---oo--o---|----o-o-o---o---|----o-------o---|----o---o--o--o-|", //SN
  "|o-o-----oo-o----|o-o-----oo-o-o-o|o-o-----oo-o----|o-o-----oooo-ooo|o-o-----oo-o----|o-o-----oo-o-o-o|o-o-----oo-o----|o-o------oo-oo-o|", //BS
// |1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|
  "4:4 [NL]8m",
  "4" //tempo
};

const static char PROGMEM pattern_25[6][36] = { //4:4
  "|x-x-o-x-x-o-x-x-|o-x-x-o-x-x-o-x-|", //HH
  "|----o-----o-----|o-----o-----o---|", //SN
  "|o-----o-o-----o-|o-----o-o-----o-|", //BS
// |1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|1eta2eta3eta4eta|
  "4:4 Bossa ",
  "4" //tempo
};


//http://www.avrfreaks.net/forum/array-arrays-flash-using-progmem


//const char* const string_table[6] PROGMEM = {pattern_1, pattern_2, pattern_3, pattern_4, pattern_5};
const char *PATTERN_pointer_array[MAX_PATTERN_NUM] = {*pattern_1,*pattern_2,*pattern_3,*pattern_4,*pattern_5,
                                        *pattern_6,*pattern_7,*pattern_8,*pattern_9,*pattern_10,
                                        *pattern_11,*pattern_12,*pattern_13,*pattern_14,*pattern_15,
                                        *pattern_16,*pattern_17,*pattern_18,*pattern_19,*pattern_20,
                                        *pattern_21,*pattern_22,*pattern_23,*pattern_24//,*pattern_25,
                                        //*pattern_26,*pattern_27,*pattern_28,*pattern_29,*pattern_30
                                        };




volatile int PATTERN_LEN; //total lenght of command chars included separators and null terminator
volatile int PATTERN_TEMPO;
//volatile int PATTERN_NUM_MEASURE;
char PATTERN_NAME[10];

volatile int PATTERN_NUM;
volatile int PATTERN_CHANGE = 0;

volatile int CUR_POS; //current note to be parsed
char HH;
char SN;
char BS;

///////////////////////////////////////////////////////////////////// Setup /////////////////////
// called only if #ifdef USE_SOURCE_PATTERN
void setup_drum_pattern() {

  if (PATTERN_DEBUG) {
    Serial.println("Pattern debug :");
  }
  //CUR_POS = 0; //current note from pattern to play //do not start at 0 since it's "|"
  switch_pattern(0, true); //test pattern
  //CURRENT_PATTERN = 5;

  //lcdPrintPatternName(PATTERN_NAME);

}


/////////////////////////////////////////////////////////////////////// helper functions ///////////////////
/*
//do not work :( why ? 
void read_pattern_on_switch(int patnum){
  
    // Using the string table in program memory requires the use of special functions to retrieve the data.

     PATTERN_LEN = strlen_P(&PATTERN_pointer_array[patnum][0]);
     get_PATTERN_NAME(&PATTERN_pointer_array[patnum][3]);
     PATTERN_TEMPO = (int)pgm_read_byte_near(&PATTERN_pointer_array[patnum][4]) - '0'; //one char only, converted to int by - '0';
}


void read_pattern_on_process(int patnum){

    // Using the string table in program memory requires the use of special functions to retrieve the data.

      HH = pgm_read_byte_near(&PATTERN_pointer_array[patnum][0] + CUR_POS);
      SN = pgm_read_byte_near(&PATTERN_pointer_array[patnum][1] + CUR_POS);
      BS = pgm_read_byte_near(&PATTERN_pointer_array[patnum][2] + CUR_POS);
}

*/
///////////////////////////////////////////////////////////////////// Switch Pattern /////////////////////
void switch_pattern(int num, bool now) { //pattern num, now = immediately (else end of measure)
  if (now == true) {
    PATTERN_NUM = num;
    CUR_POS = 0;
    PATTERN_CHANGE = 0; //set to no change
  }


    //read_pattern_on_switch(num);


  switch (num) {
    case 0: //test pattern
      PATTERN_LEN = strlen_P(pattern_0[0]);
      get_PATTERN_NAME(pattern_0[3]);
      PATTERN_TEMPO = (int)pgm_read_byte_near(pattern_0[4]) - '0'; //one char only, converted to int by - '0';
      break;
    case 1:
      PATTERN_LEN = strlen_P(pattern_1[0]);
      get_PATTERN_NAME(pattern_1[3]);
      PATTERN_TEMPO = (int)pgm_read_byte_near(pattern_1[4]) - '0'; //one char only, converted to int by - '0';
      break;
    case 2:
      PATTERN_LEN = strlen_P(pattern_2[0]);
      get_PATTERN_NAME(pattern_2[3]);
      PATTERN_TEMPO = (int)pgm_read_byte_near(pattern_2[4]) - '0'; //one char only, converted to int by - '0';
      break;
    case 3:
      PATTERN_LEN = strlen_P(pattern_3[0]);
      get_PATTERN_NAME(pattern_3[3]);
      PATTERN_TEMPO = (int)pgm_read_byte_near(pattern_3[4]) - '0'; //one char only, converted to int by - '0';
      break;
    case 4:
      PATTERN_LEN = strlen_P(pattern_4[0]);
      get_PATTERN_NAME(pattern_4[3]);
      PATTERN_TEMPO = (int)pgm_read_byte_near(pattern_4[4]) - '0'; //one char only, converted to int by - '0';
      break;
    case 5:
      PATTERN_LEN = strlen_P(pattern_5[0]);
      get_PATTERN_NAME(pattern_5[3]);
      PATTERN_TEMPO = (int)pgm_read_byte_near(pattern_5[4]) - '0'; //one char only, converted to int by - '0';
      break;
    case 6:
      PATTERN_LEN = strlen_P(pattern_6[0]);
      get_PATTERN_NAME(pattern_6[3]);
      PATTERN_TEMPO = (int)pgm_read_byte_near(pattern_6[4]) - '0'; //one char only, converted to int by - '0';
      break;

    case 7:
      PATTERN_LEN = strlen_P(pattern_7[0]);
      get_PATTERN_NAME(pattern_7[3]);
      PATTERN_TEMPO = (int)pgm_read_byte_near(pattern_7[4]) - '0'; //one char only, converted to int by - '0';
      break;

    case 8:
      PATTERN_LEN = strlen_P(pattern_8[0]);
      get_PATTERN_NAME(pattern_8[3]);
      PATTERN_TEMPO = (int)pgm_read_byte_near(pattern_8[4]) - '0'; //one char only, converted to int by - '0';
      break;

    case 9:
      PATTERN_LEN = strlen_P(pattern_9[0]);
      get_PATTERN_NAME(pattern_9[3]);
      PATTERN_TEMPO = (int)pgm_read_byte_near(pattern_9[4]) - '0'; //one char only, converted to int by - '0';
      break;

    case 10:
      PATTERN_LEN = strlen_P(pattern_10[0]);
      get_PATTERN_NAME(pattern_10[3]);
      PATTERN_TEMPO = (int)pgm_read_byte_near(pattern_10[4]) - '0'; //one char only, converted to int by - '0';
      break;

    case 11:
      PATTERN_LEN = strlen_P(pattern_11[0]);
      get_PATTERN_NAME(pattern_11[3]);
      PATTERN_TEMPO = (int)pgm_read_byte_near(pattern_11[4]) - '0'; //one char only, converted to int by - '0';
      break;

    case 12:
      PATTERN_LEN = strlen_P(pattern_12[0]);
      get_PATTERN_NAME(pattern_12[3]);
      PATTERN_TEMPO = (int)pgm_read_byte_near(pattern_12[4]) - '0'; //one char only, converted to int by - '0';
      break;
    
    case 13:
      PATTERN_LEN = strlen_P(pattern_13[0]);
      get_PATTERN_NAME(pattern_13[3]);
      PATTERN_TEMPO = (int)pgm_read_byte_near(pattern_13[4]) - '0'; //one char only, converted to int by - '0';
      break;
    
    case 14:
      PATTERN_LEN = strlen_P(pattern_14[0]);
      get_PATTERN_NAME(pattern_14[3]);
      PATTERN_TEMPO = (int)pgm_read_byte_near(pattern_14[4]) - '0'; //one char only, converted to int by - '0';
      break;
    
    case 15:
      PATTERN_LEN = strlen_P(pattern_15[0]);
      get_PATTERN_NAME(pattern_15[3]);
      PATTERN_TEMPO = (int)pgm_read_byte_near(pattern_15[4]) - '0'; //one char only, converted to int by - '0';
      break;
    
    case 16:
      PATTERN_LEN = strlen_P(pattern_16[0]);
      get_PATTERN_NAME(pattern_16[3]);
      PATTERN_TEMPO = (int)pgm_read_byte_near(pattern_16[4]) - '0'; //one char only, converted to int by - '0';
      break;
    
    case 17:
      PATTERN_LEN = strlen_P(pattern_17[0]);
      get_PATTERN_NAME(pattern_17[3]);
      PATTERN_TEMPO = (int)pgm_read_byte_near(pattern_17[4]) - '0'; //one char only, converted to int by - '0';
      break;
    
    case 18:
      PATTERN_LEN = strlen_P(pattern_18[0]);
      get_PATTERN_NAME(pattern_18[3]);
      PATTERN_TEMPO = (int)pgm_read_byte_near(pattern_18[4]) - '0'; //one char only, converted to int by - '0';
      break;
    
    case 19:
      PATTERN_LEN = strlen_P(pattern_19[0]);
      get_PATTERN_NAME(pattern_19[3]);
      PATTERN_TEMPO = (int)pgm_read_byte_near(pattern_19[4]) - '0'; //one char only, converted to int by - '0';
      break;
    
    case 20:
      PATTERN_LEN = strlen_P(pattern_20[0]);
      get_PATTERN_NAME(pattern_20[3]);
      PATTERN_TEMPO = (int)pgm_read_byte_near(pattern_20[4]) - '0'; //one char only, converted to int by - '0';
      break;
    
    case 21:
      PATTERN_LEN = strlen_P(pattern_21[0]);
      get_PATTERN_NAME(pattern_21[3]);
      PATTERN_TEMPO = (int)pgm_read_byte_near(pattern_21[4]) - '0'; //one char only, converted to int by - '0';
      break;
    
    case 22:
      PATTERN_LEN = strlen_P(pattern_22[0]);
      get_PATTERN_NAME(pattern_22[3]);
      PATTERN_TEMPO = (int)pgm_read_byte_near(pattern_22[4]) - '0'; //one char only, converted to int by - '0';
      break;
    
    case 23:
      PATTERN_LEN = strlen_P(pattern_23[0]);
      get_PATTERN_NAME(pattern_23[3]);
      PATTERN_TEMPO = (int)pgm_read_byte_near(pattern_23[4]) - '0'; //one char only, converted to int by - '0';
      break;
    
    case 24:
      PATTERN_LEN = strlen_P(pattern_24[0]);
      get_PATTERN_NAME(pattern_24[3]);
      PATTERN_TEMPO = (int)pgm_read_byte_near(pattern_24[4]) - '0'; //one char only, converted to int by - '0';
      break;
   
    case 25:
      PATTERN_LEN = strlen_P(pattern_25[0]);
      get_PATTERN_NAME(pattern_25[3]);
      PATTERN_TEMPO = (int)pgm_read_byte_near(pattern_25[4]) - '0'; //one char only, converted to int by - '0';
      break;
 /*    
    case 26:
      PATTERN_LEN = strlen_P(pattern_26[0]);
      get_PATTERN_NAME(pattern_26[3]);
      PATTERN_TEMPO = (int)pgm_read_byte_near(pattern_26[4]) - '0'; //one char only, converted to int by - '0';
      break;
    
    case 27:
      PATTERN_LEN = strlen_P(pattern_27[0]);
      get_PATTERN_NAME(pattern_27[3]);
      PATTERN_TEMPO = (int)pgm_read_byte_near(pattern_27[4]) - '0'; //one char only, converted to int by - '0';
      break;
    
    case 28:
      PATTERN_LEN = strlen_P(pattern_28[0]);
      get_PATTERN_NAME(pattern_28[3]);
      PATTERN_TEMPO = (int)pgm_read_byte_near(pattern_28[4]) - '0'; //one char only, converted to int by - '0';
      break;
    
    case 29:
      PATTERN_LEN = strlen_P(pattern_29[0]);
      get_PATTERN_NAME(pattern_29[3]);
      PATTERN_TEMPO = (int)pgm_read_byte_near(pattern_29[4]) - '0'; //one char only, converted to int by - '0';
      break;

    case 30:
      PATTERN_LEN = strlen_P(pattern_30[0]);
      get_PATTERN_NAME(pattern_30[3]);
      PATTERN_TEMPO = (int)pgm_read_byte_near(pattern_30[4]) - '0'; //one char only, converted to int by - '0';
      break;
*/
      //            default:
      //              // if nothing else matches, do the default
      //              PATTERN_LEN = strlen_P(pattern_null[0]);
      //            break;
  }


  //set new INTERVAL
  //70 miliseconds of eacht "beat" 125 = 500 miliseconds for a beat = 120 bpm
  // 110 bpm: (60000/110)/4 = 136 (110,29 bpm)
  // 100 bpm: (60000/100)/4 = 150
  // 130 ms ->  115,38
  if (now == true) {
    patternRefreshBPM();
    // INTERVAL = (60000/BPM)/(PATTERN_TEMPO)/4;
    //4:4 = 1eta2eta3eta4eta = 4*4
    //4:3 = 1eta2eta3eta = 4*3

    if (PATTERN_DEBUG) {
      Serial.print("PATTERN_NUM : ");
      Serial.println(num, DEC);
      Serial.print("PATTERN_LEN : ");
      Serial.println(PATTERN_LEN, DEC);
      Serial.print("PATTERN_NAME : ");
      Serial.println(PATTERN_NAME);
      Serial.print("PATTERN_TEMPO : ");
      Serial.println(PATTERN_TEMPO);
      Serial.print("INTERVAL : ");
      Serial.println(INTERVAL);
    }

    lcdPrintPatternName(PATTERN_NAME);

  } else {
    PATTERN_NAME[8] = '-'; // going to 
    PATTERN_NAME[9] = '>';
    lcdPrintPatternName(PATTERN_NAME);

  }

}


void patternRefreshBPM() {

  INTERVAL = (60000 / BPM) / (PATTERN_TEMPO); // /4;
  //4:4 = 1eta2eta3eta4eta = 4*4
  //4:3 = 1eta2eta3eta = 4*3
}


///////////////////////////////////////////////////////////////////// Loop /////////////////////
// called only if #ifdef USE_SOURCE_PATTERN
void loop_pattern() {

  //if(PAUSE_PATTERN == true){
  //  return;
  //}

  currentMillis = millis();

  if (currentMillis - previousMillis >= INTERVAL) {

    previousMillis = currentMillis;

    process_pattern();

  }


}


///////////////////////////////////////////////////////////////////// Process Patern /////////////////////
void process_pattern() {

  CUR_POS++; //do not start at 0 since it's "|"
  if (CUR_POS >= PATTERN_LEN) {
    CUR_POS = 1; //loop pattern //do not start at 0 since it's "|"
    if (PATTERN_DEBUG) {
      Serial.println();
    }
  }

  if ((CUR_POS % PATTERN_TEMPO) == 0) { //on tempo :) lcd blinked heart
    //if(BPM_blink){
    lcdBlinkBPM();
    if (PATTERN_DEBUG) {
      Serial.print("+");
    }
    //}

  }

  //if(PATTERN_DEBUG){
  //    Serial.print(CUR_POS);
  //}

  // Using the string table in program memory requires the use of special functions to retrieve the data.
  // The strcpy_P, strlen_P, etc, function copies a string from program space to a string in RAM ("buffer").
  // Make sure your receiving string in RAM  is large enough to hold whatever you are retrieving from program space.

  //  read_pattern_on_process(PATTERN_NUM);

  switch (PATTERN_NUM) {

    //read the char at current position directly from flash memory
    //only 1 char is set in RAM
    case 0: //test pattern
      HH = pgm_read_byte_near(pattern_0[0] + CUR_POS);
      SN = pgm_read_byte_near(pattern_0[1] + CUR_POS);
      BS = pgm_read_byte_near(pattern_0[2] + CUR_POS);
      break;
    case 1:
      HH = pgm_read_byte_near(pattern_1[0] + CUR_POS);
      SN = pgm_read_byte_near(pattern_1[1] + CUR_POS);
      BS = pgm_read_byte_near(pattern_1[2] + CUR_POS);
      break;
    case 2:
      HH = pgm_read_byte_near(pattern_2[0] + CUR_POS);
      SN = pgm_read_byte_near(pattern_2[1] + CUR_POS);
      BS = pgm_read_byte_near(pattern_2[2] + CUR_POS);
      break;
    case 3:
      HH = pgm_read_byte_near(pattern_3[0] + CUR_POS);
      SN = pgm_read_byte_near(pattern_3[1] + CUR_POS);
      BS = pgm_read_byte_near(pattern_3[2] + CUR_POS);
      break;
    case 4:
      HH = pgm_read_byte_near(pattern_4[0] + CUR_POS);
      SN = pgm_read_byte_near(pattern_4[1] + CUR_POS);
      BS = pgm_read_byte_near(pattern_4[2] + CUR_POS);
      break;
    case 5:
      HH = pgm_read_byte_near(pattern_5[0] + CUR_POS);
      SN = pgm_read_byte_near(pattern_5[1] + CUR_POS);
      BS = pgm_read_byte_near(pattern_5[2] + CUR_POS);
      break;
    case 6:
      HH = pgm_read_byte_near(pattern_6[0] + CUR_POS);
      SN = pgm_read_byte_near(pattern_6[1] + CUR_POS);
      BS = pgm_read_byte_near(pattern_6[2] + CUR_POS);
      break;

    case 7:
      HH = pgm_read_byte_near(pattern_7[0] + CUR_POS);
      SN = pgm_read_byte_near(pattern_7[1] + CUR_POS);
      BS = pgm_read_byte_near(pattern_7[2] + CUR_POS);
      break;

    case 8:
      HH = pgm_read_byte_near(pattern_8[0] + CUR_POS);
      SN = pgm_read_byte_near(pattern_8[1] + CUR_POS);
      BS = pgm_read_byte_near(pattern_8[2] + CUR_POS);
      break;

    case 9:
      HH = pgm_read_byte_near(pattern_9[0] + CUR_POS);
      SN = pgm_read_byte_near(pattern_9[1] + CUR_POS);
      BS = pgm_read_byte_near(pattern_9[2] + CUR_POS);
      break;

    case 10:
      HH = pgm_read_byte_near(pattern_10[0] + CUR_POS);
      SN = pgm_read_byte_near(pattern_10[1] + CUR_POS);
      BS = pgm_read_byte_near(pattern_10[2] + CUR_POS);
      break;

    case 11:
      HH = pgm_read_byte_near(pattern_11[0] + CUR_POS);
      SN = pgm_read_byte_near(pattern_11[1] + CUR_POS);
      BS = pgm_read_byte_near(pattern_11[2] + CUR_POS);
      break;

    case 12:
      HH = pgm_read_byte_near(pattern_12[0] + CUR_POS);
      SN = pgm_read_byte_near(pattern_12[1] + CUR_POS);
      BS = pgm_read_byte_near(pattern_12[2] + CUR_POS);
      break;
    
    case 13:
      HH = pgm_read_byte_near(pattern_13[0] + CUR_POS);
      SN = pgm_read_byte_near(pattern_13[1] + CUR_POS);
      BS = pgm_read_byte_near(pattern_13[2] + CUR_POS);
      break;
    
    case 14:
      HH = pgm_read_byte_near(pattern_14[0] + CUR_POS);
      SN = pgm_read_byte_near(pattern_14[1] + CUR_POS);
      BS = pgm_read_byte_near(pattern_14[2] + CUR_POS);
      break;
    
    case 15:
      HH = pgm_read_byte_near(pattern_15[0] + CUR_POS);
      SN = pgm_read_byte_near(pattern_15[1] + CUR_POS);
      BS = pgm_read_byte_near(pattern_15[2] + CUR_POS);
      break;
    
    case 16:
      HH = pgm_read_byte_near(pattern_16[0] + CUR_POS);
      SN = pgm_read_byte_near(pattern_16[1] + CUR_POS);
      BS = pgm_read_byte_near(pattern_16[2] + CUR_POS);
      break;
    
    case 17:
      HH = pgm_read_byte_near(pattern_17[0] + CUR_POS);
      SN = pgm_read_byte_near(pattern_17[1] + CUR_POS);
      BS = pgm_read_byte_near(pattern_17[2] + CUR_POS);
      break;
    
    case 18:
      HH = pgm_read_byte_near(pattern_18[0] + CUR_POS);
      SN = pgm_read_byte_near(pattern_18[1] + CUR_POS);
      BS = pgm_read_byte_near(pattern_18[2] + CUR_POS);
      break;
    
    case 19:
      HH = pgm_read_byte_near(pattern_19[0] + CUR_POS);
      SN = pgm_read_byte_near(pattern_19[1] + CUR_POS);
      BS = pgm_read_byte_near(pattern_19[2] + CUR_POS);
      break;
      
    case 20:
      HH = pgm_read_byte_near(pattern_20[0] + CUR_POS);
      SN = pgm_read_byte_near(pattern_20[1] + CUR_POS);
      BS = pgm_read_byte_near(pattern_20[2] + CUR_POS);
      break;
    
    case 21:
      HH = pgm_read_byte_near(pattern_21[0] + CUR_POS);
      SN = pgm_read_byte_near(pattern_21[1] + CUR_POS);
      BS = pgm_read_byte_near(pattern_21[2] + CUR_POS);
      break;
    
    case 22:
      HH = pgm_read_byte_near(pattern_22[0] + CUR_POS);
      SN = pgm_read_byte_near(pattern_22[1] + CUR_POS);
      BS = pgm_read_byte_near(pattern_22[2] + CUR_POS);
      break;
    
    case 23:
      HH = pgm_read_byte_near(pattern_23[0] + CUR_POS);
      SN = pgm_read_byte_near(pattern_23[1] + CUR_POS);
      BS = pgm_read_byte_near(pattern_23[2] + CUR_POS);
      break;
    
    case 24:
      HH = pgm_read_byte_near(pattern_24[0] + CUR_POS);
      SN = pgm_read_byte_near(pattern_24[1] + CUR_POS);
      BS = pgm_read_byte_near(pattern_24[2] + CUR_POS);
      break;


    case 25:
      HH = pgm_read_byte_near(pattern_25[0] + CUR_POS);
      SN = pgm_read_byte_near(pattern_25[1] + CUR_POS);
      BS = pgm_read_byte_near(pattern_25[2] + CUR_POS);
      break;
 /*    
    case 26:
      HH = pgm_read_byte_near(pattern_26[0] + CUR_POS);
      SN = pgm_read_byte_near(pattern_26[1] + CUR_POS);
      BS = pgm_read_byte_near(pattern_26[2] + CUR_POS);
      break;
    
    case 27:
      HH = pgm_read_byte_near(pattern_27[0] + CUR_POS);
      SN = pgm_read_byte_near(pattern_27[1] + CUR_POS);
      BS = pgm_read_byte_near(pattern_27[2] + CUR_POS);
      break;
    
    case 28:
      HH = pgm_read_byte_near(pattern_28[0] + CUR_POS);
      SN = pgm_read_byte_near(pattern_28[1] + CUR_POS);
      BS = pgm_read_byte_near(pattern_28[2] + CUR_POS);
      break;
    
    case 29:
      HH = pgm_read_byte_near(pattern_29[0] + CUR_POS);
      SN = pgm_read_byte_near(pattern_29[1] + CUR_POS);
      BS = pgm_read_byte_near(pattern_29[2] + CUR_POS);
      break;

    case 30:
      HH = pgm_read_byte_near(pattern_30[0] + CUR_POS);
      SN = pgm_read_byte_near(pattern_30[1] + CUR_POS);
      BS = pgm_read_byte_near(pattern_30[2] + CUR_POS);
      break;
  
*/
      //            default:
      //                    HH = pgm_read_byte_near(pattern_null[0] + CUR_POS);
      //                    SN = pgm_read_byte_near(pattern_null[1] + CUR_POS);
      //                    BS = pgm_read_byte_near(pattern_null[2] + CUR_POS);
      //            break;
  }


  if (HH == '\0') { //char is null terminated, so do not process
    //return;
    process_pattern(); //recall the function (cause next interval is too late)
  }

  //Serial.print(HH);
  //Serial.print(SN);
  //Serial.print(BS);


  if (HH == '|') { //start or end of measure
    if (PATTERN_DEBUG) {
      Serial.print("|"); //end of measure
    }
    //change pattern only if end of measure
    if (PATTERN_CHANGE > 0) {
      switch_pattern(PATTERN_CHANGE, true);//immediately
    }

    //lcdBlinkBPM();

    //return;
    process_pattern(); //recall the function (cause next interval is too late)
  }




  // 36 = C2 = Kick drum 1
  // 38 = D2 = Acoustic snare
  // 42 = F#2 = Close Hi-Hat
  // 44 = G#2 = Pedal Hi-Hat
  // 46 = A#2 = Open Hi-hat

  //Velocity 0 to 127 range.

  // HandleNoteOn(byte channel, byte pitch, byte velocity) {




  //// Hit hat
  switch (HH) {
    //case '-': //nothing
    //  break;
    case 'x': //hi-hat closed quiet
      //                    if(PATTERN_DEBUG){
      //                        Serial.print("hi-hat closed quiet");
      //                    }
      HandleNoteOn(0, 42, QUIET);

      break;
    case 'X': //hi-hat closed loud
      //                    if(PATTERN_DEBUG){
      //                        Serial.print("hi-hat closed loud");
      //                    }
      HandleNoteOn(0, 42, LOUD);
      break;
    case 'o': //hi-hat open quiet
      //                    if(PATTERN_DEBUG){
      //                        Serial.print("hi-hat open quiet");
      //                    }
      HandleNoteOn(0, 46, QUIET);
      break;
    case 'O': //hi-hat open loud
      //                    if(PATTERN_DEBUG){
      //                        Serial.print("hi-hat open loud");
      //                    }
      HandleNoteOn(0, 46, LOUD);
      break;
    case 'p': //hi-hat pedal quiet
      //                    if(PATTERN_DEBUG){
      //                        Serial.print("hi-hat pedal quiet");
      //                    }
      HandleNoteOn(0, 44, QUIET);
      break;
    case 'P': //hi-hat pedal loud
      //                    if(PATTERN_DEBUG){
      //                        Serial.print("hi-hat pedal loud");
      //                    }
      HandleNoteOn(0, 44, LOUD);
      break;
  }


  //// snare
  switch (SN) {
    case 'o': //snare quiet
      //                    if(PATTERN_DEBUG){
      //                        Serial.print("snare quiet");
      //                    }
      HandleNoteOn(0, 38, QUIET);
      break;
    case 'O': //snare loud
      //                    if(PATTERN_DEBUG){
      //                        Serial.print("snare loud");
      //                    }
      HandleNoteOn(0, 38, LOUD);
  }

  //// Bass
  switch (BS) {
    case 'o': //bass quiet
      //                    if(PATTERN_DEBUG){
      //                        Serial.print("bass quiet");
      //                    }
      HandleNoteOn(0, 36, QUIET);
      break;
    case 'O': //bass loud
      //                    if(PATTERN_DEBUG){
      //                        Serial.print("bass loud");
      //                    }
      HandleNoteOn(0, 36, LOUD);
  }

  // delay(INTERVAL);

  lcdPrintInstrumentHit('H', HH);
  lcdPrintInstrumentHit('S', SN);
  lcdPrintInstrumentHit('B', BS);



}

//////////////////////////////////////////////////////////// helpers
char* get_PATTERN_NAME(const char* str) {
  strcpy_P(PATTERN_NAME, (char*)str);
  return PATTERN_NAME;
}

#endif //#ifdef USE_SOURCE_PATTERN



