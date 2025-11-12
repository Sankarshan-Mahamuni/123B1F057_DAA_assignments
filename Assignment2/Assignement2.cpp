// Name: Sankarshan Satish Mahamuni
// PRN : 123B1F057
/* Movie Recommendation System Optimization
A popular OTT platform, StreamFlix, offers personalized recommendations by sorting movies
based on user preferences, such as IMDB rating, release year, or watch time popularity.
However, during peak hours, sorting large datasets slows down the system.
As a backend engineer, you must:
● Implement Quicksort to efficiently sort movies based on various user-selected
parameters.
● Handle large datasets containing of movies while maintaining fast response times
*/
#include<iostream>
#include<vector>
#include<sstream>
#include<fstream>
using namespace std;

class Movie {
    public:
        string title;
        float imdb_rating;
        int release_year;
        int popularity;

        Movie(string title,float imdb_rating, int release_year, int popularity){
            this->title=title;
            this->imdb_rating=imdb_rating;
            this->release_year=release_year;
            this->popularity=popularity;
        }

        void Print_movie(){
            cout<<"---------------------------------"<<endl;
            cout<<"Movie Name :"<<title<<endl;
            cout<<"Release Year :"<<release_year<<endl;
            cout<<"IMDB Rating :"<<imdb_rating<<endl;
            cout<<"Popularity :"<<popularity<<endl;
            cout<<"----------------------------------"<<endl;
            cout<<"\n";
        }
};

class Operations{
    public:
    vector<Movie> Load_movies(string filepath){
        vector<Movie> movies;
        ifstream file(filepath);
        if (! file.is_open()){
            cout<< " file not opened error !!"<<filepath<<endl;
        }
        string line;
        getline(file,line); //consume header file
        while (getline(file,line)){
            string title,imdb_rating_str,release_year_str,popularity_str;
            stringstream ss(line);
            getline(ss,title,',');
            getline(ss,imdb_rating_str,',');
            getline(ss,release_year_str,',');
            getline(ss,popularity_str,',');

            float imdb_rating =stof(imdb_rating_str);
            int  release_year =stoi(release_year_str);
            int popularity =stoi(popularity_str);
            
            movies.push_back(Movie(title,imdb_rating,release_year,popularity));
        }
        file.close();
        return movies;
    }

    void swap(Movie &a, Movie &b){
        Movie temp =a;
        a=b;
        b=temp;
        
    }

    int partition(vector<Movie>&movies,int l, int r, int parameter){
        Movie pivot = movies[l];
        int i=l+1;
        int j= r;
        while (i<j){
            while (i<=r){
                bool condition =false;
                if (parameter == 1) condition= (movies[i].imdb_rating>pivot.imdb_rating);
                else if (parameter ==2 )condition = movies[i].release_year> pivot.release_year;
                else if (parameter ==3 )condition = movies[i].popularity > pivot.popularity;

                if (condition) i++;
                else break;
            }

            while (j>=l+1){
                bool condition =false;
                if (parameter ==1 ) condition = movies[j].imdb_rating < pivot.imdb_rating;
                else if (parameter ==2) condition =movies[j].release_year < pivot.release_year;
                else if (parameter ==3) condition =  movies[j].popularity < pivot.popularity;

                if (condition) j--;
                else break;

            }

            if (i<j)
            swap(movies[i],movies[j]);
        }

        swap(movies[l],movies[j]);
        return j;

    }


    void quick_sort(vector<Movie> & movies,int l,int r,int parameter){
        if (l<r){
            int pivot = partition(movies,l,r,parameter);
            quick_sort(movies,l,pivot-1,parameter);
            quick_sort(movies,pivot+1,r,parameter);
        }
            
    }

};

int main(){
    vector<Movie>movies;
    Operations obj =Operations();
    movies=obj.Load_movies("movies.csv");

    cout<<" Before sort --"<<endl;
    for (auto& o : movies){
        o.Print_movie();
    }
    obj.quick_sort(movies,0,movies.size()-1,1);

    cout<<" After sort --"<<endl;
    for (auto &o : movies){
        o.Print_movie();
    }

return 0;
}