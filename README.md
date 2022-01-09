## SoftBeep ##
Reads frequency divider from stdin (the interface act like how you beep on real PC speaker)

## Features ##
1. Any number that valid to scanf's '%d' format 
2. Send EOF to stdin to stop the process 
3. Emulate PC speaker (emulating PIT operating mode)
4. You can control how loud beeps are via your OS volume control panel
5. Only accept whole numbers (yes this features because mimics limitations of PIT)

## Cons ##
1. Beeps very loud

## How to calculate divider ##
(read https://wiki.osdev.org/Programmable_Interval_Timer#The_Oscillator for where 
  the 1193182 number came from)
```
divider = round_nearest(1193182 / frequency)
```

## WARN ##
1. Beeps very loud if you didnt change the volume in control panel before use
   (Recommended volume is 25% for this program. yes im not lying it beep really loud)

