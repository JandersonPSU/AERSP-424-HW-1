#include "FlightInfo.h"
#include <string>

// Correct constructor definition with scope resolution
FlightInfo::FlightInfo(const std::string& dep, const std::string& dest, int dist)
    : departure(dep), destination(dest), distance(dist) {}
