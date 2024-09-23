#include <iostream>


void compute_squares(unsigned int* a, unsigned int* b, unsigned int n) {
    // Use pointer arithmetic to square each element in array 'a' and store the result in array 'b'
    for (unsigned int i = 0; i < n; ++i) {
        *(b + i) = (*(a + i)) * (*(a + i));
    }
}

int main() {
   const int n = 5; // or any other constant value
    // Test case 1
    unsigned int array1[n] = {1, 2, 3, 4, 5};
    unsigned int array2[n];

    compute_squares(array1, array2, n);

    std::cout << "Test Case 1:\n";
    for (unsigned int i = 0; i < n; ++i) {
        std::cout << array2[i] << " ";
    }
    std::cout << "\n\n";

    // Test case 2
    unsigned int array3[n] = {0, 10, 20, 30, 40};
    unsigned int array4[n];

    compute_squares(array3, array4, n);

    std::cout << "Test Case 2:\n";
    for (unsigned int i = 0; i < n; ++i) {
        std::cout << array4[i] << " ";
    }
    std::cout << "\n";


    return 0;
}