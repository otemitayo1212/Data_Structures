#include <iostream>
#include <string>
#include <list>
#include <cmath>
using namespace std;



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


template <class T>
void reverse(std::list<T> &data) {
  typename list<T>::iterator start = data.begin();
  typename list<T>::reverse_iterator end = data.rbegin();
  bool even = true;
  float length = (data.size())/2;
  if (fmod(length, 1.0) != 0.0) {
    even = false;
  }
  int loop = round(length);
  for (int i=1; i<=loop; i++){
    if (i==loop){
      if (even==true){
        T temp = *start;
        *start = *end;
        *end = temp;
      }
    }
    else {
      T temp = *start;
      *start = *end;
      *end = temp;
    }
    start++;
    end++;
  }
  
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