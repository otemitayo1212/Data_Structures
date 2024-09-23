#ifndef NEWUSER_H
#define NEWUSER_H

#include <string>

class NewUser {
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
    std::string LikedNumbers;

public:
    NewUser* next; // Pointer to the next user node
    NewUser* prev; // Pointer to the previous user node

    // Constructor
    NewUser(const std::string& name, const std::string& gender, const std::string& number,
            const std::string& profession, const std::string& school, int age,
            double latitude, double longitude, std::string isPremium, int minAgePreference,
            int maxAgePreference, int maxDistancePreference, const std::string& interestedGender , std::string LikedNumbers);
   NewUser(const NewUser& other);

    
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
    std::string getLikedNumbers();
    NewUser* getNext() const;
    NewUser* getPrev() const;
    void setNext(NewUser* nextNode);
    void setPrev(NewUser* prevNode);
};

#endif // NEWUSER_H
