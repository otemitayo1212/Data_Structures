#include <iostream>
#include <vector>
#include <map>

std::vector<int> findModes(const std::vector<int>& sequence) {
    std::map<int, int> countMap;

    // create an instance using the number as the key and integrate 
    for (int num : sequence) {
        countMap[num]++;
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


