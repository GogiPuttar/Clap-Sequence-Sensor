#define sensorPin A0
#define pot A1
#define LED 4
#define button 11
int sensorValue = 0;         // the sensor value
int sensorMin = 1023;        // minimum sensor value
int sensorMax = 1;      // maximum sensor value

long int startTime = 0;
long int currentTime = 0;
long int debounceTime = 500;
int m = 0;
int c = 0;
int degree;
int mean;
int state = 0;
float avg = 50;

int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

int stableMean = 0;
int prevMean =  0;
int ctr = 0;
int buff = 0;

void setup() {
  pinMode(A1, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(button, INPUT);
  Serial.begin(9600);
  
  sensorMin = 12;
  sensorMax = 143;
}

void loop() {
  
  int reading = digitalRead(button);
  //Serial.print("    ");
  //Serial.println(reading);

  if (reading != lastButtonState)
  {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) 
  {
    
    if (reading != buttonState) {
      buttonState = reading;
      
      if (buttonState == HIGH) {
        state = state == 1? 0 : 1;
        setLED(state);
        Serial.println("button");
      }
    }
  }
  lastButtonState = reading;
  
  sensorValue = analogRead(sensorPin);
  degree = analogRead(pot);
  
  sensorValue = map(sensorValue, sensorMin, sensorMax, 0, 255);
  sensorValue = constrain(sensorValue, 0, 255);

  mean = map(degree, 6, 720, 102, 143);
  mean = constrain(mean, 102, 143);

  sensorMax = mean;

  if(mean != prevMean)
  {
    ctr = 1;
    buff = mean;
  }
  
  if( mean == buff && ctr )
  {
    ctr++;
  }
  else
  {
    ctr = 0;
  }
  
  if( ctr >= 10)
  {
    ctr = 0;
    stableMean = buff;
  }

  if(stableMean != round(avg - 0.25))
  {
    Serial.print(sensorValue);
    Serial.print("  ");
    Serial.print(mean);
    Serial.print("  ");
    Serial.println(avg);
  }
  
  //if( currentTime > 10000)
  {
    stableMean = round(avg - 0.25);
  }

  if ((sensorValue > stableMean + 3 ) && m == 0)
  {
    if( c == 1)       //if second clap  
    {
      if((currentTime - startTime) <= 1000)
      {
        state = state == 1? 0 : 1;
        setLED(state);
        Serial.println(state);
        delay(1000);
      }
      c = 0;
    }
    else
    {
      startTime = millis();
      m = 1;            //don't register more claps until debounce time passed
      c = 1;            //first clap registered, the next one is the second clap
    }
    Serial.println("----------------------------------->>>>>>>>>>");
  }
  else if ( currentTime - startTime >= debounceTime )
  {
    m = 0;
    avg = (float)(0.99*avg + 0.01*sensorValue);
  }
  
  currentTime = millis();
  prevMean = mean;
}

void setLED(int state)
{
  if(state)
  {
    digitalWrite(LED, HIGH);
  }
  else
  {
    digitalWrite(LED, LOW);
  }
}
