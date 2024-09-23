#include <iostream>

int countPaths(int x, int y) {
    if (x == 0 && y == 0) {
        return 1;
    } else if (x < 0 || y < 0) {
        return 0;
    } else {
        return countPaths(x - 1, y) + countPaths(x, y - 1);
    }
}

int main() {
    int x = 5, y = 5;
    std::cout << countPaths(x, y) << std::endl;  
}
