const int pinWrite = 2;
const int pinRead = A2;

void setup() { 
  Serial.begin(9600); 
  pinMode(pinWrite, OUTPUT);
  pinMode(pinRead, INPUT);
  digitalWrite(pinWrite, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  ler();
}

void ler(){
  float switchstate = analogRead(pinRead);
  Serial.println(switchstate/220);
  
}
