#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include "Comment.h" // Include the header file for the Comment class

// Function to parse JSON file and load comments into memory
std::string extractValue(const std::string& line, const std::string& keyword) {
    std::string result;
    size_t pos;
    if (keyword == "\"video_id\":") {
        pos = line.find(keyword);
        if (pos != std::string::npos) {
            pos += 13; // Assuming each value is enclosed in double quotes
            size_t end_pos = line.find("\"", pos);
            if (end_pos != std::string::npos) {
                result = line.substr(pos , (end_pos - pos) );
            }
        }
    } else if (keyword == "\"author\":") {
        pos = line.find(keyword);
        if (pos != std::string::npos) {
            pos += 11;
            size_t end_pos = line.find("\"", pos);
            if (end_pos != std::string::npos) {
                result = line.substr(pos , (end_pos - pos) );
            }
        }
    } else if (keyword == "\"comment_id\":") {
        pos = line.find(keyword);
        if (pos != std::string::npos) {
            pos += 15;
            size_t end_pos = line.find("\"", pos);
            if (end_pos != std::string::npos) {
               result = line.substr(pos , (end_pos - pos) );
            }
        }
    } // Add similar code blocks for other categories
    else if (keyword == "\"like_count\":") {
        pos = line.find(keyword);
        if (pos != std::string::npos) {
            pos += 14;
            size_t end_pos = line.find(",", pos);
            if (end_pos != std::string::npos) {
                result = line.substr(pos, (end_pos - pos) );
            }
        }
    } else if (keyword == "\"reply_count\":") {
        pos = line.find(keyword);
        if (pos != std::string::npos) {
            pos += 15;
            size_t end_pos = line.find(",", pos);
            if (end_pos != std::string::npos) {
               result = line.substr(pos , (end_pos - pos));
            }
        }
    } else if (keyword == "\"is_reply\":") {
        pos = line.find(keyword);
        if (pos != std::string::npos) {
            pos += 12; // Length of "true" or "false"
            size_t end_pos = line.find(",", pos);
            if (end_pos != std::string::npos) {
                result = line.substr(pos , (end_pos - pos));
            }
        }
    } else if (keyword == "\"parent_comment_id\":") {
        pos = line.find(keyword);
        if (pos != std::string::npos) {
            pos += 22;
            size_t end_pos = line.find("\"", pos);
            if (end_pos != std::string::npos) {
                result = line.substr(pos , (end_pos - pos) );
            }
        }
    } else if (keyword == "\"published_date\":") {
        pos = line.find(keyword);
        if (pos != std::string::npos) {
            pos += 19;
            size_t end_pos = line.find("\"", pos);
            if (end_pos != std::string::npos) {
                result = line.substr(pos , (end_pos - pos));
            }
        }
    } else if (keyword == "\"crawled_date\":") {
        pos = line.find(keyword);
        if (pos != std::string::npos) {
            pos += 17;
            size_t end_pos = line.find("\"", pos);
            if (end_pos != std::string::npos) {
                result = line.substr(pos -1, (end_pos - pos) + 1);
            }
        }
    } else if (keyword == "\"is_video_owner\":") {
        pos = line.find(keyword);
        if (pos != std::string::npos) {
            pos += 18; // Length of "true" or "false"
            size_t end_pos = line.find(",", pos);
            if (end_pos != std::string::npos) {
               result = line.substr(pos , (end_pos - pos));
            }
        }
    } else if (keyword == "\"comment\":") {
        pos = line.find(keyword);
        if (pos != std::string::npos) {
            pos += 12;
            size_t end_pos = line.find("\"", pos);
            if (end_pos != std::string::npos) {
               result = line.substr(pos -1, (end_pos - pos) + 1);
            }
        }
    }
    return result;
}

void loadComments(const std::string& filename, std::unordered_map<std::string, Comment*>& commentMap) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::string video_id = extractValue(line, "\"video_id\":");
        std::string author = extractValue(line, "\"author\":");
        std::string comment_id = extractValue(line, "\"comment_id\":");
        std::string like_count_str = extractValue(line, "\"like_count\":");
        int like_count = like_count_str.empty() ? 0 : std::stoi(like_count_str);
        std::string reply_count_str = extractValue(line, "\"reply_count\":");
        int reply_count = reply_count_str.empty() ? 0 : std::stoi(reply_count_str);
        std::string is_reply_str = extractValue(line, "\"is_reply\":");
        bool is_reply = is_reply_str == "true" ? true : false;
        std::string parent_comment_id = extractValue(line, "\"parent_comment_id\":");
        std::string published_date = extractValue(line, "\"published_date\":");
        std::string crawled_date = extractValue(line, "\"crawled_date\":");
        std::string is_video_owner_str = extractValue(line, "\"is_video_owner\":");
        bool is_video_owner = is_video_owner_str == "true" ? true : false;
        std::string comment_content = extractValue(line, "\"comment\":");

        // Create a Comment object
        Comment* comment = new Comment(video_id, author, comment_id, like_count, reply_count, is_reply, parent_comment_id, published_date, crawled_date, is_video_owner, comment_content);
        if (parent_comment_id.empty()){
              commentMap[comment_id] = comment; // Store comment in map
        }

        if (!parent_comment_id.empty()) {
            if (commentMap.find(parent_comment_id) != commentMap.end()) {
                commentMap[parent_comment_id]->addReply(comment);
            } 
        }
    }

    file.close();
}


