#include <iostream>
#include <fstream>
#include <list>
#include <regex>
#include <string>
#include <vector>
#include <map>

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
//function to recursively crawl and buld maps
void crawl(const std::string& seedURL, std::set<std::string>& alrSearched, std::map<std::string, std::list<std::string>>& invertedIndex, std::map<std::string, std::list<std::string>>& invertedIndex) {
    if (alrSearched.find(seedURL)!= alrSearched.end()) {
        // Already visited this file, return
        return;
    }

   alrSearched.insert(seedURL);

    std::ifstream file(seedURL);
    if (!file) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return;
    } 
    std::string fileContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    std::set<std::string> content;
    content.insert(fileContent);
    invertedIndex[seedURL] = content;

    // Iterate through returned list and search each extracted link, add to inverted index map
     std::list<std::string> links = extractLinksFromHTML(fileContent);
    for (const auto& link : links) {
        // Assuming all links are relative paths for simplicity
        // Suppose URL is "html_files/subdir1/subdir2/file7.html"
        std::string directory;
        size_t last_slash_position = seedURL.find_last_of('/');
        if(last_slash_position != std::string::npos){
            // Directory will now be "html_files/subdir2/"
            directory =  seedURL.substr(0, last_slash_position+1); // Recursively crawl this link
        }

        while(link.find("..") != std::string::npos){
            size_t last_slash_position = directory.find_last_of('/', directory.length()-2);
            if (last_slash_position != std::string::npos){
                // Directory will now be "html_files/subdir1/subdir2/"
                directory = directory.substr(0,last_slash_position+1);
            }
            link = link.substr(3);
        }
        crawl(directory + link , alrSearched, invertedIndex, invertedIndex);
    }
}
int main() {
   std::vector<std::string> visitedFiles;
    std::map<std::string, std::list<std::string>> pathways;
    std::map<std::string, std::list<std::string>> invertedIndex;
  std::string filePath = "html_files/index.html";

    crawl(filePath, visitedFiles, pathways, invertedIndex);
    // Output pathways
    std::cout << "Pathways:\n";
    for (const auto& pathway : pathways) {
        std::cout << pathway.first << " -> ";
        for (const auto& link : pathway.second) {
            std::cout << link << ", ";
        }
        std::cout << std::endl;
    }

    return 0;
}
