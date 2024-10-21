#ifndef PLANE_H
#define PLANE_H

#include "FlightInfo.h"
#include <string>

class Plane {
public:
    Plane(const FlightInfo& info);
    void displayDetails();

private:
    FlightInfo flightInfo;
};

#endif // PLANE_H
