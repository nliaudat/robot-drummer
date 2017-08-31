# robot-drummer
### An Arduino robotic drummer
made as project for carnival 2015

[![N|Solid](https://github.com/nliaudat/robot-drummer/raw/master/Img_Vid/robot-drummer.jpg)]

## Functionalities : 
* Infrared remote control to setup (speed, riff)
* 25 preloaded riffs, based on ascii drum tablatures
* Possible Midi source (direct usb connection, cause Bluetooth module is not finished)
* LCD display with BPM
* RGB ledstrip synced with music

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

### Construction : 
* "Img_Vid" folder for hardware
* "Arduino" folder for logics
* "Fritzing" folder for wiring and electronic bom
* [Relays and isolation considerations](8-channel_module.md.md)
* [Voltage regulator (optional but recommended)](voltage_regulator.md)

### Got inspiration from : 
* [https://vitomakes.wordpress.com/2013/11/22/deep-inside-the-fork-o-drumbot/](https://vitomakes.wordpress.com/2013/11/22/deep-inside-the-fork-o-drumbot/)
* [http://blog.stef.be/drummerbot](http://blog.stef.be/drummerbot)
* [http://www.instructables.com/id/Arduino-Controlled-Robotic-Drum/?ALLSTEPS](http://www.instructables.com/id/Arduino-Controlled-Robotic-Drum/?ALLSTEPS)
* [http://www.instructables.com/id/Make-a-Beat-using-Solenoids/?ALLSTEPS](http://www.instructables.com/id/Make-a-Beat-using-Solenoids/?ALLSTEPS)
* [http://makezine.com/projects/make-robotic-drum-using-arduino-uno/](http://makezine.com/projects/make-robotic-drum-using-arduino-uno/)
* [http://nrqm.ca/robot-drummer/](http://nrqm.ca/robot-drummer/)

