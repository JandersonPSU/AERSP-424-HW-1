#ifndef PILOT_H
#define PILOT_H

#include <iostream>
#include <string>
#include "Plane.h"

using namespace std;

//Pilot Class Header
class Pilot {
private:
    string name;

public:
    Plane* myPlane;

    Pilot(const string& pilotName, Plane* plane);
    ~Pilot();

    string getName() const;
};

#endif // PILOT_H
