
#ifndef DRIVER_H
#define DRIVER_H
#include <vector>
#include <string>


class Driver {
public:
    // Constructor
    Driver();
    Driver(const std::vector<std::string>& driverInfo);

    // Getter methods
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getGender() const;
    int getAge() const;
    std::string getPhoneNumber() const;
    double getRating() const;
    double getCurrentLatitude() const;
    double getCurrentLongitude() const;
    std::string getVehicleType() const;
    std::string getCurrentState() const;
    std::string getRiderFirstName() const;
    std::string getRiderLastName() const;
    std::string getRiderPhoneNumber() const;

    // Setter methods
    void setFirstName(const std::string& value);
    void setLastName(const std::string& value);
    void setGender(const std::string& value);
    void setAge(int value);
    void setPhoneNumber(const std::string& value);
    void setRating(double value);
    void setCurrentLatitude(double value);
    void setCurrentLongitude(double value);
    void setVehicleType(const std::string& value);
    void setCurrentState(const std::string& value);
    void setRiderFirstName(const std::string& value);
    void setRiderLastName(const std::string& value);
    void setRiderPhoneNumber(const std::string& value);
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
    double currentLatitude;
    double currentLongitude;
    std::string vehicleType;
    std::string currentState;
    std::string riderFirstName;
    std::string riderLastName;
    std::string riderPhoneNumber;
};

#endif 