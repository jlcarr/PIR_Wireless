#define TX_PIN 0
#define READ_PIN 3
#define ON_DELAY 1000
#define OFF_DELAY 2000

void setup(){
  pinMode(TX_PIN, OUTPUT); 
  pinMode(READ_PIN, INPUT);
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
}
