#define pot A1
int degree;
void setup() {
  // put your setup code here, to run once:
  pinMode(pot,INPUT);
  Serial.begin(9600);
}
void loop() {
  // put your main code here, to run repeatedly:
  degree = analogRead(pot);
  degree = map(degree, 5, 720, 0, 100);
  degree = constrain(degree, 0, 100);
  Serial.println(degree);
}
