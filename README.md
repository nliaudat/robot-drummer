# robot-drummer
### An Arduino robotic drummer
*A funny hack for carnival 2015*

This is an automated, self playing drum machine, which can play an external midi source or preloaded patterns.
It uses door lock actuators cause it's strength, low cost and enduring

![alt text](https://github.com/nliaudat/robot-drummer/raw/master/Img_Vid/robot-drummer.jpg "Robot Drum")

## Videos: 
* [Demo 1](https://www.youtube.com/watch?v=v6FhgfrhK6E)
* [Demo 2](https://www.youtube.com/watch?v=c7GqC0ccJ8k)
* [Remote controlled BPM increase](https://www.youtube.com/watch?v=mUgUUxgfKvs)
* [Remote controlled riff change](https://www.youtube.com/watch?v=ctWj6aDz2b4)
* [Hi-Hat cymbal moving](https://www.youtube.com/watch?v=tI9TEDjx_m8)


## Functionalities : 
* Infrared remote control to setup (speed, riff)
* 25 preloaded riffs, based on ascii drum tablatures
* Possible Midi source (not yet available cause Bluetooth module is not finished, midi source is working on lab)
* LCD display
* RGB ledstrip synced with music
* Each hit can be set as loud or normal


## Hardware BOM : 
### Drums
* Hi-hat (with pedal)
* Bass drum
* Snare drum

### Electronics : 
* 4x 12V Door Lock Actuator (2.8$ x 4)
* 1x 8-Channel Relay Module (3.3$)
* 1x Arduino Mega 2560 (7$)
* 1x LCD Display Module [1602] (2.15$)
* 1x Infrared Remote Controller Kit (0.7$)

### Optional : 
* 5V Voltage regulator (DIY manual included in Fritzing schema) (0.5$)
* RGB led strip (5$) (!! Do care : some are +12V and other -12V)

### Usage : 
Plug a 12V battery (cheap chinese lithium are available under 50$)

![alt text](https://github.com/nliaudat/robot-drummer/raw/master/Img_Vid/remote_control.png "IR remote control")

## Construction : 
* "Img_Vid" folder for hardware
* "Arduino" folder for logics
* "Fritzing" folder for wiring and electronic bom
* [Relays and isolation considerations](8-channel_module.md)
* [Voltage regulator (optional but recommended)](voltage_regulator.md)

## Drum tab : 
* [How to make a new onboard riff based on drum tab](Drum-tab/drumtab.md)

## Got inspiration from : 
* [https://vitomakes.wordpress.com/2013/11/22/deep-inside-the-fork-o-drumbot/](https://vitomakes.wordpress.com/2013/11/22/deep-inside-the-fork-o-drumbot/)
* [http://blog.stef.be/drummerbot](http://blog.stef.be/drummerbot)
* [http://www.instructables.com/id/Arduino-Controlled-Robotic-Drum/?ALLSTEPS](http://www.instructables.com/id/Arduino-Controlled-Robotic-Drum/?ALLSTEPS)
* [http://www.instructables.com/id/Make-a-Beat-using-Solenoids/?ALLSTEPS](http://www.instructables.com/id/Make-a-Beat-using-Solenoids/?ALLSTEPS)
* [http://makezine.com/projects/make-robotic-drum-using-arduino-uno/](http://makezine.com/projects/make-robotic-drum-using-arduino-uno/)
* [http://nrqm.ca/robot-drummer/](http://nrqm.ca/robot-drummer/)

