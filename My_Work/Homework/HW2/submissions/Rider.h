

#ifndef RIDER_H
#define RIDER_H
#include <vector>
#include <string>

class Rider {
public:
    // Constructor
    Rider();
    Rider(const std::vector<std::string>& riderInfo);

    // Getter methods
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getGender() const;
    int getAge() const;
    std::string getPhoneNumber() const;
    double getRating() const;
    std::string getPickupLocationName() const;
    double getPickupLatitude() const;
    double getPickupLongitude() const;
    std::string getDropoffLocationName() const;
    double getDropoffLatitude() const;
    double getDropoffLongitude() const;
    std::string getVehiclePreference() const;
    std::string getCurrentState() const;
    std::string getDriverFirstName() const;
    std::string getDriverLastName() const;
    std::string getDriverPhoneNumber() const;

    // Void modifier methods
    void setFirstName(std::string aFirstName);
    void setLastName(std::string aLastName);
    void setGender(std::string aGender);
    void setAge(int aAge);
    void setPhoneNumber(std::string aPhoneNumber);
    void setRating(double aRating);
    void setPickupLocationName(std::string aPickupLocationName);
    void setPickupLatitude(double aPickupLatitude);
    void setPickupLongitude(double aPickupLongitude);
    void setDropoffLocationName(std::string aDropoffLocationName);
    void setDropoffLatitude(double aDropoffLatitude);
    void setDropoffLongitude(double aDropoffLongitude);
    void setVehiclePreference(std::string aVehiclePreference);
    void setCurrentState(std::string aCurrentState);
    void setDriverFirstName(std::string aDriverFirstName);
    void setDriverLastName(std::string aDriverLastName);
    void setDriverPhoneNumber(std::string aDriverPhoneNumber);
    void displayInfo();
    std::string Print();
    std::string change(double value);


private:
    // Member variables
    std::string firstName;
    std::string lastName;
    std::string gender;
    int age;
    std::string phoneNumber;
    double rating;
    std::string pickupLocationName;
    double pickupLatitude;
    double pickupLongitude;
    std::string dropoffLocationName;
    double dropoffLatitude;
    double dropoffLongitude;
    std::string vehiclePreference;
    std::string currentState;
    std::string driverFirstName;
    std::string driverLastName;
    std::string driverPhoneNumber;
};

// Constructor implementation
//Rider::Rider(const std::vector<std::string>& riderInfo) {
    // Initialize member variables using riderInfo vector
    // Assuming riderInfo contains information in the order of member variables
    // Example: { "John", "Doe", "Male", "25", "123456789", "4.5", ... }
//}

// Implement the rest of the methods as needed
// Remember to provide implementations for both getter and setter methods
#endif 