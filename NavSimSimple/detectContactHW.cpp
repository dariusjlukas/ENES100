#include <Arduino.h>
#include "detectContact.h"

constexpr auto detectDistance = 1.0;
constexpr float maxX = 3.8;
constexpr float maxY = 1.85;

float detectContact(float sensorVal1, float sensorVal2, float x, float y){
    float xFromWall;
    float yFromWall;

    if(x >= (maxX/2)){
        xFromWall = abs(x - maxX);    //If the rover is on the right side of the field, set the distance from the wall to be 
    }
    else{
        xFromWall = x;    //If the rover is on the right side of the field, set the distance from the wall to be
    }

    if(y >= (maxY/2)){
        yFromWall = abs(y - maxY);
     }
     else{
         yFromWall = y;
     }

    if(sensorVal1 < detectDistance || sensorVal2 < detectDistance || xFromWall < detectDistance || yFromWall < detectDistance){
        //Store the distance values in an array before sorting, assigning the inputs values:
        // 1 : sensorVal1
        // 2 : sensorVal2
        // 3 : xFromWall
        // 4 : yFromWall
        float min1 = min(sensorVal1, sensorVal2);
        float min2 = min(xFromWall, yFromWall);
        return min(min1, min2);

       
        
    }
    else {
        return 100; //Return a large value if the closest obstacle is far away
    }
}