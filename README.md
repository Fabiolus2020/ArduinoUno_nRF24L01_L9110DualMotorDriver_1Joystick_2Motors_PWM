# ArduinoUno_nRF24L01_L9110DualMotorDriver_1Joystick_2Motors_PWM

This sketch use the L9110 dual motor driver with one joystick and applying PWM for motor speed. This was a bit tricky as I needed to use the analogWrite function to control PWM to one of the pins of the motor while the other pin was to control the direction using DigitalWrite HIGH or LOW.

https://www.instructables.com/Arduino-Uno-and-the-L9110-Motor-Driver-Using-PWM-a/
