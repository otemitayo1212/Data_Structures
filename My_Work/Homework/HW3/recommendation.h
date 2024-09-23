#ifndef RECOMMENDATION_H
#define RECOMMENDATION_H

class RecommendationSystem {
public:
    // Constructor and Destructor
    RecommendationSystem(int** m, int** s, int users, int movies, int shows);

    // Getter and Setter for userMovieRatingsMatrix
    int** getUserMovieRatingsMatrix() const;
    void setUserMovieRatingsMatrix(int** matrix);

    // Getter and Setter for userShowRatingsMatrix
    int** getUserShowRatingsMatrix() const;
    void setUserShowRatingsMatrix(int** matrix);

    // Member functions
    void recommendMovies(int userId, int numRecommendations, int* recommendedMovies) const;
    void recommendShows(int userId, int numRecommendations, int* recommendedShows) const;

private:
    int** userMovieRatingsMatrix; // Matrix for movie ratings
    int** userShowRatingsMatrix;  // Matrix for show ratings
    int numUsers;
    int numMovies;
    int numShows;
};

#endif 
