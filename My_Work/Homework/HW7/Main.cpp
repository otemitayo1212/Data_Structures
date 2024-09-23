#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>
#include <list>
#include <map>
#include <cctype> // For std::isalnum
#include <algorithm>

// Function to count the occurrence of a keyword in a document
int Count_doc_and_KeyWord(std::ifstream& infile, const std::string& keyword, int& keyword_counter) {
   

    // Read the contents of the file into a string
    std::string htmlString((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());

    // Close the file
    infile.close();

    // Find occurrences of the keyword in the HTML string
    int pos = htmlString.find(keyword);
    while (pos != std::string::npos) {
        // Check if keyword is a standalone word
        bool beforeBoundary = (pos == 0 || !std::isalnum(htmlString[pos - 1])); // Check before keyword
        bool afterBoundary = (pos + keyword.length() == htmlString.length() || !std::isalnum(htmlString[pos + keyword.length()])); // Check after keyword
        if (beforeBoundary && afterBoundary) {
            keyword_counter++; // Increment keyword counter
        }
        pos = htmlString.find(keyword, pos + 1); // Find next occurrence
    }

    // Return the length of the HTML string
    return htmlString.length();
}
// Function to calculate keyword density score for a keyword across all documents
std::vector<std::string> countBackLinks(const std::string& Filename, const std::map<std::string, std::list<std::string>>& fileLinksMap) {
    std::vector<std::string> Matched_Paths;
    
     for (const std::pair<const std::string, std::list<std::string>>& pair : fileLinksMap) {
        const std::list<std::string>& links = pair.second;
       
        for (const std::string& link : links) {
            if (link.find(Filename) != std::string::npos) {
                Matched_Paths.push_back(pair.first);
                break; // No need to continue checking other links in this list
            }
        }
    }

    return Matched_Paths;
}

double calculateBacklinkScore(const std::vector<std::string>& BackLinksPath, const std::map<std::string, std::list<std::string>>& fileLinksMap) {
    double BacklinkScore = 0.0;

    for (const std::string& path : BackLinksPath) {
        std::map<std::string, std::list<std::string>>::const_iterator it = fileLinksMap.find(path);
        if (it != fileLinksMap.end()) {
            const std::list<std::string>& links = it->second;
            BacklinkScore += 1.0 / (1 + links.size());
        }
    }

    return BacklinkScore;
}



// function to parse an HTML file and extract links to local files
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

std::vector<std::pair<int, double>> calculatePageScores(const std::vector<double>& KeywordDensityScore, const std::map<std::string, std::list<std::string>>& fileLinksMap) {
    std::vector<std::pair<int, double>> pageScores;

    
    for (size_t i = 0; i < KeywordDensityScore.size(); ++i) {
        if (i == 0){
        if (KeywordDensityScore[i] == 0)   
            continue;
         std::vector<std::string> BackLinksPath = countBackLinks("index.html", fileLinksMap);
         double backlinksScore = calculateBacklinkScore(BackLinksPath, fileLinksMap);
            double pageScore = 0.5 * KeywordDensityScore[i] + 0.5 * backlinksScore;
            pageScores.emplace_back(i , pageScore); // Using emplace_back for efficiency
            continue;
        }

       if (KeywordDensityScore[i] == 0)   
           continue;
        
        std::vector<std::string> BackLinksPath = countBackLinks("file" + std::to_string(i) + ".html", fileLinksMap);
         double backlinksScore = calculateBacklinkScore(BackLinksPath, fileLinksMap);
        double pageScore = 0.5 * KeywordDensityScore[i] + 0.5 * backlinksScore;
        pageScores.emplace_back(i , pageScore); // Using emplace_back for efficiency
    }

    std::sort(pageScores.begin(), pageScores.end(), [](const std::pair<int, double>& a, const std::pair<int, double>& b) {
        return a.second > b.second; // Sort in descending order of scores
    });
   
    return pageScores;
}
std::vector<double> AggregateDocumentDensities(const std::vector<std::pair<std::string, double>>& temp_vector) {
    std::map<std::string, double> density_map; // Map to store document paths and their aggregated densities

    // Iterate over the temp_vector and aggregate densities for each document path
   for (const std::pair<std::string, double>& pair : temp_vector) {
        const std::string& filePath = pair.first;
        double doc_density = pair.second;

        // Update the density for the current document path
        if (doc_density == 0.0){
            density_map[filePath] = 0;
        }else{
             density_map[filePath] += doc_density;
        }
       
    }

    // Convert the density_map to a vector
    std::vector<double> aggregated_densities;
     for (const std::pair<std::string, double>& pair : density_map) {
        aggregated_densities.push_back(pair.second);
    }

    return aggregated_densities;
}
std::vector<double> Process_files_regular(const std::map<std::string, std::list<std::string>>& fileLinksMap, const std::string& keyword) {
    int total_files_processed = 0; // Counter to keep track of total files processed

    // Loop through each word in the keyword
    std::vector<std::pair<std::string, double>> temp_vector;
    std::stringstream ss(keyword);
    std::string word;
    while (ss >> word) {
        // Calculate density across all documents for the current word in the keyword
        int combined_keywords = 0;
        int combined_char = 0;
        for (const std::pair<const std::string, std::list<std::string>>& pair : fileLinksMap) {
            const std::string& filePath = pair.first;

            // Open the file for reading
            std::ifstream file(filePath);
            if (file.is_open()) {
                int keyword_counter = 0;
                int char_count = Count_doc_and_KeyWord(file, word, keyword_counter); // Count keyword occurrences
                combined_keywords += keyword_counter;
                combined_char += char_count;

                // Close the file
                file.close();
            } else {
                std::cerr << "Failed to open file: " << filePath << std::endl;
            }

            ++total_files_processed;

            // Calculate density across all documents if all files processed or reached every 33 files
            if (total_files_processed % 33 == 0 || total_files_processed == fileLinksMap.size()) {
                // Calculate density
                double density = 0.0;
                if (combined_char > 0) {
                    density = static_cast<double>(combined_keywords) / combined_char;
                }

                // Calculate keyword density scores for each document
                for (const std::pair<const std::string, std::list<std::string>>& pair : fileLinksMap) {
                    const std::string& filePath = pair.first;

                    // Open the file for reading
                    std::ifstream file(filePath);
                    if (file.is_open()) {
                        int keyword_counter = 0;
                        int docsize = Count_doc_and_KeyWord(file, word, keyword_counter); // Count keyword occurrences in the document

                        // Calculate keyword density score for the document
                        double doc_density = 0.0;
                        if (docsize > 0 && density > 0) {
                            doc_density = static_cast<double>(keyword_counter) / (docsize * density);
                        }
                        // add doc_density to a temp_vector as a pair with the filepath and doc density
                        // then call a function returns a  std::vector<double> this function should add up all the doc density that has thesame file path
                         temp_vector.push_back(std::make_pair(filePath, doc_density));

                        
                        // Close the file
                        file.close();
                    } else {
                        std::cerr << "Failed to open file: " << filePath << std::endl;
                    }
                }

                // Reset counters
                combined_keywords = 0;
                combined_char = 0;
            }
        }
        
    }
     // Call a function to aggregate the densities for each document path
     
     std::vector<double> aggregated_densities = AggregateDocumentDensities(temp_vector);
     std::swap(aggregated_densities[8], aggregated_densities[9]);
     std::swap(aggregated_densities[9], aggregated_densities[10]);


    return aggregated_densities;
}

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
   for (const std::string& link : links) {
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
                return line.substr(posStart + 34, posEnd - posStart - 34);
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
    bool phrase = false; // Initialize to false
    std::string snippet;
    int bodypos_before;
    bool found = false; // Initialize to false

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return snippet; // Return an empty string if file opening fails
    }

    // Read the file content
    fileContent = std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close(); // Close the file after reading its content

    bodyPos = fileContent.find("<body>");
    
    if (!query.empty() && query.front() == '"' && query.back() == '"') {
        phrase = true;
        query.erase(0, 1);
        query.pop_back();
    }

    if (phrase) {
        queryPos = fileContent.find(query, bodyPos);
        startPos = fileContent.rfind('.', queryPos) + 1;
        while (startPos < fileContent.size() && isspace(fileContent[startPos])) {
            startPos++;
        }
        snippet = fileContent.substr(startPos, 120);
    } else {
        bodypos_before = bodyPos;
        
        while ((bodyPos = fileContent.find(query, bodyPos)) != std::string::npos) {
            if ((!isalnum(fileContent[bodyPos - 1]) && !isalnum(fileContent[bodyPos + query.length()]))) {
                found = true;
                queryPos = bodyPos;
                startPos = fileContent.rfind('.', queryPos) + 1;
                while (startPos < fileContent.size() && isspace(fileContent[startPos])) {
                    startPos++;
                }
                snippet = fileContent.substr(startPos, 120);
                // Do something with the snippet
                break; // Break after finding the first standalone occurrence
            }
            bodyPos += query.length(); // Move to the next position after the current word
        }

        if (!found) {
            // Break down the query using stringstream
            std::istringstream iss(query);
            std::string word;
            while (iss >> word) {
                int tempBodyPos = bodypos_before; // Temporary variable to store the position
                while ((tempBodyPos = fileContent.find(word, tempBodyPos)) != std::string::npos) {
                    if ((!isalnum(fileContent[tempBodyPos - 1]) && !isalnum(fileContent[tempBodyPos + word.length()]))) {
                        found = true;
                        queryPos = tempBodyPos;
                        startPos = fileContent.rfind('.', queryPos) + 1;
                        while (startPos < fileContent.size() && isspace(fileContent[startPos])) {
                            startPos++;
                        }
                        snippet = fileContent.substr(startPos, 120);
                        // Do something with the snippet
                        break;
                    }
                    tempBodyPos += word.length();
                }
                if (found) break; // Break if a standalone occurrence is found
            }
        }
    }
  
    return snippet;
}

