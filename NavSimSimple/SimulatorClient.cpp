#include "SimulatorClient.h"

SimulatorClient::SimulatorClient() {

}

bool SimulatorClient::begin() {
    Serial.begin(9600);
    Serial.setTimeout(300);

    Serial.print("#destination*");
    Serial.flush();

    unsigned long start = millis();
    int state = 0;

    while((millis() - start) < 300) {
        if (Serial.available()) {
            switch(state) {
                case 0:
                destination.x = Serial.parseFloat();
                state++;
                break;
                case 1:
                destination.y = Serial.parseFloat();
                state++;
                break;
                case 2:
                return true;
                break;
                default:
                return false;
                break;
            }
        }
    }

    return false;

}

bool SimulatorClient::updateLocation() {
  Serial.print("#location*");
  Serial.flush();

  unsigned long start = millis();
  int state = 0;

  while((millis() - start) < 300) {
    if(Serial.available()) {
      switch(state) {
        case 0:
        location.x = Serial.parseFloat();
        state++;
        break;

        case 1:
        location.y = Serial.parseFloat();
        state++;
        break;

        case 2:
        location.theta = Serial.parseFloat();
        return true;
        break;

        default:
        return false;
        break;
      }
    }
  }
  return false;
}

float SimulatorClient::readDistanceSensor(int sensorIndex) {
    Serial.print("#distance");
    Serial.print(sensorIndex);
    Serial.print("*");
    Serial.flush();

    unsigned long start = millis();

    while((millis() - start) < 300) {
        if(Serial.available()) {
            return Serial.parseFloat();
        }
    }

    return 0;
}

void SimulatorClient::print(const char *msg) {
    Serial.print(msg);
    Serial.flush();
}

void SimulatorClient::print(int msg) {
    Serial.print(msg);
    Serial.flush();
}

void SimulatorClient::print(double msg) {
    Serial.print(msg);
    Serial.flush();
}

void SimulatorClient::println(const char *msg) {
    Serial.println(msg);
    Serial.flush();
}

void SimulatorClient::println(int msg) {
    Serial.println(msg);
    Serial.flush();
}

void SimulatorClient::println(double msg) {
    Serial.println(msg);
    Serial.flush();
}

