#include "Enes100.h"

void setup() {
    // Initialize Enes100 library
    // Team Name, Mission Type, Marker ID, RX Pin, TX Pin
    Enes100.begin("It's Lit", FIRE, 3, 8, 9);

    Enes100.print("Destination is at (");
    Enes100.print(Enes100.destination.x);
    Enes100.print(", ");
    Enes100.print(Enes100.destination.y);
    Enes100.println(")");

    // Any other setup code...
}

void loop() {
    // Update the OSV's current location
    if (Enes100.updateLocation()) {
        Enes100.print("OSV is at (");
        Enes100.print(Enes100.location.x);
        Enes100.print(", ");
        Enes100.print(Enes100.location.y);
        Enes100.print(", ");
        Enes100.print(Enes100.location.theta);
        Enes100.println(")");
    } else {
        // OSV's location was not found
        Enes100.println("404 Not Found");
    }
    
    // Transmit the number of candles that are lit
    Enes100.mission(BASE, 4);
}