void writeOutput(const std::string& filename, Comment* rootComment, int depth = 0) {
    std::ofstream outputFile(filename, std::ios::app);
    if (!outputFile.is_open()) {
        std::cerr << "Error opening output file: " << filename << std::endl;
        return;
    }

    // Print the root comment details
    if (rootComment->isPublishedNow()){
           outputFile << std::string(depth * 4, ' ') << rootComment->author << " " << "0 seconds ago" << std::endl;

    }else{
        outputFile << std::string(depth * 4, ' ') << rootComment->author << " " << rootComment->published_date << std::endl;
    }
    outputFile << std::string(depth * 4, ' ') << rootComment->comment << std::endl;
    outputFile << std::string(depth * 4, ' ') << "\U0001F44D " << rootComment->like_count << std::endl;
    if (rootComment->replies.empty()) {
    outputFile << "";
} else {
    int numReplies = rootComment->replies.size();
    if (numReplies == 1) {
        outputFile << std::string(depth * 4, ' ') << "1 reply" << std::endl;
    } else {
        outputFile << std::string(depth * 4, ' ') << numReplies << " replies" << std::endl;
    }
}
    // Print replies recursively
    for ( Comment* & reply : rootComment->replies) {
        writeOutput(filename, reply, depth + 1);
    }

    outputFile.close();
}

void executeOperations(const std::string& filename, std::unordered_map<std::string, Comment*>& commentMap , const std::string& outputFilename ) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening input file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::string operation;
        iss >> operation;

            if (operation == "reply_to_video") {
            std::string comment_id, author, comment_content;
            iss >> comment_id >> author;
            std::getline(iss, comment_content); // Read the rest of the line as comment content
            // check if comment_content has " in the begining or end if it does remove it 
            if (!comment_content.empty() && comment_content.front() == '"' && comment_content.back() == '"') {
                // Remove double quotes from the beginning and end of comment_content
                comment_content = comment_content.substr(1, comment_content.size() - 2);
            }

            // Create a new Comment object for replying to the video
            Comment* comment = new Comment();
            comment->comment_id = comment_id;
            comment->author = author;
            comment->comment = comment_content;

            // Add the comment to the map
            commentMap[comment_id] = comment;
        }
        else if (operation == "reply_to_comment") {

            std::string parent_comment_id, comment_id, author, content;
            iss >> parent_comment_id >> comment_id >> author;
            std::getline(iss, content); // Read the rest of the line as comment content

            

            // Create a new Comment object for replying to a comment
            Comment* comment = new Comment();
            comment->parent_comment_id = parent_comment_id;
            comment->comment_id = comment_id;
            comment->author = author;
            comment->comment = content;

            // Loop through every root comment and add the reply using addReply2
           for (std::unordered_map<std::string, Comment*>::iterator it = commentMap.begin(); it != commentMap.end(); ++it) {
                it->second->addReply2(comment);
            }

        } 
        else if (operation == "like_comment") { // working
            std::string comment_id;
            iss >> comment_id;
            // Find the comment in the map and increment its like count 
            // recursively find comment and add like
           for (std::unordered_map<std::string, Comment*>::iterator it = commentMap.begin(); it != commentMap.end(); ++it) {

                // Find the comment using findComment function
                Comment* comment = it->second->findComment(comment_id);
              if (comment) {
                comment->like_count++;
               } 

             }
           
        } 
        else if (operation == "delete_comment") {
            std::string comment_id;
            iss >> comment_id;

            // Loop through the map to find the comment
           for (std::unordered_map<std::string, Comment*>::iterator it = commentMap.begin(); it != commentMap.end(); ++it) {

                // First check if it is a root comment; if it is the root comment, remove it from the map
                if (it->first == comment_id) {
                    delete it->second; // Delete the root comment and its descendants
                    commentMap.erase(it); // Remove from map
                    break; // Exit the loop as the comment is found and deleted
                } else {
                    // If it's not the root comment, recursively search and remove the comment from its descendants
                    it->second->removeComment(comment_id);
                }
            }
        }  else if (operation == "display_comment") {
                std::string comment_id;
                iss >> comment_id;
                // Pass the root comment directly to the writeOutput function
                if (commentMap.find(comment_id) != commentMap.end()) {
                    // Get the root comment from the map
                    Comment* rootComment = commentMap[comment_id];

                    // Call the function to write the output file with the entire tree
                    writeOutput(outputFilename, rootComment);
                } else {
                    // If comment ID is not found, write a blank space to the output file
                    std::ofstream outputFile(outputFilename, std::ios_base::app);
                    if (outputFile.is_open()) {
                        outputFile << "";
                        outputFile.close();
                    } else {
                        std::cerr << "Error opening output file." << std::endl;
                    }
                }
            }

}
 inputFile.close();
}





int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " input1.json input2.txt output.txt" << std::endl;
        return 1;
    }

    std::string jsonFilename = argv[1];
    std::string inputFilename = argv[2];
    std::string outputFilename = argv[3];
    std::unordered_map<std::string, Comment*> commentMap;

    // Load existing comments from JSON file
    loadComments(jsonFilename, commentMap  );
    
    // print the map and the replies  for each of them

   // Execute operations from input file
    executeOperations(inputFilename, commentMap ,  outputFilename);

     for (std::pair<const std::string, Comment*>& pair : commentMap) {
        delete pair.second;
    }


    return 0;
}
