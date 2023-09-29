#include <iostream> 
#include <string>
using namespace std;
#include<iostream>
using namespace std;

template<typename T> class  Node{
    private:
        T data;
        Node<T>* next;
        Node<T>* prev;
        template<typename U>friend class DoublyLinkedList;
    public:
        Node(){
            next = prev = nullptr;
        }
};
template<typename T>class DoublyLinkedList{
    private:
        Node<T> *head = nullptr;
        Node<T> *tail = nullptr;
        int count = 0;
        Node<T> * createNewNode(T value){
            Node<T> *node = new Node<T>;
            node->data = value;
            return node;
        }
    public:
        bool deleteAfter ( Node<T> * prevNode){
            if (prevNode == nullptr) {return false;}
            Node<T> * deleteNode = prevNode -> next;
            if(deleteNode == nullptr) {return false;}

            prevNode -> next = deleteNode -> next;
            if(deleteNode->next != nullptr)
            {
                deleteNode->next->prev = prevNode;
            }
            delete deleteNode;
            count--;
            return true;
        }
        bool reverse (){
            if (count == 0 || head == nullptr){return false;}
            Node<T> * hnode = head;
            //traverse to set tail
                tail = head;
                while(tail->next != nullptr)
                {
                    tail->next->prev = tail;
                    tail = tail->next;
                }          
            Node<T> * tnode = tail;
            for (int i = 0; i< count/2; i++){
                T temp = hnode->data;
                hnode->data = tnode->data;
                tnode->data = temp;

                hnode = hnode->next;
                tnode = tnode->prev;
            }
        }
        bool deleteItem (T delVal) {
            T value;
            if(count == 0) {return false;}
            Node<T> * ptr = head;
            while (ptr != nullptr)
            {
                value = ptr->data;
                if(value == delVal)
                {
                    if(ptr == head ){
                        pop_front(value);
                        return true;
                    }
                    if(ptr == tail) {pop_back(value); return true;}
                    ptr = ptr->prev;
                    deleteAfter(ptr);
                    return true;
                }
                ptr = ptr->next;
            }
            return false;
        }
        DoublyLinkedList(){
            this->head = nullptr;
            this->tail = nullptr;
        }
        vector<int> searchItems(T searchVal){
            vector<int> indexes;
            Node<T> * current = head; 
            for (int i = 0; i< count; i++){
                T value = current->data;
                if (value == searchVal)
                {
                    indexes.push_back(i);
                }
                current = current->next;
            }
            return indexes;
        }
        DoublyLinkedList(const DoublyLinkedList &D);
        ~DoublyLinkedList() {
            T data;
            while(pop_front(data));
        } // destructor 
        void push_front(T value){
            Node<T> * newNode = createNewNode(value);
            newNode->next = head;
            newNode->prev = nullptr;
            if(head != nullptr)
            { newNode->next->prev = newNode; }
            else {tail = newNode; tail->prev = head;}
            count++;
            head = newNode;
        } // create and put a newNode in front of list 
        void push_back(T value){
            Node<T> * newNode = createNewNode(value);
            if(tail != nullptr) {
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
                count++;
            }
            else{
                head = newNode;
                tail = newNode;
                count++;
            }
        } // create and put a newNode at the back of list 
        bool pop_front (T &data){ // delete the first element and return the data 
            if(count==0 || head == nullptr)
                return false;
            data = head->data;
            if(head->next== nullptr){ // if this is the only node
                delete head;
                tail = nullptr;
                head = nullptr;
                count =0;
                return true;}
            Node<T> * prevHead = head;
            // head should point to the next node
            head = head->next;
            // the current head would be deleted
            head ->prev = nullptr;
            delete prevHead;
            count--;
            return true;
        }
        bool pop_back (T &d) {
            if(head != nullptr){
                //traverse to set tail
                tail = head;
                while(tail->next != nullptr)
                {
                    tail->next->prev = tail;
                    tail = tail->next;
                }                
                //------
                Node<T> * tempo = tail->prev;
                d = tail->data;
                delete tail;
                tail = tempo;
                count--;
                if(tail == nullptr){ head = nullptr; return true;}
                else {tail->next = nullptr; return true;}
            }
            return false;
                }// delete the last element and return the data 
        bool deleteNode (int index); // delete Node at a specific index 
        void displayList(){
            Node<T> * node = head;
            while(node != nullptr)
            {
                cout << node->data << "<=>";
                node = node->next;
            }
            tail = node;
            cout << "END" << endl; 
        }

        
};
template<typename T> 
DoublyLinkedList<T>::DoublyLinkedList (const DoublyLinkedList<T> &D){
    Node<T> * ptr = D.head; // this pointer points to source 
    head = tail = new Node<T>();
    head->prev = nullptr;
    head = ptr;
    ptr = ptr->next;
    Node<T> * current = head;
    while(ptr != nullptr){
        current -> next = new Node<T>();
        current -> next -> prev = current;
        current = current ->next;

        current->data = ptr->data;
        ptr = ptr -> next; 
    }
    current -> next = nullptr;
    tail = current;
}
template<typename T>
bool DoublyLinkedList<T>::deleteNode (int index){
    T value = 0;
    if (index < 0 || index >= count || head == nullptr)
    {
        return false;
    }
    if(index == 0){
        pop_front(value);
    }
    if(index == count-1){
        pop_back(value);
    }
    else {
        Node<T> * ptr = new Node<T>();
        double compare_ind = static_cast<double> (count) /2;
       
        if(index <= compare_ind){
            ptr = head;
            for (int i = 0; i<= index-2; i++){
            ptr = ptr->next;}}
        else {
            //transverse to get tail
             tail = head;
                while(tail->next != nullptr)
                {
                    tail->next->prev = tail;
                    tail = tail->next;
                }                
                //------     
            ptr = tail;
            cout << tail->prev->data;
            cout<< "ran";
            for (int i = count-1; i>=index; i--){
            ptr = ptr->prev;
            }
        }
        this->deleteAfter(ptr);
    }
    return true;
}

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

