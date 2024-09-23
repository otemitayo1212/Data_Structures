#ifndef ITEM_H
#define ITEM_H

#include <string>

// Define a class to represent an item
class Item {
public:
    std::string name;
    double price;
    double rating;

    Item(std::string n, double p, double r) : name(n), price(p), rating(r) {}
};

#endif
