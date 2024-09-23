#include "wordsearch.h"
#include <iostream>
#include <utility> 

WordSearch::WordSearch(int _rows, int _cols, const std::vector<std::string>& _words, const std::vector<std::string>& _banned_words)
    : rows(_rows), cols(_cols), words(_words), banned_words(_banned_words) {
    board.resize(rows, std::vector<char>(cols, '.'));
}
void WordSearch::generateBoards(std::string mode) {
    boards.clear();
    if (mode == "one_solution") {
        insert_word_1_sol(0); // Find only one solution
    } else if (mode == "all_solutions") {
        insert_words(0); // Find all solutions
    } else {
        std::cerr << "Invalid mode specified!" << std::endl;
    }
}

std::vector<std::vector<std::vector<char>>> WordSearch::getBoards() {
    return boards;
}


char WordSearch::getRandomLetter() {  // works will 
        return static_cast<char>('A' + (std::rand() % 26));
    }

bool WordSearch::isBoardFilled() const {
    for (const std::vector<char>& row : board) {
        for (char cell : row) {
            if (cell == '.') {
                return false; // Found a blank spot, return false
            }
        }
    }
    return true; // No blank spots found, board is filled
}


bool WordSearch::findWord(const std::string& word) const{ // works 
    static const int directions[][2] = {{-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}};
    int rows = board.size();
    int cols = board[0].size();
    int len = word.length();

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            for (const int (&dir)[2] : directions) {
                int dr = dir[0];
                int dc = dir[1];
                int i = r;
                int j = c;

                int k = 0;
                for (; k < len; ++k) {
                    if (i < 0 || i >= rows || j < 0 || j >= cols || board[i][j] != word[k]) {
                        break;
                    }

                    i += dr;
                    j += dc;
                }

                if (k == len) {
                    return true;  // Found the word
                }
            }
        }
    }

    return false;  // Word not found
}
bool WordSearch::findWord2(const std::vector<std::vector<char>>& board, const std::string& word)  {
    static const int directions[][2] = {{-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}};
    int rows = board.size();
    int cols = board[0].size();
    int len = word.length();

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            for (const int (&dir)[2] : directions) {
                int dr = dir[0];
                int dc = dir[1];
                int i = r;
                int j = c;

                int k = 0;
                for (; k < len; ++k) {
                    if (i < 0 || i >= rows || j < 0 || j >= cols || board[i][j] != word[k]) {
                        break;
                    }

                    i += dr;
                    j += dc;
                }

                if (k == len) {
                    return true;  // Found the word
                }
            }
        }
    }

    return false;  // Word not found
}

bool WordSearch::containsForbiddenWords()  {
    for (size_t i = 0; i < banned_words.size(); ++i) {
        const std::string& forbidden_word = banned_words[i];
        if (findWord(forbidden_word)) {
            return true; // Found a forbidden word
        }
    }
    return false; // No forbidden words found
}
 bool WordSearch::containsForbiddenWords2(const std::vector<std::vector<char>>& board) {
        for (size_t i = 0; i < banned_words.size(); ++i) {
        const std::string& forbidden_word = banned_words[i];
            if (findWord2(board, forbidden_word)) {
                return true; // Found a forbidden word
            }
        }
        return false; // No forbidden words found
    }


bool WordSearch::isBoardInVector(const std::vector<std::vector<char>>& board) { // Works
    for (const std::vector<std::vector<char>>& existingBoard : boards) {
        if (existingBoard == board) {
            return true;
        }
    }
    return false;
}

    std::pair<int, int> WordSearch::removeWord(const std::string& word, int row, int col) { // WORKS
        // Delete positions of the word from the vector before proceeding
        for (size_t i = 0; i < word_positions.size(); ++i) {
            if (word_positions[i].first == row && word_positions[i].second == col) {
                word_positions.erase(word_positions.begin() + i);
                break; // Assuming a word can't appear at the same position more than once
            }
        }

        int removedDirectionX = 0;
        int removedDirectionY = 0;

        // Check all directions to find the direction the word was placed in
        for (const std::pair<int, int>& direction : directions) {
        int dr = direction.first;
        int dc = direction.second;
        // This is a placeholder function, you should implement canPlaceWord() yourself
        if (canPlaceWord(word, row, col, dr, dc)) {
            // Remove the word from the board
            for (size_t i = 0; i < word.length(); ++i) {
                board[row + i * dr][col + i * dc] = '.';
            }
            removedDirectionX = dr;
            removedDirectionY = dc;
            break;
        }
        }


        return std::make_pair(removedDirectionX, removedDirectionY);
    }

 std::vector<std::vector<std::vector<char>>> WordSearch::fillBlankSpots() {
    std::vector<std::vector<std::vector<char>>> possible_boards;
    possible_boards.push_back(board);

    std::string alphabet = "abcdefghijklmnopqrstuvwxyz";

    for (std::vector<std::vector<char>>& b : possible_boards) {
        std::vector<std::vector<char>> temp_board = b; // Make a copy of the current board

        // Iterate through each empty spot in the board
        for (int i = 0; i < temp_board.size(); ++i) {
            for (int j = 0; j < temp_board[i].size(); ++j) {
                if (temp_board[i][j] == '.') {
                    // Try filling the empty spot with every letter of the alphabet
                    for (char letter : alphabet) {
                        temp_board[i][j] = letter;
                        // Check if any forbidden words are formed
                        if (!containsForbiddenWords2(temp_board)) {
                            possible_boards.push_back(temp_board); // Add valid board configuration
                        }
                    }
                    // Reset the spot to empty for the next iteration
                    temp_board[i][j] = '.';
                }
            }
        }
    }

    // Remove the original empty board
    possible_boards.erase(possible_boards.begin());

    return possible_boards;
}

