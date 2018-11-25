#include "ZOpticalSensor.h"
#include "math.h"
uint16_t ZOpticalSensor::getMeasure(   )
	{
		pinMode(pinIE,OUTPUT);
		digitalWrite(pinIE,HIGH);
		uint16_t high = (analogRead(pinIR)+analogRead(pinIR));
		digitalWrite(pinIE,LOW);
		uint16_t low = (analogRead(pinIR)+analogRead(pinIR));
		pinMode(pinIE,INPUT_PULLDOWN);
		/*uint16_t highZ = (analogRead(pinIR)+analogRead(pinIR));
		*/
		//uint16_t delta=max(high,low)-min(high,low);
		uint16_t delta=high-low;
		
		/*
		if( !avoidBurstRead ) 
			while( millis() <= lastTime + 10 ) 
		{} //wait for sensor's sampling time*/

	//	lastTime = millis();
		previousValue=delta;
			return delta;
	}

	boolean ZOpticalSensor::isDetected()
	{
         uint16_t delta= getMeasure(   );
		return delta>threshold;
	}
	void ZOpticalSensor::calibstep1()
	{
		getMeasure(   );
		}
	void ZOpticalSensor::calibstep2()
	{
		uint16_t Value1=previousValue;
		uint16_t Value2=getMeasure(   );
		threshold=((uint32_t)Value1+(uint32_t)Value2)/2;
	}


#ifdef ROS_USED 
void ZOpticalSensor::setRefreshRateUs(uint32_t intervalTime)
{
	rate=intervalTime*1000LL;
}

// ROS SECTION :
//char frameid[] = "/ir_ranger";
/** setup :
  At setup after NodeHandle setup, call this to initialise the topic
the topic is a sensor_msgs::Range.

*/
void ZOpticalSensor::setup( ros::NodeHandle * myNodeHandle,	const char   *	topic )
{
  nh=myNodeHandle;
  pub_range=new ros::Publisher( topic, &range_msg);
  nh->advertise(*pub_range);
  
  range_msg.radiation_type = sensor_msgs::Range::INFRARED;
//  range_msg.header.frame_id =  frameid;
  range_msg.field_of_view = 10;
  range_msg.min_range = ((float)5)/1000.0 ;  //5mm
  range_msg.max_range = ((float)20)/1000.0 ;   //20mm
  
  range_msg.header.stamp = nh->now();
}
#define toNSec( t ) ((uint32_t)t.sec*1000000000ull + (uint32_t)t.nsec)
/** loop :
  on loop  before NodeHandle refresh(spinOnce), call this to update the topic
*/
void ZOpticalSensor::loop()
{
	ros::Time now=nh->now();

  // publish the range value every 50 milliseconds
  //   since it takes that long for the sensor to stabilize
  if ( (toNSec( now ) ) > (((long)rate)+toNSec( (range_msg.header.stamp) ))){
    range_msg.range = range_msg.max_range*((float)threshold/(float)getMeasure(   ));
    range_msg.header.stamp = now;
    pub_range->publish(&range_msg);
  } 
}
#endif 

