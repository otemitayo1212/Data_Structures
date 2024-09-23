#include <iostream>
#include <string>
#include <vector>


template <class T>
void print(std::vector<T> &data, const std::string &label) {
  std::cout << label << " ";
  for (int i = 0; i < data.size(); i++) {
    std::cout << " " << data[i];
  }
  std::cout << std::endl;
}


#include <vector>

template <class T>
void reverse(std::vector<T> &data) {
    // Get the size of the vector
    int n = data.size();
    
    // Iterate through the first half of the vector
    // Swap elements from the beginning with elements from the end
    // This effectively reverses the order of elements in the vector
    for (int i = 0; i < n / 2; ++i) {
        // Swap data[i] with data[n - 1 - i]
        T temp = data[i];
        data[i] = data[n - 1 - i];
        data[n - 1 - i] = temp;
    }
}


int main() {
  std::vector<int> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);
  data.push_back(4);
  data.push_back(5);
  data.push_back(6);
  data.push_back(7);

  print(data,"before:");
  reverse(data);
  print(data,"after: ");

  std::vector<std::string> data2;
  data2.push_back("apple");
  data2.push_back("banana");
  data2.push_back("carrot");
  data2.push_back("date");

  print(data2,"before:");
  reverse(data2);
  print(data2,"after: ");

}
