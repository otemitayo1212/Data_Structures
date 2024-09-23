#include "wordsearch.h" // Include the header file for the WordSearch class
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

void printAllSolutions(const std::vector<std::vector<std::vector<char>>>& boards, std::ofstream& outfile) {
    outfile << boards.size() << " solution(s)" << std::endl;
    for (const std::vector<std::vector<char>>& board : boards) {
        outfile << "Board: " << std::endl;
        for (const std::vector<char>& row : board) {
            for (const char& cell : row) {
                outfile << cell;
            }
            outfile << std::endl;
        }
    }
}

void printOneSolution(const std::vector<std::vector<char>>& board, std::ofstream& outfile) {
    outfile << "Board: " << std::endl;
    for (const std::vector<char>& row : board) {
        for (const char& cell : row) {
            outfile << cell;
        }
        outfile << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cout << "Usage: " << argv[0] << " <input_file> <output_file> <mode>" << std::endl;
        return 1;
    }

    std::string input_file = argv[1];
    std::string output_file = argv[2];
    std::string mode = argv[3];
    // OPENING INPUT FILE

    std::ifstream infile(input_file);
    if (!infile) {
        std::cerr << "Error: Unable to open input file: " << input_file << std::endl;
        return 1;
    }

    int rows, cols;
    infile >> cols >> rows;
    infile.ignore(); // Ignore newline after rows and cols

    std::vector<std::string> words;
    std::vector<std::string> banned_words;

    std::string line;
    while (std::getline(infile, line)) {
        if (line.empty()) {
            break;
        }
        char sign = line[0];
        std::string word = line.substr(2); // Extract word excluding the sign
        if (sign == '+') {
            words.push_back(word);
        } else if (sign == '-') {
            banned_words.push_back(word);
        }
    }

    infile.close();

    WordSearch word_search(rows, cols, words, banned_words);
    word_search.generateBoards(mode);
    std::vector<std::vector<std::vector<char>>> boards = word_search.getBoards();
    std::ofstream outfile(output_file);
    if (!outfile) {
        std::cerr << "Error: Unable to open output file: " << output_file << std::endl;
        return 1;
    }

    if (mode == "all_solutions") {
        printAllSolutions(boards, outfile);
    } else if (mode == "one_solution") {
        printOneSolution(boards[0], outfile); // Assuming only one solution is generated
    }

    outfile.close();

    return 0;
}
