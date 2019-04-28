const int trigPin = 9;
const int echoPin = 10;

long duration;  //Duration and distance values from the ultrasonic sensor
int distance;
int distArray [10];
int distArrayCount = 0;
float averageDistance = -1;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  //Clear the triger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);     ////!!!Fix this with scheduling!!!///
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);  ////!!!Fix this with scheduling!!!///
  digitalWrite(trigPin, LOW);

  
  duration = pulseIn(echoPin, HIGH);  //Read the duration of the pulse on the echo pin

  distance = duration*0.034/2;

  if(distance > 50){  //If the distance is greater than 50, cap it to 55
    distance = 55;
  }

  distArray[distArrayCount] = distance;

  if(distArrayCount == 9){
    for(int i = 0; i < 10; i++){
      averageDistance = averageDistance + distArray[i];
    }
    averageDistance = averageDistance/10;
    distArrayCount = 0;
  }
  else{
    distArrayCount++;
  }

  
  Serial.println(averageDistance); //Print debug values

}
