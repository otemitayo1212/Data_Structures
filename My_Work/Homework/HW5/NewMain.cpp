#include <iostream>
#include "NewUser.h"
#include <string>
#include<fstream>
#include <cmath>
#include <vector>
#include <sstream>
#include <algorithm>

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
std::string replaceUnderscoresWithSpaces(const std::string& str) {
    std::string result = str;
    std::replace(result.begin(), result.end(), '_', ' ');
    return result;
}


bool comparePhoneNumbers(const std::string& phoneNumber1, const std::string& phoneNumber2) {
    std::istringstream ss1(phoneNumber1);
    std::istringstream ss2(phoneNumber2);

    std::string token1, token2;

    // Extract and compare each set of numbers
    while (std::getline(ss1, token1, '-') && std::getline(ss2, token2, '-')) {
        int number1 = std::stoi(token1);
        int number2 = std::stoi(token2);
        
        if (number1 != number2) {
            return number1 < number2;
        }
    }

    // If all sets of numbers are equal, the shorter phone number is considered smaller
    return phoneNumber1 > phoneNumber2;
}
bool compareUsersByPhoneNumber(NewUser* user1, NewUser* user2) {
    return comparePhoneNumbers(user1->getNumber(), user2->getNumber());
}

void sortUsersByPhoneNumber(std::vector<NewUser*>& users) {
    std::sort(users.begin(), users.end(), compareUsersByPhoneNumber);
}


NewUser* insertSorted(NewUser* headUser) { 
    if (!headUser) return nullptr;

    NewUser* sortedHead = nullptr;

    for (NewUser* current = headUser; current != nullptr; current = current->getNext()) {
        NewUser* newNode = new NewUser(*current);
        newNode->setPrev(nullptr);
        newNode->setNext(nullptr);

        // Insert the first node into the sorted list
        if (!sortedHead) {
            sortedHead = newNode;
        } else {
            NewUser* prev = nullptr;
            NewUser* sortedCurrent = sortedHead;

            // Find the correct position to insert the node
            while (sortedCurrent != nullptr && !comparePhoneNumbers(newNode->getNumber(), sortedCurrent->getNumber())) {
                prev = sortedCurrent;
                sortedCurrent = sortedCurrent->getNext();
            }

            // Insert the node
            if (!prev) {
                newNode->setNext(sortedHead);
                sortedHead->setPrev(newNode);
                sortedHead = newNode;
            } else {
                prev->setNext(newNode);
                newNode->setPrev(prev);
                newNode->setNext(sortedCurrent);
                if (sortedCurrent) {
                    sortedCurrent->setPrev(newNode);
                }
            }

        }
        
    }

    return sortedHead;
}


