#include <iostream>
#include <cmath>
#include <cstdlib>

bool check_root(int a, int b, int c, float root) {
  float check = a * root * root + b * root + c;
  if (fabs(check) > 0.0001) {
    std::cerr << "ERROR:  " << root << " is not a root of this formula." << std::endl;
    return false;
  } else {
    return true;
  }
}

bool find_roots(int a, int b, int c, float &root_1, float &root_2) {
  int radical = b * b - 4 * a * c;
  if (radical < 0) {
    std::cerr << "ERROR:  Imaginary roots" << std::endl;
    return false;
  }
  float sqrt_radical = sqrt(radical);
  root_1 = (-b + sqrt_radical) / (2 * a);
  root_2 = (-b - sqrt_radical) / (2 * a);
  return true;
}

int main() {
  while (true) {
    std::cout << "Enter 3 integer coefficients to a quadratic function: a*x*x + b*x + c = 0" << std::endl;
    int my_a, my_b, my_c;
    std::cin >> my_a >> my_b >> my_c;
    float root_1, root_2;
    bool success = find_roots(my_a, my_b, my_c, root_1, root_2);
    if (!success)
      continue;
    std::cout << "The roots are: " << root_1 << " and " << root_2 << std::endl;
    if (check_root(my_a, my_b, my_c, root_1) && check_root(my_a, my_b, my_c, root_2)) {
      break;
    } else {
      std::cerr << "ERROR:  Unable to verify one or both roots." << std::endl;
      exit(1);
    }
  }
  return 0;
}
