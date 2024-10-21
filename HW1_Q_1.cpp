#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    double DryWeight; // Pounds
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


    /****************************************************************** Takeing in User Data *******************************************************************************/

    // Most of the code in this section follows the format below
    // Cout mesage to user to enter a relavant airplane spec
    // Cin that variable

    cout << endl << "Please enter the airplane empty weight in pounds:" << endl;
    cin >> DryWeight;
    cout << endl << "Please enter the airplane empty-weight moment in pounds-inches:" << endl;
    cin >> DryWeightMoment;

    cout << endl << "Please enter the number of front seat occupants:" << endl;
    cin >> NumFrontPassengers;
    
    double FrontWeightSum = 0; // Finding total weight of front passenegers
    for (int i = 1; i <= NumFrontPassengers; i++) // Used ChatGPT for this to find an error (I had i < NumFrontPassengers which resulted in me having 1 less than desired)
    {
        double FrontWeight = 0;
        cout << endl << "Please enter the weight for front seat occupant " << i << " in pounds: " << endl;
        cin >> FrontWeight;
        FrontWeightSum += FrontWeight;
    }

    cout << endl << "Total front ccupant weight: " << FrontWeightSum << " pounds."  << endl;

    cout << endl << "Please enter the front seat moment arm in inches:" << endl;
    cin >> FrontSeatMomentArm;

    cout << endl << "Please enter the number of rear seat occupants:" << endl;
    cin >> NumRearPassengers;

    double RearWeightSum = 0; // Finding total weight of rear passenegers

    for (int j = 1; j <= NumRearPassengers; j++) 
    {
        double RearWeight = 0;
        cout << endl << "Please enter the weight for rear seat occupant " << j << " in pounds: " << endl;
        cin >> RearWeight;
        RearWeightSum += RearWeight;
    }

    cout << endl << "Total rear occupant weight: " << FrontWeightSum << " pounds." << endl;

    cout << endl << "Please enter the rear seat moment arm in inches:" << endl;
    cin >> RearSeatMomentArm;

    cout << endl << "Please enter the number of gallons of usable fuel:" << endl;
    cin >> MaxFuel;
    cout << endl << "Please enter the usable fuel weight per gallon using units of pounds per gallon:" << endl;
    cin >> FuelDenisty;
    cout << endl << "Please enter the fuel tank moment arm in inches:" << endl;
    cin >> FuelMomentArm;

    double FuelWeight =  MaxFuel*FuelDenisty; // Finding fuel weight

    cout << endl << "Please enter the baggage weight in pounds:" << endl;
    cin >> BaggageWeight;
    cout << endl << "Please enter the baggage moment arm in inches:" << endl;
    cin >> BaggageMomentArm;

