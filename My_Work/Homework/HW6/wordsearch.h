#ifndef WORDSEARCH_H
#define WORDSEARCH_H

#include <iostream>
#include <vector>
#include <string>
#include <utility>

class WordSearch {
public:
    WordSearch(int _rows, int _cols, const std::vector<std::string>& _words, const std::vector<std::string>& _banned_words);

    void generateBoards(std::string mode);
    std::vector<std::vector<std::vector<char>>> getBoards();

private:
    std::vector<std::vector<char>> board;
    std::vector<std::string> words;
    std::vector<std::string> banned_words;
    std::vector<std::vector<std::vector<char>>> boards;
    std::vector<std::pair<int, int>> word_positions; // Store the positions where each word is placed
    std::vector<std::pair<int, int>> directions{
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},           {0, 1},
        {1, -1},  {1, 0},  {1, 1}
    };
    int rows, cols;
    char getRandomLetter();
    bool isBoardFilled() const;
    bool findWord(const std::string& word) const;
    bool findWord2(const std::vector<std::vector<char>>& board, const std::string& word);
    bool containsForbiddenWords() ;
    bool containsForbiddenWords2(const std::vector<std::vector<char>>& board) ;
    bool isBoardInVector(const std::vector<std::vector<char>>& board);
    std::pair<int, int> removeWord(const std::string& word, int row, int col);
    std::vector<std::vector<std::vector<char>>> fillBlankSpots();
    bool isBoardCompleteAndValid();
    bool canPlaceWord(const std::string& word, int row, int col, int dr, int dc);
    void placeWord(const std::string& word, int row, int col, int dr, int dc);
    void insert_words(int wordIndex);
    void insert_word_1_sol(int wordIndex);
};

#endif // WORDSEARCH_H
