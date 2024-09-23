HOMEWORK 6: INVERSE WORD SEARCH

NAME: Temitayo Oladeji

COLLABORATORS AND OTHER RESOURCES:
I did not collaborate with anyone specifically for this assignment. I mainly relied on online resources, including YouTube videos, such as the one linked (https://www.youtube.com/watch?v=RjO-HDjRMpM&list=PLjkkQ3iH4jy82KRn9jXeFyWzvX7sqYrjE&index=23), for conceptual understanding.

ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT: Approximately 70 hours.

ALGORITHM ANALYSIS:
The order notation of my algorithm is likely exponential due to the recursive nature of the problem and the branching factor involved in exploring possible word placements on the board.




MISC. COMMENTS TO GRADER:  
Optional, please be concise!



## Reflection and Self Assessment ##
Throughout the completion of this assignment, I faced significant challenges in understanding the code structure and implementing the required algorithms effectively. Specifically, I struggled with comprehending the logic behind recursive functions and their application in solving the inverse word search problem.

In particular, I found it challenging to grasp how to recursively explore all possible word placements on the board while ensuring the validity of each configuration. Understanding the intricacies of backtracking and recursion within the context of this problem was particularly daunting.

Furthermore, I encountered difficulties in debugging and optimizing the code, especially when dealing with edge cases and handling various board configurations.








Run time  
WordSearch::WordSearch(int _rows, int _cols, const std::vector<std::string>& _words, const std::vector<std::string>& _banned_words) - Constructor function.

Runtime: Depends on the size of _rows and _cols since it involves resizing the board vector to the specified dimensions. The resizing operation runs in O(rows * cols) time.
WordSearch::generateBoards(std::string mode) - Function to generate boards based on the mode specified.

Runtime: Depends on the mode specified. It either calls insert_word_1_sol() or insert_words(), both of which have their own runtimes.
WordSearch::getBoards() - Function to return the generated boards.

Runtime: O(1). It simply returns the boards vector.
WordSearch::getRandomLetter() - Function to generate a random letter.

Runtime: O(1).
WordSearch::isBoardFilled() const - Function to check if the board is completely filled.

Runtime: O(rows * cols). It iterates through each cell of the board.
WordSearch::findWord(const std::string& word) const - Function to find a word on the board.

Runtime: O(rows * cols * word_length). It iterates through each cell of the board and checks for the presence of the word in all directions.
WordSearch::findWord2(const std::vector<std::vector<char>>& board, const std::string& word) - Function similar to findWord() but works with a separate board.

Runtime: O(rows * cols * word_length). Similar to findWord().
WordSearch::containsForbiddenWords() - Function to check if the board contains any forbidden words.

Runtime: O(rows * cols * num_banned_words * word_length). It iterates through the board and checks for each forbidden word.
WordSearch::containsForbiddenWords2(const std::vector<std::vector<char>>& board) - Function similar to containsForbiddenWords() but works with a separate board.

Runtime: O(rows * cols * num_banned_words * word_length). Similar to containsForbiddenWords().
WordSearch::isBoardInVector(const std::vector<std::vector<char>>& board) - Function to check if a board configuration is already present in the boards vector.

Runtime: O(num_boards * rows * cols). It iterates through each board in the boards vector and compares it with the given board.
WordSearch::removeWord(const std::string& word, int row, int col) - Function to remove a word from the board.

Runtime: O(word_length). It removes the word from the specified position on the board.
WordSearch::fillBlankSpots() - Function to fill blank spots on the board with all possible letters and return valid board configurations.

Runtime: Exponential, depends on the number of blank spots and the number of letters in the alphabet.
WordSearch::isBoardCompleteAndValid() - Function to check if the board is complete and valid.

Runtime: O(rows * cols * word_length) + O(num_words). It iterates through the board to check completeness and checks for the presence of each word.
WordSearch::canPlaceWord(const std::string& word, int row, int col, int dr, int dc) - Function to check if a word can be placed at a given position and direction.

Runtime: O(word_length). It checks if the word can fit in the specified position and direction without overlapping existing letters.
WordSearch::placeWord(const std::string& word, int row, int col, int dr, int dc) - Function to place a word on the board.

Runtime: O(word_length). It places the word at the specified position and direction on the board.
WordSearch::insert_words(int wordIndex) - Recursive function to insert words onto the board and generate all possible valid configurations.

Runtime: Exponential, depends on the number of words and the dimensions of the board.
WordSearch::insert_word_1_sol(int wordIndex) - Similar to insert_words() but stops after finding one solution.

Runtime: Exponential, similar to insert_words() but may terminate earlier if a solution is found. 