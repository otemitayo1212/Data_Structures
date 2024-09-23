#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    std::vector<int> frequencies = {3, 7, 5, 9, 2}; // Example frequencies

    // Initialize maxFrequency
    int maxFrequency = 0;

    // Find the maximum frequency in the vector
    for (int freq : frequencies) {
        maxFrequency = std::max(maxFrequency, freq);
    }

    std::cout << "The maximum frequency in the vector is: " << maxFrequency << std::endl;

    return 0;
}
