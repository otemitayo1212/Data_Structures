#include <iostream>
#include <map>
#include <string>
using namespace std;

void add(map<int, string> &phonebook, int number, string const& name) {
    phonebook[number] = name;
}

void identify(const map<int, string> &phonebook, int number) {
    auto it = phonebook.find(number);
    if (it != phonebook.end())
        cout << it->second << " is calling!" << endl;
    else
        cout << "unknown caller!" << endl;
}

int main() {
    map<int, string> phonebook;

    add(phonebook, 1111, "fred");
    add(phonebook, 2222, "sally");
    add(phonebook, 3333, "george");

    identify(phonebook, 2222);
    identify(phonebook, 4444);

    return 0;
}
