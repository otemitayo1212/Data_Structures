#include <vector>
#include <limits>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int minPrice = numeric_limits<int>::max();
        int maxProfit = 0;

        for (int i = 0; i < prices.size(); i++) {
            // Update the minimum price if the current price is lower
            if (prices[i] < minPrice) {
                minPrice = prices[i];
            }
            // Calculate the profit if the current price is sold
            int currentProfit = prices[i] - minPrice;
            // Update the maximum profit if the current profit is higher
            if (currentProfit > maxProfit) {
                maxProfit = currentProfit;
            }
        }

        return maxProfit;
    }
};
