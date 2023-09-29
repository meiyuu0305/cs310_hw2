#include <iostream> 
#include <string>
using namespace std;
/**
 * @brief class movie, with string title, director name and the int year release
 * has a friend class to overload the << cout operator
 */
class Movie {
    private: 
        string title;
        string director_name;
        int release_year;
        friend ostream & operator << (ostream &out, const Movie&m);
    public: 
    Movie();
    Movie(string t, string dn, int ry);
    Movie(const Movie& obj);
    string toString();
    bool operator==(const Movie& obj) const;
};
//overload the << operator 
ostream & operator << (ostream &out, const Movie&m){
    return out << m.title << " " << m.director_name << " " << m.release_year;
}

//default constructor 
Movie::Movie(){
    this->title = "";
    this->director_name = "";
    this->release_year= 0;
}
//constructor
Movie::Movie(string t, string dn, int ry){
    this->title = t;
    this->director_name = dn;
    this->release_year = ry;
}
//copy constructor 
Movie::Movie(const Movie &obj){
    this->title = obj.title;
    this->director_name = obj.director_name;
    this->release_year = obj.release_year;
}
//to string function 
string Movie::toString(){
    string result ="";
    result = title+ " " + director_name + " " + to_string(release_year);
    return result;
}

//overload == operator 
bool Movie :: operator == (const Movie &obj) const{
    string oriDN = this->director_name;
    string compareDN = obj.director_name;
    string oriT = this->title;
    string compareT = obj.title;
    if (this->release_year == obj.release_year &&
        oriDN.compare(compareDN) == 0 &&
        oriT.compare(compareT) == 0)
    { return true; }
    return false;
}
int main(){
    Movie harrypotter ("Harry Potter", "dr", 2006);
    Movie harrypotter2 ("Harry Potter", "dr", 2006);
    Movie sherlock ("Sherlock Holmes", "dr", 2005);
    Movie sherlock2 (sherlock);
    bool ans = (harrypotter == harrypotter2);
    cout << harrypotter.toString() << " is equal to " << harrypotter2.toString() << endl;
    cout << "This is copied obj" <<sherlock2.toString() <<endl; 
    cout<< sherlock;
}