void findMatchedUsers(const std::string& mainNumber, std::string numbers,  NewUser* headUser , std::string ouputName) {  
    // Store all numbers in a vector
    std::vector<std::string> allNum;
    NewUser* secondheadUser = nullptr;
    NewUser* secondprevUser = nullptr;
    int pos = 0; // Move the position variable outside of the loop
    if (numbers == "null") {
     std::cout << "You haven't swiped right on any one" << std::endl;
    return ;
    } else {
        for (int i = 0; i < numbers.size() - 11; i++) {
            std::string num = "";
            if (numbers[i] == '_') {
                num = numbers.substr(pos, 12);
                allNum.push_back(num);
                pos = i + 1; // Update the position after pushing the number
            }
        }
        // Add the last number after the last underscore
        allNum.push_back(numbers.substr(pos, 12));
    }

    // Loop through all numbers in the list
    for (const std::string& num : allNum) {
        // Loop through the users linked to the headUser pointer
        // First find the users with thesame number (num)
        NewUser* current = headUser;
        while (current != nullptr) {
            // Check if the current user's liked numbers contain the mainNumber
            if ( current->getNumber() == num){
                std::string likedNumbers = current->getLikedNumbers();
                if (likedNumbers.find(mainNumber) != std::string::npos) {
                    // If found, create a new linked pointer
                    NewUser* NewcurrentUser = new NewUser(*current);

                    // If this is the first user, set it as the head
                    if (secondprevUser == nullptr) {
                        secondheadUser = NewcurrentUser;
                    } else {
                        // Link the previous user to the current user
                        secondprevUser->next = NewcurrentUser;
                        NewcurrentUser->prev = secondprevUser;
                    }

                    // Update prevUser pointer to the current user
                    secondprevUser = NewcurrentUser;
                }

            }
            
            current = current->next;
        }

        
    }
    // Find a way to sort (secondheadUser) peferable a function to keep code fluidity
    NewUser* sortedHead = insertSorted(secondheadUser);
    std::ofstream outputFile(ouputName);
    if (sortedHead == nullptr) {
        outputFile << "You do not have any matches at this moment." << std::endl;
        outputFile.close();
        return;
    }

    NewUser* currentUser = sortedHead;
    while (currentUser != nullptr) {
       outputFile << currentUser->getName() << " " << currentUser->getAge() << std::endl;
    
    // Print profession if available
    if (currentUser->getProfession() != "Undisclosed")
        outputFile <<replaceUnderscoresWithSpaces(currentUser->getProfession()) << std::endl;
    
    // Print school if available
    if (currentUser->getSchool() != "Undisclosed")
        outputFile <<replaceUnderscoresWithSpaces(currentUser->getSchool()) << std::endl;
    if (currentUser->next != nullptr)
        outputFile << std::endl;
        currentUser = currentUser->next;
    }
      // Close the output file
    outputFile.close();
    currentUser = secondheadUser;
    while (currentUser != nullptr) {
        NewUser* temp = currentUser; // Save the pointer to delete later
        currentUser = currentUser->next;
        delete temp; // Deallocate memory for the current user
    }


}


