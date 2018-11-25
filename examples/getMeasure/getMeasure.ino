/*
 * getDistance
 *
 * Example of using SharpIR library to calculate the distance beetween the sensor and an obstacle
 *
 * Created by Giuseppe Masino, 15 June 2016
 *
 * -----------------------------------------------------------------------------------
 *
 * Things that you need:
 * - Arduino
 * - A Sharp IR Sensor
 *
 *
 * The circuit:
 * - Arduino 5V -> Sensor's pin 1 (Vcc)
 * - Arduino GND -> Sensor's pin 2 (GND)
 * - Arduino pin A0 -> Sensor's pin 3 (Output)
 *
 *
 * See the Sharp sensor datasheet for the pin reference, the pin configuration is the same for all models.
 * There is the datasheet for the model GP2Y0A41SK0F:
 *
 * http://www.robotstore.it/open2b/var/product-files/78.pdf
 *
 */


#include <Wire.h>
#include <SPI.h>
#include <variant.h>
#include <bootloaders/boot.h>

#if defined(BOARD_ID_Pilo)
#include <Wire.h>
#include <SPI.h>
#include <variant.h>

#include <WireUtility.h>




#elif defined(BOARD_ID_Captor)
#include <Wire.h>
#include <SPI.h>
#include <variant.h>

#include <WireUtility.h>




#else
//#include <Servo.h> 

#endif

//import the library in the sketch
#include <ZOpticalSensor.h>

//Create a new instance of the library
//Call the sensor "sensor"
//The model of the sensor is "GP2YA41SK0F"
//The sensor output pin is attached to the pin A0
//ZOpticalSensor sensor( P_IR[0].Pin.IRR,P_IR[0].Pin.IRE );
ZOpticalSensor sensor( P_IR[1].Pin.IRR,P_IR[1].Pin.IRE );

void setup()
{
  Serial.begin( 9600 ); //Enable the serial comunication
}

void loop()
{
  int distance = sensor.getMeasure(); //Calculate the distance in centimeters and store the value in a variable

  Serial.println( distance ); //Print the value to the serial monitor
}
