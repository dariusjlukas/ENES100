#include <Wire.h>//Request 8 bytes from address 85 (0x55 in hex)
class LaserRange{

public:
    int address = 0;
    LaserRange(int a){
        address = a;
    }

    void setup(){
        Wire.begin();
    }

    long getRange(){
        long distance = 0;
        Wire.requestFrom(85, 2);  //Request 8 bytes from address 85 (0x55 in hex)
  
        while(Wire.available()) {
            distance = distance + Wire.read();
        }
        return distance;
    }
};