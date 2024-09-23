#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <map>
#include <list>

// Function to extract links from HTML content
std::list<std::string> extractLinksFromHTML(const std::string& fileContent) {
    std::list<std::string> links;
    // regular expression to match href attributes in anchor tags
    std::regex linkRegex("<a\\s+[^>]*href\\s*=\\s*['\"]([^'\"]+)['\"][^>]*>");
    std::smatch match;

    // search for links in the HTML content
    std::string::const_iterator start = fileContent.cbegin();
    while (std::regex_search(start, fileContent.cend(), match, linkRegex)) {
        if (match.size() > 1) {
            links.push_back(match[1].str());
        }
        start = match.suffix().first;
    }

    return links;
}

// Recursive crawl function
void crawl(const std::string& rootDirectory, std::vector<std::string>& visited_paths, std::map<std::string, std::list<std::string>>& filemaps) {
    // Check if the rootDirectory has already been searched
    if (std::find(visited_paths.begin(), visited_paths.end(), rootDirectory) != visited_paths.end()) {
        return; // If visited, return to avoid redundant crawling
    }

    // Add the rootDirectory to visited paths
    visited_paths.push_back(rootDirectory);

    // Open the file corresponding to the rootDirectory
    std::ifstream inputFile(rootDirectory);
    if (!inputFile.is_open()) {
        std::cerr << "Unable to open file: " << rootDirectory << std::endl;
        return;
    }

    // Read file content into a string
    std::string fileContent((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    inputFile.close();

    // Store file content in the inverted index
    filemaps[rootDirectory] = extractLinksFromHTML(fileContent);

    // Extract links from fileContent
    std::list<std::string> links = extractLinksFromHTML(fileContent);

    // Resolve relative paths and recursively call crawl for each link
   for (const auto& link : links) {
    // Prepare the full URL by resolving relative paths
    std::string fullURL;
    std::string directory;
    size_t last_slash_position = rootDirectory.find_last_of('/');
    if(last_slash_position != std::string::npos){
        // Directory will now be "html_files/subdir2/"
        directory =  rootDirectory.substr(0, last_slash_position+1);
    }

    // Resolve relative paths
    std::string linkCopy = link;
    while(linkCopy.find("..") != std::string::npos){
        size_t last_slash_position = directory.find_last_of('/', directory.length()-2);
        if (last_slash_position != std::string::npos){
            // Directory will now be "html_files/subdir1/subdir2/"
            directory = directory.substr(0,last_slash_position+1);
        }
        linkCopy = linkCopy.substr(3);
    }
    fullURL = directory + linkCopy;

    // Recursive call to crawl with the new URL
    crawl(fullURL, visited_paths, filemaps);
}

}

int main() {
    // Example usage
    std::vector<std::string> visited_paths;
    std::map<std::string, std::list<std::string>> filemaps;

    crawl("html_files/index.html", visited_paths, filemaps);

    // Display the inverted index
    for (const auto& pair : filemaps) {
        std::cout << "File: " << pair.first << std::endl;
        std::cout << "Links:" << std::endl;
        for (const auto& link : pair.second) {
            std::cout << "- " << link << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}
