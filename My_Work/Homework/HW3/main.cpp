#include <sstream>
#include <iostream>
#include<fstream>
#include "recommendation.h"

class Movie {
public:
    int movieId;
    std::string title;
};

class TVShow {
public:
    int tvShowId;
    std::string title;
};

// Oscar-winning movies
Movie movies[] = {
    {0, "Elvis"},
    {1, "The Shawshank Redemption"},
    {2, "The Godfather"},
    {3, "Schindler's List"},
    {4, "The Lord of the Rings: The Return of the King"},
    {5, "Forrest Gump"},
    {6, "Titanic"},
    {7, "Gladiator"},
    {8, "The Departed"},
    {9, "12 Years a Slave"},
    {10, "Green Book"},
    {11, "The Silence of the Lambs"},
    {12, "The Sound of Music"},
    {13, "Amadeus"},
    {14, "The Shape of Water"},
    {15, "Braveheart"},
    {16, "The English Patient"},
    {17, "Moonlight"},
    {18, "Argo"},
    {19, "Birdman"},
    {20, "No Country for Old Men"},
    {21, "A Beautiful Mind"},
    {22, "Spotlight"},
    {23, "The King's Speech"},
    {24, "Platoon"},
    {25, "Dances with Wolves"},
    {26, "Gandhi"},
    {27, "The Green Mile"},
    {28, "The Pianist"},
    {29, "The Bridge on the River Kwai"},
    {30, "West Side Story"},
    {31, "The Godfather: Part II"},
    {32, "Crouching Tiger, Hidden Dragon"},
    {33, "The Hurt Locker"},
    {34, "Slumdog Millionaire"},
    {35, "Million Dollar Baby"},
    {36, "Rain Man"},
    {37, "Rocky"},
    {38, "Inception"},
    {39, "Chariots of Fire"},
    {40, "The Great Gatsby"},
    {41, "All About Eve"},
    {42, "One Flew Over the Cuckoo's Nest"},
    {43, "The Apartment"},
    {44, "The French Connection"},
    {45, "The Grand Budapest Hotel"},
    {46, "Rebecca"},
    {47, "Gone with the Wind"},
    {48, "Casablanca"},
    {49, "Ben-Hur"},
    {50, "Lawrence of Arabia"},
    {51, "The Phantom of the Opera"},
    {52, "The Godfather: Part III"},
    {53, "Annie Hall"},
    {54, "Out of Africa"},
    {55, "My Fair Lady"},
    {56, "The Life of Emile Zola"},
    {57, "On the Waterfront"},
    {58, "The Best Years of Our Lives"},
    {59, "The Deer Hunter"},
    {60, "Midnight Cowboy"},
    {61, "American Beauty"},
    {62, "Gigi"},
    {63, "Going My Way"},
    {64, "Gentleman's Agreement"},
    {65, "From Here to Eternity"},
    {66, "Oliver!"},
    {67, "Patton"},
    {68, "The Artist"},
    {69, "The Family Plan"},
    {70, "A Man for All Seasons"},
    {71, "Lincoln"},
    {72, "The Greatest Show on Earth"},
    {73, "An American in Paris"},
    {74, "Kramer vs. Kramer"},
    {75, "The Descendants"},
    {76, "Driving Miss Daisy"},
    {77, "All Quiet on the Western Front"},
    {78, "The Greatest Showman"},
    {79, "Mutiny on the Bounty"},
    {80, "The Lost Weekend"},
    {81, "The Batman"},
    {82, "Aquaman and the Lost Kingdom"},
    {83, "Parasite"},
    {84, "Ordinary People"},
    {85, "Wonka"},
    {86, "Tom Jones"},
    {87, "The Last Emperor"},
    {88, "Don't Look Up"},
    {89, "Chicago"},
    {90, "The Revenant"},
    {91, "Darkest Hour"},
    {92, "Manchester by the Sea"},
    {93, "Hacksaw Ridge"},
    {94, "The Theory of Everything"},
    {95, "Midnight in Paris"},
    {96, "Coda"},
    {97, "Catch Me If You Can"},
    {98, "Nomadland"},
    {99, "The Graduate"},
    {100, "Pearl Harbor"},
    {101, "Dune"},
    {102, "King Richard"},
    {103, "Drive My Car"},
    {104, "The Fabelmans"},
    {105, "The Long Goodbye"},
    {106, "Nightmare Alley"},
    {107, "A Star is Born"},
    {108, "Top Gun: Maverick"},
    {109, "Everything Everywhere All at Once"},
};

