#include <iostream>
#include <string>

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    while (head != nullptr) {
        ListNode* next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }
    return prev;
}
 int getLength(ListNode* head) {
        if (head == NULL) {
            return 0;
        }
        ListNode* temp = head;
        int ans = 0;
        while (temp) { // while temp still exists
            ans++;
            temp = temp->next;
        }
        return ans;
    }
void printList(ListNode* head) {
    while (head != nullptr) {
        std::cout << head->val << " -> ";
        head = head->next;
    }
    std::cout << "nullptr" << std::endl;
}


ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    // Next step is to even out the numbers by comparing lengths
    int a = getLength(l1);
    int b = getLength(l2);
    int difference = abs(a - b);
    
   if (a < b) {
    ListNode* temp1 = l1;
    while (temp1->next != nullptr) {
        temp1 = temp1->next;
    }
    while (difference > 0) {
        temp1->next = new ListNode(0);
        temp1 = temp1->next;
        difference--;
    }
} else if (b < a) {
    ListNode* temp2 = l2;
    while (temp2->next != nullptr) {
        temp2 = temp2->next;
    }
    while (difference > 0) {
        temp2->next = new ListNode(0);
        temp2 = temp2->next;
        difference--;
    }
}
ListNode* result = nullptr;
ListNode* resultHead = nullptr; // Pointer to the head of the result list
int carry = 0;

while (l1 != nullptr || l2 != nullptr) {
    int sum = carry; // Initialize sum with the carry
    if (l1 != nullptr) {
        sum += l1->val;
        l1 = l1->next;
    }
    if (l2 != nullptr) {
        sum += l2->val;
        l2 = l2->next;
    }

    carry = sum / 10;
    int digit = sum % 10;

    // Create a new node with the sum
    ListNode* newNode = new ListNode(digit);
    if (result == nullptr) {
        result = newNode;
        resultHead = result; // Set the head of the result list
    } else {
        result->next = newNode;
        result = result->next;
    }
}

// Check if there is a carry after the loop
if (carry > 0) {
    ListNode* newNode = new ListNode(carry);
    result->next = newNode;
}

return resultHead; // Return the head of the result list
}

int main() {
    // Create input linked lists
    ListNode* l1 = new ListNode(9);
    ListNode* temp1 = l1;
    for (int i = 0; i < 6; ++i) {
        temp1->next = new ListNode(9);
        temp1 = temp1->next;
    }

    ListNode* l2 = new ListNode(9);
    ListNode* temp2 = l2;
    for (int i = 0; i < 3; ++i) {
        temp2->next = new ListNode(9);
        temp2 = temp2->next;
    }

    std::cout << "Input l1: ";
    printList(l1);

    std::cout << "Input l2: ";
    printList(l2);

    // Calculate the sum of the linked lists
    ListNode* result = addTwoNumbers(l1, l2);

    std::cout << "Output: ";
    printList(result);

    // Clean up memory
    while (l1 != nullptr) {
        ListNode* temp = l1;
        l1 = l1->next;
        delete temp;
    }
    while (l2 != nullptr) {
        ListNode* temp = l2;
        l2 = l2->next;
        delete temp;
    }
    while (result != nullptr) {
        ListNode* temp = result;
        result = result->next;
        delete temp;
    }

    return 0;
}
