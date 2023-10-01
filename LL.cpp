/*****************************************
** File:    LL.cpp
** This file contains the functions that help with perfoming actions 
** such as (removing, inserting, finding, deconstructing) to a LL
**
***********************************************/
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

//DO NOT ADD ANY CONSTANTS OR FUNCTIONS TO ANY CLASS

// Templated Node class
// Normal node except that each node can hold a pair <T,int>
// where the first value is templated and the second value is the frequency
// (or quantity) of the first
// For example, if T was a string then it would hold string,int
template <class T>
class Node {
  public:
    Node(const T& data); //Node Constructor - Assume each quan
    pair<T,int>& GetData(); //Node Data Getter
    void SetData(const pair<T,int>&); //Node Data Setter
    Node<T>* GetNext(); //Node m_next getter
    void SetNext(Node<T>* next ); //Node m_next setter
  private:
    pair <T,int> m_data; //Holds templated data
    Node<T>* m_next; //Pointer to next node
};

template <class T>
Node<T>::Node(const T& data){
  m_data = make_pair(data,1);
  m_next = nullptr;
}

template <class T>
pair<T,int>& Node<T>::GetData() {
  return m_data;
}

template <class T>
void Node<T>::SetData(const pair<T,int>& data) {
  m_data = data;
}

template <class T>
Node<T>* Node<T>::GetNext() {
  return m_next;
}

template <class T>
void Node<T>::SetNext(Node<T>* next) {
  m_next = next;
}

//Templated Linked List class
template <class T>
class LL {
public:
  // Name: LL() (Linked List) - Default Constructor
  // Desc: Used to build a new linked list
  // Preconditions: None
  // Postconditions: Creates a new linked list where m_head points to nullptr
  LL(){
    m_head = nullptr;
    m_size = 0;
  }

  // Name: ~LL() - Destructor
  // Desc: Used to destruct a LL
  // Preconditions: There is an existing LL with at least one node
  // Postconditions: A LL is deallocated (including dynamically allocated nodes)
  //                 to have no memory leaks!
  ~LL(){
    cout << "De-constructor called\n";
    Node<T>* curr = m_head;
    Node<T>* prev = nullptr;
    // loop through the LL
    while(curr != nullptr){
      prev = curr;
      curr = curr -> GetNext();
      delete prev;
    }
    m_head = nullptr;
    m_size = 0;
  }
  // Name: LL (Copy Constructor)
  // Desc: Creates a copy of existing LL
  //       Requires a LL - REQUIRED to be implemented even if not used
  // Preconditions: Source LL exists
  // Postconditions: Copy of source LL
  LL(const LL& other){
    Node<T>* curr = other.m_head;
    m_head = nullptr;

    while(curr != nullptr){
      for (int i = 0; i < curr -> GetData().second; i++){
        Insert(curr -> GetData().first);
      }
      curr = curr -> GetNext();
    }
  }
  // Name: operator= (Overloaded Assignment Operator)
  // Desc: Makes two LL of the same type have identical number of nodes and values
  // Preconditions: Requires two linked lists of the same templated type
  //                REQUIRED to be implemented even if not used
  // Postconditions: Two idenetical LL
  LL<T>& operator= (const LL& other){
    // checks against self-assignment 
    if (this != &other){
      Node<T>* nodeDelete = m_head;
      // reset the linked list
      while(nodeDelete != nullptr){
        RemoveAt(nodeDelete->GetData().first);
        nodeDelete = nodeDelete -> GetNext();
      }
      m_head = nullptr;
      m_size = 0;
      Node<T>* curr = other.m_head;
      // insertion into linked list
      while(curr != nullptr){
        for (int i = 0; i < curr -> GetData().second; i++){
          Insert(curr -> GetData().first);
        }
        curr = curr ->GetNext();
        this->m_size += 1;
      }
    }
    return *this;
  }
  // Name: Find
  // Desc: Iterates through LL and returns node if data found
  // Preconditions: LL Populated
  // Postconditions: Returns nullptr if not found OR Node pointer if found
  Node<T>* Find(const T& data){
    // checks if LL is empty
    if (m_head == nullptr){
      return nullptr;
    }else{
      Node<T>* curr = m_head;
      while(curr != nullptr){
        // if data is found, return the node
        if (curr -> GetData().first == data){
          return curr;
        }
        curr = curr -> GetNext();
      }
    }
    // return nullptr if node isnt found
    return nullptr;
  }

