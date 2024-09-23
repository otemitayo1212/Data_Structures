#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <unordered_map>
#include <set>
#include <vector>
#include "Video.h"
#include <queue>
#include <utility>
#include <algorithm>

struct HashTag {
    std::string name;
    long count; // occurence 
    long totalViewCount;
    
    // Define a priority queue of Video objects
    std::priority_queue<Video> videoQueue;

    // Custom operator< to compare HashTag objects
    bool operator<(const HashTag& other) const {
        if (count != other.count)
            return count < other.count; // Higher count has higher priority
        if (totalViewCount != other.totalViewCount)
            return totalViewCount < other.totalViewCount; // Higher total view count has higher priority
        return name > other.name; // If both counts and total view counts are equal, use lexicographical order of name (lesser string has priority)
    }
};


struct sounds {
    std::string musicId;
    std::string musicName;
    std::string musicAuthor;
    long totalViewCount;
    
    // Define a priority queue of Video objects
    std::priority_queue<Video> videoQueue;

    // Custom operator< to compare sounds objects
    bool operator<(const sounds& other) const {
        if (totalViewCount != other.totalViewCount)
            return totalViewCount < other.totalViewCount; // Higher total view count has higher priority
        return musicId > other.musicId; // If total view counts are equal, use lexicographical order of musicId (lesser string has priority)
    }
};



// Function to extract musicId from the JSON-like data
std::string extractMusicId(const std::string& data) {
    size_t startPos = data.find("\"musicId\": \"") + 12;
    size_t endPos = data.find("\"", startPos);  
    return data.substr(startPos, endPos - startPos);
}

// Function to extract coverUrl from the JSON-like data
std::string extractCoverUrl(const std::string& data) {
    size_t startPos = data.find("\"coverUrl\": \"") ;
    if (startPos == std::string::npos)
        return "";

    startPos += 13; // Length of "\"coveUrl\": \""
    size_t endPos = data.find("\"definition\"", startPos) - 3 ;
    if (endPos == std::string::npos)
        return "";

    return data.substr(startPos, endPos - startPos);
}

// Function to extract musicName from the JSON-like data
std::string extractMusicName(const std::string& data) {
    size_t startPos = data.find("\"musicName\": \"");
    if (startPos == std::string::npos)
        return "";

    startPos += 14; // Length of "\"musicName\": \""
    size_t endPos = data.find("\"", startPos);
    if (endPos == std::string::npos)
        return "";

    return data.substr(startPos, endPos - startPos);
}

// Function to extract musicAuthor from the JSON-like data
std::string extractMusicAuthor(const std::string& data) {
    size_t startPos = data.find("\"musicAuthor\": \"");
    if (startPos == std::string::npos)
        return "";

    startPos += 16; // Length of "\"musicAuthor\": \""
    size_t endPos = data.find("\"", startPos);
    if (endPos == std::string::npos)
        return "";

    return data.substr(startPos, endPos - startPos);
}

std::string extractId(const std::string& data) {
    size_t startPos = data.find("\"id\": \"");
    if (startPos == std::string::npos)
        return "";

    startPos += 7; // Length of "\"id\": \""
    size_t endPos = data.find("\"", startPos);
    if (endPos == std::string::npos)
        return "";

    return data.substr(startPos, endPos - startPos);
}

// Function to extract text from the JSON-like data
std::string extractText(const std::string& data) {
    size_t startPos = data.find("\"text\": \"");
    if (startPos == std::string::npos)
        return "";

    startPos += 9; // Length of "\"text\": \""
    size_t endPos = data.find("\"", startPos);
    if (endPos == std::string::npos)
        return "";

    return data.substr(startPos, endPos - startPos);
}

// Function to extract webVideoUrl from the JSON-like data
std::string extractWebVideoUrl(const std::string& data) {
    size_t startPos = data.find("\"webVideoUrl\": \"");
    if (startPos == std::string::npos)
        return "";

    startPos += 16; // Length of "\"webVideoUrl\": \""
    size_t endPos = data.find("\"", startPos);
    if (endPos == std::string::npos)
        return "";

    return data.substr(startPos, endPos - startPos);
}

// Function to extract playCount from the JSON-like data
long extractPlayCount(const std::string& data) {
    size_t startPos = data.find("\"playCount\": ");
    startPos += 13; // Length of "\"playCount\": "
    size_t endPos = data.find("\"commentCount\"", startPos) - 2;

    return std::stoi(data.substr(startPos, endPos - startPos));
}

