
## Make a new riff based on drum tab : 

### What are drum tabs ?

* https://en.wikipedia.org/wiki/Drum_tablature
* [Explanations] (http://www.cygnusproductions.com/rtp/drums/dtab_explanation.txt)


### Where to find samples ? 

* http://www.drumtabs.org/
* http://www.911tabs.com
* http://drumbum.com/drumtabs/


### How to code for arduino : 

#### Sample code
```
const static char PROGMEM pattern_num[6][36] = { //36 = pattern lenght + 1 null terminator
  "|x-x-o-x-x-o-x-x-|o-x-x-o-x-x-o-x-|", //HH : hit-hat
  "|----o-----o-----|o-----o-----o---|", //SN : snare
  "|o-----o-o-----o-|o-----o-o-----o-|", //BS : bass
// |1eta2eta3eta4eta|1eta2eta3eta4eta|
  "4:4 Bossa nova ",
  "4" //tempo
};
```


### Drumcodes 
```
"-", //nothing
"|", //end of measure
"x", //hit (snare or closed hi-hat)
"o", //hit on open hi-hat
"h", //hit on 1/2 open hi-hat
"p", //hi-hat pedal
"f"};// hit with 2 hands (considered as simple hit)
```

**MAJ letter are for loud, min are for normal**