// Emmy Award-winning TV shows
TVShow tvShows[] = {
    {0, "Little Women"},
    {1, "The West Wing"},
    {2, "The Sopranos"},
    {3, "Breaking Bad"},
    {4, "Game of Thrones"},
    {5, "The Twilight Zone"},
    {6, "The Simpsons"},
    {7, "Friends"},
    {8, "The Mary Tyler Moore Show"},
    {9, "M*A*S*H"},
    {10, "The Wire"},
    {11, "The Marvelous Mrs. Maisel"},
    {12, "The Crown"},
    {13, "Fleabag"},
    {14, "Stranger Things"},
    {15, "The Mandalorian"},
    {16, "Veep"},
    {17, "The Big Bang Theory"},
    {18, "Homeland"},
    {19, "The Handmaid's Tale"},
    {20, "The Office (U.S.)"},
    {21, "Cheers"},
    {22, "The Golden Girls"},
    {23, "I Love Lucy"},
    {24, "The Americans"},
    {25, "Sherlock"},
    {26, "Fargo"},
    {27, "The People v. O.J. Simpson: American Crime Story"},
    {28, "Black Mirror"},
    {29, "Westworld"},
    {30, "Mad Men"},
    {31, "The Boys"},
    {32, "Better Call Saul"},
    {33, "Hand of God"},
    {34, "The Good Place"},
    {35, "Atlanta"},
    {36, "Barry"},
    {37, "The Office (UK)"},
    {38, "Fawlty Towers"},
    {39, "Monty Python's Flying Circus"},
    {40, "The Daily Show with Jon Stewart"},
    {41, "Late Night with David Letterman"},
    {42, "The Tonight Show Starring Johnny Carson"},
    {43, "Saturday Night Live"},
    {44, "The X-Files"},
    {45, "Downton Abbey"},
    {46, "The Big C"},
    {47, "Six Feet Under"},
    {48, "Ray Donovan"},
    {49, "Curb Your Enthusiasm"},
    {50, "Keeping Up with the Kardashians"},
    {51, "The Twilight Zone (2002)"},
    {52, "Dexter"},
    {53, "House of Cards"},
    {54, "Boardwalk Empire"},
    {55, "The Newsroom"},
    {56, "Black-ish"},
    {57, "The Good Wife"},
    {58, "Parks and Recreation"},
    {59, "Pose"},
    {60, "This Is Us"},
    {61, "Watchmen"},
    {62, "The Office (U.K.)"},
    {63, "Vigil"},
    {64, "The Ellen DeGeneres Show"},
    {65, "True Detective"},
    {66, "The Cosby Show"},
    {67, "The Witcher"},
    {68, "Succession"},
    {69, "The Tonight Show Starring Jimmy Fallon"},
    {70, "Scrubs"},
    {71, "Mindhunter"},
    {72, "Euphoria"},
    {73, "The Umbrella Academy"},
    {74, "Arrested Development"},
    {75, "Jury Duty"},
    {76, "Seinfeld"},
    {77, "Great News"},
    {78, "Killers of the Flower Moon"},
    {79, "House"},
    {80, "Ted Lasso"},
    {81, "How I Met Your Mother"},
    {82, "Unbreakable Kimmy Schmidt"},
    {83, "All in the Family"},
    {84, "The Leftovers"},
    {85, "Wednesday"},
    {86, "Frasier"},
    {87, "Modern Family"},
    {88, "Better Things"},
    {89, "Brooklyn Nine-Nine"},
    {90, "Everybody Loves Raymond"},
    {91, "Taxi"},
    {92, "Late Night with Seth Meyers"},
    {93, "30 Rock"},
    {94, "Community"},
    {95, "Squid Game"},
    {96, "Will & Grace"},
    {97, "Schitt's Creek"},
    {98, "Get Smart"},
    {99, "The Monkees"},
};

