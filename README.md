# Read_Object_Distance_Microcontroller_ATMEGA328p
Read the distance of an object by using an ultrasonic sensors

This code is used to read the distance (expressed in cm) of objects by using an Ultrasonic sensor. 

These two simple files are used to have two arduino UNO (Microchip: ATMEGA328p) boards communicate with one another via USART. While I am aware that what I am posting is something very basic, I hope it can be of some help to people new to microcontrollers. You will need two arduino boards to execute this code and the ATMEL ICE to burn the code provided in the file named "Distance_ATMEL", as that code was written in Microchip Studio. Alternatively, you can obviously have one arduino board and buy an ATMEGA328p microcontroller and use it on your own board.

1) The file namedd "Arduino.cpp" is used to have the first arduino board (AB1) to plot the distance;

2) The file named "Distance_ATMEL" is used to set the USART in the second arduino board (AB2) and to calcualte the distance of the object. If the object is < 10 cm, then a LED connected to PD6 will start fleshing, otherwise another LED connected to PD5 will start fleshing. This code was written in Microchip Studio and was burnt into ATMEGA328p by using ATMEL ICE.

The Ultrasound sensor (HC-SR04) has 4 pins: Vcc, GND, Trig and Echo. The trig needs to be high for 10us for the sensor to send a 40 kHz sound. After those 10us, the pin Echo will read the sound bouncing back from the object.

I hope that this code can be useful to someone.

If you have any questions and/or want to report bugs, please e-mail me (Ale) at: pressalex@hotmail.com
