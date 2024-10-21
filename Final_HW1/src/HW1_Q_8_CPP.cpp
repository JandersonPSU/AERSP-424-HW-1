#include <iostream>
#include "Plane.h"  // Brings in FlightInfo.h indirectly
#include "Pilot.h"  

using namespace std;

// Main function (QUESTION 08)
int main() {
    cout<<"######################## QUESTION 8 ########################"<<endl;
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

     // Create the plane using std::unique_ptr
    auto plane = make_shared<Plane>(input_from, input_to);
    plane->setVel(flight_speed); // Set the plane's velocity

    // Create two pilot objects using std::unique_ptr
    auto pilot1 = make_shared<Pilot>("Alpha", plane.get()); // Pilot 1 in control initially
    auto pilot2 = make_shared<Pilot>("Unknown", nullptr);

    // Start with pilot1 who is in control
    shared_ptr<Pilot> currentPilot = pilot1;
    shared_ptr<Pilot> standbyPilot = pilot2;

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

    // Iterating 
    for (int current_iteration = 0; current_iteration < iterations; current_iteration++) {
        if (current_iteration==0){
            // Print info about the pilots/plane 
            cout <<endl<< "Pilot " << currentPilot->getName() << " with certificate number " << currentPilot << " is in control of a plane: " << currentPilot->myPlane << endl;
            cout << "Pilot " << standbyPilot->getName() << " with certificate number " << standbyPilot << " is in control of a plane: " << standbyPilot->myPlane << endl<<endl;
        }
        //cout << "Time: " << current_iteration * timestep << " seconds, Position: " << plane.getPos() << " miles." << endl;
        plane->operate(timestep);

        // Check if the plane is at SCE as question requests
        if (plane->getAtSCE()) {
            cout << "The plane " << &plane << " is at SCE." << endl;

            // Swap pilots
            swap(currentPilot, standbyPilot);

            // Assign the plane to the new pilot
            currentPilot->myPlane = plane.get();
            standbyPilot->myPlane = nullptr;

            // Print info about the pilots/plane 
            cout <<endl<< "Pilot " << currentPilot->getName() << " with certificate number " << currentPilot << " is in control of a plane: " << currentPilot->myPlane << endl;
            cout << "Pilot " << standbyPilot->getName() << " with certificate number " << standbyPilot << " is in control of a plane: " << standbyPilot->myPlane << endl<<endl;
        }
    }



    return 0;
}