std::vector<std::string> extractHashtagsFromText(const std::string& text) {
    // Define a regular expression to match hashtags
    std::regex hashtagRegex("#([\\w\\u0080-\\uFFFF]+)");

    // Create a vector to store the hashtags
    std::vector<std::string> hashtags;

    // Create an iterator for matching
    std::sregex_iterator hashtagIterator(text.begin(), text.end(), hashtagRegex);
    std::sregex_iterator endIterator;

    // Iterate over the matches and extract the hashtags
    while (hashtagIterator != endIterator) {
        std::smatch match = *hashtagIterator;
        std::string hashtag = match.str(1);  // Extract the first capturing group
        // Push the hashtag longo the vector
        hashtags.push_back(hashtag);

        ++hashtagIterator;
    }

    // Return the vector of hashtags
    return hashtags;
}

void processHashtag(const std::string& inputFile, const std::string& outputFile) {
    // Open the input file
   std::unordered_map<std::string, HashTag> hashtagMap;
   std::priority_queue<HashTag> hashtagPQ;
    std::ifstream input(inputFile);
    if (!input.is_open()) {
        std::cerr << "Error opening input file: " << inputFile << std::endl;
        return;
    }

    // Process the input file for hashtags
    std::string line;
    while (std::getline(input, line)) {
         std::string id = extractId(line);
        std::string text = extractText(line);
        std::string webVideoUrl = extractWebVideoUrl(line);
        long playCount = extractPlayCount(line);
        std::string musicId = extractMusicId(line);
        std::string coverUrl = extractCoverUrl(line);
        std::string musicName = extractMusicName(line);
        std::string musicAuthor = extractMusicAuthor(line);

        // Process each line for hashtags
        std::vector<std::string> extractedHashtags = extractHashtagsFromText(line);
        // put each hashtag into a map [ string , HashtagObjct] 
        // also add the video object that have the hashtag to the priority queue in the hashtag
       for (const std::string& hashtag : extractedHashtags) {
            // Check if the hashtag already exists in the map
            std::unordered_map<std::string, HashTag>::iterator it = hashtagMap.find(hashtag);
            if (it == hashtagMap.end()) {
                // If the hashtag does not exist, create a new HashTag object and insert it into the map
               HashTag newHashtag;
                newHashtag.name = hashtag;
                // Initialize other member variables
                newHashtag.count = 1; // Initialize count to 1 since it's the first occurrence
                newHashtag.totalViewCount = playCount; // Initialize totalViewCount
                // Insert the new HashTag object into the map
                hashtagMap[hashtag] = newHashtag;
                 // Add the current video to the priority queue of the corresponding HashTag in the map
               hashtagMap[hashtag].videoQueue.push(Video(id, musicId, text, webVideoUrl, coverUrl, musicName, musicAuthor, playCount));


            }else{
                // if the Hash tag exist in the map
                // Increment the count of the HashTag object in the map
                hashtagMap[hashtag].count++;
                // Increment the totalViewCount of the HashTag object in the map
                hashtagMap[hashtag].totalViewCount += playCount;
                // Add the current video to the priority queue of the corresponding HashTag in the map
                hashtagMap[hashtag].videoQueue.push(Video(id, musicId, text, webVideoUrl, coverUrl, musicName, musicAuthor,  playCount));
            }
            
        }


        // Now create a video object with this line and add it to a set
    }

    // Put the hash tag from maps in a priority queue (use the hashtag count as the priority if this is equal , use total view count ( hashtagMap[hashtag][1]) and if this equals too , then use compare hashtag (Name))
    // Insert elements from the map longo the priority queue
    for (std::pair<const std::string, HashTag>& pair : hashtagMap) {
    hashtagPQ.push(pair.second);
   }
    
    // Your implementation here
    // Close the input file
    input.close();
   // Write the results to the output file
    std::ofstream output(outputFile);
    if (!output.is_open()) {
        std::cerr << "Error opening output file: " << outputFile << std::endl;
        return;
    }
    // Prlong the top 10 trending hashtags to the output file
   output << "trending hashtags:\n\n";
    
   long count = 0;
    while (!hashtagPQ.empty() && count < 10) {
        output << "========================\n";
        HashTag topHashTag = hashtagPQ.top();
        hashtagPQ.pop();
        output << "#" << topHashTag.name << "\n";
        output << "used " << topHashTag.count << " times\n";
        output << topHashTag.totalViewCount << " views\n\n";

        // Prlong top 3 videos for this hashtag
        // Print to 3 videos from topHashTag priority queue.
        // Print top 3 videos for this hashtag
        long videoCount = 0; // Reset video count for each hashtag
        while (!topHashTag.videoQueue.empty() && videoCount < 3) {
            Video topVideo = topHashTag.videoQueue.top();
            topHashTag.videoQueue.pop();
            output << "cover url: " << topVideo.getCoverUrl() << "\n";
            output << "web video url: " << topVideo.getWebVideoUrl() << "\n";
            videoCount++;
        }

        // Print separator between hashtags       
         output << "========================\n";     


            count++;
    }

    output.close();
}



