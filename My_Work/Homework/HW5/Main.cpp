#include <iostream>
#include <list>
#include <string>
#include<fstream>
#include "User.h"
#include <cmath>
#include "MyList.h"


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

void findMatchedUsers(const std::string& mainNumber, MyList<std::string>& numbers, MyList<User>& allUsers, std::string ouputName) {  // Check
    MyList<User> matchedUsers; // Create a new MyList to store matched users

    // Loop through each number in the numbers list
    typename MyList<std::string>::Node* numNode = numbers.head;
    while (numNode != nullptr) {
        std::string number = numNode->data;

        // Loop through each user in the allUsers list
        typename MyList<User>::Node* userNode = allUsers.head;
        while (userNode != nullptr) {
            if (userNode->data.getNumber() == number ) {
                std::cout << "Found the person the user liked " << userNode->data.getNumber() <<" "<< userNode->data.getName() << std::endl;
                // Check if the user's liked users list contains the main number
                MyList<std::string> likedUsers = userNode->data.getLikedUsers();
                typename MyList<std::string>::Node* likedNode = likedUsers.head;
                while (likedNode != nullptr) {
                    std::string likedNumber = likedNode->data;

                    // If the main number is found in the liked users list, add the user to the matchedUsers list
                    if (likedNumber == mainNumber) {
                        std::cout <<userNode->data.getName() << "Matched with you"<<std::endl;
                        matchedUsers.push_back(userNode->data);
                        break; // Exit the innermost loop since the user is already added
                    }

                    likedNode = likedNode->next;
                }

            }

            userNode = userNode->next;
        }

        numNode = numNode->next;
    }
    std::ofstream outputFile(ouputName);
    if ( matchedUsers.getSize() == 0){
     outputFile << "You do not have any matches at this moment." << std::endl;
     return ;

    }
    typename MyList<User>::Node* matched = matchedUsers.head;
    while (matched != nullptr) {
        outputFile << matched->data.getName() << std::endl;
        matched = matched->next;
    }
    outputFile.close();

    // Now, matchedUsers contains all users who have the mainNumber in their liked list
    // You can further process matchedUsers or perform any desired operations with it
}


// Assume the Person class has getLat(), getLong(), getAge(), and getGender() methods

void profile(int ageMin, int ageMax, const std::string& outputName, double maxDistance, const std::string& gender, double firstLat, double firstLon, MyList<User>& myList) {
    MyList<User> matchedList; // Create a new MyList to store matched persons
    int counter = 0;

    // Loop through all objects in myList
    typename MyList<User>::Node* current = myList.head;
    while (current != nullptr) {
        // Get latitude and longitude of the current person
        double currentLat = current->data.getLatitude(); // check 
        double currentLon = current->data.getLongitude(); // check

        // Calculate distance between the current person and the first latitude/longitude
        double distance = calculateDistance(firstLat, firstLon, currentLat, currentLon);

        // Check if distance is within maxDistance and age is between ageMin and ageMax
        // Also check if gender matches
        if (distance <= maxDistance && current->data.getAge() >= ageMin && current->data.getAge() <= ageMax &&
            (gender == "both" || current->data.getGender() == gender)) {
            // Push back the current person to the matched list
            matchedList.push_back(current->data);
            counter++;
        }

        current = current->next;
    }
    std::ofstream outputFile(outputName);
    if (matchedList.getSize() == 0){
        outputFile << "There are no users matching with your preference at this moment." << std::endl;
        outputFile.close();
        return;
    }

    // Output the names of matched persons to the specified output
    typename MyList<User>::Node* matchedCurrent = matchedList.head;
    while (matchedCurrent != nullptr) {
        outputFile << matchedCurrent->data.getName() << std::endl;
        matchedCurrent = matchedCurrent->next;
    }
    outputFile.close();
}






