// user.cpp

#include "User.h"
#include "MyList.h"

// Constructor implementation
User::User(const std::string& name, const std::string& gender, const std::string& number,
           const std::string& profession, const std::string& school, int age,
           double latitude, double longitude,  std::string isPremium, int minAgePreference,
           int maxAgePreference, int maxDistancePreference, const std::string& interestedGender)
    : name(name), gender(gender), number(number), profession(profession),
      school(school), age(age), latitude(latitude), longitude(longitude),
      isPremium(isPremium), minAgePreference(minAgePreference),
      maxAgePreference(maxAgePreference), maxDistancePreference(maxDistancePreference),
      interestedGender(interestedGender) {}



// Getter implementations
std::string User::getName() const {
    return name;
}

std::string User::getGender() const {
    return gender;
}

std::string User::getNumber() const {
    return number;
}

std::string User::getProfession() const {
    return profession;
}

std::string User::getSchool() const {
    return school;
}

int User::getAge() const {
    return age;
}

double User::getLatitude() const {
    return latitude;
}

double User::getLongitude() const {
    return longitude;
}

std::string User::getIsPremium() const {
    return isPremium;
}

int User::getMinAgePreference() const {
    return minAgePreference;
}

int User::getMaxAgePreference() const {
    return maxAgePreference;
}

int User::getMaxDistancePreference() const {
    return maxDistancePreference;
}

std::string User::getInterestedGender() const {
    return interestedGender;
}

MyList<std::string> User::getLikedUsers() const {
    return likedUsers;
}

// Function to add a liked user
void User::addLikedUser(const std::string& phoneNumber) {
    likedUsers.push_back(phoneNumber);
}
