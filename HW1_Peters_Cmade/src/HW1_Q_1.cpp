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
    
    double MaxWeightTO = 2950; // Pound
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

    double FuelWeight =  MaxFuel*FuelDenisty;

    cout << endl << "Please enter the baggage weight in pounds:" << endl;
    cin >> BaggageWeight;
    cout << endl << "Please enter the baggage moment arm in inches:" << endl;
    cin >> BaggageMomentArm;

double FrontWeightSum = 0;
double RearWeightSum = 0;

    for (int i = 1; i <= NumFrontPassengers; i++) // Used ChatGPT for this to find an error (I had i < NumFrontPassengers which resulted in me having 1 less than desired)
    {
        double FrontWeight = 0;
        cout << endl << "Please enter the weight for front seat occupant " << i << " in pounds: " << endl;
        cin >> FrontWeight;
        FrontWeightSum += FrontWeight;
    }

    cout << endl << "Total front ccupant weight: " << FrontWeightSum << " pounds."  << endl;

    for (int j = 1; j <= NumRearPassengers; j++) 
    {
        double RearWeight = 0;
        cout << endl << "Please enter the weight for rear seat occupant " << j << " in pounds: " << endl;
        cin >> RearWeight;
        RearWeightSum += RearWeight;
    }

    cout << endl << "Total rear occupant weight: " << FrontWeightSum << " pounds." << endl;

    double WeightTO = DryWeight + FrontWeightSum + RearWeightSum + FuelWeight + BaggageWeight;
    double NetMoment = DryWeightMoment + (FrontWeightSum * FrontSeatMomentArm) + (RearWeightSum * RearSeatMomentArm) + (FuelWeight * FuelMomentArm) + (BaggageWeight * BaggageMomentArm);
    double CGLocation = NetMoment / WeightTO; 

    
    if (WeightTO > MaxWeightTO || CGLocation < CGForwardLim || CGLocation > CGRearLim)
    {
    
        if (WeightTO > MaxWeightTO)
        {
            cout << endl << "The current take off weight of the plane (" << fixed << setprecision(2) << WeightTO << ") pounds is above the max designed take off weight of " << fixed << setprecision(2) << MaxWeightTO << " pounds." << endl;
            double FuelWeightRemove = (WeightTO - MaxWeightTO); // Pounds of fuel that need to be removed
            double FuelGallonsRemove = (WeightTO - MaxWeightTO) / FuelDenisty;
            WeightTO -= FuelWeightRemove;
            NetMoment = DryWeightMoment + (FrontWeightSum * FrontSeatMomentArm) + (RearWeightSum * RearSeatMomentArm) + ((FuelWeight - FuelWeightRemove) * FuelMomentArm) + (BaggageWeight * BaggageMomentArm);
            CGLocation = NetMoment / WeightTO; 
            cout << "In order to make take off weight requirements (" << fixed << setprecision(2) << FuelWeightRemove << ") pounds of fuel was removed which is (" << fixed << setprecision(2) << FuelGallonsRemove << ") Gallons." << endl;
            cout << "The new take off weight of the plane is now (" << fixed << setprecision(2) << WeightTO << ") pounds." << endl;
        }

        if (CGLocation < CGForwardLim)
        {   
            cout << endl << "The current location of the center of gravity (CG) of the plane (" << fixed << setprecision(2) << CGLocation << " inches) is ahead of the safe forward limit for the CG which is " 
                 << fixed << setprecision(2)  << CGForwardLim << " inches." << endl;
                
            double NetMomentAdjustFCG = (CGForwardLim - CGLocation) * WeightTO;
            double FuelWeightAjustFCG = NetMomentAdjustFCG / FuelMomentArm;
            double FuelGallonAdjustFCG = FuelWeightAjustFCG / FuelDenisty;
            NetMoment = DryWeightMoment + (FrontWeightSum * FrontSeatMomentArm) + (RearWeightSum * RearSeatMomentArm) + ((FuelWeight - FuelWeightAjustFCG) * FuelMomentArm) + (BaggageWeight * BaggageMomentArm);
            CGLocation = NetMoment / WeightTO;

            double FuelMomentArmCheckFCG = FuelMomentArm - CGForwardLim; 
            
            if (FuelMomentArmCheckFCG < 0) // Fuel needs to be removed
            {
                cout << "In order to make take off CG requirements (" << fixed << setprecision(2) << FuelWeightAjustFCG << ") pounds of fuel was removed which is (" << fixed << setprecision(2) << FuelGallonAdjustFCG << ") Gallons." << endl;
                cout << "The new location of the CG for the plane is at (" << fixed << setprecision(2) << CGLocation << ") inches." << endl;
                MaxFuel -= FuelGallonAdjustFCG;
                WeightTO -= FuelWeightAjustFCG;
            }

            if (FuelMomentArmCheckFCG > 0) // Fuel needs to be added
            {
                cout << "In order to make take off CG requirements (" << fixed << setprecision(2) << FuelWeightAjustFCG << ") pounds of fuel was added which is (" << fixed << setprecision(2) << FuelGallonAdjustFCG << ") Gallons." << endl;
                cout << "The new location of the CG for the plane is at (" << fixed << setprecision(2) << CGLocation << ") inches." << endl;
                MaxFuel += FuelGallonAdjustFCG;
                WeightTO += FuelWeightAjustFCG;
            }
        }


        if (CGLocation > CGRearLim)
        {   
            cout << endl << "The current location of the center of gravity (CG) of the plane (" << fixed << setprecision(2) << CGLocation << " inches) is behind of the safe rear limit for the CG which is" 
                 << fixed << setprecision(2) << CGRearLim << " inches." << endl;

            double NetMomentAdjustRCG = (CGLocation - CGRearLim) * WeightTO;
            double FuelWeightAjustRCG = NetMomentAdjustRCG / FuelMomentArm;
            double FuelGallonAdjustRCG = FuelWeightAjustRCG / FuelDenisty;
            NetMoment = DryWeightMoment + (FrontWeightSum * FrontSeatMomentArm) + (RearWeightSum * RearSeatMomentArm) + ((FuelWeight - FuelWeightAjustRCG) * FuelMomentArm) + (BaggageWeight * BaggageMomentArm);
            CGLocation = NetMoment / WeightTO;

            double FuelMomentArmCheckRCG = CGRearLim - FuelMomentArm; 
            
            if (FuelMomentArmCheckRCG < 0) // Fuel needs to be removed
            {
                cout << "In order to make take off CG requirements (" << fixed << setprecision(2) << FuelWeightAjustRCG << ") pounds of fuel was removed which is (" << fixed << setprecision(2) << FuelGallonAdjustRCG << ") Gallons." << endl;
                cout << "The new location of the CG for the plane is at (" << fixed << setprecision(2) << CGLocation << ") inches." << endl;
                MaxFuel -= FuelGallonAdjustRCG;
                WeightTO -= FuelWeightAjustRCG;
            }

            if (FuelMomentArmCheckRCG > 0) // Fuel needs to be added
            {
                cout << "In order to make take off CG requirements (" << fixed << setprecision(2) << FuelWeightAjustRCG << ") pounds of fuel was added which is (" << fixed << setprecision(2) << FuelGallonAdjustRCG << ") Gallons." << endl;
                cout << "The new location of the CG for the plane is at (" << fixed << setprecision(2) << CGLocation << ") inches." << endl;
                MaxFuel += FuelGallonAdjustRCG;
                WeightTO += FuelWeightAjustRCG;
            }
        }

    }
    else
    {
        cout << endl << "The current plane setup is within design limits" << endl;
    }

    cout << endl << "The final plane set up at take off is:" << endl;
    cout << "The plane's takeoff weight is " << fixed << setprecision(2) <<  WeightTO << " pounds." << endl;
    cout << "The plane's CG is located at " << fixed << setprecision(2) << CGLocation << " inches." << endl;
    cout << "The plane is carrying " << fixed << setprecision(2) <<  MaxFuel << " Gallons of fuel" << endl;

    return 0;
}