// this function reads the one line, and update row i of the matrix.
void process_one_line(int** matrix, int i, std::string& line){
	std::istringstream iss(line);
	// process each (index, value) pair
        int index, value;
        char openParen, comma, closeParen;
	// when used with integers, it reads characters until it encounters a non-digit character or whitespace. However, when used with characters, it reads a single character.
        while (iss >> openParen >> index >> comma >> value >> closeParen) {
            matrix[i][index] = value;
        }
}

void writeMoviesToFile(const std::string& filename, Movie movies[], int *movie_pointer, int size) {
    std::ofstream outputFile(filename );
     if (outputFile.is_open()){
        outputFile << "Prime: Movies we think you'll like:\n";
     for (int i = 0; i < 110; i++) {

        for (int j = 0 ; j < size;j++){
            if (i == movie_pointer[j]){
            outputFile << movies[i].title << "\n";
            }
        }
    }
     }else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
  
}

// Function to write TV show titles to a file
void writeTVShowsToFile(const std::string& filename, TVShow tvShows[], int *shows_pointer, int size) {
    std::ofstream outputFile(filename , std::ios::app );
    if (outputFile.is_open()){
         outputFile <<"Prime: TV shows we think you'll like:\n";
         for (int i = 0; i < 100; ++i) {
            // check if the number is in the show array
            for (int j = 0 ; j < size;j++ ){
                if (i == shows_pointer[j]){
                    outputFile << tvShows[i].title << "\n";
                }
            }        
        }
        outputFile.close();
    }else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    } 
}


int main(int argc, char* argv[]) {
    // Define constants for the number of users, movies, and shows
    const int numUsers = 500;
    const int numMovies = 110;
    const int numShows = 100;

    // Check the number of command line arguments
    if (argc != 6) {
        std::cerr <<"Usage: nyrecommender.exe movieRatings.txt showRatings.txt output.txt userID numRecommendations"<< std::endl;
        return 0;
    }

    // Check if userID is within the valid range
    int userID = std::stoi(argv[4]);
    if (userID < 0 || userID > 499) {
        std::cerr << "Invalid User ID." << std::endl;
        return 0;
    }

    // Check if numRecommendations is 0
    int numRecommendations = std::stoi(argv[5]);
    if (numRecommendations == 0) {
        std::ofstream outputFile(argv[3]);
        outputFile << "Prime: Movies we think you'll like:\n";
        outputFile << "Prime: TV shows we think you'll like:\n";
        outputFile.close();
        return 0;
    }

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
    std::ifstream movieFile(argv[1]);
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
        return 0;
    }

    // Read and process show ratings file
    std::ifstream showFile(argv[2]);
    userIndex = 0;
    if (showFile.is_open()) {
        while (std::getline(showFile, line)) {
            process_one_line(showRatingsMatrix, userIndex, line);
            ++userIndex;
        }
        showFile.close();
    } else {
        std::cerr << "Unable to open show ratings file." << std::endl;
        return 0;
    }



    // Create a recomendation class by puting in both 
    RecommendationSystem recommendationSystem(movieRatingsMatrix,  showRatingsMatrix , numUsers , numMovies , numShows );
    // create a poiner with the array of the recomended list 
    int*movie_pointer = new int[numRecommendations];
    int*shows_pointer = new int[numRecommendations];
    // need userID , numRecomendation , put in pointer
    recommendationSystem.recommendMovies( userID ,  numRecommendations ,  movie_pointer);
    recommendationSystem.recommendShows( userID, numRecommendations,  shows_pointer);
    
    // Write movies to outputfile
    writeMoviesToFile(argv[3], movies, movie_pointer, numRecommendations);

    // Write TV shows to outputfile
    writeTVShowsToFile(argv[3], tvShows, shows_pointer,numRecommendations);

    for (int i = 0; i < numUsers; ++i) {
        delete[] movieRatingsMatrix[i];
        delete[] showRatingsMatrix[i];
    }
    delete[] movieRatingsMatrix;
    delete[] showRatingsMatrix;
    delete[] movie_pointer;
    delete[] shows_pointer;

    return 0; 
}