void processSound(const std::string& inputFile, const std::string& outputFile) {
    // Open the input file
  std::unordered_map<std::string, sounds > soundsMap;
    std::priority_queue<sounds> pq;
    std::ifstream input(inputFile);
    if (!input.is_open()) {
        std::cerr << "Error opening input file: " << inputFile << std::endl;
        return;
    }

    // Process the input file for sounds
    std::string line;
while (std::getline(input, line)) {
    std::vector<std::string> extractedHashtags = extractHashtagsFromText(line);
    std::string id = extractId(line);
    std::string text = extractText(line);
    std::string webVideoUrl = extractWebVideoUrl(line);
    long playCount = extractPlayCount(line);
    std::string musicId = extractMusicId(line);
    std::string coverUrl = extractCoverUrl(line);
    std::string musicName = extractMusicName(line);
    std::string musicAuthor = extractMusicAuthor(line);

    // Add sound to map [ Key , soundObject]
    std::string key = musicId;
    if (soundsMap.find(key) != soundsMap.end()) {
        // If the key already exists in the map, update the total view count
        soundsMap[key].totalViewCount += playCount;
        // Add the current video to the priority queue of the corresponding sounds in the map
        soundsMap[key].videoQueue.push(Video(id, musicId, text, webVideoUrl, coverUrl, musicName, musicAuthor, playCount));
    } else {
        // If the key doesn't exist in the map, create a new sounds object
        soundsMap[key] = { musicId, musicName, musicAuthor, playCount };
        // Add the current video to the priority queue of the corresponding sounds in the map
        soundsMap[key].videoQueue.push(Video(id, musicId, text, webVideoUrl, coverUrl, musicName, musicAuthor, playCount));
    }
 }



    for (const std::pair<const std::string, sounds>& entry : soundsMap) {
           pq.push(entry.second);
    }

    // Close the input file
    input.close();

    // Write the results to the output file
    std::ofstream output(outputFile);
    if (!output.is_open()) {
        std::cerr << "Error opening output file: " << outputFile << std::endl;
        return;
    }

    // Write the top 10 trending sounds to the output file
     output << "trending sounds:\n\n";
    
    long count = 0;
    while (!pq.empty() && count < 10) {
        output << "========================\n";
        sounds topSound = pq.top();
        pq.pop();
        output << topSound.musicName << "\n";
        output << topSound.totalViewCount << " views\n";
        output << topSound.musicAuthor << "\n";
        output << "music id: " << topSound.musicId << "\n\n";

        // Print top 3 videos for this sound
        long videoCount = 0;
        std::priority_queue<Video> soundVideoQueue = topSound.videoQueue; // Copy the video queue from the sound object
        while (!soundVideoQueue.empty() && videoCount < 3) {
            Video topVideo = soundVideoQueue.top();
            soundVideoQueue.pop();
            output << "cover url: " << topVideo.getCoverUrl() << "\n";
            output << "web video url: " << topVideo.getWebVideoUrl() << "\n";
            videoCount++;
        }
         output << "========================\n";

        count++;
    }

    // Close the output file
    output.close();
}






int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " input.json output.txt [hashtag|sound]" << std::endl;
        return 1;
    }

    std::string inputFile = argv[1];
    std::string outputFile = argv[2];
    std::string mode = argv[3];

    if (mode == "hashtag") {
        processHashtag(inputFile, outputFile);
    } else if (mode == "sound") {
        processSound(inputFile, outputFile);
    } else {
        std::cerr << "Invalid mode. Use 'hashtag' or 'sound'." << std::endl;
        return 1;
    }

    return 0;
}
