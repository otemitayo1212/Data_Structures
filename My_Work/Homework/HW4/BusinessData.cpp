#include "BusinessData.h"
#include <string>
#include <sstream>
#include <iostream>


BusinessData::BusinessData(std::string& l) : line(l) {
}
// Copy constructor
BusinessData::BusinessData(const BusinessData& other) : line(other.line) {}

// Copy assignment operator
BusinessData& BusinessData::operator=(const BusinessData& other) {
    if (this != &other) {
        // Copy the value of 'line' from 'other' to 'this'
        line = other.line;
    }
    return *this;
}
std::string BusinessData::getName()const{
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


double BusinessData::getRating()const{
        int start = 0;
        // starting from the position start, and search the string variable line,
        // to find the first stars string.
        int key_start = line.find("stars", start);
        int value_start = key_start + 7;
        // remember to use escape.
        int value_end = line.find("\"", value_start);
        // -1 here because this is not a string.
        int len = value_end - value_start - 1;
        // go from start to end, but exclude the character at end.
        // when we use the substr(start, length) function on a std::string,
        // the substring includes the character at the start position,
        // and the length of the substring is length.
        // It does not include the character at the position start + length.
        // convert this string to a double
        double stars = stod(line.substr(value_start, len));
        return stars;
}

int BusinessData::getPrice()const{
        int start = 0;
        // starting from the position start, and search the string variable line,
        // to find the first RestaurantsPriceRange2 string.
        int key_start = line.find("RestaurantsPriceRange2", start);
        // if not found, return now
        if(key_start == std::string::npos){
                return -1;
        }
        int value_start = key_start + 25;
        // remember to use escape.
        int value_end = line.find("\"", value_start);
        // -1 here because this is not a string.
        int len = value_end - value_start;
        // go from start to end, but exclude the character at end.
        // when we use the substr(start, length) function on a std::string,
        // the substring includes the character at the start position,
        // and the length of the substring is length.
        // It does not include the character at the position start + length.
        // convert this string to an integer
        int price = stoi(line.substr(value_start, len));
        return price;

    
}

int BusinessData::getReviewCount() const{
    int start = 0;
    int Key_start = line.find("review_count",start);
    if (Key_start == std::string::npos) {
    return -1;
}
    int value_start = Key_start + 14;
    int value_end = line.find(",",value_start);
    int len = value_end - value_start;
    int count = stoi(line.substr(value_start, len));
    return count;

 }
    
double BusinessData::getStars()const{
    int start = 0;
    int Key_start = line.find("stars",start);
   if (Key_start == std::string::npos) {
    return -1;
}
    int value_start = Key_start + 7;
    int value_end = line.find(",",value_start);
    int len = value_start - value_end;
    double numStars = stod(line.substr(value_start, len));
    return numStars;  

}
// check
std::string BusinessData::getCity() const {
    int start = 0;
    int key_start = line.find("\"city\"", start);
    int value_start = line.find(":", key_start) + 2; // Move past the colon and the opening quote
    int value_end = line.find("\"", value_start);
    int len = value_end - value_start;
    std::string city = line.substr(value_start, len);
    return city;
}

std::string BusinessData::getCategories()const{
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


