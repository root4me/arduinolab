
#include <SD.h>
bool enabled = 0;
int pingPin = 2;
int safeDistance = 4; //distance ahead in inch
int safeEdge = 400; // depth or distance from floor using custom optical sensor
bool rightTurn = false;
int rightTurnCount = 0;

int frontSensorPin = A0;

unsigned long counterStart = 0;

int motor1Pin1 = 3;
int motor1Enable = 4;
int motor1Pin2 = 5;
int motor2Pin1 = 6;
int motor2Enable = 7;
int motor2Pin2 = 9;

boolean forwardState = false;
boolean startState =  false;

void setup()
{


Serial.begin(9600);


  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);

  pinMode(motor1Enable, OUTPUT);
  pinMode(motor2Enable, OUTPUT);
}

void loop()
{

	// Set a three sec delay if this is the first time
	if (enabled == 0)
	{
		delay(3000);
		//do a spin 
		//spin(150);
		motorsStart();
		//turnLeft(200);
		//delay(3000);
		//motorsStop();
		delay(200);
		enabled = 1;
		return;
	}

	if (canGoForward() == true)
	{
		runForward(200);
	}
	else
	{
		if (forwardState == true)
		{
			motorsStop();
			delay(500);
			runReverse(200);
			delay(1500);
			if (rightTurn == false)
			{
				turnRight(200);
				delay(2000);
			}
			else
			{
				turnLeft(200);
				delay(2000);
				rightTurnCount = rightTurnCount + 1;

				if (rightTurnCount == 2)
				{
					rightTurnCount = 0;
					rightTurn = false;
				}
			}

			motorsStop();
		}
	}

	delay(200);
}

void spin(int speed)
{
	Serial.println ("Spin start.. ");
	motorsStart();
	analogWrite(motor1Pin1,speed);
	digitalWrite(motor1Pin2,LOW);
	digitalWrite(motor2Pin1,LOW);
	digitalWrite(motor2Pin2,LOW);

	delay(3000);
	motorsStop();
	Serial.println ("Spin stop.. ");
}

bool canGoForward()
{
	int sensorValue = analogRead(frontSensorPin);  
	
	//Serial.println ("Sensor Value " + String(sensorValue));
	//&& distance() < safeDistance

	if (sensorValue < safeEdge)
	{
		return false;
	}
	if (distance() < safeDistance)
	{
		return false;
	}

	return true;
}

void motorsStop()
{
	Serial.println ("Motor Stop..");
	digitalWrite(motor1Enable,LOW);
	digitalWrite(motor2Enable,LOW);
	forwardState = false;
}

void motorsStart()
{
	digitalWrite(motor1Enable,HIGH);
	digitalWrite(motor2Enable,HIGH);
}

void runForward(int speed)
{

	if (forwardState == true) { Serial.println ("Already Forward " + String(speed)); return; }

	motorsStart();
	analogWrite(motor1Pin1,speed);
	digitalWrite(motor1Pin2,LOW);
	analogWrite(motor2Pin1,speed);
	digitalWrite(motor2Pin2,LOW);

	Serial.println ("Running forward..." );
	forwardState = true;
}

void runReverse(int speed)
{
  forwardState = false;

	motorsStart();
  	digitalWrite(motor1Pin1,LOW);
	analogWrite(motor1Pin2,speed);
	digitalWrite(motor2Pin1,LOW);
	analogWrite(motor2Pin2,speed);

	Serial.println ("Running Reverse");
}

void turnRight(int speed)
{
	forwardState = false;
	motorsStart();
	analogWrite(motor1Pin1,speed);
	digitalWrite(motor1Pin2,LOW);
	digitalWrite(motor2Pin1,LOW);
	analogWrite(motor2Pin2,speed);

	rightTurn = true;
	Serial.println ("Turn Right");
}

void turnLeft(int speed)
{
  forwardState = false;
	motorsStart();
	digitalWrite(motor1Pin1,LOW);
	analogWrite(motor1Pin2,speed);
	analogWrite(motor2Pin1,speed);
	digitalWrite(motor2Pin2,LOW);

  Serial.println ("Turn Left");
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

  //Serial.println("Distance : " + String(pingTimein));

  //Serial.println(pingTimein);

	Serial.println("Distance" + String(pingTimein));


  return pingTimein;

  // 3000 microseconds ping time is ~20 inches to an obstacle
  // Refer: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  //	Inches = (microseconds / 73.744) / 2
  //	Centimeters = (microseconds / 29.034) / 2
}