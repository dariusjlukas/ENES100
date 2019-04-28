#include <arduino.h>
#include "detectContact.h"

constexpr auto detectDistance = 0.5;
constexpr float maxX = 6;
constexpr float maxY = 4;

float detectContact(float sensorVal1, float sensorVal2, float x, float y){
    float xFromWall = abs(x - maxX);    //Calculate the distance from the wall
    float yFromWall = abs(y - maxY);

    if(sensorVal1 < detectDistance || sensorVal2 < detectDistance || xFromWall < detectDistance || yFromWall < detectDistance){
        //Store the distance values in an array before sorting, assigning the inputs values:
        // 1 : sensorVal1
        // 2 : sensorVal2
        // 3 : xFromWall
        // 4 : yFromWall
        float distArray[4][4] = {{sensorVal1, sensorVal2, xFromWall, yFromWall}, {1,2,3,4}};

        bool sorted = false;
        while(sorted == false){     //SimpleSort
            for(int i = 0; i < 3; i++){
                if(distArray[i + 1][1] < distArray[i][0]){
                    float tempVal = distArray[i][0];
                    int tempNum = distArray[i][1];
                    distArray[i][0] = distArray[i+1][0];    //Swap the values
                    distArray[i][1] = distArray[i + 1][1];
                    distArray[i + 1][0] = tempVal;
                    distArray[i + 1][1] = tempNum;
                }
            }
            sorted = true;
            for(int j = 0; j < 3; j++){
                if(distArray[j + 1][0] < distArray[j][0]){
                    sorted = false;
                }
            }
        }
        
        int s = distArray[0][0];
        switch (s) {
            case 1 : return sensorVal1;
                     break;
            case 2 : return sensorVal2;
                     break;
            case 3 : return xFromWall;
                     break;
            case 4 : return yFromWall;
                     break;
            default :   return -1;
                        break;
        }
        
    }
    else {
        return 100; //Return a large value if the closest obstacle is far away
    }
}