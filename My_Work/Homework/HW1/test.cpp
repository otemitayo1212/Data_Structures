
#include <iostream>
#include <vector>
#include <string>

int main() {
    // Sample vector of names
    std::vector<std::string> names = {"Alice", "Bob", "Charlie"};

    // Name to insert
    std::string newName = "David";

    // Position to insert (0 in this case)
    size_t position = 0;

    // Inserting the new name at the specified position
    names.insert(names.begin() + position, newName);

    // Display the updated vector
    for (const auto& name : names) {
        std::cout << name << " ";
    }

    return 0;
}




