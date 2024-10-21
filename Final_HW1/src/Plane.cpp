#include "Plane.h"
#include "FlightInfo.h"

using namespace std;
//Plane Constructor
Plane::Plane(const string& from, const string& to)
    : pos(0.0), vel(0.0), at_SCE(false), origin(from), destination(to) {
    //setting flightinfo container
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
    //Output plane address
    cout << "Plane Created with a tail number: " << this << endl;
}
//Plane Destructor
Plane::~Plane() {
    //plane destructor print statements
    cout << "Plane Destroyed" << endl;
}
//Operate function in Plane
void Plane::operate(double dt) {
    //Running if position is less than distance
    if (pos < distance) {
        pos += vel * dt;//Adding the updated distance traveled to the position
        
        at_SCE = false;//setting the at state college bool to false
    } else {
        //Runs when you are beyond the distance
        //printing where you are and where you can from.
        cout << "Navigation from " << origin << " to " << destination
             << " has been completed. On to the next leg!" << endl;
        
        //Running if you are at State college
        if (destination == "SCE") {
            at_SCE = true; //setting the state college bool to true if you are at state college
        }
        swap(origin, destination); //swapping the origin and destination
        pos = 0.0; //resetting position to 0 miles
    }
}
//variable initialization
double Plane::getPos() const { return pos; }
string Plane::getOrigin() const { return origin; }
string Plane::getDestination() const { return destination; }
bool Plane::getAtSCE() const { return at_SCE; }
double Plane::getVel() const { return vel; }
void Plane::setVel(double v) { vel = v; }
