#define TX_PIN 0
#define READ_PIN 3
#define ON_DELAY 50
#define OFF_DELAY 100

void setup(){
  pinMode(TX_PIN, OUTPUT); 
  pinMode(READ_PIN, INPUT);
}

void loop(){
  if(digitalRead(READ_PIN)){
    digitalWrite(TX_PIN,LOW);
    delay(ON_DELAY);
    digitalWrite(TX_PIN,HIGH);
    delay(ON_DELAY);
  }
  else{
    digitalWrite(TX_PIN,LOW);
    delay(OFF_DELAY);
    digitalWrite(TX_PIN,HIGH);
    delay(OFF_DELAY);
  }
}
