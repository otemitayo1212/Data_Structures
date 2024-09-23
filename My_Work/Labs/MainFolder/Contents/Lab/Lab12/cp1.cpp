#include <iostream>
#include <unordered_set>
#include <unordered_map>

bool isGood_set(int n) {
    std::unordered_set<int> seen;
    while (n != 1 && seen.find(n) == seen.end()) {
        seen.insert(n);
        int sum = 0;
        while (n > 0) {
            int digit = n % 10;
            sum += digit * digit;
            n /= 10;
        }
        n = sum;
    }
    return n == 1;
}

bool isGood_map(int n) {
    std::unordered_map<int, bool> seen;
    while (n != 1 && seen.find(n) == seen.end()) {
        seen[n] = true;
        int sum = 0;
        while (n > 0) {
            int digit = n % 10;  // this is going to split the number if it is 2 digits ex 12 = 1 2
            sum += digit * digit;
            n /= 10;
        }
        n = sum;
    }
    return n == 1;  // returns true if its(n is 1 )
}

int main() {
    // Test cases
    // 2, 4, 5, 6, 17, 18, 20 are not good numbers.
    // 1, 7, 10, 13, 19, 23, 28, 68 are good numbers.

    int testCases[] = {2,4,5,6,17,18,20,1,7,10,13,19,23,28,68};

    std::cout << "Using unordered_set:" << std::endl;
    for (int n : testCases) {
        if (isGood_set(n)) {
            std::cout << n << " is a good number." << std::endl;
        } else {
            std::cout << n << " is not a good number." << std::endl;
        }
    }

    std::cout << "\nUsing unordered_map:" << std::endl;
    for (int n : testCases) {
        if (isGood_map(n)) {
            std::cout << n << " is a good number." << std::endl;
        } else {
            std::cout << n << " is not a good number." << std::endl;
        }
    }

    return 0;
}
