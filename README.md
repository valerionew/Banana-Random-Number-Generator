# Banana Random Number Generator
[![License: CC BY-SA 4.0](https://img.shields.io/badge/Hardware%20license-CC--BY--SA%204.0-brightgreen.svg)](http://creativecommons.org/licenses/by-sa/4.0/)  
[![License: GPL v3](https://img.shields.io/badge/Firmware%20license-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)


## Project description 
An Arduino based true random number generator. Takes it's peculiar name from the potassium-40 present in bananas, used as radiation source for the random number generatation.  
  
_Disclaimer: the radioactivity from the bananas doesn't quite make the difference, the background radiation is more than enough to make the generator work and afaik the banana's is not even detectable._

![layout 1](/images/layout.png)

1. [Project status](#project-status)  
1. [Hardware](#hardware)  
1. [Software](#software) 
1. [Enclosure](#enclosure) 

## Project status 
The current released hardware version is fully working. 
The software may need some work
## Hardware 
The hardware is based around the popular ATMega328P and the STS-5 (a.k.a. CTC-5) Geiger-Müller tube.
## Software
I'm currently working on an arduino version on the software, that will be published in this repo as soon as it gives consistent results.
In the future another version of the software which makes use of the hardware as a plain Geiger counter might be release.
## Enclosure
The board is designed to fit in a laser cut acrylic enclosure to protect the user from the high voltage present onboard. 
The enclosure design files are included and licensed under [CC-BY-SA 4.0 license](http://creativecommons.org/licenses/by-sa/4.0/)  