  // Name: Insert
  // Desc: Either inserts a node to the linked list OR increments frequency of first
  //       Takes in data. If "first" (of pair) NOT in list, adds node
  //       If "first" (of pair) is already in list, increments quantity
  //       Inserts "first" in order with no duplicates
  // Preconditions: Requires a LL.
  // Postconditions: Node inserted in LL based on first value (or quantity incremented)
  void Insert(const T& item){
    Node<T>* newNode = new Node<T>(item);
    Node<T>* curr = m_head;
    Node<T>* prev = nullptr;
    
    //loop through LL until the end or the previous value is greater than the value you want to insert
    while(curr != nullptr and curr -> GetData().first < newNode->GetData().first){
      prev = curr;
      curr = curr -> GetNext();
    }
    //checks if item doesnt exit in the LL
    if (Find(newNode->GetData().first) == nullptr){
      if (prev == nullptr){
        newNode -> SetNext(m_head);
        m_head = newNode;
      }else{
        // set the new node next to point to point to curr, 
        // therefore inserting it in the middle of prev and curr
        prev->SetNext(newNode);
        newNode->SetNext(curr);
      }
      m_size++;
    }else{
      // if item exist, keep looping till you get to the node, then increase the node
      while(curr != Find(newNode->GetData().first)){
        curr = curr -> GetNext();
      }
      // delete the node that was made since the word already exist in the linked list
      delete newNode;
      // increase the frequency
      curr -> GetData().second += 1;
    }
  }
  // Name: RemoveAt
  // Desc: Removes a node at a particular position based on data passed (matches first)
  // Preconditions: LL with at least one node. 
  // Postconditions: Removes first node with passed value (in first)
  void RemoveAt(const T& item){
    if (m_head == nullptr){
      cout << "The linked list is empty\n";
    }else if (m_head-> GetData().first == item){
      // checks if LL consist of only one node
      Node<T>* temp = m_head;
      m_head = m_head -> GetNext();
      delete temp;
      m_size--;
    }else{
      Node<T>* curr = m_head;
      Node<T>* prev = nullptr;
      // loop till you node isnt found or the item is found
      while (curr != nullptr and curr ->GetData().first != item){
        prev = curr;
        curr = curr -> GetNext();
      }
      if (curr != nullptr){
        // sets the prev to point to the curr next to avoid data loss
        prev->SetNext(curr->GetNext());
        delete curr;
        m_size--;
      }
    }
  }
  // Name: Display
  // Desc: Display all nodes in linked list
  // Preconditions: Outputs the LL
  // Postconditions: Displays the pair in each node of LL 
  void Display(){
    cout << *this;
    cout << "END" << endl;
  }
  // Name: GetSize
  // Desc: Returns the size of the LL
  // Preconditions: Requires a LL
  // Postconditions: Returns m_size
  int GetSize(){
    return m_size;
  }
  // Name: operator<< (Overloaded << operator)
  // Desc: Returns the ostream of the data in each node
  // Preconditions: Requires a LL
  // Postconditions: Returns an ostream with the data from each node on different line
  template <class U>
  friend ostream& operator<<(ostream& output, const LL<U>& nodeList){
    Node<T>* curr = nodeList.m_head;
    if (nodeList.m_head == nullptr){
      output << "Empty linked list\n";
    }else{
      while(curr != nullptr){
        output << curr -> GetData().first << ":" << curr-> GetData().second << endl;
        curr = curr -> GetNext();
      }
    }
    return output;
  }
  // Name: Overloaded [] operator
  // Desc: When passed an integer, returns the data at that location
  // Precondition: Existing LL
  // Postcondition: Returns pair from LL using []
  //Overloaded [] operator to pull data from LL
  pair<T,int>& operator[] (int x){
    int i = 0;
    Node<T>* curr = m_head;
    // increments i while its not = to the index we need
    while(curr != nullptr and i != x){
      curr = curr ->GetNext();
      i++;
    }
    return curr-> GetData();
  }
private:
  Node <T> *m_head; //Node pointer for the head
  int m_size; //Number of nodes in queue
};
//*****************************************************************
