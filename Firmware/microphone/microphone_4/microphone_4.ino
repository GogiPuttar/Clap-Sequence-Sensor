/*
  Calibration

  Demonstrates one technique for calibrating sensor input. The sensor readings
  during the first five seconds of the sketch execution define the minimum and
  maximum of expected values attached to the sensor pin.

  The sensor minimum and maximum initial values may seem backwards. Initially,
  you set the minimum high and listen for anything lower, saving it as the new
  minimum. Likewise, you set the maximum low and listen for anything higher as
  the new maximum.

  The circuit:
  - analog sensor (potentiometer will do) attached to analog input 0
  - LED attached from digital pin 9 to ground

  created 29 Oct 2008
  by David A Mellis
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Calibration
*/

// These constants won't change:
const int sensorPin = A0;    // pin that the sensor is attached to
const int ledPin = 9;        // pin that the LED is attached to

// variables:
int sensorValue = 0;         // the sensor value
int sensorMin = 1023;        // minimum sensor value
int sensorMax = 0;      // maximum sensor value
float filterSensor = 13.0;


void setup() {
  // turn on LED to signal the start of the calibration period:
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  Serial.begin(9600);
  // calibrate during the first five seconds
  sensorMin = 12;
  sensorMax = 163;

  // signal the end of the calibration period
  digitalWrite(13, LOW);
}

void loop() {
  // read the sensor:
  sensorValue = analogRead(sensorPin);

  // apply the calibration to the sensor reading
  sensorValue = map(sensorValue, sensorMin, sensorMax, 0, 255);

  // in case the sensor value is outside the range seen during calibration
  sensorValue = constrain(sensorValue, 0, 255);

  filterSensor = (float)(0.2*sensorValue + 0.8*filterSensor);

  // fade the LED using the calibrated value:
  analogWrite(ledPin, sensorValue);
  if (sensorValue > 15 || sensorValue <= 12)
  {
    delay(1000);
    sensorValue = analogRead(sensorPin);
    sensorValue = map(sensorValue, sensorMin, sensorMax, 0, 255);
    sensorValue = constrain(sensorValue, 0, 255);
    if (sensorValue > 15 || sensorValue <= 12)
    {
      Serial.println(1);
    }
    else
    {
      Serial.println(sensorValue);  
    }
  }
}