/****************************************************************** Processing User Entered Data *******************************************************************************/

    double WeightTO = DryWeight + FrontWeightSum + RearWeightSum + FuelWeight + BaggageWeight; // Finding total inital weight
    double NetMoment = DryWeightMoment + (FrontWeightSum * FrontSeatMomentArm) + (RearWeightSum * RearSeatMomentArm) + (FuelWeight * FuelMomentArm) + (BaggageWeight * BaggageMomentArm); // Finding inital moment acting on the plane
    double CGLocation = NetMoment / WeightTO; // Finding the cent of gravity location

    
    if (WeightTO > MaxWeightTO || CGLocation < CGForwardLim || CGLocation > CGRearLim) // Checking to make sure that the plane is within design reqs
    {
    
        if (WeightTO > MaxWeightTO) // Checking to see if the plane is below max take off weight
        {
            cout << endl << "The current take off weight of the plane (" << fixed << setprecision(2) << WeightTO << ") pounds is above the max designed take off weight of " << fixed << setprecision(2) << MaxWeightTO << " pounds." << endl;
            double FuelWeightRemove = (WeightTO - MaxWeightTO); // Pounds of fuel that need to be removed
            double FuelGallonsRemove = (WeightTO - MaxWeightTO) / FuelDenisty; // Corrisponding amount of gallens that need to be removed
            WeightTO -= FuelWeightRemove; // Updating the weight of the plane
            NetMoment = DryWeightMoment + (FrontWeightSum * FrontSeatMomentArm) + (RearWeightSum * RearSeatMomentArm) + ((FuelWeight - FuelWeightRemove) * FuelMomentArm) + (BaggageWeight * BaggageMomentArm); // Updating the net moment
            CGLocation = NetMoment / WeightTO;  // Updating the CG location
            cout << "In order to make take off weight requirements (" << fixed << setprecision(2) << FuelWeightRemove << ") pounds of fuel was removed which is (" << fixed << setprecision(2) << FuelGallonsRemove << ") Gallons." << endl;
            cout << "The new take off weight of the plane is now (" << fixed << setprecision(2) << WeightTO << ") pounds." << endl;
        }

        if (CGLocation < CGForwardLim) // Checking to see if the CG location is behind the forward limit
        {   
            cout << endl << "The current location of the center of gravity (CG) of the plane (" << fixed << setprecision(2) << CGLocation << " inches) is ahead of the safe forward limit for the CG which is " 
                 << fixed << setprecision(2)  << CGForwardLim << " inches." << endl;
                
            double NetMomentAdjustFCG = (CGForwardLim - CGLocation) * WeightTO; // getting needed moment ajustment to get the CG within limits
            double FuelWeightAjustFCG = NetMomentAdjustFCG / FuelMomentArm; // Finding the fuel weight needed to make that ajustment
            double FuelGallonAdjustFCG = FuelWeightAjustFCG / FuelDenisty; // Finding the gallons of fuel that corrisponds to 
            NetMoment = DryWeightMoment + (FrontWeightSum * FrontSeatMomentArm) + (RearWeightSum * RearSeatMomentArm) + ((FuelWeight - FuelWeightAjustFCG) * FuelMomentArm) + (BaggageWeight * BaggageMomentArm); // Updating the net moment
            CGLocation = NetMoment / WeightTO; // Updating the CG location

            double FuelMomentArmCheckFCG = FuelMomentArm - CGForwardLim; // A check to see if fuel was added or removed
            
            if (FuelMomentArmCheckFCG < 0) // Fuel needs to be removed
            {
                cout << "In order to make take off CG requirements (" << fixed << setprecision(2) << FuelWeightAjustFCG << ") pounds of fuel was removed which is (" << fixed << setprecision(2) << FuelGallonAdjustFCG << ") Gallons." << endl;
                cout << "The new location of the CG for the plane is at (" << fixed << setprecision(2) << CGLocation << ") inches." << endl;
                MaxFuel -= FuelGallonAdjustFCG; // Updating the fuel the plane is carrying
                WeightTO -= FuelWeightAjustFCG; // Updating the weight of take off
            }

            if (FuelMomentArmCheckFCG > 0) // Fuel needs to be added
            {
                cout << "In order to make take off CG requirements (" << fixed << setprecision(2) << FuelWeightAjustFCG << ") pounds of fuel was added which is (" << fixed << setprecision(2) << FuelGallonAdjustFCG << ") Gallons." << endl;
                cout << "The new location of the CG for the plane is at (" << fixed << setprecision(2) << CGLocation << ") inches." << endl;
                MaxFuel += FuelGallonAdjustFCG; // Updating the fuel the plane is carrying
                WeightTO += FuelWeightAjustFCG; // Updating the weight of take off
            }
        }


        if (CGLocation > CGRearLim) // Checking to see if the CG location is ahead of the rear limit
        {   
            cout << endl << "The current location of the center of gravity (CG) of the plane (" << fixed << setprecision(2) << CGLocation << " inches) is behind of the safe rear limit for the CG which is" 
                 << fixed << setprecision(2) << CGRearLim << " inches." << endl;

            double NetMomentAdjustRCG = (CGLocation - CGRearLim) * WeightTO; // getting needed moment ajustment to get the CG within limits
            double FuelWeightAjustRCG = NetMomentAdjustRCG / FuelMomentArm; // Finding the fuel weight needed to make that ajustment
            double FuelGallonAdjustRCG = FuelWeightAjustRCG / FuelDenisty; // Finding the gallons of fuel that corrisponds to 
            NetMoment = DryWeightMoment + (FrontWeightSum * FrontSeatMomentArm) + (RearWeightSum * RearSeatMomentArm) + ((FuelWeight - FuelWeightAjustRCG) * FuelMomentArm) + (BaggageWeight * BaggageMomentArm); // Updating the net moment
            CGLocation = NetMoment / WeightTO; // Updating the CG location

            double FuelMomentArmCheckRCG = CGRearLim - FuelMomentArm; // A check to see if fuel was added or removed
            
            if (FuelMomentArmCheckRCG < 0) // Fuel needs to be removed
            {
                cout << "In order to make take off CG requirements (" << fixed << setprecision(2) << FuelWeightAjustRCG << ") pounds of fuel was removed which is (" << fixed << setprecision(2) << FuelGallonAdjustRCG << ") Gallons." << endl;
                cout << "The new location of the CG for the plane is at (" << fixed << setprecision(2) << CGLocation << ") inches." << endl;
                MaxFuel -= FuelGallonAdjustRCG; // Updating the fuel the plane is carrying
                WeightTO -= FuelWeightAjustRCG; // Updating the weight of take off
            }

            if (FuelMomentArmCheckRCG > 0) // Fuel needs to be added
            {
                cout << "In order to make take off CG requirements (" << fixed << setprecision(2) << FuelWeightAjustRCG << ") pounds of fuel was added which is (" << fixed << setprecision(2) << FuelGallonAdjustRCG << ") Gallons." << endl;
                cout << "The new location of the CG for the plane is at (" << fixed << setprecision(2) << CGLocation << ") inches." << endl;
                MaxFuel += FuelGallonAdjustRCG; // Updating the fuel the plane is carrying
                WeightTO += FuelWeightAjustRCG; // Updating the weight of take off
            }
        }

    }
    else
    {
        cout << endl << "The current plane setup is within design limits" << endl;
    }

    if (WeightTO > MaxWeightTO || CGLocation < CGForwardLim || CGLocation > CGRearLim) // A final check to make sure the ajustments fixed the issue
    {
        cout << endl << "**********************************WARNING**********************************" << endl;
        cout << "The current load on the plane cannot be adjusted to within design requirement via ajusting the fuel level. DO NOT FLY";
    }
    else // Giving the end user the updated plane load out
    {
        cout << endl << "The final plane set up at take off is:" << endl;
        cout << "The plane's takeoff weight is " << fixed << setprecision(2) <<  WeightTO << " pounds." << endl;
        cout << "The plane's CG is located at " << fixed << setprecision(2) << CGLocation << " inches." << endl;
        cout << "The plane is carrying " << fixed << setprecision(2) <<  MaxFuel << " Gallons of fuel" << endl;
    }
    return 0;
}