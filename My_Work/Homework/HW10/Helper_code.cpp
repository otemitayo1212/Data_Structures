#include <queue>
#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>

// Data structure to store video information
struct Video {
    std::string name;
    int viewCount;

    // Constructor
    Video(std::string n, int views) : name(n), viewCount(views) {}

    // Overload '<' operator for sorting
    bool operator<(const Video& other) const {
        return viewCount < other.viewCount;
    }
};

// Custom comparison function for priority queue
struct CompareHashTags {
    bool operator()(const std::pair<std::string, std::pair<int, int>>& a, const std::pair<std::string, std::pair<int, int>>& b) const {
        // Compare based on total views
        if (a.second.first != b.second.first)
            return a.second.first < b.second.first;
        // If total views are equal, compare based on hashtag count
        return a.second.second < b.second.second;
    }
};

int main() {
    // Sample data: map of hashtags to vector of videos
    std::unordered_map<std::string, std::pair<int, int>> hashtags = {
        {"#hashtag1", {1000, 10}},
        {"#hashtag2", {2000, 5}},
        {"#hashtag3", {1500, 15}}
    };

    // Priority queue to store hashtags based on custom comparison function
    std::priority_queue<std::pair<std::string, std::pair<int, int>>, std::vector<std::pair<std::string, std::pair<int, int>>>, CompareHashTags> pq;

    // Insert hashtags into priority queue
    for (const auto& entry : hashtags) {
        pq.push(entry);
    }

    // Process and print top hashtags along with top 3 videos
    while (!pq.empty()) {
        auto top = pq.top();
        std::cout << "Hashtag: " << top.first << ", Total Views: " << top.second.first << ", Hashtag Count: " << top.second.second << std::endl;

        // Get the videos associated with the current hashtag
        // Here, you would replace the sample logic with your actual video data retrieval logic
        std::vector<Video> videos = {
            {"Video1", 500},
            {"Video2", 1000},
            {"Video3", 750},
            {"Video4", 800}
        };

        // Sort videos based on view count
        std::sort(videos.begin(), videos.end());

        // Print top 3 videos for the current hashtag
        int count = 0;
        for (auto it = videos.rbegin(); it != videos.rend() && count < 3; ++it) {
            std::cout << "   Video: " << it->name << ", Views: " << it->viewCount << std::endl;
            count++;
        }

        pq.pop();
    }

    return 0;
}
