#include "Driver.h"
#include <iostream>


// Constructor
Driver::Driver() {
    // Default constructor
    firstName = "null";
    lastName = "null";
    gender = "Unknown";
    age = 0;
    phoneNumber = "null";
    rating = 0.0;
    currentLatitude = 0.0;
    currentLongitude = 0.0;
    vehicleType = "Unknown";
    currentState = "Unknown";
    riderFirstName = "N/A";
    riderLastName = "N/A";
    riderPhoneNumber = "N/A";
}

Driver::Driver(const std::vector<std::string>& driverInfo) {
    // Initialize member variables from the driverInfo vector
    // Assuming the driverInfo vector has exactly 13 elements
    firstName = driverInfo[0];
    lastName = driverInfo[1];
    gender = driverInfo[2];
    age = std::stoi(driverInfo[3]);
    phoneNumber = driverInfo[4];
    rating = std::stod(driverInfo[5]);
    currentLatitude = std::stod(driverInfo[6]);
    currentLongitude = std::stod(driverInfo[7]);
    vehicleType = driverInfo[8];
    currentState = driverInfo[9];
    riderFirstName = driverInfo[10];
    riderLastName = driverInfo[11];
    riderPhoneNumber = driverInfo[12];
    // add this ' displayInfo()' 
}
std::string Driver ::change (double value) {

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

std::string Driver::getFirstName() const {
    return firstName;
}

std::string Driver::getLastName() const {
    return lastName;
}

std::string Driver::getGender() const {
    return gender;
}

int Driver::getAge() const {
    return age;
}

std::string Driver::getPhoneNumber() const {
    return phoneNumber;
}

double Driver::getRating() const {
    return rating;
}

double Driver::getCurrentLatitude() const {
    return currentLatitude;
}

double Driver::getCurrentLongitude() const {
    return currentLongitude;
}

std::string Driver::getVehicleType() const {
    return vehicleType;
}

std::string Driver::getCurrentState() const {
    return currentState;
}

std::string Driver::getRiderFirstName() const {
    return riderFirstName;
}

std::string Driver::getRiderLastName() const {
    return riderLastName;
}

std::string Driver::getRiderPhoneNumber() const {
    return riderPhoneNumber;
}
void Driver::setFirstName(const std::string& value) {
    firstName = value;
}

void Driver::setLastName(const std::string& value) {
    lastName = value;
}

void Driver::setGender(const std::string& value) {
    gender = value;
}

void Driver::setAge(int value) {
    age = value;
}

void Driver::setPhoneNumber(const std::string& value) {
    phoneNumber = value;
}

void Driver::setRating(double value) {
    rating = value;
}

void Driver::setCurrentLatitude(double value) {
    currentLatitude = value;
}

void Driver::setCurrentLongitude(double value) {
    currentLongitude = value;
}

void Driver::setVehicleType(const std::string& value) {
    vehicleType = value;
}

void Driver::setCurrentState( const std::string& value) {
    currentState = value;
}

void Driver::setRiderFirstName( const std::string& value) {
    riderFirstName = value;
}

void Driver::setRiderLastName( const std::string& value) {
    riderLastName = value;
}

void Driver::setRiderPhoneNumber(const std::string& value) {
    riderPhoneNumber = value;
}

// Display info method implementation
void Driver::displayInfo()  {
    std::cout << "Driver Information:" << std::endl;
    std::cout << "Name: " << firstName << " " << lastName << std::endl;
    std::cout << "Gender: " << gender << std::endl;
    std::cout << "Age: " << age << std::endl;
    std::cout << "Phone Number: " << phoneNumber << std::endl;
    std::cout << "Rating: " << rating << std::endl;
    std::cout << "Current Location: (Lat: " << currentLatitude
              << ", Long: " << currentLongitude << ")" << std::endl;
    std::cout << "Vehicle Type: " << vehicleType << std::endl;
    std::cout << "Current State: " << currentState << std::endl;
    std::cout << "Rider Information:" << std::endl;
    std::cout << "Rider Name: " << riderFirstName << " " << riderLastName << std::endl;
    std::cout << "Rider Phone Number: " << riderPhoneNumber << std::endl;
}

std::string Driver::Print() {
    std::string text = firstName + " " + lastName + " " + gender + " " + std::to_string(age) + " " + phoneNumber + " "
                  + change(rating) + " " + change(currentLatitude) + " " + change(currentLongitude) + " "
                  + vehicleType + " " + currentState + " " + riderFirstName + " " + riderLastName + " " + riderPhoneNumber;
    return text;
}