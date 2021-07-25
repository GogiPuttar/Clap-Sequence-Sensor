#define sensorPin A0
#define pot A1
int sensorValue = 0;         // the sensor value
int sensorMin = 1023;        // minimum sensor value
int sensorMax = 0;      // maximum sensor value
float filterSensor = 13.0;

long int startTime = 0;
long int currentTime = 0;
long int debounceTime = 500;
int m = 0;
int c = 0;
int degree;
int mean;

void setup() {
  pinMode(A1, INPUT);
  Serial.begin(9600);
  
  sensorMin = 12;
  sensorMax = 163;
}

void loop() {
  sensorValue = analogRead(sensorPin);
  degree = analogRead(pot);
  
  sensorValue = map(sensorValue, sensorMin, sensorMax, 0, 255);
  sensorValue = constrain(sensorValue, 0, 255);

  mean = map(degree, 6, 720, 1, 37);
  mean = constrain(mean, 1, 37);
  Serial.println(mean);

  if ((sensorValue > mean + 2 || sensorValue <= mean - 1) && m == 0)
  {
    if( c == 1)
    {
      if((currentTime - startTime) <= 1000)
      {
        Serial.println("Yeaaaaaaaaaayyyyyy");
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
