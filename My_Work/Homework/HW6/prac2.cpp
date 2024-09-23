#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <cstdlib>
#include <ctime>
#include <utility>

class WordSearch {
private:
    int rows, cols;
    std::vector<std::string> words;
    std::vector<std::string> banned_words;
    std::vector<std::vector<char>> board;
    std::vector<std::vector<std::vector<char>>> boards;
    std::vector<std::pair<int, int>> word_positions;
    std::vector<std::pair<int, int>> directions = {{-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}};

    char getRandomLetter() {
        return static_cast<char>('A' + (std::rand() % 26));
    }

    bool isBoardFilled() const {
        for (const std::vector<char>& row : board) {
            for (char cell : row) {
                if (cell == '.') {
                    return false;
                }
            }
        }
        return true;
    }

    bool isBoardInVector(const std::vector<std::vector<char>>& board) {
        for (const std::vector<std::vector<char>>& existingBoard : boards) {
            if (existingBoard == board) {
                return true;
            }
        }
        return false;
    }

    bool containsForbiddenWords() const {
        for (const std::string& forbidden_word : banned_words) {
            if (findWord(forbidden_word)) {
                return true;
            }
        }
        return false;
    }

    bool findWord(const std::string& word) const {
        int len = word.length();

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                for (const auto& direction : directions) {
                    int dr = direction.first;
                    int dc = direction.second;
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
                        return true;
                    }
                }
            }
        }

        return false;
    }

    bool canPlaceWord(const std::string& word, int row, int col, int dr, int dc) {
        if (row + dr * (word.length() - 1) < 0 || row + dr * (word.length() - 1) >= rows ||
            col + dc * (word.length() - 1) < 0 || col + dc * (word.length() - 1) >= cols)
            return false;

        for (size_t i = 0; i < word.length(); ++i) {
            if (board[row + i * dr][col + i * dc] != '.' && board[row + i * dr][col + i * dc] != word[i])
                return false;
        }
        return true;
    }

    std::pair<int, int> getDirectionOfWord(const std::string& word, int row, int col) {
        for (const auto& direction : directions) {
            int dr = direction.first;
            int dc = direction.second;
            if (canPlaceWord(word, row, col, dr, dc)) {
                return direction;
            }
        }
        return std::make_pair(-1, -1);
    }

  void backtrack() {
    // Backtrack to the previous board state
    std::vector<std::vector<char>> prevBoard = board;
    std::vector<std::pair<int, int>> prevWordPositions = word_positions;

    // Remove the last word placed
    std::pair<int, int> lastWordPos = word_positions.back();
    board[lastWordPos.first][lastWordPos.second] = '.';
    word_positions.pop_back();

    // Try a different direction for the last placed word
    while (!directions.empty()) {
        std::pair<int, int> direction = directions.back();
        directions.pop_back();
        int dr = -direction.first;
        int dc = -direction.second;

        // Check if the word can be placed in this direction
        if (canPlaceWord(words.back(), lastWordPos.first, lastWordPos.second, dr, dc)) {
            placeWord(words.back(), lastWordPos.first, lastWordPos.second, dr, dc);
            return;
        }
    }

    // Restore the board state
    board = prevBoard;
    word_positions = prevWordPositions;
}

void insert_words(int wordIndex) {
    if (wordIndex == words.size()) {
        
        if (isBoardFilled() && !containsForbiddenWords() && !isBoardInVector(board)) {
            boards.push_back(board);
        }
        return;
    }

    std::string word = words[wordIndex];

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            for (const auto& direction : directions) {
                int dr = direction.first;
                int dc = direction.second;

                if (canPlaceWord(word, r, c, dr, dc)) {
                    placeWord(word, r, c, dr, dc);
                    insert_words(wordIndex + 1);
                    // Backtrack if the word cannot be placed
                    backtrack();
                }
            }
        }
    }
}

void placeWord(const std::string& word, int row, int col, int dr, int dc) {
    word_positions.push_back({row, col});
    for (size_t i = 0; i < word.length(); ++i) {
        board[row + i * dr][col + i * dc] = word[i];
    }
}

public:
    WordSearch(int _rows, int _cols, const std::vector<std::string>& _words, const std::vector<std::string>& _banned_words)
        : rows(_rows), cols(_cols), words(_words), banned_words(_banned_words) {
        board.resize(rows, std::vector<char>(cols, '.'));
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
    }

    void generateBoards() {
        boards.clear();
        insert_words(0);
    }

    std::vector<std::vector<std::vector<char>>> getBoards() {
        return boards;
    }
};

int main() {
    std::vector<std::string> words = {"tenet", "alula", "tat", "nun"};
    std::vector<std::string> banned_words = {"ale", "an", "tent", "tnt", "aa", "ee", "ll", "au",
                                             "b", "c", "d", "f", "g", "h", "i", "j", "k", "m",
                                             "o", "p", "q", "r", "s", "v", "w", "x", "y", "z"};

    WordSearch wordSearch(3, 5, words, banned_words);
    wordSearch.generateBoards();

    std::vector<std::vector<std::vector<char>>> boards = wordSearch.getBoards();

    std::cout << "Number of valid boards: " << boards.size() << std::endl;
    for (const auto& board : boards) {
        for (const auto& row : board) {
            for (char cell : row) {
                std::cout << cell << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}