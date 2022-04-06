void setup() {
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(HIGH);
  
}

void loop() {
  int a = Serial.read();
  a-= 48;
  if(a == 1){
    if(bitRead(PORTD, 3) == HIGH){
      digitalWrite(3, LOW);
      Serial.write("off");
    }
      
    else{
      digitalWrite(3, HIGH);
      Serial.write("on");
    }
  }
    
    
}
