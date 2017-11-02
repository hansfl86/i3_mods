#!/bin/bash

DELTA=$1
MAX=$(cat /sys/class/backlight/intel_backlight/max_brightness)
CURRENT=$(cat /sys/class/backlight/intel_backlight/brightness)
echo $DELTA;
echo $MAX;
echo $CURRENT;

let brightness=$CURRENT+$DELTA;
if (($brightness < $MAX)); then
    echo "$brightness" > /sys/class/backlight/intel_backlight/brightness;
fi
