#include <iostream>
#include <cmath>
#include <vector>
#include <string>

using namespace std;

// Creating a struct for the flight info
struct FlightInfo {
    string departure; // defining a string for the departure location
    string destination; // defining a string for the destination location
    int distance; // defining the distance travelled in miles

    // Constructor
    FlightInfo(const string& dep, const string& dest, int dist)
        : departure(dep), destination(dest), distance(dist) {}
};

// Plane class definition (QUESTION 03/QUESTION 04)
class Plane {
private:
    double pos;              // Position of the plane
    double vel;              // Velocity of the plane
    double distance;         // Total distance for the flight
    bool at_SCE;             // Whether the plane is at SCE or not
    string origin;           // Origin of the flight
    string destination;      // Destination of the flight
    vector<FlightInfo> flights; // Container for flight information

public:
    // Constructor that takes in two locations (origin and destination)
    Plane(const string& from, const string& to)
        : pos(0.0), vel(0.0), at_SCE(0), origin(from), destination(to) {
        // Initialize flight data 
        flights = {
            FlightInfo("SCE", "PHL", 160),
            FlightInfo("SCE", "ORD", 640),
            FlightInfo("SCE", "EWR", 220)
        };

        // Find the distance for the current flight
        for (const auto& flight : flights) {
            if ((flight.departure == origin && flight.destination == destination) || (flight.departure == destination && flight.destination == origin)) {
                distance = flight.distance; // Match the destination and origin
                break;
            }
        }
        cout << "Plane Created with a tail number:  " << this << endl; // Print the memory address of the plane
    }

    // Destructor 
    ~Plane() {
        cout << "Plane Destroyed" << endl;
    }

    // Operate function to move the plane based on the velocity and timestep
    void operate(double dt) {
        if (pos < distance) {
            pos += vel * dt;
            at_SCE = false;
        }
        else {
            cout << "Navgation from " << origin << " to " << destination << " has been completed. On to the next leg!" << endl;
            if (destination == "SCE") {
                at_SCE = true;
            }
            // Swap origin and destination
            string temp = origin;
            origin = destination;
            destination = temp;
            pos = 0.0; // Reset position for the next leg
        }
    }

    // Getter functions for pos, origin, destination, and at_SCE
    double getPos() const { return pos; }
    string getOrigin() const { return origin; }
    string getDestination() const { return destination; }
    bool getAtSCE() const { return at_SCE; }

    // Getter and setter for velocity
    double getVel() const { return vel; }
    void setVel(double v) { vel = v; }
};

// Pilot class (QUESTION 06)
class Pilot {
private:
    string name;

public:
    Plane* myPlane;

    Pilot(const string& pilotName, Plane* plane)
        : name(pilotName), myPlane(plane) {
        cout << "Pilot " << name << " with certificate number " << this << " is at the gate, ready to board the plane." << endl;
    }

    ~Pilot() {
        cout << "Pilot " << name << " with certificate number " << this << " is out of the plane." << endl;
    }

    string getName() const { return name; }
};

// Main function (QUESTION 05)
int main() {
    cout<<"######################## QUESTION 7 ########################"<<endl;
    double flight_speed = 0;
    while (flight_speed < 400 || flight_speed > 500) {
        cout << "Pick a flight speed between 400 and 500 mph: ";
        cin >> flight_speed;
    }
    flight_speed = flight_speed / 3600; // Convert to miles per second

    string input_from = "init";
    string input_to = "init";

    // Getting user input for departure and destination
    while (input_from != "SCE" && input_from != "PHL" && input_from != "ORD" && input_from != "EWR") {
        cout << "Enter the starting location (must be SCE, PHL, ORD, or EWR): ";
        cin >> input_from;
    }
    while (input_to != "SCE" && input_to != "PHL" && input_to != "ORD" && input_to != "EWR") {
        cout << "Enter the destination location (must be SCE, PHL, ORD, or EWR): ";
        cin >> input_to;
        if (input_from == input_to) {
            cout << "Starting location and destination cannot be the same. Please try again." << endl;
        }
    }

    // Create the plane
    Plane plane(input_from, input_to);
    plane.setVel(flight_speed); // Set the planes velocity

    // Create two pilot objects
    Pilot pilot1("Alpha", &plane); // This will be the starting pilot
    Pilot pilot2("Unknown", nullptr); 

    // Get user input for timestep and iterations
    double timestep = 0.0;
    while (timestep < 10 || timestep > 100) {
        cout << "Pick a time step between 10 and 100: ";
        cin >> timestep;
    }

    int iterations = 0;
    while (iterations < 1000 || iterations > 2000) {
        cout << "Pick a number of iterations between 1000 and 2000: ";
        cin >> iterations;
    }

    // Start with pilot1 who is is in control
    Pilot* currentPilot = &pilot1;
    Pilot* standbyPilot = &pilot2;

    // Iterating 
    for (int current_iteration = 0; current_iteration < iterations; current_iteration++) {
        if (current_iteration==0){
            // Print info about the pilots/plane 
            cout <<endl<< "Pilot " << currentPilot->getName() << " with certificate number " << currentPilot << " is in control of a plane: " << currentPilot->myPlane << endl;
            cout << "Pilot " << standbyPilot->getName() << " with certificate number " << standbyPilot << " is in control of a plane: " << standbyPilot->myPlane << endl<<endl;
        }
        //cout << "Time: " << current_iteration * timestep << " seconds, Position: " << plane.getPos() << " miles." << endl;
        plane.operate(timestep);

        // Check if the plane is at SCE as question requests
        if (plane.getAtSCE()) {
            cout << "The plane " << &plane << " is at SCE." << endl;

            // Swap pilots
            swap(currentPilot, standbyPilot);

            // Assign the plane to the new pilot
            currentPilot->myPlane = &plane;
            standbyPilot->myPlane = nullptr;

            // Print info about the pilots/plane 
            cout <<endl<< "Pilot " << currentPilot->getName() << " with certificate number " << currentPilot << " is in control of a plane: " << currentPilot->myPlane << endl;
            cout << "Pilot " << standbyPilot->getName() << " with certificate number " << standbyPilot << " is in control of a plane: " << standbyPilot->myPlane << endl<<endl;
        }
    }

    return 0;
}
