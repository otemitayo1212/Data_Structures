#include <iostream>
#include <vector>
#include <string>

using namespace std;

class WordSearch {
private:
    vector<vector<char>> board;
    vector<string> words;
    vector<string> banned_words;
    vector<vector<vector<char>>> boards;
    vector<pair<int, int>> word_positions; // Store the positions where each word is placed
    vector<pair<int, int>> directions{
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},           {0, 1},
        {1, -1},  {1, 0},  {1, 1}
    };
    int rows, cols;

    template<typename T>
    bool tryDifferentDirection(int index, const T& directions) {
        string currentWord = words[index]; // The last word placed on the board
        pair<int, int> lastWordPosition = word_positions[index]; // Get the position where the last word was placed
        int row = lastWordPosition.first;
        int col = lastWordPosition.second;
        bool placed = false;

        // Remove the last word from the board
        removeWord(currentWord, row, col, -1, -1); // You need to implement this function

        // Try placing the last word in a different direction
        for (const auto& direction : directions) {
            int dr = direction.first;
            int dc = direction.second;
            if (canPlaceWord(currentWord, row, col, dr, dc)) {
                placed = true;
                placeWord(currentWord, row, col, dr, dc); // Place the last word in a different direction
                break; // Break the loop as we have found a valid direction
            }
        }

        return placed;
    }

    bool canPlaceWord(const string& word, int row, int col, int dr, int dc) {
        if (row + dr * (word.length() - 1) < 0 || row + dr * (word.length() - 1) >= board.size() ||
            col + dc * (word.length() - 1) < 0 || col + dc * (word.length() - 1) >= board[0].size())
            return false;

        for (int i = 0; i < word.length(); ++i) {
            if (board[row + i * dr][col + i * dc] != '.' && board[row + i * dr][col + i * dc] != word[i])
                return false;
        }
        return true;
    }

    void placeWord(const string& word, int row, int col, int dr, int dc) {
        word_positions.push_back({row, col}); // Store the position where the word is placed
        for (int i = 0; i < word.length(); ++i) {
            board[row + i * dr][col + i * dc] = word[i];
        }
    }

    bool fillBoard(int index) {
            if (index == words.size()) {
            boards.push_back(board); // Found 1 solution
            // Remove the last placed word from the board and try a different direction
            bool placed = tryDifferentDirection(index - 1, directions);
            if (!placed) {
                // remove the previous word and try a different direction for the previous word and then try this word
                

            }
            return true;
        }

        string currentWord = words[index];
        for (auto word : words) {
            for (int row = 0; row < board.size(); ++row) {
                for (int col = 0; col < board[0].size(); ++col) {
                    for (const auto& direction : directions) {
                        int dr = direction.first;
                        int dc = direction.second;
                        if (canPlaceWord(word, row, col, dr, dc)) {
                            placeWord(word, row, col, dr, dc);
                        }
                    }
                }
            }
        }

        return false;
    }

public:
    WordSearch(int _rows, int _cols, const vector<string>& _words, const vector<string>& _banned_words) {
        rows = _rows;
        cols = _cols;
        board.resize(rows, vector<char>(cols, '.'));
        words = _words;
        banned_words = _banned_words;
    }

    void generateBoards() {
        boards.clear();
        fillBoard(0);
    }

    vector<vector<vector<char>>> getBoards() {
        return boards;
    }
};

int main() {
    int rows = 3; // You can modify this to the desired number of rows
    int cols = 5; // You can modify this to the desired number of columns

    vector<string> words = {"yeti", "karma", "squid"};
    vector<string> banned_words = {"sky", "red", "ski", "me", "at", "rut", "is", "yum"};

    WordSearch puzzle(rows, cols, words, banned_words);
    puzzle.generateBoards();
    vector<vector<vector<char>>> boards = puzzle.getBoards();
    cout << boards.size() << endl;

    for (const auto& board : boards) {
        for (const auto& row : board) {
            for (char c : row) {
                cout << c << ' ';
            }
            cout << endl;
        }
        cout << endl;
    }

    return 0;
}
