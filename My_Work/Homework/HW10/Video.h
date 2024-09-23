#ifndef VIDEO_H
#define VIDEO_H

#include <string>
#include <vector>

class Video {
private:
    std::string id;
    std::string musicId;
    std::string text;
    std::string webVideoUrl;
    std::string coverUrl;
    std::string musicName;
    std::string musicAuthor;
    long playCount; // views on the video

public:
    // Constructor
    Video(const std::string& id, const std::string& musicId, const std::string& text, 
          const std::string& webVideoUrl, const std::string& coverUrl, 
          const std::string& musicName, const std::string& musicAuthor, 
          long playCount);

    // Getter functions
    std::string getId() const;
    std::string getMusicId() const;
    std::string getText() const;
    std::string getWebVideoUrl() const;
    std::string getCoverUrl() const;
    std::string getMusicName() const;
    std::string getMusicAuthor() const;
    long getPlayCount() const;
    bool operator<(const Video& other) const ;
};

#endif // VIDEO_H
