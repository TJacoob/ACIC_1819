int led = 0;
boolean pause = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(2,INPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2), lerBotao, RISING);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.print("x");
  //lerBotao();
  if ( pause )
  {
    Serial.println("nothing happens");
  }
  else
  {
    Serial.println("Next Step");
    passo(); 
    delay(1000);
  }
}

void passo(){
  digitalWrite(led,LOW);
  nextLed();
  Serial.println(led);
  digitalWrite(led,HIGH);
}

void lerBotao(){
  switchstate = digitalRead(2);
  if ( switchstate == HIGH )
    pause = !pause ;
  //Serial.print("botão pressionado: ");
  //Serial.println(pause);
}

void nextLed(){
  led += 1;
  if ( led == 7 )
    led = 2;
}