void profile(int ageMin, int ageMax, const std::string& outputName, double maxDistance, const std::string& gender, double firstLat, double firstLon, NewUser* headUser , std::string actualNumber) {

    // Loop through all objects in the linked list
    NewUser* secondheadUser = nullptr;
    NewUser* secondprevUser = nullptr;

    NewUser* current = headUser;
    while (current != nullptr) {
        // Get latitude and longitude of the current person
        double currentLat = current->getLatitude();
        double currentLon = current->getLongitude();

        // Calculate distance between the current person and the first latitude/longitude
        double distance = calculateDistance(firstLat, firstLon, currentLat, currentLon);

        // Check if distance is within maxDistance and age is between ageMin and ageMax
        // Also check if gender matches
        if (current->getNumber() == actualNumber){
            current = current->next;
            continue;

        }

        if (distance <= maxDistance && current->getAge() >= ageMin && current->getAge() <= ageMax &&  (gender == "Both" || current->getGender() == gender)) {
            // Push back the current person to the matched list
            // If this is the first user, set it as the head
             NewUser* NewcurrentUser = new NewUser(*current); 
            
            if (secondprevUser == nullptr) {
                secondheadUser = NewcurrentUser;
            } else {
                // Link the previous user to the current user
                secondprevUser->next = NewcurrentUser;
                NewcurrentUser->prev = secondprevUser;
            }

            // Update prevUser pointer to the current user
            secondprevUser = NewcurrentUser;
        }


        current = current->next;
    }
    std::ofstream outputFile(outputName);
   
    
    // Check if secondheadUser is null
    if (secondheadUser == nullptr) {
        outputFile << "There are no users matching with your preference at this moment." << std::endl;
        outputFile.close();
        return;
    }

    // Output the names of matched persons to the specified output
   NewUser* currentUser = secondheadUser;
    while (currentUser != nullptr) {
        // Print name and age
        outputFile << currentUser->getName() << " " << currentUser->getAge() << std::endl;
        
        // Print profession if available
        if (currentUser->getProfession() != "Undisclosed")
            outputFile << replaceUnderscoresWithSpaces(currentUser->getProfession()) << std::endl;
        
        // Print school if available
        if (currentUser->getSchool() != "Undisclosed")
            outputFile <<replaceUnderscoresWithSpaces(currentUser->getSchool()) << std::endl;
        
       if (currentUser->next != nullptr)
        outputFile << std::endl;
        
        currentUser = currentUser->next;
    }

      // Close the output file
    outputFile.close();
    
    // Deallocate memory for the second list
    currentUser = secondheadUser;
    while (currentUser != nullptr) {
        NewUser* temp = currentUser; // Save the pointer to delete later
        currentUser = currentUser->next;
        delete temp; // Deallocate memory for the current user
    }

}
void blocked(NewUser* headUser, NewUser* user1, NewUser* user2, const std::string& outputName) { 
    NewUser* firstHeadUser = nullptr;
    NewUser* firstPrevUser = nullptr;

    NewUser* secondHeadUser = nullptr;
    NewUser* secondPrevUser = nullptr;

    // Filtering for user1 and user2
    NewUser* current = headUser;
    while (current != nullptr) {
        // Skip if user is user1 or user2
        if (current->getNumber() == user1->getNumber() || current->getNumber() == user2->getNumber()) {
            current = current->next;
            continue;
        }
        double currentLat = current->getLatitude();
        double currentLon = current->getLongitude();

        // Calculate distance between the current person and the first latitude/longitude
        double distance1 = calculateDistance(user1->getLatitude(), user1->getLongitude(), currentLat, currentLon);
        double distance2 = calculateDistance(user2->getLatitude(), user2->getLongitude(), currentLat, currentLon);

        // Filtering based on user1's preferences
        if (distance1 <= user1->getMaxDistancePreference() && current->getAge() >= user1->getMinAgePreference() && current->getAge() <= user1->getMaxAgePreference() && (user1->getInterestedGender() == "Both" || current->getGender() == user1->getInterestedGender())) {
            // Creating a new node for filtered user for user1
           
            NewUser* newCurrentUser = new NewUser(*current);

            if (firstPrevUser == nullptr) {
                firstHeadUser = newCurrentUser;
            } else {
                // Link the previous user to the current user for user1
                firstPrevUser->setNext(newCurrentUser);
                newCurrentUser->setPrev(firstPrevUser);
            }

            // Update prevUser pointer to the current user for user1
            firstPrevUser = newCurrentUser;
        }

        // Filtering based on user2's preferences
        if (distance2 <= user2->getMaxDistancePreference() && current->getAge() >= user2->getMinAgePreference() && current->getAge() <= user2->getMaxAgePreference() && (user2->getInterestedGender() == "Both" || current->getGender() == user2->getInterestedGender())) {
            // Creating a new node for filtered user for user2
            
            NewUser* newCurrentUser = new NewUser(*current);

            if (secondPrevUser == nullptr) {
                secondHeadUser = newCurrentUser;
            } else {
                // Link the previous user to the current user for user2
                secondPrevUser->setNext(newCurrentUser);
                newCurrentUser->setPrev(secondPrevUser);
            }

            // Update prevUser pointer to the current user for user2
            secondPrevUser = newCurrentUser;
        }

        current = current->getNext();
    }

    std::ofstream outputFile(outputName);

outputFile << "profiles shown to " << user1->getName() << ":\n\n";

// Output profiles for user1
if (firstHeadUser == nullptr) {
    outputFile << "There are no users matching with your preference at this moment.\n\n";
} else {
    for (NewUser* current = firstHeadUser; current != nullptr; current = current->getNext()) {
        outputFile << current->getName() << " " << current->getAge() << "\n";
        if (current->getProfession() != "Undisclosed")
            outputFile << replaceUnderscoresWithSpaces(current->getProfession()) << "\n";
        if (current->getSchool() != "Undisclosed")
            outputFile << replaceUnderscoresWithSpaces(current->getSchool()) << "\n";
        outputFile << "\n";
    }
}

outputFile << "======\n\n";

outputFile << "profiles shown to " << user2->getName() << ":\n\n";

// Output profiles for user2
if (secondHeadUser == nullptr) {
    outputFile << "There are no users matching with your preference at this moment.\n\n";
} else {
    for (NewUser* current = secondHeadUser; current != nullptr; current = current->getNext()) {
        outputFile << current->getName() << " " << current->getAge() << "\n";
        if (current->getProfession() != "Undisclosed")
            outputFile << replaceUnderscoresWithSpaces(current->getProfession()) << "\n";
            
        if (current->getSchool() != "Undisclosed")
            outputFile << replaceUnderscoresWithSpaces(current->getSchool()) << "\n";
       if (current->getNext() != nullptr) {
        outputFile << "\n"; // Print newline only if there's another object after current
    }
    }
}

outputFile.close();


    // Clean up memory
    while (firstHeadUser != nullptr) {
        NewUser* temp = firstHeadUser;
        firstHeadUser = firstHeadUser->getNext();
        delete temp;
    }

    while (secondHeadUser != nullptr) {
        NewUser* temp = secondHeadUser;
        secondHeadUser = secondHeadUser->getNext();
        delete temp;
    }
}

