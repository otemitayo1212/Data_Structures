
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

class NewUser {
private:
    std::string name;
    std::string number;
    NewUser* prev;
    NewUser* next;

public:
    NewUser(const std::string& _name, const std::string& _number)
        : name(_name), number(_number), prev(nullptr), next(nullptr) {}
    NewUser(const NewUser& other)
        : name(other.name), number(other.number), prev(nullptr), next(nullptr) {}

    std::string getNumber() const {
        return number;
    }

    std::string getName() const {
        return name;
    }

    NewUser* getNext() const {
        return next;
    }

    NewUser* getPrev() const {
        return prev;
    }

    void setNext(NewUser* node) {
        next = node;
    }

    void setPrev(NewUser* node) {
        prev = node;
    }
};

bool comparePhoneNumbers(const NewUser* user1, const NewUser* user2) {
    return user1->getNumber() < user2->getNumber();
}

int main() {
    // Sample collection of NewUser pointers
    std::vector<NewUser*> users;
    users.push_back(new NewUser("Alice", "123-456-789"));
    users.push_back(new NewUser("Bob", "234-567-890"));
    users.push_back(new NewUser("Charlie", "345-678-901"));

    // Additional test cases
    users.push_back(new NewUser("David", "456-789-012"));
    users.push_back(new NewUser("Emily", "567-890-123"));
    users.push_back(new NewUser("Frank", "678-901-234"));
    users.push_back(new NewUser("Grace", "789-012-345"));
    users.push_back(new NewUser("Henry", "890-123-456"));
    users.push_back(new NewUser("Isabel", "901-234-567"));
    users.push_back(new NewUser("Jack", "012-345-678"));
    users.push_back(new NewUser("Karen", "123-234-345"));

    // Sort the collection based on phone numbers
    std::sort(users.begin(), users.end(), comparePhoneNumbers);

    // Print the sorted collection
    for (const auto& user : users) {
        std::cout << user->getName() << ": " << user->getNumber() << std::endl;
    }

    // Clean up allocated memory
    for (auto user : users) {
        delete user;
    }

    return 0;
}
