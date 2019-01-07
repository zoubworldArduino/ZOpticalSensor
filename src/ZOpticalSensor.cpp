#include "ZOpticalSensor.h"
#include "math.h"
/*
uint16_t averageLigthLevel[16];
uint8_t averageLigthIndex=0;
*/
/** measure perform with reflexion.
This method work well when the object isn't black or dark.

*/
uint16_t ZOpticalSensor::getMeasure(   )
	{
            volatile int i=0;
		pinMode(pinIE,OUTPUT);
		digitalWrite(pinIE,HIGH);
               
                for(i=0;i<20;i++);// delay(1);
		uint16_t high = (analogRead(pinIR)+analogRead(pinIR)+analogRead(pinIR)+analogRead(pinIR));
		digitalWrite(pinIE,LOW);
		for(i=0;i<20;i++);//delay(1);//need a delay for settle time
                uint16_t low = (analogRead(pinIR)+analogRead(pinIR)+analogRead(pinIR)+analogRead(pinIR));
		pinMode(pinIE,INPUT);
                uint16_t delta=max(high,low)-min(high,low);
       
                /*uint32_t average=0;
                for(i=0;i<16;i++)//delay(1);//need a delay for settle time
                average+=averageLigthLevel[i];
                average=average>>4;
		uint16_t highZ = (analogRead(pinIR)+analogRead(pinIR)+analogRead(pinIR)+analogRead(pinIR));
		averageLigthLevel[(averageLigthIndex++)%16]=highZ;		
		uint16_t delta=max(highZ,average)-min(highZ,average);
		µ/
		/*
		if( !avoidBurstRead ) 
			while( millis() <= lastTime + 10 ) 
		{} //wait for sensor's sampling time*/

	//	lastTime = millis();
		previousValue=delta;
			return delta;
	}

/** direct measure perform from ambiant ligth
This method can be interesting when the object is dark black, we detect that the obect create a shadow.
but this is sensible to ambiant environment

*/
uint16_t ZOpticalSensor::getMeasureLigth(   )
	{
            volatile int i=0;
		
		pinMode(pinIE,INPUT);
                /*uint32_t average=0;*/
                for(i=0;i<16;i++)//delay(1);//need a delay for settle time
                /*average+=averageLigthLevel[i]*/;
                /*average=average>>4;*/
		uint16_t highZ = (analogRead(pinIR)+analogRead(pinIR)+analogRead(pinIR)+analogRead(pinIR));
		/*averageLigthLevel[(averageLigthIndex++)%16]=highZ;		
		uint16_t delta=max(highZ,average)-min(highZ,average);
*/
                uint16_t delta=highZ;
			return delta;
	}



	boolean ZOpticalSensor::isDetected()
	{
         uint16_t delta= getMeasure(   );
		return delta>threshold;
	}
/** call this methode when no object is in front of captor,
and just after call calibstep2()
*/
	void ZOpticalSensor::calibstep1()
	{
		getMeasure(   );
		}
/** call this methode when an object is in front of captor,
and just before you should call calibstep1()
this update the threshold of detection.
*/
	void ZOpticalSensor::calibstep2()
	{
		uint16_t Value1=previousValue;
		uint16_t Value2=getMeasure(   );
		threshold=((uint32_t)Value1+(uint32_t)Value2)/2;
	}


#ifdef ROS_USED 
void ZOpticalSensor::setRefreshRateUs(uint32_t intervalTime)
{
	rate=intervalTime;
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
  assert( pub_range!=0);// heap issue.
  nh->advertise(*pub_range);
  setRefreshRateUs( 100000);
  /*
  range_msg.radiation_type = sensor_msgs::Range::INFRARED;
//  range_msg.header.frame_id =  frameid;
  range_msg.field_of_view = 10;
  range_msg.min_range = 0 ;  //5mm
  range_msg.max_range = 4096*4;   //20mm
  range_msg.header.stamp = nh->now();
  */
  
}
#define toNSec( t ) ((uint32_t)t.sec*1000000000ull + (uint32_t)t.nsec)
/** loop :
  on loop  before NodeHandle refresh(spinOnce), call this to update the topic
*/
void ZOpticalSensor::loop()
{
  if (pub_range!=0){
	//ros::Time now=nh->now();
    

  // publish the range value every 50 milliseconds
  //   since it takes that long for the sensor to stabilize
  //if ( (toNSec( now ) ) > (((long)rate)+toNSec( (/*range_msg.header.*/stamp) )))
    if(micros()-timestamp>rate)
        {
    range_msg.data = getMeasure(   );
  //  range_msg.range = (float)getMeasure(   );
    /*range_msg.header.*/
    //stamp = now;
    timestamp=micros();
     pub_range->publish(&range_msg);
        }
  } 
}
#endif 

