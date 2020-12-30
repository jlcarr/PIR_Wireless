#define TX_PIN 0
#define READ_PIN 3
#define ON_DELAY 1000
#define OFF_DELAY 2000

#define RX_PIN 0


int state = 0;
unsigned long previousMillis = 0;
long DELAY = 0;
unsigned long switch_time = 0;

void setup(){
  pinMode(TX_PIN, OUTPUT); 
  pinMode(READ_PIN, INPUT);
  
  Serial.begin(9600);
  pinMode(RX_PIN,INPUT);
}

void loop(){
  if(digitalRead(READ_PIN)){
    digitalWrite(TX_PIN,LOW);
    delayMicroseconds(ON_DELAY);
    digitalWrite(TX_PIN,HIGH);
    delayMicroseconds(ON_DELAY);
  }
  else{
    digitalWrite(TX_PIN,LOW);
    delayMicroseconds(OFF_DELAY);
    digitalWrite(TX_PIN,HIGH);
    delayMicroseconds(OFF_DELAY);
  }
  
  
  unsigned long currentMillis = millis();
  
  if(currentMillis - previousMillis >= 100){
    previousMillis = currentMillis;
    if(DELAY > 800 && DELAY < 1200){
      Serial.println("OFF");
    }
    else{
      Serial.println("ON");
    }
    Serial.println(DELAY);
  }
  
  if(digitalRead(RX_PIN) && state == 0){
    state = 1;
    switch_time = micros();
  }
  else if(!digitalRead(RX_PIN) && state != 0){
    state = 0;
    DELAY = micros() - switch_time;
  }
  
}
