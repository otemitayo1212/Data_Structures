#include <iostream>

// Function to calculate the product of two numbers
int multiply(int a, int b) {
    return a * b;
}

int main() {
    int num1 = 5;
    int num2 = 7;

    int sum = num1 + num2;
    int product = multiply(num1, num2);

    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Product: " << product << std::endl;

    return 0;
}

