#!/bin/bash

# You might want to change this path according to the position of your avr-gcc tools
# Here i'm using the toolchain included in arduino
TOOLS=$HOME/arduino-1.8.5/hardware/tools/avr/bin

TARGET=atmega328p

if [[ $1 -eq 0 ]] ; then
    echo 'Usage: loadscript.sh source.c /dev/port'
    exit 1
fi
if [[ $2 -eq 0 ]] ; then
    echo 'Usage: loadscript.sh source.c /dev/port'
    exit 1
fi
SOURCE=$1
PORT=$2


$TOOLS/avr-gcc -Wall -Wextra -Wpedantic -mmcu=$TARGET $SOURCE -o tempbin.elf
$TOOLS/avr-objcopy -j .text -j .data -O ihex tempbin.elf tempbin.hex
avrdude -C./avrdude.conf -v -p$TARGET -carduino -P$PORT -b115200 -D -Uflash:w:tempbin.hex:i

rm tempbin.hex tempbin.elf

