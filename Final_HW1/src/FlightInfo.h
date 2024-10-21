#ifndef FLIGHTINFO_H
#define FLIGHTINFO_H

#include <string>
using namespace std;
//Flight Info struct header
struct FlightInfo {
   //variable decalarations 
    string departure;
    string destination;
    int distance;

    // Constructor declaration
    FlightInfo(const string& dep, const string& dest, int dist);
};

#endif // FLIGHTINFO_H
