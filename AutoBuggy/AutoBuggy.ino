
#include <Servo.h>

int motorPnp1 = 2;
int motorNpn1 = 3;
int motorPnp2 = 4;
int motorNpn2 = 5;
//	h-Bridge ........
//	Pnp1		Pnp2
//       Motor
//	Npn1		Npn2
int steerServoPin = 6;
int visionServoPin = 7;
int pingPin = 8;
int indicatorLed = 9;

int slowSpeed = 150;
int fastSpeed = 254;
int cruiseSpeed = 254;

Servo steerServo;
int steerServoCenter = 88; // Angle at which the wheel centers
int steerServoRight = 170; // 
int steerServoLeft = 10; // 

Servo visionServo;
int visionServoCenter = 100;
int visionServoRight = 170;
int visionServoLeft = 10;

boolean forwardState = false;
int safeDistance = 60; //inch

void setup()
{
  pinMode(indicatorLed,OUTPUT);

  pinMode(motorPnp1, OUTPUT);
  pinMode(motorNpn1, OUTPUT);
  pinMode(motorPnp2, OUTPUT);
  pinMode(motorNpn2, OUTPUT);

  steerServo.attach(steerServoPin);
  visionServo.attach(visionServoPin);

  Serial.begin(9600);

  reset();
}

void loop()
{

  scenarioFull();

  delay(300);
}

void scenarioFull()
{

  if (distance() < safeDistance)
  {
	digitalWrite(indicatorLed,HIGH);
    reset();
		
	// Wait for a second before doing anything
	delay(1000);

	if (distance() > safeDistance) return; // Let it keep runnig forward if the distance is fine

	if (driveLeftOrRight() == false)
	{	  
		driveReverse();
	}

  }
  else
  {
	digitalWrite(indicatorLed,LOW);
    runForward(cruiseSpeed);
  }

}

boolean driveLeftOrRight()
{
  long _distanceRight = 0;
  long _distanceLeft = 0;
  long _distanceStraight = 0;

	turnServo(visionServo, visionServoRight);
    _distanceRight = distance();
    turnServo(visionServo, visionServoLeft);
    _distanceLeft = distance();
    turnServo(visionServo, visionServoCenter);

	if (_distanceLeft > safeDistance)
	{
	  turnAndRunForward(steerServo, steerServoLeft, cruiseSpeed);
	}
	else if (_distanceRight > safeDistance)
	{
	  turnAndRunForward(steerServo, steerServoRight, cruiseSpeed);
	}
	else
	{
		return false;
	}

	return true;
}

void driveReverse()
{
	runReverse();
	delay(1500);
	reset();

	while (driveLeftOrRight() == false)
	{
	  runReverse();
	  delay(1500);
	  reset();
	}
}


void scenario1()
{
  long _distanceRight = 0;
  long _distanceLeft = 0;
  long _distanceStraight = 0;

  if (distance() < safeDistance)
  {
	digitalWrite(indicatorLed,HIGH);
    reset();

  }
  else
  {
	digitalWrite(indicatorLed,LOW);
    runForward(cruiseSpeed);
  }
}

// Reverse Scenario
void scenario3()
{
  long _distanceRight = 0;
  long _distanceLeft = 0;
  long _distanceStraight = 0;

  if (distance() < safeDistance)
  {
	digitalWrite(indicatorLed,HIGH);
    reset();

	
	turnServo(visionServo, 170);
    _distanceRight = distance();
    turnServo(visionServo, 20);
    _distanceLeft = distance();
    turnServo(visionServo, visionServoCenter);
    
	//Testing    
    _distanceStraight = distance();

    //if ((_distanceStraight > _distanceRight) && (_distanceStraight > _distanceLeft))
    //{
      runReverse();
      // Testing . This should be changed to continue reverse till an alternate route is found
      delay(1500);
      reset();
    //}

  }
  else
  {
	digitalWrite(indicatorLed,LOW);
    runForward(cruiseSpeed);
  }
}