void Likes(NewUser* headUser, const std::string& output, const std::string& number) {  
    NewUser* headforLikes = nullptr;
    NewUser* prevUserforLikes = nullptr;
    int counter;

    // Loop through the objects linked to headUser
    NewUser* current = headUser;
    while (current != nullptr) {
        // Get the liked numbers of the current user
        std::string likedNumbers = current->getLikedNumbers();

        // Check if the provided number is found in the liked numbers
        if (likedNumbers.find(number) != std::string::npos) {
            // Create a new user object with the same data as the current user
            NewUser* newUser = new NewUser(*current);

            // Link the new user to the linked list headforLikes
            if (prevUserforLikes == nullptr) {
                headforLikes = newUser;
            } else {
                prevUserforLikes->next = newUser;
                newUser->prev = prevUserforLikes;
            }
            prevUserforLikes = newUser;
        }

        current = current->next;
    }

     // You can write code here to perform further operations, such as printing or sorting
    std::ofstream outputFile(output);
    if (headforLikes == nullptr) {
        outputFile << "You have not received any likes so far." << std::endl;
        outputFile.close();
        return;
    }

     NewUser* currentUser = headforLikes;
        while (currentUser != nullptr) {
            // Print liked object data to output file
             outputFile << currentUser->getName() << " " << currentUser->getAge() << std::endl;
    
    // Print profession if available
    if (currentUser->getProfession() != "Undisclosed")
        outputFile << replaceUnderscoresWithSpaces(currentUser->getProfession()) << std::endl;
    
    // Print school if available
    if (currentUser->getSchool() != "Undisclosed")
        outputFile <<replaceUnderscoresWithSpaces(currentUser->getSchool()) << std::endl;
    if (currentUser->next != nullptr)
        outputFile << std::endl;
    currentUser = currentUser->next;
        }
        // Close the output file
        outputFile.close(); 
    // Free memory for the liked users after closing the output file
    currentUser = headforLikes;
    while (currentUser != nullptr) {
        NewUser* temp = currentUser;
        currentUser = currentUser->next;
        delete temp; // Deallocate memory for the node 
}
}


void removeNumber(std::string& numbers, const std::string& numberToRemove) {
    // Find the position of the number to remove in the string
    std::size_t pos = numbers.find(numberToRemove);

    // If the number is found, remove it along with the preceding underscore
   
    if (pos == 0) {
        numbers.erase(pos, numberToRemove.length() + 1);
    } else if (pos != std::string::npos) {
        numbers.erase(pos - 1, numberToRemove.length() + 1);
    }

}



