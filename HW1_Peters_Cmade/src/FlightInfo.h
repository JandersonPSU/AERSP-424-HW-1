#ifndef FLIGHTINFO_H
#define FLIGHTINFO_H

#include <string>
using namespace std;

struct FlightInfo {
    string departure;
    string destination;
    int distance;

    FlightInfo(const string& dep, const string& dest, int dist)
        : departure(dep), destination(dest), distance(dist) {}
};

#endif // FLIGHTINFO_H
