/*
 * ZOpticalSensor
 * Library to detect object
 */

#pragma once

#include <Arduino.h>
#include <assert.h>
#ifdef ROS_USED 
#include <ros.h>
#include <ros/time.h>
//#include <sensor_msgs/Range.h>
#include <std_msgs/Int16.h>
#endif 

class ZOpticalSensor
	{
		public:

			

			ZOpticalSensor( uint32_t _sensorPinIR, uint32_t _emitterPinIE ) : pinIR( _sensorPinIR ) , pinIE( _emitterPinIE ) 
			{
				threshold=50;rate=50000000LL;previousValue=0xffff;lastTime = 0;
			pinMode(pinIR,INPUT_PULLUP);
			}

			
			boolean isDetected();
			uint16_t getMeasure();
			
			
			
			void ZOpticalSensor::calibstep1();
			void ZOpticalSensor::calibstep2();
                        uint16_t getMeasureLigth(   );
			
			
#ifdef ROS_USED 
    void setup( ros::NodeHandle  *myNodeHandle,	const char   *	topic);
	void loop();
	void setRefreshRateUs(uint32_t intervalTime);
#endif 

		protected:
			 
			 uint16_t threshold;
			 uint32_t pinIR;
			 uint32_t pinIE;

		private:
		#ifdef ROS_USED 
                  //ros::Time stamp;
                  int timestamp;
                  uint32_t rate;
                  
    ros::NodeHandle  *nh;
    //sensor_msgs::Range range_msg;
	std_msgs::Int16 range_msg;
    ros::Publisher *pub_range;
#endif
			uint16_t previousValue;
			uint32_t lastTime  ;
	};
