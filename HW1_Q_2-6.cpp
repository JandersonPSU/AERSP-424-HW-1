#include <iostream>
#include <cmath>
#include <vector>
#include <string>


using namespace std;
//Creating a struct for the flight info
struct FlightInfo {
    string departure; //defining a string for the departure location
    string destination; //defining a string for the destination location
    int distance; //defining the distance travelled in miles

    // Constructor (Used ChatGPT for the constructor)
    FlightInfo(const string& dep, const string& dest, int dist)
        : departure(dep), destination(dest), distance(dist) {}
};

// Plane class definition (QUESTION 03/QUESTION 04)
class Plane {
private:
    //Variable Declaration
    double pos;              // Position of the plane
    double vel;              // Velocity of the plane
    double distance;         // Total distance for the flight
    bool at_SCE;             // Whether the plane is at SCE or not
    string origin;      // Origin of the flight
    string destination; // Destination of the flight
    vector<FlightInfo> flights; // Container for flight information

public:
    // Constructor that takes in two from and to
    Plane(const string& from, const string& to) 
        : pos(0.0), vel(0.0), at_SCE(0), origin(from), destination(to) {
        // Initialize flight data 


        //Get the FlightInfo Struct
        flights = {
            FlightInfo("SCE", "PHL", 160),
            FlightInfo("SCE", "ORD", 640),
            FlightInfo("SCE", "EWR", 220)
        };

        // Find the distance for the current flight by looping through the FlightInfo struct
        for (const auto& flight : flights) {
            if ((flight.departure == origin && flight.destination == destination) || (flight.departure == destination && flight.destination == origin)) {
                distance = flight.distance; //storing the distance by matching the destination and origin (forawrds and backwards matching)
                break;
            }
        }
        cout<<"Plane Created at: "<<this<<endl; //Printing the Plane was created and printing its memory address using the this pointer
    }

    // Destructor 
    ~Plane() {
        cout<<"Plane Destroyed" <<endl; //Printing the plane destroyed in the deconstructor
    }

    // Operate function 
    void operate(double dt) {
        if (pos<distance){
            pos+=vel*dt;
            at_SCE=0;
        }
        else{
            cout<<"Arrived at: "<<destination<<" from: "<< origin<<". Turning around:"<<endl;
            if (destination == "SCE"){
                at_SCE==1;
            }
            string temp=origin;
            origin=destination;
            destination=temp;
            pos=0.0;
        }
    }

    // Getter functions for pos, origin, destination, and at_SCE
    double getPos() const { return pos; } //Get func for position
    string getOrigin() const { return origin; }//Get func for origin
    string getDestination() const { return destination; }//Get func for destination
    bool getAtSCE() const { return at_SCE; }//Get func for at_sce

    // Getter and setter for vel
    double getVel() const { return vel; } //Get func for vel
    void setVel(double v) { vel = v; } //Set function for velocity
};

//(QUESTION 06)
class Pilot {
private:
    //Variable Declaration
    string name;
public:
    Plane* myPlane;
    Pilot(const string& pilotName, Plane* plane) 
        : name(pilotName), myPlane(plane){
        cout<<"The pilot's name is: "<<name<<endl<<"The memory address is: "<<this<<endl<<"The pilot is at the gate and ready to board the plane."<<endl; 
    }
    ~Pilot(){
        cout<<"The pilot's name is: "<<name<<endl<<"The pilot is out of the plane."<<endl; 
    }
    
    string getName() const { return name;}


};

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