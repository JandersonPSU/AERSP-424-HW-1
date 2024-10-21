#include "Pilot.h"
#include <iostream>

using namespace std;

Pilot::Pilot(const string& pilotName, Plane* plane)
    : name(pilotName), myPlane(plane) {
    cout << "Pilot " << name << " with certificate number " << this
         << " is at the gate, ready to board the plane." << endl;
}

Pilot::~Pilot() {
    cout << "Pilot " << name << " with certificate number " << this
         << " is out of the plane." << endl;
}

string Pilot::getName() const { return name; }
