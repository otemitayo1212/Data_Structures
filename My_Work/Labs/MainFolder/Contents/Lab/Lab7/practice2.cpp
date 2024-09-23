// Overloading the output stream operator as a member function.

#include <vector>
#include <iostream>
#include <algorithm>

int main() {
   std::vector<int> myList;
    myList.push_back(1);
    myList.push_back(2);
    myList.push_back(3);
    myList.push_back(4);
    myList.push_back(5);
    myList.push_back(3);
    myList.push_back(3);

    // Using erase-remove idiom
    myList.erase(std::remove(myList.begin(), myList.end(), 3)); // Removes all occurrences of value 3

    // Printing the vector after removal
    for (auto elem : myList) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    return 0;
}
