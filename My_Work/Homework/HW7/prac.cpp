#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iomanip>

// Function to extract title from HTML file
std::string extractTitle(const std::string& filePath) {
    std::ifstream file(filePath);
    std::string line;
    while (std::getline(file, line)) {
        size_t posStart = line.find("<title>");
        size_t posEnd = line.find("</title>");
        if (posStart != std::string::npos && posEnd != std::string::npos) {
            return line.substr(posStart + 7, posEnd - posStart - 7);
        }
    }
    return "Title not found";
}

// Function to extract URL from file path
std::string extractURL(const std::string& filePath) {
    size_t pos = filePath.find("html_files/");
    if (pos != std::string::npos) {
        return filePath.substr(pos);
    }
    return "URL not found";
}

// Function to extract description from HTML file
std::string extractDescription(const std::string& filePath) {
    std::ifstream file(filePath);
    std::string line;
    while (std::getline(file, line)) {
        size_t posStart = line.find("<meta name=\"description\" content=\"");
        if (posStart != std::string::npos) {
            size_t posEnd = line.find("\">");
            if (posEnd != std::string::npos) {
                return line.substr(posStart + 33, posEnd - posStart - 33);
            }
        }
    }
    return "Description not found";    
}

// Function to construct snippet from HTML file
std::string constructSnippet(const std::string& filePath, std::string& query) {
    std::ifstream file(filePath);
    std::string fileContent;
    int bodyPos;
    int queryPos;
    int startPos;
    std::string snippet;

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return snippet; // Return an empty string if file opening fails
    }

    // Read the file content
    fileContent = std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close(); // Close the file after reading its content

    bodyPos = fileContent.find("<body>");
    
    if (!query.empty() && query.front() == '"' && query.back() == '"') {
        query.erase(0, 1);
        query.pop_back();
    }
    // Search for the query string within the file content
    queryPos = fileContent.find(query, bodyPos);
    if (queryPos != std::string::npos) {
        // Find the position of the last '.' character before the query string
        startPos = fileContent.rfind('.', queryPos) + 1;

        // Skip any leading whitespace characters
        while (startPos < fileContent.size() && isspace(fileContent[startPos])) {
            startPos++;
        }

        // Extract a snippet of maximum 120 characters starting from startPos
        snippet = fileContent.substr(startPos, 120);
    }

    return snippet;
}

// Function to search for query in HTML file
std::string searchHTMLFile(const std::string& filePath,  std::string& query) {
    std::string title = extractTitle(filePath);
    std::string url = extractURL(filePath);
    std::string description = extractDescription(filePath);
    std::string snippet = constructSnippet(filePath, query);

    std::string output = "Title: " + title + "\n" + "URL: " + url + "\n" + "Description: " + description + "\n" + "Snippet: " + snippet + "\n\n";
    return output;
}

// Function to perform search and generate output file
void searchAndOutput(const std::vector<std::string>& filePaths,  std::string& query, const std::string& outputBaseFileName) {
    // Open output file outside the loop to avoid opening it multiple times
    std::ofstream outputFile(outputBaseFileName + ".txt");
    bool anyMatch = false;
    std::string allResults; // Variable to accumulate all results

    for (const auto& filePath : filePaths) {
        // Perform search for each file
        std::string result = searchHTMLFile(filePath, query);
        
        if (!result.empty()) {
            anyMatch = true;
            allResults += result; // Accumulate the result
        }
    }

    if (anyMatch) {
        // Write accumulated results and matching documents header
        outputFile << "Matching documents:\n\n" << allResults;
    } else {
        // If no matches found in any file, write a message indicating so
        outputFile << "Your search - " << query << " - did not match any documents.\n";
    }

    // Close the output file after processing all files
    outputFile.close();
}

int main() {
    std::vector<std::string> files = {
        "html_files/subdir1/subdir2/file7.html",
        "html_files/subdir1/subdir2/subdir3/subdir5/subdir6/subdir7/subdir8/file21.html",
        "html_files/subdir1/subdir2/subdir3/subdir5/subdir6/subdir7/subdir8/subdir9/subdir10/file27.html",
        "html_files/file1.html"
    };
    std::vector<std::string> querys = {"Tom"}; // Example search query
    std::string outputBaseFileName = "out"; // Base name for output files
    for (int i = 0; i < querys.size(); i++) {
    outputBaseFileName = "out" + std::to_string(i + 1);
    searchAndOutput(files, querys[i], outputBaseFileName);
}
    

    return 0;
}
