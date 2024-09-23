#include <iostream>
#include "bplustree.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

std::string getTitle(const std::string& line) { // works
    std::string title;
    size_t titleStart = line.find("\"title\":") + 10;
    size_t commaPos = line.find("\"average_rating\":", titleStart) - 3 ; // changed from comma pos to next section pos
    title = line.substr(titleStart , commaPos - titleStart);


    return title;
}

std::string getThumbUrl(const std::string& line) {
    std::string thumb_url;
    size_t thumbUrlStart = line.find("\"thumb\":") + 10;
    size_t commaPos = line.find("\"", thumbUrlStart) ; // changed from comma pos to next section pos
    thumb_url = line.substr(thumbUrlStart , commaPos - thumbUrlStart);
    return thumb_url;
}

double getAverageRating(const std::string& line) {
    double average_rating = 0.0;
    size_t ratingStart = line.find("\"average_rating\":") + 18;
    size_t commaPos = line.find(',', ratingStart);
    average_rating = std::stod(line.substr(ratingStart , commaPos - ratingStart)); 
    return average_rating;
}

int getRatingNumber(const std::string& line) {
    int rating_number = 0;
    size_t ratingNumberStart = line.find("\"rating_number\":") + 17;
     size_t commaPos = line.find(',', ratingNumberStart);
    rating_number = std::stoi(line.substr(ratingNumberStart , commaPos - ratingNumberStart)); 
    
    return rating_number;
}

double getPrice(const std::string& line) {
    double price = 0.0;
    size_t priceStart = line.find("\"price\":");
    if (priceStart != std::string::npos) {
        // Check if price is null
        // If not null, extract price
        size_t priceEnd = line.find(",", priceStart + 9); // 9 is the length of "\"price\":"
        if (priceEnd != std::string::npos) {
            price = std::stod(line.substr(priceStart + 9, priceEnd - priceStart - 9));
        }
    }
    return price;
}


void rangeSearchHelper(Node* node, double minPrice, double maxPrice, vector<Item*>& itemsInRange) {
    if (node == nullptr)
        return;

    // Traverse through the items of the current node
    for (int i = 0; i < node->items.size(); i++) {
        double price = node->items[i]->price;
        if (price >= minPrice && price <= maxPrice) {
            itemsInRange.push_back(node->items[i]);
        }
    }

    // If not a leaf node, recursively call rangeSearchHelper for children
    if (!node->isLeaf) {
        for (int i = 0; i < node->children.size(); i++) {
            rangeSearchHelper(node->children[i], minPrice, maxPrice, itemsInRange);
        }
    }
}

vector<Item*> rangeSearch(BPlusTree& bPlusTree, double minPrice, double maxPrice) {
    vector<Item*> itemsInRange;
    Node* current = bPlusTree.getRoot();
    
    // Recursive function to perform range search
    rangeSearchHelper(current, minPrice, maxPrice, itemsInRange);
    
    return itemsInRange;
}

int main(int argc, char* argv[]) {
    if (argc != 5) {
        cerr << "Usage: " << argv[0] << " input.json output.txt min max" << endl;
        return 1;
    }
    string inputFile = argv[1];
    string outputFile = argv[2];
    double minPrice = stod(argv[3]);
    double maxPrice = stod(argv[4]);
    // Create B+ tree with order 4
    BPlusTree bPlusTree(4);

    // Open the JSON file
    ifstream file(inputFile);
    if (!file.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    string line;
    while (std::getline(file, line)) {
        // Extract necessary information from JSON line
        double price;
        size_t priceStart = line.find("\"price\":");
        if (priceStart != std::string::npos) {
            // Move 9 spots forward to skip over the characters '"price": '
            size_t nullStart = priceStart + 9;
            // Find the position of the next comma after "price"
            size_t commaPos = line.find(',', nullStart);
            // Check if "null" is present between "price" and the next comma
            if (line.substr(nullStart, commaPos - nullStart) == "null") {
                continue; // If price is null, skip to the next iteration
            }
        }

        std::string title = getTitle(line);
        double average_rating = getAverageRating(line);
        int rating_number = getRatingNumber(line);
        std::string thumb_url = getThumbUrl(line);
        price = getPrice(line);

        // Create Item object
        Item* newItem = new Item(title, average_rating, rating_number, thumb_url, price);

        // Insert the Item object into the B+ tree
        bPlusTree.insert(newItem);
    }

    // Close the file
    file.close();
    // Next Step is to do a range search on the B+ tree between the range , if it is between the range of the max and the min then you add to a vector
    vector<Item*> itemsInRange = rangeSearch(bPlusTree, minPrice, maxPrice);
    // Sort the items based on the provided criteria
    sort(itemsInRange.begin(), itemsInRange.end(), [](Item* a, Item* b) {
        if (a->average_rating != b->average_rating)
            return a->average_rating > b->average_rating;
        if (a->price != b->price)
            return a->price < b->price;
        return a->title < b->title;
    });


    // Displaying items within the range
     // Open the output text file
    ofstream outputFileStream(outputFile);
    if (!outputFileStream.is_open()) {
        cerr << "Error opening output file." << endl;
        return 1;
    }

    // Write items within the range to the output text file
   for (Item* item : itemsInRange) {
    outputFileStream << item->title << endl;
    outputFileStream << item->average_rating << endl;
    outputFileStream << item->rating_number << endl;
    outputFileStream << item->thumb_url << endl;
    outputFileStream << "$" << item->price;
    if (item != itemsInRange.back()) { // Check if it's not the last item
        outputFileStream << endl; // Add newline if it's not the last item
    }
}

    // Close the output file
    outputFileStream.close();

    
    return 0;
}