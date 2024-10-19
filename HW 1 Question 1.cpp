#include <iostream>
#include <iomanip>
#include <utility>
#include <vector>
#include <string>

using namespace std;

int main()
{
    double DryWeight;
    double DryWeightMoment; // Pound-Inch

    int NumFrontPassengers;
    double FrontSeatMomentArm; // Inch

    int NumRearPassengers;
    double RearSeatMomentArm; // Inch

    double MaxFuel; //Gallons
    double FuelDenisty; // Pounds per Gallon
    double FuelMomentArm; // Inch

    double BaggageWeight; // Pound
    double BaggageMomentArm; // Inch
    
    double MaxWetWeight = 2950; // Pound
    double CGForwardLim = 82.1; // Inch
    double CGRearLim = 84.7; // Inch

    cout << endl << "Please enter the airplane empty weight in pounds:" << endl;
    cin >> DryWeight;
    cout << endl << "Please enter the airplane empty-weight moment in pounds-inches:" << endl;
    cin >> DryWeightMoment;

    cout << endl << "Please enter the number of front seat occupants:" << endl;
    cin >> NumFrontPassengers;
    cout << endl << "Please enter the front seat moment arm in inches:" << endl;
    cin >> FrontSeatMomentArm;

    cout << endl << "Please enter the number of rear seat occupants:" << endl;
    cin >> NumRearPassengers;
    cout << endl << "Please enter the rear seat moment arm in inches:" << endl;
    cin >> RearSeatMomentArm;

    cout << endl << "Please enter the number of gallons of usable fuel:" << endl;
    cin >> MaxFuel;
    cout << endl << "Please enter the usable fuel weight per gallon using units of pounds per gallon:" << endl;
    cin >> FuelDenisty;
    cout << endl << "Please enter the fuel tank moment arm in inches:" << endl;
    cin >> FuelMomentArm;

    cout << endl << "Please enter the baggage weight in pounds:" << endl;
    cin >> BaggageWeight;
    cout << endl << "Please enter the baggage moment arm in inches:" << endl;
    cin >> BaggageMomentArm;
}