// Function to check if the board is complete and doesn't contain forbidden words // no need because we would have already checked for this before
bool WordSearch::isBoardCompleteAndValid() { // WORKS
     // Check if all words are present on the board
        for (const std::string& word : words) {
            if (!findWord(word)) {
                return false;
            }
        }

        // Check for any remaining blank spots
        for (const std::vector<char>& row : board) {
            for (char cell : row) {
                if (cell == '.') {
                    return false; // Board is not complete
                }
            }
        }

        return true; // Board is complete and valid
}
bool WordSearch::canPlaceWord(const std::string& word, int row, int col, int dr, int dc) { // WORKS
    if (row + dr * (word.length() - 1) < 0 || row + dr * (word.length() - 1) >= board.size() ||
        col + dc * (word.length() - 1) < 0 || col + dc * (word.length() - 1) >= board[0].size())
        return false;

    for (size_t i = 0; i < word.length(); ++i) {
        if (board[row + i * dr][col + i * dc] != '.' && board[row + i * dr][col + i * dc] != word[i])
            return false;
    }
    return true;
}

void WordSearch::placeWord(const std::string& word, int row, int col, int dr, int dc) { // WORKS
    word_positions.push_back({row, col}); // Store the position where the word is placed
    for (size_t i = 0; i < word.length(); ++i) {
        board[row + i * dr][col + i * dc] = word[i];
    }
}


void WordSearch::insert_words(int wordIndex) {
    // Base case: if all words are placed, check if the board configuration is valid
    if (wordIndex == words.size()) {
        // Check if the board is filled, doesn't contain forbidden words, and is not already in the boards vector
         std::vector<std::vector<std::vector<char>>>  temp_boards = fillBlankSpots();   // loop through filblankspots see with is not in the board then we add to the boards list
         for ( std::vector<std::vector<char>> b : temp_boards){
            if (!isBoardInVector(b) && isBoardCompleteAndValid()) {
                boards.push_back(b);
            }
         }
      //  if (isBoardFilled() && !containsForbiddenWords() && !isBoardInVector(board)) {
      //      boards.push_back(board); // Add the current board configuration to the vector of boards
      //  }
        return; // Return to terminate the recursion
    }

    // Get the word at the current index
    std::string word = words[wordIndex];
    int len = word.length();

    // Iterate over all positions on the board
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            // Iterate over all directions
            for (const std::pair<int, int>& direction : directions) {
                int dr = direction.first;
                int dc = direction.second;

                // Check if the word can be placed in the current position and direction
                if (canPlaceWord(word, r, c, dr, dc)) {
                    // Save the current board state
                    std::vector<std::vector<char>> prevBoard = board;
                    // Clear word positions vector
                    word_positions.clear();
                    // Place the word on the board
                    placeWord(word, r, c, dr, dc);
                    // Recursively insert the next word
                    insert_words(wordIndex + 1);
                    // Restore the previous board state for backtracking
                    board = prevBoard;
                }
            }
        }
    }
}

void WordSearch::insert_word_1_sol(int wordIndex) {
    // Check if a solution has already been found
    if (!boards.empty()) {
        return; // Stop the recursion if a solution is found
    }

    // Base case: if all words are placed, check if the board configuration is valid
     if (wordIndex == words.size()) {
        // Check if the board is filled, doesn't contain forbidden words, and is not already in the boards vector
         std::vector<std::vector<std::vector<char>>>  temp_boards = fillBlankSpots();   // loop through filblankspots see with is not in the board then we add to the boards list
         for ( std::vector<std::vector<char>> b : temp_boards){
            if (!isBoardInVector(b) && isBoardCompleteAndValid()) {
                boards.push_back(b);
            }
         }
      //  if (isBoardFilled() && !containsForbiddenWords() && !isBoardInVector(board)) {
      //      boards.push_back(board); // Add the current board configuration to the vector of boards
      //  }
        return; // Return to terminate the recursion
    }

    // Get the word at the current index
    std::string word = words[wordIndex];
    int len = word.length();

    // Iterate over all positions on the board
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            // Iterate over all directions
            for (const std::pair<int, int>& direction : directions) {
                int dr = direction.first;
                int dc = direction.second;

                // Check if the word can be placed in the current position and direction
                if (canPlaceWord(word, r, c, dr, dc)) {
                    // Save the current board state
                    std::vector<std::vector<char>> prevBoard = board;
                    // Clear word positions vector
                    word_positions.clear();
                    // Place the word on the board
                    placeWord(word, r, c, dr, dc);
                    // Recursively insert the next word
                    insert_word_1_sol(wordIndex + 1);
                    // Restore the previous board state for backtracking
                    board = prevBoard;

                    // If a solution is found, return to stop further exploration
                    if (!boards.empty()) {
                        return;
                    }
                }
            }
        }
    }
}
