#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

class VideoInfo {
private:
    std::vector<std::string> hashtags;
    int playCount; // views on the video

public:
    // Constructor
    VideoInfo(const std::vector<std::string>& hashtags, int playCount)
        : hashtags(hashtags), playCount(playCount) {}

    // Getter functions
    std::vector<std::string> getHashtags() const { return hashtags; }
    int getPlayCount() const { return playCount; }
      bool operator<(const VideoInfo& other) const {
        // You can define your comparison logic here.
        // For example, sorting based on play count.
        return playCount > other.playCount;
    }
};
std::vector<VideoInfo> filterByHashtag(const std::set<VideoInfo>& videos, const std::string& hashtag) {
    std::vector<VideoInfo> filteredVideos;

    // Iterate through each video in the set
    for (const auto& video : videos) {
        // Check if the current video contains the specified hashtag
        const auto& hashtags = video.getHashtags();
        if (std::find(hashtags.begin(), hashtags.end(), hashtag) != hashtags.end()) {
            // If the video contains the hashtag, add it to the filtered vector
            filteredVideos.push_back(video);
        }
    }
     

    return filteredVideos;
}


int main() {
    // Initialize a set of VideoInfo objects
    std::set<VideoInfo> videos = {
        {{"cat", "funny"}, 100},
        {{"dog", "funny"}, 200},
        {{"cat", "cute"}, 150},
        {{"dog", "cute"}, 250},
        {{"funny"}, 300}
    };

    // Filter the videos by the hashtag "funny"
    std::string hashtagToFilter = "funny";
    std::vector<VideoInfo> filteredVideos = filterByHashtag(videos, hashtagToFilter);

    // Output the filtered videos
    std::cout << "Filtered videos with hashtag #" << hashtagToFilter << ":" << std::endl;
    for (const auto& video : filteredVideos) {
        std::cout << "Playcount: " << video.getPlayCount() << std::endl;
    }

    return 0;
}