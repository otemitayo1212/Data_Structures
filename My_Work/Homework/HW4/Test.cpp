#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <algorithm>
#include <vector>
#include "BusinessData.h"
using namespace std;



// Helper functions
std::string getName(std::string& line){
        int start = 0;
        // starting from the position start, and search the string variable line,
        // to find the first name string.
        int key_start = line.find("name", start);
        int value_start = key_start + 7;
        // remember to use escape.
        int value_end = line.find("\"", value_start);
        int len = value_end - value_start;
        // go from start to end, but exclude the character at end.
        // when we use the substr(start, length) function on a std::string,
        // the substring includes the character at the start position,
        // and the length of the substring is length.
        // It does not include the character at the position start + length.
        std::string name = line.substr(value_start, len);
        return name;
}
void printStar(std::ofstream& output, double value) {
    if (output.is_open()) {
        int wholePart = static_cast<int>(value);
        double fractionalPart = value - wholePart;
        while (wholePart > 0) {
            output << "\u2605"; // Print full star
            wholePart--;
        }
        if (fractionalPart == 0.5) {
             output << "\u00BD"; // Half star
        }
    } else {
        std::cerr << "Unable to open output file" << std::endl;
    }
}

string extractZipcode(const string& jsonString) {
    int startIndex = jsonString.find("\"postal_code\":\"");
    if (startIndex != string::npos) {
        startIndex += string("\"postal_code\":\"").length();
        int endIndex = jsonString.find("\"", startIndex);
        return jsonString.substr(startIndex, endIndex - startIndex);
    }
    return ""; // Return empty string if postal code is not found
}

bool compareFunction(const BusinessData& obj1, const BusinessData& obj2) {
    return obj1.getRating() > obj2.getRating();
}

std::string Find_cat(std::string& line){
        int start = 0;
        // starting from the position start, and search the string variable line,
        // to find the first categories string.
        int key_start = line.find("categories", start);
        int value_start = key_start + 13;
        // remember to use escape.
        int value_end = line.find("\"", value_start);
        int len = value_end - value_start;
        // go from start to end, but exclude the character at end.
        // when we use the substr(start, length) function on a std::string,
        // the substring includes the character at the start position,
        // and the length of the substring is length.
        // It does not include the character at the position start + length.
        std::string categories = line.substr(value_start, len);
        return categories;
}
void printDollar(std::ofstream& output, int value) {
    if (output.is_open()) {
        while (value > 0) {
            output << "$";
            value--;
        }
    } else {
        std::cerr << "Unable to open output file" << std::endl;
    }
}

// Fix up this function 
// Missing dollar sign is the price level
void printBusiness(const list<BusinessData>& businesses, const string& outputFilename) {
    ofstream outFile(outputFilename);
    if (!outFile.is_open()) {
        cerr << "Unable to open output file" << endl;
        return;
    }
    int counter = 0 ;


    for (std::list<BusinessData>::const_iterator it = businesses.begin(); it != businesses.end(); ++it) {
        counter ++;
        outFile << "=====================" << endl;
        outFile << counter << ". ";
        outFile << it->getName() << endl;
        printStar(outFile, it->getStars());
        outFile <<" " << it->getStars() << " (" << it->getReviewCount() << " reviews)" << endl; // add print star function
        // Print price using the printStar function
        outFile <<it->getCity() << " " ; // replace getPrice by a function that prints dolarsign
        printDollar(outFile,it->getPrice()) ;
        outFile << endl;
        outFile << it->getCategories() << endl;
    }
    outFile << "=====================" << endl;
    outFile.close();

}


int main(int argc, char *argv[]) {
    if (argc < 5) {
        cout << "Usage: " << argv[0] << " input.json output.txt zipcode categories" << endl;
        return 1;
    }

    string inputFilename = argv[1];
    string outputFilename = argv[2];
    string zipcode = argv[3];
    vector<string> categories;

    // Extract categories from command line arguments
    for (int i = 4; i < argc; ++i) {
        categories.push_back(argv[i]);
    }

    ifstream inputFile(inputFilename);
    if (!inputFile.is_open()) {
        cerr << "Error opening input file " << inputFilename << endl;
        return 1;
    }


    vector<BusinessData> businesses;
     list<BusinessData> PrintList;

    string line;
    while (getline(inputFile, line)) {
        bool matchCategory = false;
        for (const string& category : categories) { // works till here
            // TODO Replace line with the categories in the text
            string temp = Find_cat(line);
            
            if (temp.find(category) != string::npos) {  // works till here
                matchCategory = true;
                break;
            }
        }

        
        if (matchCategory) {
            string businessZipcode = extractZipcode(line);
            if (businessZipcode == zipcode) {
                // Construct BusinessData object and add to vector
                BusinessData business(line);
                businesses.push_back(business);
                PrintList.push_back(business);
            }
        }

       // Every thing works fine till here 

    }
   
    if (businesses.size() == 0){
        ofstream outFile(outputFilename);
        outFile <<"Sorry, we couldn't find any results"<< endl;
        outFile.close();
        return 1;
    }



    PrintList.sort(compareFunction); // debug
    //std::cout<<PrintList.size()<<std::endl; // debug
    //std::cout<<businesses.size()<<std::endl; // debug

    // Print businesses to output file
    // Do this by calling the business function
    printBusiness(PrintList,outputFilename);




    // Close files
    inputFile.close();
    return 0;
}
