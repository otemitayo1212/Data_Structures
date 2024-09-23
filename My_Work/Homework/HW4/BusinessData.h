#ifndef BUSINESSDATA_H
#define BUSINESSDATA_H
#include <string>
#include <iostream>
class BusinessData {
    public:
    BusinessData(std::string& l);
    BusinessData(const BusinessData& other);
    BusinessData& operator=(const BusinessData& other);

    std::string getName() const;
    double getRating() const;
    int getPrice()const;
    int getReviewCount()const;
    double getStars()const;
    std::string getCity() const;
    std::string getCategories() const;
   

        

    private:
    std::string line;

};
#endif 