/**
 * @file Deliverable1.cpp
 * @author My Nguyen
 * @brief DoublyLinkedList Template class
 * @version 0.1
 * @date 2023-09-28
 * 
 */
#include<iostream>
using namespace std;

/**
 * @brief Create a structure for Node, with template in mind
 */
template<typename T>class Node{
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
 * @brief Create a structure for DoublyLinkedList, to link nodes together with two pointer - head and tail
 */
template<typename T>class DoublyLinkedList{
    private:
        Node<T>* head;
        Node<T>*tail;
        int count = 0;
    public:
        DoublyLinkedList(){
            this->head = NULL;
            this->tail = NULL;
        }
};
int main(){
    DoublyLinkedList<string> city_names;
    return 0; 
}