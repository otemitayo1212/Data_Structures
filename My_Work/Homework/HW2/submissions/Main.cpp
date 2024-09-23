#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>
#include "Rider.h"
#include "Driver.h"


// calculate the distance between two coordinates using Haversine formula
double calculateDistance(double lat1, double lon1, double lat2, double lon2) {
    const double radiusOfEarth = 6371.0; // Earth's radius in kilometers

    // convert latitude and longitude from degrees to radians
    lat1 *= M_PI / 180.0;
    lon1 *= M_PI / 180.0;
    lat2 *= M_PI / 180.0;
    lon2 *= M_PI / 180.0;

    // Haversine formula
    double dLat = lat2 - lat1;
    double dLon = lon2 - lon1;
    double a = sin(dLat / 2.0) * sin(dLat / 2.0) + cos(lat1) * cos(lat2) * sin(dLon / 2.0) * sin(dLon / 2.0);
    double c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));
    // distance in kilometers
    double distanceKM = radiusOfEarth * c;
    // convert it to distance in miles
    double distanceMiles = distanceKM * 0.621371;

    return distanceMiles;
}
std::string Change (double value ){
    std::string originalString = std::to_string(value) ;

    // Find the position of the decimal point
    int decimalPos = originalString.find('.');

    // Extract the substring up to the first decimal place
    std::string result = originalString.substr(0, decimalPos + 2); // Include one digit after the decimal point

    return result ;
}