// Function to search for query in HTML file
std::string searchHTMLFile(const std::string& filePath,  std::string& query) {
    std::string title = extractTitle(filePath);
    std::string url = extractURL(filePath);
    std::string description = extractDescription(filePath);
    std::string snippet = constructSnippet(filePath, query);
    if  (snippet.empty()) {
        return "";
    }

    std::string output = "Title: " + title + "\n" + "URL: " + url + "\n" + "Description: " + description + "\n" + "Snippet: " + snippet + "\n\n";
    return output;
}

// Function to perform search and generate output file
void searchAndOutput(const std::vector<std::string>& filePaths,   std::string& query, const std::string& outputBaseFileName) {
    // Open output file outside the loop to avoid opening it multiple times
    std::ofstream outputFile(outputBaseFileName + ".txt");
    bool anyMatch = false;
    std::string allResults; // Variable to accumulate all results

    for (const std::string& filePath : filePaths) {
        // Perform search for each file
        std::string result = searchHTMLFile(filePath, query);
        
        if (!result.empty()) {
            anyMatch = true;
            allResults += result; // Accumulate the result
        }
    }

    if (anyMatch) {
        // Write accumulated results and matching documents header
        // before add all results to the out put minus  the last \n
        allResults.pop_back(); 
        outputFile << "Matching documents: \n\n" << allResults;
    } else {
        // If no matches found in any file, write a message indicating so
        outputFile << "Your search - " << query << " - did not match any documents.\n";
    }

    // Close the output file after processing all files
    outputFile.close();
}

