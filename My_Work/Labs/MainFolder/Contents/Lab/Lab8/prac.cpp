#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int count = 0;
        for (auto it = nums.begin(); it != nums.end(); ) {
            if (*it != val) {
                count++;
                ++it; // Move the iterator forward
            } else {
                it = nums.erase(it); // Erase the element and get the next valid iterator
            }
        }
        return count;
    }
};

// Function to test removeElement function
void testRemoveElement() {
    Solution solution;

    // Test cases
    vector<vector<int> > testCases;
    testCases.push_back(vector<int>{3, 2, 2, 3});
    testCases.push_back(vector<int>{0, 1, 2, 2, 3, 0, 4, 2});

    vector<int> values;
    values.push_back(3);
    values.push_back(2);

    for (auto &testCase : testCases) {
        for (auto &val : values) {
            vector<int> nums = testCase;
            int result = solution.removeElement(nums, val);
            cout << "For input array: ";
            for (int num : testCase) {
                cout << num << " ";
            }
            cout << "and val = " << val << ", result: " << result << endl;
        }
    }
}

int main() {
    testRemoveElement();
    return 0;
}
