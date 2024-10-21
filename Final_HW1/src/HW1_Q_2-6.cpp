#include <iostream>
#include "Plane.h"  // Brings in the Plane class definition
#include "Pilot.h"  // Brings in the Pilot class definition
#include <string>


using namespace std;

//(QUESTION 05)
int main() {
    double flight_speed=0;
    while(flight_speed<400 ||flight_speed>500){
        cout<<"Pick a flight speed between 400 and 500 mph"<<endl;
        cin>>flight_speed;
    }
    flight_speed=flight_speed/3600; //setting to mi/sec

    string input_from="init";
    string input_to="init";
    //Checking that the cin inputs are correct
    while (input_from!="SCE"&&input_from!="PHL"&&input_from!="ORD"&&input_from!="EWR"){
        cout<<"Enter the starting location (must be SCE, PHL, ORD, or EWR): "<<endl;
        cin>>input_from;
    }
    while (input_to!="SCE"&&input_to!="PHL"&&input_to!="ORD"&&input_to!="EWR"){
        cout<<"Enter the final location (must be SCE, PHL, ORD, or EWR): "<<endl;
        cin>>input_to;
        if (input_from==input_to){
            cout<<"Do not set the same starting and ending point,try again please"<<endl;
        }
    }

    Plane plane(input_from, input_to); // Creating an instance of the Plane class from State college to philadelphia
    plane.setVel(flight_speed); // Using the velset function to set the plane's flight speed

    double timestep=0.0; //initializing the timestep
    while(timestep<10||timestep>100){
        cout<<"Pick a time step between 10 and 100"<<endl;
        cin>>timestep;
    }
    int iterations=0; //initializing the iterations
    while(iterations<1000||iterations>2000){
        cout<<"Pick a number of iterations between 1000 and 2000"<<endl;
        cin>>iterations;
    }

    //iterating
    for(int current_iteration=0;current_iteration<iterations;current_iteration++){
        cout<<"Time: "<<current_iteration*timestep<<" seconds, Position: "<<plane.getPos()<<" miles."<<endl;
        plane.operate(timestep);
    }
    
    return 0;
}