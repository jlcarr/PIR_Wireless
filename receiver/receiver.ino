#define RX_PIN 0
#define ON_PIN 6
#define ERROR_PIN 7


int state = 0;
unsigned long previousMillis = 0;
unsigned long DELAY = 0;
unsigned long switch_time = 0;

void setup(){  
  Serial.begin(9600);
  pinMode(RX_PIN, INPUT);
  pinMode(ON_PIN, OUTPUT);
  pinMode(ERROR_PIN, OUTPUT);  
}

void loop(){
  unsigned long currentMillis = millis();
  
  if(currentMillis - previousMillis >= 1000){
    previousMillis = currentMillis;
    if(DELAY > 25 && DELAY < 75){
      Serial.println("ON");
      digitalWrite(ON_PIN,HIGH);
      digitalWrite(ERROR_PIN,LOW);
    }
    else if (DELAY > 75 && DELAY < 125){
      Serial.println("OFF");
      digitalWrite(ON_PIN,LOW);
      digitalWrite(ERROR_PIN,LOW);
    }
    else{
      Serial.println("UNKNOWN");
      digitalWrite(ON_PIN,LOW);
      digitalWrite(ERROR_PIN,HIGH);
    }
    Serial.println("Current");
    Serial.println(DELAY);
    Serial.println(state);
  }
  
  if(digitalRead(RX_PIN) && state == 0){
    state = 1;
    switch_time = millis();
  }
  else if(!digitalRead(RX_PIN) && state != 0){
    state = 0;
    DELAY = millis() - switch_time;
  }
  
}