//Example
int main(int argc, char* argv[]) {
    Driver driver;
    std::string drivertxt = argv[1];
    std::string riderstxt = argv[2];
    std::string output0 =  argv[3];
    std::string output1 =  argv[4];
    std::string output2 = argv[5];
    std::string phonenumber = argv[6];
    std::string action = argv[7];
   // check phone number syntax
 
    std::ifstream inputFile(drivertxt);
    std::ifstream inputFile2(riderstxt);


    // Vector to store all Driver and rider objects
    std::vector<Driver> allDrivers;
    std::vector<Rider> allRiders;
    // check if phone number is in the right format
    std::ofstream output_main(output0);
    std::ofstream output_drivers(output1);
    std::ofstream output_riders(output2);


    // Read each line from the file
    std::string line;
    while (std::getline(inputFile, line)) {
        // Create a stringstream to split the line into tokens
        std::istringstream iss(line);
        std::vector<std::string> driverInfo;
        

        // Read each token and add it to the driverInfo vector
        std::string token;
        while (iss >> token) {
            driverInfo.push_back(token);
        } 

        // Create a Driver object and add it to the vector
        allDrivers.emplace_back(driverInfo);
    }
    std::string line2;
    while (std::getline(inputFile2, line2)) {
        // Create a stringstream to split the line into tokens
        std::istringstream iss(line2);
        std::vector<std::string> riderInfo;

        // Read each token and add it to the driverInfo vector
        std::string token2;
        while (iss >> token2) {
            riderInfo.push_back(token2);
        }

        // Create a Rider object and add it to the vector
        allRiders.emplace_back(riderInfo);
    }
   
    
    if (action == "request") {
        // check syntax
    if (phonenumber.size() != 12 || phonenumber[3] != '-' || phonenumber[7] != '-') {
        output_main << "Phone number is invalid.\n";
        return 0;
    }
    // Step 1: Find person through phone number
    Rider rider; // Assuming 'Rider' is the class/type for riders
    bool riderfound = false;
    for (int i = 0; i < allRiders.size(); i++) {
        if (phonenumber == allRiders[i].getPhoneNumber()) {
            rider = allRiders[i];
            riderfound = true; 
            break;
         }
   
 }
   // this means the rider was not found through the number
    if (!riderfound) {
        output_main << "Account does not exist.\n"; 
        return 0 ;
    }

    // Now check if the rider can request
    if (rider.getCurrentState() == "Driver_on_the_way") {
        output_main << "You have already requested a ride and your driver is on the way to the pickup location.\n";
       
        return 0;
    } else if (rider.getCurrentState() == "During_the_trip") {
        output_main << "You can not request a ride at this moment as you are already on a trip.\n";
        
        return 0;
    }
    // Now we find the clossest driver

    bool driverFound = false;
    double minDistance = std::numeric_limits<double>::max();
    Driver closestDriver;

    for (int i = 0; i < allDrivers.size(); ++i) {
        double distance = calculateDistance(rider.getPickupLatitude(), rider.getPickupLongitude(), allDrivers[i].getCurrentLatitude(), allDrivers[i].getCurrentLongitude());

        if (allDrivers[i].getCurrentState() == "Available" && 
            allDrivers[i].getVehicleType() == rider.getVehiclePreference() &&
            distance <= minDistance) {
            
            minDistance = distance;
            closestDriver = allDrivers[i];
            driverFound = true;
            // No need for driverFound, as closestDriver being set indicates a driver is found
        }
    }

       if (driverFound) {
        // Found an available driver
        // Do further processing with 'closestDriver'
        // output 1.1 goes here

        // Step 3: Write Updated Data to Output File
        if (rider.getVehiclePreference() == "Premium" || rider.getVehiclePreference() == "Standard" ){
        output_main << "Ride requested for rider " << rider.getFirstName() << ", looking for a " << rider.getVehiclePreference() << " vehicle.\n";
        output_main << "Pick Up Location: " << rider.getPickupLocationName() << ", Drop Off Location: " << rider.getDropoffLocationName() << ".\n";
        output_main << "We have found the closest driver " << closestDriver.getFirstName()  << "(" << closestDriver.getRating() << ") for you.\n";
        output_main << closestDriver.getFirstName() << " is now " <<    Change (calculateDistance(rider.getPickupLatitude(), rider.getPickupLongitude(), closestDriver.getCurrentLatitude(), closestDriver.getCurrentLongitude()) )<< " miles away from you.\n";
        closestDriver.setCurrentState("On_the_way_to_pickup") ;
        closestDriver.setRiderFirstName(rider.getFirstName());
        closestDriver.setRiderLastName(rider.getLastName());
         closestDriver.setRiderPhoneNumber(rider.getPhoneNumber());
         rider.setCurrentState("Driver_on_the_way");
         rider.setDriverFirstName(closestDriver.getFirstName());
         rider.setDriverLastName(closestDriver.getLastName()) ;
         rider. setDriverPhoneNumber(closestDriver.getPhoneNumber());
         for ( Rider rider : allRiders) {
           output_riders << rider.Print() << std::endl;
           }
        for ( Driver driver : allDrivers) {
            output_drivers << driver.Print() << std::endl;
        }
 
        }
        else{
        output_main << "Ride requested for rider " << rider.getFirstName() << ", looking for an " << rider.getVehiclePreference() << " vehicle.\n";
        output_main << "Pick Up Location: " << rider.getPickupLocationName() << ", Drop Off Location: " << rider.getDropoffLocationName() << ".\n";
        output_main << "We have found the closest driver " << closestDriver.getFirstName()  << "(" << closestDriver.getRating() << ") for you.\n";
        output_main << closestDriver.getFirstName() << " is now " << Change(calculateDistance(rider.getPickupLatitude(), rider.getPickupLongitude(), closestDriver.getCurrentLatitude(), closestDriver.getCurrentLongitude())) << " miles away from you.\n";
        closestDriver.setCurrentState("On_the_way_to_pickup") ;
        closestDriver.setRiderFirstName(rider.getFirstName());
        closestDriver.setRiderLastName(rider.getLastName());
         closestDriver.setRiderPhoneNumber(rider.getPhoneNumber());
         rider.setCurrentState("Driver_on_the_way");
         rider.setDriverFirstName(closestDriver.getFirstName());
         rider.setDriverLastName(closestDriver.getLastName()) ;
         rider. setDriverPhoneNumber(closestDriver.getPhoneNumber());
        for ( Rider rider : allRiders) {
           output_riders << rider.Print() << std::endl;
           }
        for ( Driver driver : allDrivers) {
            output_drivers << driver.Print() << std::endl;
        }
        }
        

        return 0 ;
    } else {
        // Driver not found
        // Output 2 goes here
        if (rider.getVehiclePreference() == "Premium" ||rider.getVehiclePreference() == "Standard"){
        output_main << "Ride requested for rider " << rider.getFirstName() << ", looking for a " << rider.getVehiclePreference() << " vehicle.\n";
        output_main << "Pick Up Location: " << rider.getPickupLocationName() << ", Drop Off Location: " << rider.getDropoffLocationName() << ".\n";
        output_main << "Sorry we can not find a driver for you at this moment.\n";
        }
        else{
             output_main << "Ride requested for rider " << rider.getFirstName() << ", looking for a " << rider.getVehiclePreference() << " vehicle.\n";
        output_main << "Pick Up Location: " << rider.getPickupLocationName() << ", Drop Off Location: " << rider.getDropoffLocationName() << ".\n";
        output_main << "Sorry we can not find a driver for you at this moment.\n";
        }
       
        return 0;
        
    }
   }
   if (action == "cancel"){
    Driver driver2;
    Rider rider2;
    int index1 = 0;
    bool Its_a_driver = false;
    bool Its_a_rider = false;
    for (int i = 0; i < allDrivers.size(); i++) {
        if (phonenumber == allDrivers[i].getPhoneNumber()) {
            driver2 = allDrivers[i];
            index1 = i;
            Its_a_driver = true;
            break;
        }
    }
    int index2 = 0;
    for (int i = 0; i < allRiders.size(); i++) {
        if (phonenumber == allRiders[i].getPhoneNumber()) {
            rider2 = allRiders[i];
            index2 = i;
            Its_a_rider = true;
            break;
        }
    }

    
    Driver newDriver;
    if (Its_a_driver && !Its_a_rider) {
    if (driver2.getCurrentState() == "Available" || driver2.getCurrentState() == "During_the_trip") {
        output_main << "You can only cancel a ride request if you are currently on the way to the pickup location.\n";
    }
    else if (driver2.getCurrentState() == "On_the_way_to_pickup") {
        double min = std::numeric_limits<double>::max();
        std::string number = driver2.getRiderPhoneNumber();

        for (int i = 0; i < allRiders.size(); i++) {
                if (number == allRiders[i].getPhoneNumber()) {
                    rider2 = allRiders[i];
                    index2 = i;
                    break;
                }
            }
        for (int i = 0; i < allDrivers.size(); ++i) {
            // find rider's info to search for location
            double distance = calculateDistance(rider2.getPickupLatitude(), rider2.getPickupLongitude(), allDrivers[i].getCurrentLatitude(), allDrivers[i].getCurrentLongitude());
            if (driver2.getPhoneNumber() == allDrivers[i].getPhoneNumber()) {
                // this means that it is the old driver 
                continue;
            }
            if (allDrivers[i].getCurrentState() == "Available" && rider2.getVehiclePreference() == allDrivers[i].getVehicleType() && distance < min ) {  
                    min = distance;
                    newDriver = allDrivers[i];
                    index1=i;
            }
        }
        
        if  (rider2.getVehiclePreference() == "Premium" || rider2.getVehiclePreference() == "Standard" ){
            output_main << "Your driver " << driver2.getFirstName() << " has canceled the ride request. We will now find a new driver for you.\n";
        output_main << "Ride requested for rider " << rider2.getFirstName() << ", looking for a " << rider2.getVehiclePreference() << " vehicle.\n";
        output_main << "Pick Up Location: " << rider2.getPickupLocationName() << ", Drop Off Location: " << rider2.getDropoffLocationName() << ".\n";
        output_main << "We have found the closest driver " << newDriver.getFirstName() << "(" << newDriver.getRating() << ") for you.\n";
        output_main << newDriver.getFirstName() << " is now " << Change(calculateDistance(rider2.getPickupLatitude(), rider2.getPickupLongitude(), newDriver.getCurrentLatitude(), newDriver.getCurrentLongitude())) << " miles away from you.\n";
        // Note change rider2 information with newDriver
        allDrivers[index1].setCurrentState("Available");
        allDrivers[index1].setRiderFirstName("null");
        allDrivers[index1].setRiderLastName("null");
        allDrivers[index1].setRiderPhoneNumber("null");
        allRiders[index2].setCurrentState("Driver_on_the_way");
        allRiders[index2].setDriverFirstName(newDriver.getFirstName());
        allRiders[index2].setDriverLastName(newDriver.getLastName());
        allRiders[index2].setDriverPhoneNumber(newDriver.getPhoneNumber());
        for (Rider rider : allRiders) {
            output_riders << rider.Print() << std::endl;
        }
        for (Driver driver : allDrivers) {
            output_drivers << driver.Print() << std::endl;
        }

        }
        else{
            output_main << "Your driver " << driver2.getFirstName() << " has canceled the ride request. We will now find a new driver for you.\n";
        output_main << "Ride requested for rider " << rider2.getFirstName() << ", looking for an " << rider2.getVehiclePreference() << " vehicle.\n";
        output_main << "Pick Up Location: " << rider2.getPickupLocationName() << ", Drop Off Location: " << rider2.getDropoffLocationName() << ".\n";
        output_main << "We have found the closest driver " << newDriver.getFirstName() << "(" << newDriver.getRating() << ") for you.\n";
        output_main << newDriver.getFirstName() << " is now " << Change(calculateDistance(rider2.getPickupLatitude(), rider2.getPickupLongitude(), newDriver.getCurrentLatitude(), newDriver.getCurrentLongitude())) << " miles away from you.\n";
        // Note change rider2 information with newDriver
        allDrivers[index1].setCurrentState("Available");
        allDrivers[index1].setRiderFirstName("null");
        allDrivers[index1].setRiderLastName("null");
        allDrivers[index1].setRiderPhoneNumber("null");
        allRiders[index2].setCurrentState("Driver_on_the_way");
        allRiders[index2].setDriverFirstName(newDriver.getFirstName());
        allRiders[index2].setDriverLastName(newDriver.getLastName());
        allRiders[index2].setDriverPhoneNumber(newDriver.getPhoneNumber());
        for (Rider rider : allRiders) {
            output_riders << rider.Print() << std::endl;
        }
        for (Driver driver : allDrivers) {
            output_drivers << driver.Print() << std::endl;
        }
        }
    }
}

if (Its_a_rider && !Its_a_driver) {
    // cancel the request, but at the same time, find another closest driver
    if (rider2.getCurrentState() != "Driver_on_the_way") {
        output_main << "You can only cancel a ride request if your driver is currently on the way to the pickup location.\n";
    } else {
        output_main << "Ride request for rider " << rider2.getFirstName() << " is now canceled by the rider.\n";
        // find phone num from rirder and find driver
        std::string phone_num = rider2.getDriverPhoneNumber();
        for (int i = 0 ; i < allDrivers.size(); i++){
            if (phone_num == allDrivers[i].getPhoneNumber()){
                index1=i;
            }
        }
        allDrivers[index1].setCurrentState("Available");
        allDrivers[index1].setRiderFirstName("null");
        allDrivers[index1].setRiderLastName("null");
        allDrivers[index1].setRiderPhoneNumber("null");
        allRiders[index2].setCurrentState("Ready_to_request");
        allRiders[index2].setDriverFirstName("null");
        allRiders[index2].setDriverLastName("null");
        allRiders[index2].setDriverPhoneNumber("null");
        for (Rider rider : allRiders) {
            output_riders << rider.Print() << std::endl;
        }
        for (Driver driver : allDrivers) {
            output_drivers << driver.Print() << std::endl;
        }
        return 0;
    }
} else if (!Its_a_driver && !Its_a_rider) {
    // Handle the case when both Its_a_driver and Its_a_rider are false
    output_main << "Account does not exist.\n";
    return 0;
}


     


     }


}
