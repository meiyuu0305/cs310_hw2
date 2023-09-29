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
            next = prev = nullptr;
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
        // the function will reverse the list, so that tail is head and head is tail.
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
        //function to run deleteItem
        // void insertAfter ( Node<T> * prevNode, T value);
        DoublyLinkedList(){
            this->head = nullptr;
            this->tail = nullptr;
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
        // int size();
        // bool isEmpty();
        
};
int main(){
    DoublyLinkedList<int> city_names;
    city_names.push_front(1);
    city_names.push_front(5);
    city_names.push_front(6);
    city_names.displayList();
    city_names.reverse();
    city_names.displayList();
    return 0; 
}

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