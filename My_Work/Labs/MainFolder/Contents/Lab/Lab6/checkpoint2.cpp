#include <iostream>
#include <string>
#include <list>
#include <cmath>
using namespace std;


template <class T>
void reverse(std::list<T> &data) {
    typename std::list<T>::iterator end = data.end();
     --end ; // Move end iterator to the last element

   for (int i = 0 ; i < data.size(); i++) {
        T temp = *end; // Store the value of the current element
        end = data.erase(end); // Erase the current element and update end iterator
        data.push_back(temp); // Push the stored value to the back of the list
        --end; // Move end iterator towards the beginning
    }
}

template <class T>
void print(std::list<T> &data, const std::string &label) {
  typename list<T>::iterator printer = data.begin();
  std::cout << label << " ";
  while (printer != data.end()) {
    std::cout << " " << *printer;
    printer++;
  }
  std::cout << std::endl;
}

int main() {
  std::list<int> data;
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

  std::list<std::string> data2;
  data2.push_back("apple");
  data2.push_back("banana");
  data2.push_back("carrot");
  data2.push_back("date");

  print(data2,"before:");
  reverse(data2);
  print(data2,"after: ");
}
//  g++ -o prog checkpoint2.cpp

// ./prog