#include <iostream>
#include <string>
#include <algorithm> // For std::remove

int main() {
    // Original phone number
    std::string phoneNumber = "318-125-5013";

    // Remove hyphens from the phone number
    phoneNumber.erase(std::remove(phoneNumber.begin(), phoneNumber.end(), '-'), phoneNumber.end());

    // Print the converted phone number
    std::cout << "Converted phone number: " << phoneNumber << std::endl;

    return 0;
}
