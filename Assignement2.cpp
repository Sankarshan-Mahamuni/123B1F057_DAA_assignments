#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>
using namespace std;

class Movie {
public:
    string title;
    double imdbRating;
    int releaseYear;
    int watchCount;

    Movie(string t, double r, int y, int w)
        : title(t), imdbRating(r), releaseYear(y), watchCount(w) {}
};

// Partition function for QuickSort
int partition ( vector<Movie> & movies,int low,int high,const string &sortBy){
    Movie pivot =movies[low];
    int i=low+1;
    int j=high;
    while (i<=j){
        if (sortBy =="rating"){
            while (i<=high && movies[i].imdbRating<=pivot.imdbRating) i++;
            while (j>=low && movies[j].imdbRating>pivot.imdbRating) j--;
        }
        else if (sortBy == "year") {
            while (i <= high && movies[i].releaseYear <= pivot.releaseYear) i++;
            while (j >= low && movies[j].releaseYear > pivot.releaseYear) j--;
        } else if (sortBy == "watch") {
            while (i <= high && movies[i].watchCount <= pivot.watchCount) i++;
            while (j >= low && movies[j].watchCount > pivot.watchCount) j--;
        }
        if (i< j){
            swap(movies[i],movies[j]);
        }

    }
    swap(movies[low],movies[j]);
    return j;

}

// QuickSort function
void quickSort(vector<Movie>& movies, int low, int high, const string& sortBy) {
    if (low < high) {
        int pivotIndex = partition(movies, low, high, sortBy);
        quickSort(movies, low, pivotIndex - 1, sortBy);
        quickSort(movies, pivotIndex + 1, high, sortBy);
    }
}

// Sample movie data
vector<Movie> sampleMovies() {
    return {
        {"Avengers", 8.5, 2012, 9500},
        {"Inception", 8.8, 2010, 8700},
        {"Titanic", 7.8, 1997, 12000},
        {"Matrix", 8.7, 1999, 9800},
        {"Interstellar", 8.6, 2014, 7300},
        {"Joker", 8.4, 2019, 8200},
        {"Avatar", 7.9, 2009, 15000},
        {"Gladiator", 8.5, 2000, 6600},
        {"Up", 8.2, 2009, 5400},
        {"Coco", 8.4, 2017, 4700}
    };
}

int main() {
    vector<Movie> movies = sampleMovies();
    string sortBy;

    cout << "Sort movies by (rating/year/watch): ";
    cin >> sortBy;

    transform(sortBy.begin(), sortBy.end(), sortBy.begin(), ::tolower);
    if (sortBy != "rating" && sortBy != "year" && sortBy != "watch") {
        cout << "Invalid sort option!" << endl;
        return 0;
    }

    auto start = chrono::high_resolution_clock::now();
    quickSort(movies, 0, movies.size() - 1, sortBy);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> timeTaken = end - start;

    cout << "\nMovies sorted by " << sortBy << ":\n";
    printf("%-15s %-8s %-6s %-6s\n", "Title", "Rating", "Year", "Watch");
    cout << "-------------------------------------------\n";
    for (const auto& m : movies) {
        printf("%-15s %-8.1f %-6d %-6d\n", m.title.c_str(), m.imdbRating, m.releaseYear, m.watchCount);
    }
    printf("\nTime taken by QuickSort: %.3f ms\n", timeTaken.count());
    return 0;
}