void unmatch(const std::string& firstName, const std::string& firstLikedNumbers, const std::string& userOneMainNumber,const std::string& secondName,const std::string& secondLikedNumbers,
             const std::string& userTwoMainNumber, const std::string& outputFileName, NewUser* headUser) {
    // Convert firstLikedNumbers and secondLikedNumbers to vectors of strings
    std::vector<std::string> firstLikedNums;
    std::vector<std::string> secondLikedNums;
    int pos = 0; // Move the position variable outside of the loop
    if (firstLikedNumbers == "null") {
        std::cout << "First user hasn't swiped right on anyone" << std::endl;
        return;
    } else {
        for (int i = 0; i < firstLikedNumbers.size() - 11; i++) {
            std::string num = "";
            if (firstLikedNumbers[i] == '_') {
                num = firstLikedNumbers.substr(pos, 12);
                firstLikedNums.push_back(num);
                pos = i + 1; // Update the position after pushing the number
            }
        }
        // Add the last number after the last underscore
        firstLikedNums.push_back(firstLikedNumbers.substr(pos, 12));
    }

    pos = 0; // Reset the position variable
    if (secondLikedNumbers == "null") {
        std::cout << "Second user hasn't swiped right on anyone" << std::endl;
        return;
    } else {
        for (int i = 0; i < secondLikedNumbers.size() - 11; i++) {
            std::string num = "";
            if (secondLikedNumbers[i] == '_') {
                num = secondLikedNumbers.substr(pos, 12);
                secondLikedNums.push_back(num);
                pos = i + 1; // Update the position after pushing the number
            }
        }
        // Add the last number after the last underscore
        secondLikedNums.push_back(secondLikedNumbers.substr(pos, 12));
    }
    std::vector<NewUser*> userOneMatches;
    std::vector<NewUser*> userTwoMatches;


    for (const std::string& num : firstLikedNums) {
        // Loop through the users linked to the headUser pointer
        // First find the users with the same number (num)
        NewUser* current = headUser;
        while (current != nullptr) {
            // Check if the current user's number matches num
            if (current->getNumber() == num) {
                std::string likedNumbers = current->getLikedNumbers();
                // Check if the mainNumber is in the likedNumbers
                if (likedNumbers.find(userOneMainNumber) != std::string::npos) {
                    // If found, add to the vector
                    userOneMatches.push_back(current);
                }
            }
            // Move to the next user
            current = current->next;
        }
    }
    for (const std::string& num : secondLikedNums) {
        // Loop through the users linked to the headUser pointer
        // First find the users with the same number (num)
        NewUser* current = headUser;
        while (current != nullptr) {
            // Check if the current user's number matches num
            if (current->getNumber() == num) {
                std::string likedNumbers = current->getLikedNumbers();
                // Check if the mainNumber is in the likedNumbers
                if (likedNumbers.find(userTwoMainNumber) != std::string::npos) {
                    // If found, add to the vector
                    userTwoMatches.push_back(current);
                }
            }
            // Move to the next user
            current = current->next;
        }
    }
sortUsersByPhoneNumber(userOneMatches);
sortUsersByPhoneNumber(userTwoMatches);

std::ofstream outputFile(outputFileName);

if (userOneMatches.empty() && !userTwoMatches.empty()) {
    outputFile << firstName << "'s match list:" << std::endl << std::endl;
    outputFile << "You do not have any matches at this moment." << std::endl << std::endl ;

    outputFile << "======" << std::endl << std::endl;
    outputFile << secondName << "'s match list:" << std::endl << std::endl;
    for (size_t i = 0; i < userTwoMatches.size(); ++i) {
        const NewUser* user = userTwoMatches[i];
        outputFile << user->getName() << " " << user->getAge() << std::endl;
        if (user->getProfession() != "Undisclosed")
            outputFile << replaceUnderscoresWithSpaces(user->getProfession()) << std::endl;
        if (user->getSchool() != "Undisclosed")
            outputFile << replaceUnderscoresWithSpaces(user->getSchool()) << std::endl;
        if (i != userTwoMatches.size() - 1)
            outputFile << std::endl;
    }
} else if (userTwoMatches.empty() && !userOneMatches.empty()) {
    outputFile << firstName << "'s match list:" << std::endl << std::endl;
    for (size_t i = 0; i < userOneMatches.size(); ++i) {
        const NewUser* user = userOneMatches[i];
        outputFile << user->getName() << " " << user->getAge() << std::endl;
        if (user->getProfession() != "Undisclosed")
            outputFile << replaceUnderscoresWithSpaces(user->getProfession()) << std::endl;
        if (user->getSchool() != "Undisclosed")
            outputFile << replaceUnderscoresWithSpaces(user->getSchool()) << std::endl;
        if (i != userOneMatches.size() - 1)
            outputFile << std::endl;
    }
    outputFile << std::endl;
    outputFile << "======" << std::endl << std::endl;
    outputFile << secondName << "'s match list:" << std::endl << std::endl;
    outputFile << "You do not have any matches at this moment." << std::endl;
} else if (userTwoMatches.empty() && userOneMatches.empty()) {
    outputFile << firstName << "'s match list:" << std::endl << std::endl;
    outputFile << "You do not have any matches at this moment." << std::endl << std::endl;
    outputFile << "======" << std::endl << std::endl;
    outputFile << secondName << "'s match list:" << std::endl << std::endl;
    outputFile << "You do not have any matches at this moment." << std::endl;
} else {
    outputFile << firstName << "'s match list:" << std::endl << std::endl;
    for (size_t i = 0; i < userOneMatches.size(); ++i) {
        const NewUser* user = userOneMatches[i];
        outputFile << user->getName() << " " << user->getAge() << std::endl;
        if (user->getProfession() != "Undisclosed")
            outputFile << replaceUnderscoresWithSpaces(user->getProfession()) << std::endl;
        if (user->getSchool() != "Undisclosed")
            outputFile << replaceUnderscoresWithSpaces(user->getSchool()) << std::endl;

         if (i != userOneMatches.size() - 1)
            outputFile << std::endl;
    }
     outputFile << std::endl;

    outputFile << "======" << std::endl << std::endl;
    outputFile << secondName << "'s match list:" << std::endl << std::endl;
    for (size_t i = 0; i < userTwoMatches.size(); ++i) {
        const NewUser* user = userTwoMatches[i];
        outputFile << user->getName() << " " << user->getAge() << std::endl;
        if (user->getProfession() != "Undisclosed")
            outputFile << replaceUnderscoresWithSpaces(user->getProfession()) << std::endl;
        if (user->getSchool() != "Undisclosed")
            outputFile << replaceUnderscoresWithSpaces(user->getSchool()) << std::endl;
        if (i != userTwoMatches.size() - 1)
            outputFile << std::endl;
    }
}

outputFile.close();


    }



