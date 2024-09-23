#include <iostream>
#include <string>
#include <unordered_map>

int lengthOfLongestSubstring(std::string s) {
    std::unordered_map<char, int> charIndexMap;
    int maxLength = 0;
    int start = 0;

    for (int end = 0; end < s.length(); ++end) {
        // If the current character is already in the map and its index is after the start of the current substring
        if (charIndexMap.find(s[end]) != charIndexMap.end() && charIndexMap[s[end]] >= start) {
            // Move the start of the substring to one position after the last occurrence of the current character
            start = charIndexMap[s[end]] + 1;
        }

        // Update the index of the current character in the map
        charIndexMap[s[end]] = end;

        // Update the maximum length if needed
        maxLength = std::max(maxLength, end - start + 1);
    }

    return maxLength;
}

int main() {
    // Test cases
    std::string s1 = "abcabcbb";
    std::string s2 = "bbbbb";
    std::string s3 = "pwwkew";

    std::cout << "Length of longest substring without repeating characters in \"" << s1 << "\": " << lengthOfLongestSubstring(s1) << std::endl;
    std::cout << "Length of longest substring without repeating characters in \"" << s2 << "\": " << lengthOfLongestSubstring(s2) << std::endl;
    std::cout << "Length of longest substring without repeating characters in \"" << s3 << "\": " << lengthOfLongestSubstring(s3) << std::endl;

    return 0;
}



