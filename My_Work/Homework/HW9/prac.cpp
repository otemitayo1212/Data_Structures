#include <iostream>
#include <boost/btree/btree_map.hpp>
#include <vector>
#include <algorithm>

struct Product {
    std::string title;
    double price;
    int rating;

    bool operator<(const Product& other) const {
        if (rating != other.rating)
            return rating > other.rating;
        if (price != other.price)
            return price < other.price;
        return title < other.title;
    }
};

int main() {
    // Define a comparator for sorting based on price
    auto compare_by_price = [](const Product& p1, const Product& p2) {
        return p1.price < p2.price;
    };

    // Create multiple objects
    std::vector<Product> products = {
        {"Product A", 10.5, 4},
        {"Product B", 8.0, 5},
        {"Product C", 12.0, 3},
        {"Product D", 9.5, 4},
        {"Product E", 11.0, 5}
    };

    // Put these objects in a B+ Tree
    boost::btree::btree_map<double, Product> btree;
    for (const auto& product : products) {
        btree.insert(std::make_pair(product.price, product));
    }

    // Use Range search to search for the products in the price range
    double min_price = 9.0;
    double max_price = 11.0;

    auto lower = btree.lower_bound(min_price);
    auto upper = btree.upper_bound(max_price);

    // Store the products within the price range in a vector
    std::vector<Product> productsInRange;
    for (auto it = lower; it != upper; ++it) {
        productsInRange.push_back(it->second);
    }

    // Sort the products based on the defined comparison criteria
    std::sort(productsInRange.begin(), productsInRange.end(), compare_by_price);

    // Display the sorted products
    std::cout << "Products within price range " << min_price << " - " << max_price << ":\n";
    for (const auto& product : productsInRange) {
        std::cout << "Title: " << product.title << ", Price: " << product.price << ", Rating: " << product.rating << std::endl;
    }

    return 0;
}
