#include <Wire.h>
class LaserRange{
    public:
    int address;
    long distance = 0;

    LaserRange(int a){
        address = a;
    }

    void setup(){
        Wire.begin();
    }

    long getRange(){
        Wire.requestFrom(address, 2);  //Request 8 bytes from address 85 (0x55 in hex)
  
        while(Wire.available()) {
        distance = distance + Wire.read();
        }
        
        return(distance);
        distance = 0; //Reset the distance measurment
    }
};