#include "Pilot.h"
#include <iostream>

using namespace std;
//Pilot Constructor
Pilot::Pilot(const string& pilotName, Plane* plane)
    : name(pilotName), myPlane(plane) {
        //Printing statements
    cout << "Pilot " << name << " with certificate number " << this
         << " is at the gate, ready to board the plane." << endl;
}
//Pilot Deconstructor
Pilot::~Pilot() {
    //Destructor printing statements
    cout << "Pilot " << name << " with certificate number " << this
         << " is out of the plane." << endl;
}
//Pilot Getname Function
string Pilot::getName() const { return name; }