int main(int argc, char* argv[]) {

    /*
    // Creating an instance of MyList with integer elements
    MyList<int> myList;

    // Test push_front: Adding elements to the front of the list
    myList.push_front(3);
    myList.push_front(2);
    myList.push_front(1);
    myList.print(); // Output: 1 2 3

    // Test push_back: Adding elements to the back of the list
    myList.push_back(4);
    myList.print(); // Output: 1 2 3 4

    // Test pop_front: Removing the first element of the list
    myList.pop_front();
    myList.print(); // Output: 2 3 4

    // Test pop_back: Removing the last element of the list
    myList.pop_back();
    myList.print(); // Output: 2 3

    // Test getSize: Getting the current size of the list
    std::cout << "Size: " << myList.getSize() << std::endl; // Output: Size: 2
*/
    MyList<User> People;
    std::string output = argv[2];
    std::string phone_number = argv[3];
    std::string action = argv[4];
    // open input file 
    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open input file." << std::endl;
        return 1;
    }
    int counter = 0;
    std::string name, gender, number, profession, school , interestedGender , Line, premium ;
    int age , minAgePreference, maxAgePreference, maxDistancePreference;
    double latitude, longitude ;
    while (inputFile >> name >> age >> gender >> number >> profession >> school >> latitude >> longitude >> premium  >> minAgePreference >> maxAgePreference >> maxDistancePreference >> interestedGender >> Line) {
        // Create a new User object
        User user(name, gender, number, profession, school, age, latitude, longitude, premium, minAgePreference, maxAgePreference, maxDistancePreference, interestedGender );
        // break down the number and add it to the class
        int pos = 0; // Move the position variable outside of the loop
        if (Line == "null"){
             user.addLikedUser(Line);
              People.push_back(user);
              counter++;
             continue;
        }else{
             for (int i = 0; i < Line.size() - 11; i++) {
            std::string num = "";
            if (Line[i] == '_') {
                num = Line.substr(pos, 12);
                user.addLikedUser(num);
                pos = i + 1; // Update the position after pushing the number
            }
        }
        // Add the last number after the last underscore
        user.addLikedUser(Line.substr(pos, 12));

        }
       
        // add user to the list of people
        People.push_back(user);
        counter++;

    }
    // for match First get the user were working with, and then  ceate  variables to store prefrence  age, gender, and distance
    // find the user using the number get the information you need for the first part 
    int min_age;
    int Max_age;
    std::string Gender;
    int MaxDistance;
    double Person_lat;
    double Person_long;
    double Distance;
    MyList<std::string> num_list;
    if (action == "profile"){
        typename MyList<User>::Node* current = People.head;
        while (current != nullptr) {
            if (current->data.getNumber() == phone_number ) {
                std::cout << "Found Person with number " << current->data.getNumber() <<" "<< current->data.getName() << std::endl;
                min_age = current->data.getMinAgePreference();
                Max_age = current->data.getMaxAgePreference();
                Gender = current->data.getInterestedGender();
                MaxDistance = current->data.getMaxDistancePreference();
                Person_lat = current->data.getLatitude();
                Person_long = current->data.getLongitude();
                profile(min_age, Max_age, output, MaxDistance, Gender, Person_lat, Person_long, People);


                break; // Exit the loop once found
            }
            current = current->next;
        }
        // now just call match

    }
        if (action == "match") {
        typename MyList<User>::Node* current = People.head;
        while (current != nullptr) {
            if (current->data.getNumber() == phone_number) {
                std::cout << "Found Person with number " << current->data.getNumber() << " " << current->data.getName() << std::endl;
                MyList<std::string> num_list = current->data.getLikedUsers();
            
                // Check if the list is empty or contains only "null" values
                if (num_list.getSize() == 0) {
                    std::cout << "You haven't swiped to the right" << std::endl;
                    return 0;
                }

                // Check if the list has a "null" value
                typename MyList<std::string>::Node* check = num_list.head;
                while (check != nullptr) {
                    std::cout<< check->data <<std::endl;
                    if (check->data == "null") {
                        std::cout << "You haven't swiped to the right" << std::endl;
                        return 0;
                    }
                    check = check->next; // Move to the next node
                }

                // If the list is valid, proceed with finding matched users
                findMatchedUsers(current->data.getNumber(), num_list, People, output);
                break; // Exit the loop once found
            }
            current = current->next;
        }
    }

    

  




    return 0;
}
