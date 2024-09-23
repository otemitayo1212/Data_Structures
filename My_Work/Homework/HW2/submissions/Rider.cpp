#include "Rider.h"
#include <iostream>

// Constructor
Rider::Rider() {
    // Default constructor
    firstName = "null";
    lastName = "null";
    gender = "null";
    age = 0;
    phoneNumber = "null";
    rating = 0.0;
    pickupLocationName = "N/A";
    pickupLatitude = 0.0;
    pickupLongitude = 0.0;
    dropoffLocationName = "N/A";
    dropoffLatitude = 0.0;
    dropoffLongitude = 0.0;
    vehiclePreference = "Unknown";
    currentState = "Unknown";
    driverFirstName = "N/A";
    driverLastName = "N/A";
    driverPhoneNumber = "N/A";
}
Rider::Rider(const std::vector<std::string>& riderInfo) {
    // Initialize member variables from the riderInfo vector
    // Assuming the riderInfo vector has exactly 17 elements
    firstName = riderInfo[0];
    lastName = riderInfo[1];
    gender = riderInfo[2];
    age = std::stoi(riderInfo[3]);
    phoneNumber = riderInfo[4];
    rating = std::stod(riderInfo[5]);
    pickupLocationName = riderInfo[6];
    pickupLatitude = std::stod(riderInfo[7]);
    pickupLongitude = std::stod(riderInfo[8]);
    dropoffLocationName = riderInfo[9];
    dropoffLatitude = std::stod(riderInfo[10]);
    dropoffLongitude = std::stod(riderInfo[11]);
    vehiclePreference = riderInfo[12];
    currentState = riderInfo[13];
    driverFirstName = riderInfo[14];
    driverLastName = riderInfo[15];
    driverPhoneNumber = riderInfo[16];
   
}

std::string Rider:: change (double value) {

   std::string text = std::to_string(value);
    while (text.back() =='0') {
        text = text.substr(0, text.size()-1);
    }
    if(text.back() == '.') {
        text = text.substr(0,text.size()-1);
    }
   
    return text ;
}
// Implement getter methods
std::string Rider::getFirstName() const {
    return firstName;
}

std::string Rider::getLastName() const {
    return lastName;
}

std::string Rider::getGender() const {
    return gender;
}

int Rider::getAge() const {
    return age;
}

std::string Rider::getPhoneNumber() const {
    return phoneNumber;
}

double Rider::getRating() const {
    return rating;
}

std::string Rider::getPickupLocationName() const {
    return pickupLocationName;
}

double Rider::getPickupLatitude() const {
    return pickupLatitude;
}

double Rider::getPickupLongitude() const {
    return pickupLongitude;
}

std::string Rider::getDropoffLocationName() const {
    return dropoffLocationName;
}

double Rider::getDropoffLatitude() const {
    return dropoffLatitude;
}

double Rider::getDropoffLongitude() const {
    return dropoffLongitude;
}

std::string Rider::getVehiclePreference() const {
    return vehiclePreference;
}

std::string Rider::getCurrentState() const {
    return currentState;
}

std::string Rider::getDriverFirstName() const {
    return driverFirstName;
}

std::string Rider::getDriverLastName() const {
    return driverLastName;
}

std::string Rider::getDriverPhoneNumber() const {
    return driverPhoneNumber;
}

void Rider::setFirstName(std::string aFirstName) {
    firstName = aFirstName;
}

void Rider::setLastName(std::string aLastName) {
    lastName = aLastName;
}

void Rider::setGender(std::string aGender) {
    gender = aGender;
}

void Rider::setAge(int aAge) {
    age = aAge;
}

void Rider::setPhoneNumber(std::string aPhoneNumber) {
    phoneNumber = aPhoneNumber;
}

void Rider::setRating(double aRating) {
    rating = aRating;
}

void Rider::setPickupLocationName(std::string aPickupLocationName) {
    pickupLocationName = aPickupLocationName;
}

void Rider::setPickupLatitude(double aPickupLatitude) {
    pickupLatitude = aPickupLatitude;
}

void Rider::setPickupLongitude(double aPickupLongitude) {
    pickupLongitude = aPickupLongitude;
}

void Rider::setDropoffLocationName(std::string aDropoffLocationName) {
    dropoffLocationName = aDropoffLocationName;
}

void Rider::setDropoffLatitude(double aDropoffLatitude) {
    dropoffLatitude = aDropoffLatitude;
}

void Rider::setDropoffLongitude(double aDropoffLongitude) {
    dropoffLongitude = aDropoffLongitude;
}

void Rider::setVehiclePreference(std::string aVehiclePreference) {
    vehiclePreference = aVehiclePreference;
}

void Rider::setCurrentState(std::string aCurrentState) {
    currentState = aCurrentState;
}

void Rider::setDriverFirstName(std::string aDriverFirstName) {
    driverFirstName = aDriverFirstName;
}

void Rider::setDriverLastName(std::string aDriverLastName) {
    driverLastName = aDriverLastName;
}

void Rider::setDriverPhoneNumber(std::string aDriverPhoneNumber) {
    driverPhoneNumber = aDriverPhoneNumber;
}
void Rider::displayInfo()  {
    std::cout << "Rider Information:" << std::endl;
    std::cout << "Name: " << firstName << " " << lastName << std::endl;
    std::cout << "Gender: " << gender << std::endl;
    std::cout << "Age: " << age << std::endl;
    std::cout << "Phone Number: " << phoneNumber << std::endl;
    std::cout << "Rating: " << rating << std::endl;
    std::cout << "Pickup Location: " << pickupLocationName << " (Lat: " << pickupLatitude
              << ", Long: " << pickupLongitude << ")" << std::endl;
    std::cout << "Dropoff Location: " << dropoffLocationName << " (Lat: " << dropoffLatitude
              << ", Long: " << dropoffLongitude << ")" << std::endl;
    std::cout << "Vehicle Preference: " << vehiclePreference << std::endl;
    std::cout << "Current State: " << currentState << std::endl;
    std::cout << "Driver Information:" << std::endl;
    std::cout << "Driver Name: " << driverFirstName << " " << driverLastName << std::endl;
    std::cout << "Driver Phone Number: " << driverPhoneNumber << std::endl;
}
std::string Rider::Print() {
    std::string text = firstName + " " + lastName + " " + gender + " " + std::to_string(age) + " " + phoneNumber
                  + " " + change(rating) + " " + pickupLocationName+" "+ change(pickupLatitude) + " " + change(pickupLongitude) + " "  + dropoffLocationName +" "+ change(dropoffLatitude) + " " + change(dropoffLongitude) + " " + vehiclePreference + " " + currentState + " "
                  + driverFirstName + " " + driverLastName + " " + driverPhoneNumber;
    return text;
}
