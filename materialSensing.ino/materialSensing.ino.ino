//Outputs the material in the claw
//Tested with 4 magnets, and the orientation does matter

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println(analogRead(A0));
  if(analogRead(A0) > 502){
    Serial.println("Copper (or empty)");
  }
  else if(analogRead(A0) < 501 && analogRead(A0) > 493){
    Serial.println("Steel");
  }
  if(analogRead(A0) <= 493){
    Serial.println("The claw is open");
  }
  
  
}