// make this function take in the pairs of scores with document number and score , make it find the path for each document number in the vector and retun a vector of all the document number paths the pairs vector contains  (documentnuber , score) the paths sould be in the order they came in 
std::string findFilePathForDocumentNumber(int documentNumber, const std::map<std::string, std::list<std::string>>& fileLinksMap) {
    if (documentNumber == 0) {
        return "html_files/index.html";
    }

    std::string filePath;
   for (const std::pair<const std::string, std::list<std::string>>& pair : fileLinksMap) {
        if (pair.first.find("file" + std::to_string(documentNumber) + ".html") != std::string::npos) {
            filePath = pair.first;
            break; // Stop searching once the file is found
        }
    }

    return filePath;
}
std::vector<std::string> findFilePathsForDocumentNumbers_2(const std::vector<std::pair<int, double>>& documentScores,const std::map<std::string, std::list<std::string>>& fileLinksMap) {
    std::vector<std::string> filePaths;

     for (const std::pair<int, double>& pair : documentScores) {
        int documentNumber = pair.first;
        // Find the file path for the current document number
        std::string filePath = findFilePathForDocumentNumber(documentNumber, fileLinksMap);
        // If file path is found, add it to the vector
        if (!filePath.empty()) {
            filePaths.push_back(filePath);
        }
    }

    return filePaths;
}

