// user.h

#ifndef USER_H
#define USER_H

#include "MyList.h" // Assuming you have a homemade MyList implementation

class User {
private:
    std::string name;
    std::string gender;
    std::string number;
    std::string profession;
    std::string school;
    int age;
    double latitude;
    double longitude;
    std::string isPremium;
    int minAgePreference;
    int maxAgePreference;
    int maxDistancePreference;
    std::string interestedGender; 
    MyList<std::string> likedUsers;

public:
    // Constructor
    User(const std::string& name, const std::string& gender, const std::string& number,
         const std::string& profession, const std::string& school, int age,
         double latitude, double longitude, std::string isPremium, int minAgePreference,
         int maxAgePreference, int maxDistancePreference, const std::string& interestedGender);

    // Getters
    std::string getName() const;
    std::string getGender() const;
    std::string getNumber() const;
    std::string getProfession() const;
    std::string getSchool() const;
    int getAge() const;
    double getLatitude() const;
    double getLongitude() const;
    std::string getIsPremium() const;
    int getMinAgePreference() const;
    int getMaxAgePreference() const;
    int getMaxDistancePreference() const;
    std::string getInterestedGender() const;
    MyList<std::string> getLikedUsers() const;

    // Function to add a liked user
    void addLikedUser(const std::string& phoneNumber);
};

#endif // USER_H
