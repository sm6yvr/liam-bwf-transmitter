# liam-bwf-transmitter - DIY Robot lawn mover

This project is the code for the charging station/BWF transmitter for your [liam - DIY Robot lawn mower](https://github.com/sm6yvr/liam). 

It will send out a 100µs, then delay 10ms.


    100µs
     __
    |  |
    |  |        10ms
    |  |   ______________
       |  |
       |  |
       |__|

Licensed under GNU GPL 3.0

(c) 2017 Jonas Forssell & team


The signal will be recieved differently by the cutter depending on
if it is inside or outside of the BWF
For this reason, it is important to connect the BWF ends the right
way. Should the cutter think it is outside, try switching the ends.

There are serveral different versions of this shield

1. A standalone shield connected to an aruduino through a cable
   - A standalone shield can be run on higher voltage and has a
     built in voltage converter for the arduino
     This is perfect for larger lawns which requires a strong signal
2. A normal L298 motor shield on an Arduino
   - Easy to put together. Same as for the Liam reciever but max 12V
3. A L293 motor shield on an Arduino
   - A very low cost shield but limited in voltage (12V) and speed
4. A MegaMoto shield on an Arduino
   - Higher cost but very powerful and strong signal with little heat generation

Connector usage
------
The BWF should be connected to motor A or motor 0 on all shields

For the standalone shield (nr 1), pins A0 and A1 should be connected to input pins
for motor 1 on the shield (In1 and In2)