// Advanced Reverse Scenario
void scenario4()
{
  long _distanceRight = 0;
  long _distanceLeft = 0;
  long _distanceStraight = 0;

  if (distance() < safeDistance)
  {
	digitalWrite(indicatorLed,HIGH);
	reset();
	
	turnServo(visionServo, 170);
    _distanceRight = distance();
    turnServo(visionServo, 20);
    _distanceLeft = distance();
    turnServo(visionServo, visionServoCenter);

    //Testing    
    _distanceStraight = distance();

    //if ((_distanceStraight > _distanceRight) && (_distanceStraight > _distanceLeft))
    //{
      runReverse();
      delay(1500);
      reset();
		
	  turnServo(visionServo, 170);
		_distanceRight = distance();
		turnServo(visionServo, 10);
		_distanceLeft = distance();

	  while ((_distanceRight < safeDistance) && (_distanceLeft < safeDistance))
	  {
		 runReverse();
		// Testing . This should be changed to continue reverse till an alternate route is found
		delay(1000);
		reset();

		turnServo(visionServo, 170);
		_distanceRight = distance();
		turnServo(visionServo, 10);
		_distanceLeft = distance();
		turnServo(visionServo, visionServoCenter);
	  }

	  if (_distanceRight > _distanceLeft)
	  {
	    turnAndRunForward(steerServo, steerServoRight, cruiseSpeed);
		reset();
	  }
	  else
	  {
	    turnAndRunForward(steerServo, steerServoLeft, cruiseSpeed);
		reset();
	  }
    //}

  }
  else
  {
	digitalWrite(indicatorLed,LOW);
    runForward(cruiseSpeed);
  }
}

// Turn right scenario
void scenario2()
{
  long _distanceRight = 0;
  long _distanceLeft = 0;
  long _distanceStraight = 0;

  if (distance() < safeDistance)
  {

	digitalWrite(indicatorLed,HIGH);
    reset();
	
	turnServo(visionServo, 170);
    _distanceRight = distance();
    turnServo(visionServo, 10);
    _distanceLeft = distance();
    turnServo(visionServo, visionServoCenter);
    _distanceStraight = distance();

	turnAndRunForward(steerServo, steerServoLeft, cruiseSpeed);
    reset();

  }
  else
  {
	digitalWrite(indicatorLed,LOW);
    runForward(cruiseSpeed);
  }
}


void turnServo(Servo servo, int angle)
{
  servo.write(angle);
  Serial.println("Turning : " + String(angle) + " degree");
  delay(1000);
}

void turnAndRunForward(Servo servo, int angle,int speed)
{

  turnServo(servo, angle);
  runForward(speed);
  delay(1500);
  reset();
}

void reset()
{
  stop();
  steerServo.write(steerServoCenter);
  visionServo.write(visionServoCenter);
  digitalWrite(indicatorLed,LOW);
  forwardState = false;
  Serial.println ("Reset");
}

void runReverse()
{
  forwardState = false;
  digitalWrite(motorPnp1, LOW);
  digitalWrite(motorPnp2, HIGH);
  analogWrite(motorNpn1, 0);
  Serial.println ("Reverse");

  for (int i = 100; i < cruiseSpeed; i++)
  {
    //Serial.println (i);
    analogWrite(motorNpn2,i);
  }
  Serial.println ("Running Reverse");
}

void runForward(int speed)
{
	if (forwardState == true) { Serial.println ("Already Forward " + String(speed)); return; }
  
  digitalWrite(motorPnp1, HIGH);
  digitalWrite(motorPnp2, LOW);
  Serial.println ("Forward");
  //for (int i = 80; i < speed; i++)
  //{
  //  Serial.println (i);
  //  analogWrite(motorNpn1, i);
  //}
  analogWrite(motorNpn1, speed);
  Serial.println ("Runnig Forward " + String(speed));
  analogWrite(motorNpn2,0);
  forwardState = true;
}


void stop()
{
  digitalWrite(motorPnp1, HIGH);
  digitalWrite(motorPnp2, HIGH);
  delay(200);
  analogWrite(motorNpn1,0);
  analogWrite(motorNpn2,0);
  forwardState = false;
  Serial.println ("Stopped");
}

// Use Ping Sensor to find the distance and return back the duration in microSeconds
long distance()
{
  long pingTime;
  long pingTimein;

  // Activate Ping Sensor. Give a HIGH Pulse for 2 or more micro Seconds
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  //Receive the ping response
  pinMode(pingPin,INPUT);
  pingTime = pulseIn(pingPin, HIGH);

  // Testing
  //pingTime= 1000;

  pingTimein = (pingTime / 73.744) / 2;

  Serial.println("Distance : " + String(pingTimein));

  //Serial.println(pingTimein);

  //printLn("Distance",String(pingTimein));

  return pingTimein;

  // 3000 microseconds ping time is ~20 inches to an obstacle
  // Refer: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  //	Inches = (microseconds / 73.744) / 2
  //	Centimeters = (microseconds / 29.034) / 2
}

