#define sensorPin A0
#define pot A1
#define LED 4
int sensorValue = 0;         // the sensor value
int sensorMin = 1023;        // minimum sensor value
int sensorMax = 1;      // maximum sensor value
float filterSensor = 13.0;

long int startTime = 0;
long int currentTime = 0;
long int debounceTime = 500;
int m = 0;
int c = 0;
int degree;
int mean;
int state = 0;
float avg = 16;
void setup() {
  pinMode(A1, INPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  
  sensorMin = 12;
  sensorMax = 163;
}

void loop() {
  if(state)
  {
    digitalWrite(LED, HIGH);
  }
  else
  {
    digitalWrite(LED, LOW);
  }
  
  sensorValue = analogRead(sensorPin);
  degree = analogRead(pot);
  
  sensorValue = map(sensorValue, sensorMin, sensorMax, 0, 255);
  sensorValue = constrain(sensorValue, 0, 255);

  mean = map(degree, 6, 720, 1, 37);
  mean = constrain(mean, 1, 37);

  avg = (float)(0.99*avg + 0.01*sensorValue);
  
  if(mean != round(avg - 0.25))
  {
    Serial.print(sensorValue);
    Serial.print("  ");
    Serial.print(mean);
    Serial.print("  ");
    Serial.println(avg);
  }

  if ((sensorValue > mean + 2 ) && m == 0)
  {
    if( c == 1)
    {
      if((currentTime - startTime) <= 1000)
      {
        Serial.println(state);
        state = state == 1? 0 : 1;
      }
      c = 0;
    }
    else
    {
      startTime = millis();
      m = 1;
      c = 1;
    }
  }
  else if ( currentTime - startTime >= debounceTime )
  {
    m = 0;
  }
  currentTime = millis();
}
