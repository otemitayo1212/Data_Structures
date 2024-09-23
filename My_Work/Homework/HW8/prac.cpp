#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Function to convert time strings like '7 hours ago' to integer representation
int convertToMinutes(const string& timeStr) {
    size_t found = timeStr.find("hours ago");
    if (found != string::npos) {
        return stoi(timeStr.substr(0, found)) * 60;
    }

    found = timeStr.find("minutes ago");
    if (found != string::npos) {
        return stoi(timeStr.substr(0, found));
    }

    found = timeStr.find("days ago");
    if (found != string::npos) {
        return stoi(timeStr.substr(0, found)) * 24 * 60;
    }

    found = timeStr.find("months ago");
    if (found != string::npos) {
        return stoi(timeStr.substr(0, found)) * 30 * 24 * 60;
    }

    found = timeStr.find("years ago");
    if (found != string::npos) {
        return stoi(timeStr.substr(0, found)) * 365 * 24 * 60;
    }

    return 0;
}

// Custom comparator function to sort time strings from latest to earliest
bool compareTime(const string& a, const string& b) {
    return convertToMinutes(a) > convertToMinutes(b);  // this is where you pick out the portion you want to compare with
}

// Function to sort the vector of time strings
void sortTimeVector(vector<string>& timeVec) {
    sort(timeVec.begin(), timeVec.end(), compareTime);
}

int main() {
    vector<string> timeVec = {
        "7 hours ago", "7 hours ago", "2 hours ago", "7 hours ago", "6 hours ago",
        "51 minutes ago", "4 hours ago", "7 hours ago", "7 hours ago", "6 hours ago",
        "7 hours ago", "7 hours ago", "7 hours ago", "7 hours ago", "11 years ago",
        "7 hours ago", "6 hours ago", "1 month ago", "4 hours ago", "6 months ago",
        "7 hours ago", "7 months ago", "5 hours ago", "7 days ago", "7 hours ago"
    };

    cout << "Before sorting:" << endl;
    for (const auto& time : timeVec) {
        cout << time << endl;
    }

    sortTimeVector(timeVec);

    cout << "\nAfter sorting:" << endl;
    for (const auto& time : timeVec) {
        cout << time << endl;
    }

    return 0;
}