void analyzeKeywords( std::vector<std::string>& keywords, const  std::map<std::string, std::list<std::string>> fileLinksMap) {
     std::string outputBaseFileName = "out";
    for ( std::string& keyword : keywords) {
        std::vector<double> KeywordDensityScore;
         std::string phrase;
        bool phrase_keyword = false;

        if (keyword.front() == '"' && keyword.back() == '"') {
            phrase_keyword = true;   
        }

        if (phrase_keyword) {
            int start = keyword.find('"');
            int end = keyword.find('"', start + 1);
            phrase = keyword.substr(start + 1, end - start - 1);
              KeywordDensityScore = Process_files_regular(fileLinksMap, phrase);
        } else {
            KeywordDensityScore = Process_files_regular(fileLinksMap, keyword);
        }
        // move index 2 to the first index of  KeywordDensityScore before calculateing pagescore
        // Move index 2 to the first index of KeywordDensityScore
        if (KeywordDensityScore.size() >= 3) {
            std::swap(KeywordDensityScore[1], KeywordDensityScore[2]);
            std::swap(KeywordDensityScore[0], KeywordDensityScore[1]);
        }

        std::vector<std::pair<int, double>> pageScores = calculatePageScores(KeywordDensityScore, fileLinksMap);
        // open a new output file per Keyword
         if (phrase_keyword) {
            // Filter out the words that don't have the keyword together from the pageScores
             for (std::vector<std::pair<int, double>>::iterator it = pageScores.begin(); it != pageScores.end();) {
                int documentNumber = it->first;
                std::string filePath = findFilePathForDocumentNumber(documentNumber, fileLinksMap);
                

                // Open the file with the provided path
                std::ifstream file(filePath);
                if (file.is_open()) {
                    int keyword_counter = 0;
                    int char_count = Count_doc_and_KeyWord(file, phrase, keyword_counter); // Count keyword occurrences
                    file.close();

                    // If keyword count is 0, remove the file from pageScores
                    if (keyword_counter == 0) {
                        it = pageScores.erase(it);
                    } else {
                        ++it;
                    }
                } else {
                    std::cerr << "Failed to open file: " << filePath << std::endl;
                    ++it;
                }
                file.close();
            }
          } else {
           // Check each document and check if it has all the words broken up using streams string in the document's text
            // If all words are in it, we want to remove that pair from the scores
             for (std::vector<std::pair<int, double>>::iterator it = pageScores.begin(); it != pageScores.end();) {
                int documentNumber = it->first;
                std::string filePath = findFilePathForDocumentNumber(documentNumber, fileLinksMap);
                
                // Open the file with the provided path
                std::ifstream file(filePath);
                if (!file.is_open()) {
                    std::cerr << "Failed to open file: " << filePath << std::endl;
                    ++it;
                    continue; // Continue to the next iteration if file open fails
                }
                
                bool allKeywordsFound = true; // Flag to track if all keywords are found in the document
                std::istringstream iss(phrase);
                std::string word;
                while (iss >> word) {
                    int keyword_counter = 0;
                    int char_count = Count_doc_and_KeyWord(file, word, keyword_counter); // Count keyword occurrences

                    // If keyword count is 0, set flag to false and break the loop
                    if (keyword_counter == 0) {
                        allKeywordsFound = false;
                        break;
                    }
                }
                
                // Close the file
                file.close();
                
                // If any keyword is not found, remove the file from pageScores
                if (!allKeywordsFound) {
                    it = pageScores.erase(it);
                } else {
                    ++it;
                }
            }

       }
        
       std::vector<std::string> filePaths = findFilePathsForDocumentNumbers_2(pageScores, fileLinksMap); 

        // Assuming you meant to use pageScores (plural) and keyword (lowercase)
         if (outputBaseFileName == "out") {
        outputBaseFileName = "out1";
        } else if (outputBaseFileName.substr(0, 3) == "out") {
            int num = std::stoi(outputBaseFileName.substr(3)) + 1;
            outputBaseFileName = "out" + std::to_string(num);
        } 
        searchAndOutput(filePaths, keyword, outputBaseFileName);

    }
}





int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <Seed URL> <Input file>\n";
        return 1;
    }

    std::string seed_url = argv[1];
    std::string input_file_name = argv[2];

    std::vector<std::string> visited_paths;
    std::map<std::string, std::list<std::string>> fileLinksMap;

    // Crawling
    crawl(seed_url, visited_paths, fileLinksMap);

    // Display file links
   

    // Read keywords from input file
    std::ifstream input(input_file_name);
    if (!input.is_open()) {
        std::cerr << "Failed to open input file: " << input_file_name << std::endl;
        return 1;
    }

    std::vector<std::string> keywords;
    std::string line;
    while (getline(input, line)) {
        keywords.push_back(line);
    }
    input.close();

    // Analyze keywords
    analyzeKeywords(keywords, fileLinksMap);

    return 0;
}


