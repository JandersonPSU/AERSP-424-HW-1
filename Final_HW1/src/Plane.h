#ifndef PLANE_H
#define PLANE_H

#include <iostream>
#include <string>
#include <vector>
#include "FlightInfo.h"

using namespace std;
//Plane Class Header
class Plane {
private:
    double pos;               // Position of the plane
    double vel;               // Velocity of the plane
    double distance;          // Total distance for the flight
    bool at_SCE;              // Whether the plane is at SCE or not
    string origin;            // Origin of the flight
    string destination;       // Destination of the flight
    vector<FlightInfo> flights; // Container for flight information

public:
    // Constructor
    Plane(const string& from, const string& to);

    // Destructor
    ~Plane();

    // Operate function to move the plane
    void operate(double dt);

    // Getters
    double getPos() const;
    string getOrigin() const;
    string getDestination() const;
    bool getAtSCE() const;

    // Velocity getter and setter
    double getVel() const;
    void setVel(double v);
};

#endif // PLANE_H
