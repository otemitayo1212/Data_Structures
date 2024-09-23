#include <iostream>
#include <cstdlib>  // For atoi function

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <integer1> <integer2> ..." << std::endl;
        return 1;  // Exit with an error code
    }

    int product = 1;

    for (int i = 1; i < argc; ++i) {
        // Convert the command-line argument to an integer using atoi
        int num = std::atoi(argv[i]);

        // Check if conversion was successful
        if (num == 0 && argv[i][0] != '0') {
            std::cerr << "Invalid input: " << argv[i] << " is not a valid integer." << std::endl;
            return 1;  // Exit with an error code
        }

        // Multiply the current integer with the product
        product *= num;
    }

    // Print the product of integers
    std::cout << "Product of integers: " << product << std::endl;

    return 0;  // Exit successfully
}
