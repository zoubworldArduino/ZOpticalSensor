# ZOpticalSensor
An Arduino library that allows to detect object thank to a IR emitter and an IR receiver

## Currently supported sensor models
- CNY70 

## Usage

you define a IE pin that drive the Emitter, and a IR pin that read the reciever.
an analog read is done with emitter OFF, an analog read is done with EI on.
based on the delta, it return true or false about the detection of an object.
Absolute value isn't consider, only the delta, absolute value is link to the ambiant ligth.
if a object reflect the ligth of emitter a delta is captured.
so a thresold is define to detect object. this thresold can be calibrated.

call isDetected(); to test if obect is present

## calibration procedure :
-# call calibstep1() when the object is present; 
-# call calibstep2() when the object is removed.
-# the threhold is updated.
.
Becarefull the behaviour of the captor isn't lineare with the ligth present, the calibration is true the a specific ambiant ligth level/range.
so reading getMeasure() isn't a good idea because the range of variation can change the the ambient ligth.


## calibration procedure :
use setup( ros::NodeHandle * myNodeHandle,	const char   *	topic ) to publish a topic of type sensor_msgs/Range 
it return a valid value between 5 and 20mm, when the detection is limit it return 20mm, when the detection is good it return a smaller value. when the detection is poor it return an higher value.
you have to call loop() is you main loop().
you can adjust the publish periodicity with setRefreshRateUs(uint32_t intervalTime); default is 50ms.(max 4s)


## example of captor behaviour with the CNY70 :
captor is standalone :
distance /  value in ohms
infinity dark         18M
inf      neon ligth   150k
6 cm			      80k
5 cm 			      70k
4 cm 			      60k
3 cm 			      17k
2 cm 			      11.5k
1 cm 			       7k
0.5 cm 			       6k
0.2 cm 			       7k
0   cm 			      18k
captor with 10Kohms resistor in serial connected between gnd and 5V
on analogread baed on 10 bits measure twice(like getmeasure()), so 2048 means 5v
code / distance
<20 		 noise level
20  			5   cm
25 				4   cm
30 				3   cm
50 				2   cm
120 			1   cm
180 			0.8 cm
230 			0.5 cm
116 			0.2 cm
63  			0   cm
*/
	



*/
