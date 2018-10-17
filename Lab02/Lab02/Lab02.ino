// Pins
const int pinTemp = A0;
const int pinLight = A1;
const int pinPoten = A3;

// Constants
const int errorMargin = 1.1;
const float roomTemp = 26.0;
int ledSpeed = 500;

// Last Values Sampled
// The goal is to only run the data handling when there is a new value in the pin
// We also have an "error margin" to counterbalance the current fluctuations
int lastTemp = 0;
int lastPoten = 0;
int lastLight = 0;

void setup() {
  Serial.begin(9600);
  // Temperature LED
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
  // Potentiometer LED
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  // RGB Led
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
}

void loop() {
  // Round-Robin Architecture
  // Temperature
  if ( analogRead(pinTemp) < (lastTemp-errorMargin) || analogRead(pinTemp) > (lastTemp+errorMargin) )
    temperatureSensor();
  // Potentiometer
  if ( analogRead(pinPoten) < (lastPoten-errorMargin) || analogRead(pinPoten) > (lastPoten+errorMargin) )
    potentiometer();
  ledBlink();
  // Light Sensor
  if ( analogRead(pinLight) < (lastLight-errorMargin) || analogRead(pinLight) > (lastLight+errorMargin) )
    lightSensor();
}

// Temperature Functions
void temperatureSensor() {
  int sensorVal = analogRead(pinTemp);   // Read Pin
  lastTemp = sensorVal;   // Store value to check for changes in the loop
  float temperature =  (((sensorVal/1024.0)*5.0)-0.5)*100; // Data Conversion
  //Serial.print("Temperature: ");
  //Serial.println(temperature);
  if (temperature >= roomTemp) 
    digitalWrite(4, HIGH);
  else
    digitalWrite(4, LOW);
}

// Potentiometer Functions
void potentiometer(){
  int potenVal = analogRead(pinPoten);
  lastPoten = potenVal; // Store value to check for changes in the loop
  //Serial.print("Potence: ");
  //Serial.println(potenVal);
  // Maping out the ledspeed between 200ms and 1400ms to match
  // the outcome of the potentiometer
  ledSpeed = map(potenVal, 0, 1023, 200, 1400);
  //Serial.print("LED Speed: ");
  //Serial.println(ledSpeed);
}

void ledBlink(){ // Blink the LED
  digitalWrite(2, LOW);
  delay(ledSpeed);
  digitalWrite(2, HIGH);
  delay(ledSpeed);
}

// Light Functions
void lightSensor(){
  int sensorLight = analogRead(pinLight);   // Read the Pin
  int light = sensorLight / 4;    // Transform from 1024 to 255
  lastLight = light;      // Store value to check for changes in the loop
  Serial.print("light: ");
  Serial.println(255-light);
  //analogWrite(8, 255-light);   // R
  //analogWrite(9, 255-light);   // G
  analogWrite(10, 255-light);    // B
}
