#include "Video.h"

// Constructor implementation
Video::Video(const std::string& id, const std::string& musicId, const std::string& text,
             const std::string& webVideoUrl, const std::string& coverUrl,
             const std::string& musicName, const std::string& musicAuthor, long playCount)
    : id(id), musicId(musicId), text(text), webVideoUrl(webVideoUrl), coverUrl(coverUrl),
      musicName(musicName), musicAuthor(musicAuthor), playCount(playCount) {}

// Getter implementations
std::string Video::getId() const {
    return id;
}

bool Video::operator<(const Video& other) const {
        // You can define your comparison logic here.
        // For example, sorting based on play count.
        return playCount < other.playCount;
 }

std::string Video::getMusicId() const {
    return musicId;
}

std::string Video::getText() const {
    return text;
}

std::string Video::getWebVideoUrl() const {
    return webVideoUrl;
}

std::string Video::getCoverUrl() const {
    return coverUrl;
}

std::string Video::getMusicName() const {
    return musicName;
}

std::string Video::getMusicAuthor() const {
    return musicAuthor;
}

long Video::getPlayCount() const {
    return playCount;
}
