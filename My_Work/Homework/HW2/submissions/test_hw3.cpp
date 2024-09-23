#include <iostream>
#include <fstream>
#include <sstream>

void process_one_line(int** matrix, int i, std::string& line){
    std::istringstream iss(line);
    // process each (index, value) pair
    int index, value;
    char openParen, comma, closeParen;
    // when used with integers, it reads characters until it encounters a non-digit character or whitespace.
    // However, when used with characters, it reads a single character.
    while (iss >> openParen >> index >> comma >> value >> closeParen) {
        matrix[i][index] = value;
    }
}

int main() {
    // Define constants for the number of users, movies, and shows
    const int numUsers = 500;
    const int numMovies = 110;
    const int numShows = 100;

    // Allocate memory for movie ratings matrix
    int** movieRatingsMatrix = new int*[numUsers];
    for (int i = 0; i < numUsers; ++i) {
        movieRatingsMatrix[i] = new int[numMovies];
        // Initialize all ratings to 0
        for (int j = 0; j < numMovies; ++j) {
            movieRatingsMatrix[i][j] = 0;
        }
    }

    // Allocate memory for show ratings matrix
    int** showRatingsMatrix = new int*[numUsers];
    for (int i = 0; i < numUsers; ++i) {
        showRatingsMatrix[i] = new int[numShows];
        // Initialize all ratings to 0
        for (int j = 0; j < numShows; ++j) {
            showRatingsMatrix[i][j] = 0;
        }
    }

    // Read and process movie ratings file
    std::ifstream movieFile("movieRatings.txt");
    std::string line;
    int userIndex = 0;
    if (movieFile.is_open()) {
        while (std::getline(movieFile, line)) {
            process_one_line(movieRatingsMatrix, userIndex, line);
            ++userIndex;
        }
        movieFile.close();
    } else {
        std::cerr << "Unable to open movie ratings file." << std::endl;
    }

    // Read and process show ratings file
    std::ifstream showFile("showRatings.txt");
    userIndex = 0;
    if (showFile.is_open()) {
        while (std::getline(showFile, line)) {
            process_one_line(showRatingsMatrix, userIndex, line);
            ++userIndex;
        }
        showFile.close();
    } else {
        std::cerr << "Unable to open show ratings file." << std::endl;
    }

    // Now you have filled movieRatingsMatrix and showRatingsMatrix with the ratings data
    // You can use these matrices in your recommendation system
    
    // Don't forget to deallocate memory for the matrices when done
    for (int i = 0; i < numUsers; ++i) {
        delete[] movieRatingsMatrix[i];
        delete[] showRatingsMatrix[i];
    }
    delete[] movieRatingsMatrix;
    delete[] showRatingsMatrix;

    return 0;
}
