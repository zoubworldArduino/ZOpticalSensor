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


#define ROS_SERIAL (P_COM3.serial2)
#define ROS_BAUDRATE 57600
#include "ros.h"
ros::NodeHandle  nh;

#elif defined(BOARD_ID_Captor)
#include <Wire.h>
#include <SPI.h>
#include <variant.h>

#include <WireUtility.h>


#define ROS_SERIAL (P_COM0.serial2)
#define ROS_BAUDRATE 57600

#include "ros.h"
ros::NodeHandle  nh;

#else
//#include <Servo.h> 
#include "ros.h"
ros::NodeHandle  nh;
#endif

//import the library in the sketch
#include <ZOpticalSensor.h>

//Create a new instance of the library
//Call the sensor "sensor"
//The model of the sensor is "GP2YA41SK0F"
//The sensor output pin is attached to the pin A0
//ZOpticalSensor sensor( P_IR[0].Pin.IRR,P_IR[0].Pin.IRE );
ZOpticalSensor sensor0( P_IR[0].Pin.IRR,P_IR[0].Pin.IRE );
ZOpticalSensor sensor1( P_IR[1].Pin.IRR,P_IR[1].Pin.IRE );
ZOpticalSensor sensor2( P_IR[2].Pin.IRR,P_IR[2].Pin.IRE );
ZOpticalSensor sensor3( P_IR[3].Pin.IRR,P_IR[3].Pin.IRE );
ZOpticalSensor sensor4( P_IR[4].Pin.IRR,P_IR[4].Pin.IRE );
ZOpticalSensor sensor5( P_IR[5].Pin.IRR,P_IR[5].Pin.IRE );
ZOpticalSensor sensor6( P_IR[6].Pin.IRR,P_IR[6].Pin.IRE );
ZOpticalSensor sensor7( P_IR[7].Pin.IRR,P_IR[7].Pin.IRE );

void setup()
{
  	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)


nh.initNode(); 
analogReadResolution(12);
sensor0.setup(&nh,"/sensor/0/");
 sensor1.setup(&nh,"/sensor/1/");
 sensor2.setup(&nh,"/sensor/2/");
 sensor3.setup(&nh,"/sensor/3/");
 sensor4.setup(&nh,"/sensor/4/");
 sensor5.setup(&nh,"/sensor/5/");
 sensor6.setup(&nh,"/sensor/6/");
 sensor7.setup(&nh,"/sensor/7/");
   //wait until you are actually connected
    while (!nh.connected())
    {
      nh.spinOnce();
      delay(10);
    }
}

void loop()
{
 sensor0.loop();
 sensor1.loop();
 sensor2.loop();
 sensor3.loop();
 sensor4.loop();
 sensor5.loop();
 sensor6.loop();
 sensor7.loop();
   
   nh.loginfo("loop");
   nh.spinOnce();
 delay(200);
 
}
