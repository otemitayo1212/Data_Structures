#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include "Comment.h" // Include the header file for the Comment class
#include <algorithm>

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
            pos += 13;
            size_t end_pos = line.find("\"", pos);
            if (end_pos != std::string::npos) {
               result = line.substr(pos -1, (end_pos - pos) + 1);
            }
        }
    }
    return result;
}


std::vector<Comment*> processMap(std::unordered_map<std::string, Comment*>& inputMap) {
    std::vector<Comment*> roots;

    // Loop through the input map to find parent keys
  for (std::unordered_map<std::string, Comment*>::iterator it = inputMap.begin(); it != inputMap.end(); ++it) {
        if (!it->second->is_reply) {
            // It's a parent key, add it to roots
            roots.push_back(it->second);
        }
    }

    // Loop through the input map again to find child keys
   for (std::unordered_map<std::string, Comment*>::iterator it = inputMap.begin(); it != inputMap.end(); ++it) {
        if (it->second->is_reply) {
            // It's a child key, find its parent in roots and add as reply
            for (Comment* root : roots) {
                if (root->comment_id == it->second->parent_comment_id) {
                    root->addReply(it->second);
                    break;
                }
            }
        }
    }


    return roots;
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


void loadComments(const std::string& filename, std::unordered_map<std::string, Comment*> & commentMap) {
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
      commentMap[comment_id] = new Comment(video_id, author, comment_id, like_count, reply_count, is_reply, parent_comment_id, published_date, crawled_date, is_video_owner, comment_content);
       
    }

    file.close();
   

}


void executeOperations(const std::string& filename,  std::vector<Comment*>& roots , const std::string& outputFilename ) {
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
        // treat it like a root create a defult wile adding the information extracted from the line in
        std::string comment_id, author, comment_content;
        iss >> comment_id >> author;
        std::getline(iss, comment_content);
        // Remove leading whitespace characters from content
        size_t start_pos = comment_content.find_first_not_of(" ");
        comment_content = (start_pos == std::string::npos) ? "" : comment_content.substr(start_pos);

        // Remove trailing whitespace characters from content
        size_t end_pos = comment_content.find_last_not_of(" ");
        comment_content = (end_pos == std::string::npos) ? "" : comment_content.substr(0, end_pos + 1);

        // Remove surrounding quotes from content if present
        if (comment_content.size() >= 2 && comment_content.front() == '"' && comment_content.back() == '"') {
            comment_content = comment_content.substr(1, comment_content.size() - 2);
        }
       // std::cout << "Comment  ID: " << comment_id << ", Author: " << author << " Content: " << comment_content << "\n"; 
        Comment* comment = new Comment();
        comment->comment_id = comment_id;
        comment->author = author;
        comment->comment = comment_content;
        roots.push_back(comment);

        } else if (operation == "reply_to_comment") {
        std::string parent_comment_id, comment_id, author, content;
        iss >> parent_comment_id >> comment_id >> author;
        std::getline(iss, content);

        // Remove leading whitespace characters from content
        size_t start_pos = content.find_first_not_of(" ");
        content = (start_pos == std::string::npos) ? "" : content.substr(start_pos);

        // Remove trailing whitespace characters from content
        size_t end_pos = content.find_last_not_of(" ");
        content = (end_pos == std::string::npos) ? "" : content.substr(0, end_pos + 1);

        // Remove surrounding quotes from content if present
        if (content.size() >= 2 && content.front() == '"' && content.back() == '"') {
            content = content.substr(1, content.size() - 2);
        }
        Comment* comment = new Comment();
            comment->parent_comment_id = parent_comment_id;
            comment->comment_id = comment_id;
            comment->author = author;
            comment->comment = content;
        
         for (Comment* root : roots) {
         
        root->addReply2(comment);
           
        }

        } else if (operation == "like_comment") { 
            std::string comment_id;
            iss >> comment_id;

             for (Comment* root : roots) {
         
              root->addLike(comment_id);
           
             }

        }else if (operation == "delete_comment") {
            std::string comment_id;
            iss >> comment_id;

            // Loop through the root vector to find the comment
            for (std::vector<Comment*>::iterator it = roots.begin(); it != roots.end(); ++it) {
                if ((*it)->comment_id == comment_id) {
                    // Delete the root comment and its descendants
                    delete *it;
                    roots.erase(it); // Remove from vector
                    break; // Exit the loop as the comment is found and deleted
                } else {
                    // If it's not the root comment, recursively search and remove the comment from its descendants
                    (*it)->removeComment(comment_id);
                }
            }
     } else if (operation == "display_comment") {
        std::string comment_id;
        iss >> comment_id;
        bool found = false;

        for (std::vector<Comment*>::iterator it = roots.begin(); it != roots.end(); ++it) {
            if ((*it)->comment_id == comment_id) {
                // Found the root comment with the given ID
                Comment* rootComment = *it;
                found = true;

                // Assuming writeOutput function is declared somewhere
                // Write the output for the found root comment
                writeOutput(outputFilename, rootComment);

                // Set the found flag and continue searching if needed
                break;
            } else {
                // Recursively find the comment to display
                Comment* rootComment = (*it)->findComment(comment_id);
                if (rootComment != NULL) {
                    found = true;
                    // Assuming writeOutput function is declared somewhere
                    // Write the output for the found root comment
                    writeOutput(outputFilename, rootComment);
                    break; // Exit the loop as the comment is found
                }
            }
        }

        // If the comment is not found, create an empty output file
        if (!found) {
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
    loadComments(jsonFilename, commentMap );

    std::vector<Comment*> roots = processMap(commentMap);
   
    executeOperations(inputFilename, roots,  outputFilename);



    return 0;
}


