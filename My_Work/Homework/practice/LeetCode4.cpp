#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> seen;
        for (int num : nums) {
            if (seen.count(num)) {
                return true;
            }
            seen.insert(num);
        }
        return false;
    }
};
// I learned the .count function returns 1 if its in the set already and 0 if its not 
// I also learned that unordered_set is a hash table and is faster than a vector
// i learned that the vector class doesnt have a .length() function


/*

#include <vector>
using namespace std;

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) { // Start from i + 1 to avoid comparing the same elements
                if (nums[j] == nums[i]) {
                    return true;
                }
            }
        }
        return false;
    }
};



*/