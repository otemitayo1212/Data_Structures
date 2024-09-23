#include <iostream>
#include <vector>
#include <map>

std::vector<int> findModes(const std::vector<int>& sequence) {
    std::map<int, int> countMap;

    // Count occurrences of each integer in the sequence
    for (int num : sequence) {
        auto it = countMap.find(num);  
        if (it != countMap.end()) {
            // Key already exists, increment value
            it->second++;
        } else {
            // Key does not exist, insert new key-value pair
            countMap.insert(std::make_pair(num, 1));
        }
    }

    // Find the maximum frequency
    int maxFrequency = 0;
    for (const auto& pair : countMap) {
        maxFrequency = std::max(maxFrequency, pair.second);
    }

    // Find modes
    std::vector<int> modes;
    for (const auto& pair : countMap) {
        if (pair.second == maxFrequency) {
            modes.push_back(pair.first);
        }
    }

    return modes;
}

int main() {
    std::vector<int> sequence = {19, 83, -12 ,83, 65 ,19 ,45, -12, 45, 19, 45};
    
    std::vector<int> modes = findModes(sequence);

    std::cout << "Modes: ";
    for (int mode : modes) {
        std::cout << mode << " ";
    }
    std::cout << std::endl;

    return 0;
}
