int sensorPin = A0;
int sensorValue = 0;
int led= 4;
int i;
int n;

void setup() {
  Serial.begin(9600);
  pinMode(led,OUTPUT);
  i=1;
}

void loop() {
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  motorControl();
  delay(5000);
}
int motorControl(){
  if(sensorValue>500){
    digitalWrite(led,HIGH);
    Serial.println("on");
    i++;
    
    if(i<7){
    i=i;}
    
    else{
      i=0;
    }
  }
  else if(sensorValue<500& i!=0){
    digitalWrite(led,HIGH);
    Serial.println("on");
    i++;
    if(i<7){
    i=i;
    }
    else{
      i=0;
    }
    }
    
  else{
    digitalWrite(led,LOW);
    Serial.println("off");
    i=0;
    }
      Serial.println("i=");
      Serial.print(i);
  }
