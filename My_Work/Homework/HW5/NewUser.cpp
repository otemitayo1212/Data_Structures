#include "NewUser.h"


// Copy constructor
NewUser::NewUser(const NewUser& other) :
    name(other.name),
    gender(other.gender),
    number(other.number),
    profession(other.profession),
    school(other.school),
    age(other.age),
    latitude(other.latitude),
    longitude(other.longitude),
    isPremium(other.isPremium),
    minAgePreference(other.minAgePreference),
    maxAgePreference(other.maxAgePreference),
    maxDistancePreference(other.maxDistancePreference),
    interestedGender(other.interestedGender),
    LikedNumbers(other.LikedNumbers),
    next(nullptr),
    prev(nullptr)
{}


// Constructor
NewUser::NewUser(const std::string& name, const std::string& gender, const std::string& number,
                 const std::string& profession, const std::string& school, int age,
                 double latitude, double longitude, std::string isPremium, int minAgePreference,
                 int maxAgePreference, int maxDistancePreference, const std::string& interestedGender , std::string LikedNumbers)
                 : name(name), gender(gender), number(number), profession(profession),
                   school(school), age(age), latitude(latitude), longitude(longitude),
                   isPremium(isPremium), minAgePreference(minAgePreference),
                   maxAgePreference(maxAgePreference), maxDistancePreference(maxDistancePreference),
                   interestedGender(interestedGender), LikedNumbers(LikedNumbers),  next(nullptr), prev(nullptr) {}

// Getters
std::string NewUser::getName() const {
    return name;
}

std::string NewUser::getGender() const {
    return gender;
}

std::string NewUser::getNumber() const {
    return number;
}

std::string NewUser::getProfession() const {
    return profession;
}

std::string NewUser::getSchool() const {
    return school;
}

int NewUser::getAge() const {
    return age;
}

double NewUser::getLatitude() const {
    return latitude;
}

double NewUser::getLongitude() const {
    return longitude;
}

std::string NewUser::getIsPremium() const {
    return isPremium;
}

int NewUser::getMinAgePreference() const {
    return minAgePreference;
}

int NewUser::getMaxAgePreference() const {
    return maxAgePreference;
}

int NewUser::getMaxDistancePreference() const {
    return maxDistancePreference;
}

std::string NewUser::getInterestedGender() const {
    return interestedGender;
}

std::string NewUser::getLikedNumbers(){
    return LikedNumbers;

}
NewUser* NewUser::getNext() const {
    return next;
}

NewUser* NewUser::getPrev() const {
    return prev;
}

void NewUser::setNext(NewUser* nextNode) {
    next = nextNode;
}

void NewUser::setPrev(NewUser* prevNode) {
    prev = prevNode;
}