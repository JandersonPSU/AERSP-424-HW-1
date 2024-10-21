#include "Plane.h"
#include "FlightInfo.h"

using namespace std;

Plane::Plane(const string& from, const string& to)
    : pos(0.0), vel(0.0), at_SCE(false), origin(from), destination(to) {
    flights = {
        FlightInfo("SCE", "PHL", 160),
        FlightInfo("SCE", "ORD", 640),
        FlightInfo("SCE", "EWR", 220)
    };

    // Find the distance for the flight
    for (const auto& flight : flights) {
        if ((flight.departure == origin && flight.destination == destination) ||
            (flight.departure == destination && flight.destination == origin)) {
            distance = flight.distance;
            break;
        }
    }
    cout << "Plane Created with a tail number: " << this << endl;
}

Plane::~Plane() {
    cout << "Plane Destroyed" << endl;
}

void Plane::operate(double dt) {
    if (pos < distance) {
        pos += vel * dt;
        at_SCE = false;
    } else {
        cout << "Navigation from " << origin << " to " << destination
             << " has been completed. On to the next leg!" << endl;

        if (destination == "SCE") {
            at_SCE = true;
        }
        swap(origin, destination);
        pos = 0.0;
    }
}

double Plane::getPos() const { return pos; }
string Plane::getOrigin() const { return origin; }
string Plane::getDestination() const { return destination; }
bool Plane::getAtSCE() const { return at_SCE; }
double Plane::getVel() const { return vel; }
void Plane::setVel(double v) { vel = v; }
