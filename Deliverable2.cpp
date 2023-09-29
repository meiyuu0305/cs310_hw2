#include<iostream>
using namespace std;

/**
 * @brief The class create Node, has data and pointers (next and prev)
 * @tparam T 
 */
template<typename T> class  Node{
    private:
        T data;
        Node<T>* next;
        Node<T>* prev;
        template<typename U>friend class DoublyLinkedList;
    public:
        Node(){
            this->next = NULL;
            this->prev = NULL;
        }
};
/**
 * @brief The class create list, has head points to first element, tail ponts to last element
 * @tparam T 
 */
template<typename T>class DoublyLinkedList{
    private:
        Node<T> *head = nullptr;
        Node<T> *tail = nullptr;
        int count = 0;
        Node<T> * createNewNode(T value){
            Node<T> *node = new Node<T>;
            node->data = value;
            node->next = nullptr;
            node->prev = nullptr;
            return node;
        }
    public:
    //Default Constructor
        DoublyLinkedList(){
            this->head = nullptr;
            this->tail = nullptr;
        }
    //Copy constructure
        DoublyLinkedList(const DoublyLinkedList &D);
    //Destructor 
        ~DoublyLinkedList() {
            T data;
            while(pop_front(data));
        } 
    //Insert element at the head
        void push_front(T value){
            Node<T> * newNode = createNewNode(value);
            if(head != nullptr) {
                newNode->next = head;
                head->prev = newNode;
                head = newNode;
            }
            else{
                head = newNode;
                tail = newNode;
            }count++;
        } 
        void push_back( T value); // create and put a newNode at the back of list 
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
            count --;
            return true;

        }
        //display the list
        void displayList(){
            Node<T> * node = head;
            while(node != nullptr)
            {
                cout << node->data << "<=>";
                node = node->next;
            }
            tail = node;
            cout << "END"<< endl;
        }
        // int size();
        // bool isEmpty();
        
};
int main(){
    DoublyLinkedList<int> city_names;
    city_names.push_front(1);
    city_names.push_front(5);
    city_names.push_front(6);
    cout << "Main list:";
    city_names.displayList();
    cout << "\nCopy list:";
    DoublyLinkedList<int> copier (city_names);
    copier.displayList();
    return 0; 
}
/**
 * @brief create a new element at the end of the list
 * @tparam T 
 * @param value - data for new Node
 */
template<typename T> 
void DoublyLinkedList<T>::push_back(T value){
     Node<T> * newNode = createNewNode(value);
            if(tail != nullptr) {
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            }
            else{
                head = newNode;
                tail = newNode;
            }count++;
}
template<typename T> 
DoublyLinkedList<T>::DoublyLinkedList (const DoublyLinkedList<T> &D){
    Node<T> * ptr = D.head; // this pointer points to source 
    while(ptr != NULL){
        this->push_back(ptr->data);
        ptr = ptr->next;
    }
}