int main(int argc, char* argv[]) {
    
    std::string output = argv[2];
    std::string phone_number = argv[3];
    std::string action = argv[4];
    // open input file 
    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open input file." << std::endl;
        return 1;
    }
   std::string name, gender, number, profession, school , interestedGender , Line, premium ;
    int age , minAgePreference, maxAgePreference, maxDistancePreference;
    double latitude, longitude ;
    // Pointer to keep track of the head of the linked list
    NewUser* headUser = nullptr;
    // Pointer to keep track of the previous user
    NewUser* prevUser = nullptr;

    // Read data from the file and create NewUser objects
    while (inputFile >> name >> age >> gender >> number >> profession >> school >> latitude >> longitude >> premium >> minAgePreference >> maxAgePreference >> maxDistancePreference >> interestedGender >> Line) {
        // Create a new NewUser object
        NewUser* currentUser = new NewUser(name, gender, number, profession, school, age, latitude, longitude, premium, minAgePreference, maxAgePreference, maxDistancePreference, interestedGender , Line);

        // If this is the first user, set it as the head
        if (prevUser == nullptr) {
            headUser = currentUser;
        } else {
            // Link the previous user to the current user
            prevUser->next = currentUser;
            currentUser->prev = prevUser;
        }

        // Update prevUser pointer to the current user
        prevUser = currentUser;
    }

    // Close the input file
    inputFile.close();
   // Now find the user name given in the comand line input


    // Traverse the linked list and print user information
    NewUser* currentUser = headUser; // Start from the head of the list
    NewUser* Main_user = nullptr;
    while (currentUser != nullptr) {
        if ( currentUser->getNumber() == phone_number){
            Main_user = currentUser;
        }
        
        // Move to the next user
        currentUser = currentUser->next;
    }
    if (Main_user == nullptr){
        std::cout<< "person is not found"<< std::endl;
        return 1;
    }
    int min_age;
    int Max_age;
    std::string numbers;
    std::string Gender;
    int MaxDistance;
    double Person_lat;
    double Person_long;
    if (action == "profile"){
                min_age = Main_user->getMinAgePreference();
                Max_age = Main_user->getMaxAgePreference();
                Gender = Main_user->getInterestedGender();
                MaxDistance = Main_user->getMaxDistancePreference();
                Person_lat = Main_user->getLatitude();
                Person_long = Main_user->getLongitude();
                profile(min_age, Max_age, output, MaxDistance, Gender, Person_lat, Person_long, headUser , phone_number);


    }
    if (action == "match"){
         numbers = Main_user->getLikedNumbers();

        findMatchedUsers(phone_number , numbers, headUser , output );


    }
    if (action == "like"){
         std::cout << "Found Person with number " << Main_user->getNumber() <<" "<< Main_user->getName() << std::endl;
        if (Main_user->getIsPremium() == "false"){
            std::ofstream outputFile(output);
            outputFile << "Only premium users can view who liked you." << std::endl;
            outputFile.close();
            return 1;
        }else{ 
            Likes(headUser, output, phone_number);
        }

    }
    if (action == "unmatch"){
       
        std::string second_phone_number = argv[5];
        std::string line1 =  Main_user->getLikedNumbers();
        std::string line2 ;
 
        NewUser* currentUser = headUser; // Start from the head of the list
        NewUser* Second_user = nullptr;
        while (currentUser != nullptr) {
            
            if ( currentUser->getNumber() == second_phone_number){
                Second_user  = currentUser;
                line2 = Second_user->getLikedNumbers();
                break;
            }
            
            // Move to the next user
            currentUser = currentUser->next;
        }
        // first check if they actially matched each other
        if ((line1.find(second_phone_number)  != std::string::npos) && (line2.find(phone_number) != std::string::npos )  ) {
            // remove the numbers from the string and then call the matched fuction 
            removeNumber(line1, second_phone_number);
            removeNumber(line2, phone_number);
            // call the unmatch function we created
            unmatch( Main_user->getName() , line1 , phone_number, Second_user->getName() ,line2 ,
             second_phone_number,output,headUser);


        } else {
            std::cout << "You guys are not matched"<< std::endl;
            return 1;
        }

    }
    if (action == "block"){
         std::string second_phone_number = argv[5];

        NewUser* currentUser = headUser; // Start from the head of the list
        NewUser* Second_user = nullptr;
        while (currentUser != nullptr) {
            
            if ( currentUser->getNumber() == second_phone_number){
                Second_user  = currentUser;
                break;
            }
            
            // Move to the next user
            currentUser = currentUser->next;
        }
        blocked(headUser, Main_user, Second_user , output);
    }


// TODO Remove _ from schools
// TODO Find a way to sort by Number before outputing
    // Free memory
    while (headUser != nullptr) {
        NewUser* temp = headUser->next;
        delete headUser;
        headUser = temp;
    }



    return 0;
}
