#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <map>

#include <iostream>
#include <string>

void updateOutputFileName(std::string& outputBaseFileName, int i) {
    if (outputBaseFileName == "out") {
        outputBaseFileName = "out1";
    } else if (outputBaseFileName.substr(0, 3) == "out") {
        int num = std::stoi(outputBaseFileName.substr(3)) + 1;
        outputBaseFileName = "out" + std::to_string(num);
    } 
}

int main() {
    std::string outputBaseFileName1 = "out";
    std::string outputBaseFileName2 = "out1";
    std::string outputBaseFileName3 = "test";

    updateOutputFileName(outputBaseFileName1, 0);
    updateOutputFileName(outputBaseFileName2, 0);
    updateOutputFileName(outputBaseFileName3, 0);

    std::cout << "Updated outputBaseFileName1: " << outputBaseFileName1 << std::endl;
    std::cout << "Updated outputBaseFileName2: " << outputBaseFileName2 << std::endl;
    std::cout << "Updated outputBaseFileName3: " << outputBaseFileName3 << std::endl;

    return 0;
}




/*
std::vector<double> Process_files_regular(const std::map<std::string, std::list<std::string>>& fileLinksMap, const std::string& keyword) {
    std::vector<double> density_per_doc;
    int combined_keywords = 0;
    int combined_char = 0;

    // Loop through each word in the keyword if there is more than one word
    std::stringstream ss(keyword);
    std::string word;
    std::cout<<word; // debug
    while (ss >> word) {
        combined_keywords = 0;
        combined_char = 0;

        // Iterate over each document in the fileLinksMap
        for (const std::pair<std::string, std::list<std::string>>& pair : fileLinksMap) {
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
        }

        // Calculate density across all documents
        double density = 0.0;
        if (combined_char > 0) {
            density = static_cast<double>(combined_keywords) / combined_char;
            std::cout << "Density Across All Documents for Keyword \"" << word << "\": " << density << std::endl; // debug


        }

        // Calculate keyword density scores for each document
        int number = 0;
        for (const std::pair<std::string, std::list<std::string>>& pair : fileLinksMap) {
            const std::string& filePath = pair.first;

            // Open the file for reading
            std::ifstream file(filePath);
            if (file.is_open()) {
                int keyword_counter = 0;
                int docsize = Count_doc_and_KeyWord(file, word, keyword_counter); // Count keyword occurrences in the document
                double doc_density = 0.0;
                if (docsize > 0) {
                    doc_density = static_cast<double>(keyword_counter) / (docsize * density);
                }

                // Store the result in the vector
                if (density_per_doc.size() <= 33) {
                 density_per_doc.push_back(doc_density);
                } else {
                    int index = (number % 33) - 1;
                   density_per_doc[index] += doc_density;
                }

                // Close the file
                file.close();
            } else {
                std::cerr << "Failed to open file: " << filePath << std::endl;
            }
            number++;
        }
    }
      // indes.html is index 2 and is throwing of the indexes by one

    return density_per_doc;
  
}
*/