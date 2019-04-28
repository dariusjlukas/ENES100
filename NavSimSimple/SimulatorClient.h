#ifndef SimulatorClient_h
#define SimulatorClient_h

#include <Arduino.h>

#ifndef Coordinate_h
#define Coordinate_h

class Coordinate {
public:
    double x;
    double y;
    double theta;
    Coordinate() {
        init(0, 0, 0);
    }

    Coordinate(double x, double y) {
        init(x, y, 0);
    }

    Coordinate(double x, double y, double theta) {
        init(x, y, theta);
    }
private:
    void init(double x, double y, double theta) {
        this->x = x;
        this->y = y;
        this->theta = theta;
    }
};
#endif

class SimulatorClient {

public:

    Coordinate destination;
    Coordinate location;

    SimulatorClient();

    bool begin();
    bool updateLocation();
    float readDistanceSensor(int sensorIndex);

    void print(const char *msg);
    void print(int msg);
    void print(double msg);

    void println(const char *msg);
    void println(int msg);
    void println(double msg);

};


#endif