ostream & operator << (ostream &out, const Movie&m){
    return out << m.title << " " << m.director_name << " " << m.release_year << endl;
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
    // declare 10 movies
    Movie bomb ("Oppenheimer", "Christopher Nolan", 2023);
    Movie time ("Tenet", "Christopher Nolan", 2020);
    Movie space_time ("Interstellar", "Christopher Nolan", 2014);
    Movie oldbat ("The Dark Knight ", "Christpher Nolan", 2008);
    Movie joker ("Joker", "Todd Phillips", 2019);
    Movie newbat ("The Batman", "Matt Reeves", 2022);
    Movie oldspider ("The Amaxing Spiderman ", "Marc Webb", 2005);
    Movie newspider ("Spider-Man: No Way Home", "Jon Watts", 2021);
    Movie sherlock ("Sherlock", "Mark Gatiss", 2010);
    Movie dystopia ("Black Mirror", "David Slade", 2011);

    // add them to movCollection 
    DoublyLinkedList<Movie> movCollection; 
    movCollection.push_front(bomb);
    movCollection.push_front(time);
    movCollection.push_front(space_time);
    movCollection.push_front(oldbat);
    movCollection.push_front(joker);
    movCollection.push_front(newbat);
    movCollection.push_front(oldspider);
    movCollection.push_front(newspider);
    movCollection.push_front(sherlock);
    movCollection.push_front(dystopia);

    // display all Movie obj
    movCollection.displayList();

    // copy list and display it
    DoublyLinkedList<Movie> myMovCollection (movCollection);
    myMovCollection.displayList();

    // reverse order of movCollection and display it
    movCollection.reverse();
    movCollection.displayList();

    // declare a movie obj and perform search in movCollection 
    Movie searchtrue ("Oppenheimer", "Christopher Nolan", 2023);
    Movie searchfalse ("Bum Bum", "Christopher Nolan", 2023);

    vector <int> indexes = movCollection.searchItems(searchtrue);
    if (indexes.size()!= 0){
        for (int x: indexes)
        {
            cout << "Found at " << x << "\t";
        }
    }
    else { cout << "None found " ;}

    indexes = movCollection.searchItems(searchfalse);
    if (indexes.size()!= 0){
        for (int x: indexes)
        {
            cout << "Found at " << " " << "\t";
        }
    }
    else { cout << "None found for " << searchfalse ;}

    //delete Items and display movCollection
    movCollection.deleteItem(searchtrue);
    movCollection.displayList(); 
}

