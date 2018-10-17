// Pins
const int pinTemp = A0;
const int pinPoten = A3;

// Constants
const int errorMargin = 1.1;
const float roomTemp = 26.0;
int ledSpeed = 500;


// Last Values Sampled
int lastTemp = 0;
int lastPoten = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // Temperature LED
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
  // Potentiometer LED
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  if ( analogRead(pinTemp) < (lastTemp-errorMargin) || analogRead(pinTemp) > (lastTemp+errorMargin) )
    temperatureSensor();
  if ( analogRead(pinPoten) < (lastPoten-errorMargin) || analogRead(pinPoten) > (lastPoten+errorMargin) )
    potentiometer();
  ledBlink();
}

void temperatureSensor() {
  int sensorVal = analogRead(pinTemp);   // Read Pin
  lastTemp = sensorVal;   // Store value to check for changes in the loop
  float temperature =  (((sensorVal/1024.0)*5.0)-0.5)*100; // Data Conversion
  Serial.print("Temperature: ");
  Serial.println(temperature);
  if (temperature >= roomTemp) 
    digitalWrite(4, HIGH);
  else
    digitalWrite(4, LOW);
}

void potentiometer(){
  int potenVal = analogRead(pinPoten);
  lastPoten = potenVal;
  //Serial.print("Potence: ");
  //Serial.println(potenVal);
  ledSpeed = map(potenVal, 0, 1023, 200, 1400);
  Serial.print("LED Speed: ");
  Serial.println(ledSpeed);
}

void ledBlink(){
  digitalWrite(2, LOW);
  delay(ledSpeed);
  digitalWrite(2, HIGH);
  delay(ledSpeed);
}
