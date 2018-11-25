/*
 * ZOpticalSensor
 * Library to detect object
 */

#pragma once

#include <Arduino.h>
#ifdef ROS_USED 
#include <ros.h>
#include <ros/time.h>
#include <sensor_msgs/Range.h>
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
			
			
#ifdef ROS_USED 
    void setup( ros::NodeHandle  *myNodeHandle,	const char   *	topic);
	void loop();
	void setRefreshRateUs(uint32_t intervalTime);
#endif 

		protected:
			 uint32_t rate;
			 uint16_t threshold;
			 uint32_t pinIR;
			 uint32_t pinIE;

		private:
		#ifdef ROS_USED 
    ros::NodeHandle  *nh;
    sensor_msgs::Range range_msg;
    ros::Publisher *pub_range;
#endif
			uint16_t previousValue;
			uint32_t lastTime  ;
	};
