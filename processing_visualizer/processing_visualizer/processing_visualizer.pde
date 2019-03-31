import processing.serial.*;

Serial serial; //Create a serial object

String serialData = null; //variable to store serial data
String [] words;
int nl = 10; //ASCII code for carage return
float numSerialData; //float serial data
float distance1 = -1;

float robotX;
float robotY;
float robotW = 20;
float robotH = 20;
float sizeMultiplyer = 2; //The default scaling is one pixel per one cm, but the sizeMultiplyer scales everything up

void setup(){
  size(600, 600);
  robotX = width/2;
  robotY = height/2;
  
  //Open serial port
  String port = Serial.list() [0]; //get the serial port
  serial = new Serial(this, port, 9600);
}

void draw() {
  background(255); //Reset the background (clear the screen)
  drawRobot(robotX, robotY, robotW, robotH, sizeMultiplyer);  //Draw the robot
  
  while (serial.available() > 0){ //Check that there is information available on the serial port
    //serialData = serial.readStringUntil(nl);
    serialData = serial.readStringUntil(nl);
    if(serialData != null){
    words = serialData.split("[ ]+");
      for(int i = 0; i < words.length; i++){
         print(float(words[i])); 
         print(" ");
      }
      println();
      
      distance1 = float(words[0]);  //Update the value of the distance variable based on what came in over serial
      serialData = null; //Set the serial data variable back to null so it does not get continuously read
    }
  }
  
  if(distance1 != -1){  //Check that a distance value has been recieved
    drawObstacle(robotX, robotY, robotW, robotH, 1, distance1, sizeMultiplyer); //Draw the obstacle
  }
}

//Custom functions//
void drawRobot(float x, float y, float rWidth, float rHeight, float sM){
  fill(0,0,200);
  rect(x - (rWidth*sM)/2, y - (rHeight*sM)/2, rWidth * sM, rHeight * sM);  //Draw the robot as a rectangle
}

void drawObstacle(float rX, float rY, float rW, float rH, int sensorNum, float distance, float sM){
  if(distance < 50){  //Distances 50 and above should not be drawn because they will be ignored  
  rW = rW * sM;
  rH = rH * sM;
  distance = distance * sM;
  
  switch(sensorNum)
  {
   case 1:
     strokeWeight(5);
     line(rX  - rW/2, rY - rH/2 - distance, rX + rW/2, rY - rH/2 - distance);  //Draw the obstacle as a line
     strokeWeight(1);
     break;
   default :
     println("Invalid sensor number");
  }
  }
}
