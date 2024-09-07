#include <iostream>
using namespace std;

template <typename T>
struct Node
{
    T data;
    Node* prev;
    Node* next;

    Node(T data) : data(data), prev(nullptr), next(nullptr) {}
};

template <typename T>
class DoublyLinkedList
{
private:
    Node<T>* head;

public:
    DoublyLinkedList() : head(nullptr) {}

    void insertAtBeginning(const T& data);
    void print() const;

    DoublyLinkedList<T>* clone() const;
    DoublyLinkedList<T>* operator+(const DoublyLinkedList<T>& other) const;
    DoublyLinkedList<T>* operator*(const DoublyLinkedList<T>& other) const;

private:
    bool find(const T& data) const;
};


template <typename T>
void DoublyLinkedList<T>::insertAtBeginning(const T& data)
{
    Node<T>* newNode = new Node<T>(data);
    if (head == nullptr)
    {
        head = newNode;
    }
    else
    {
        head->prev = newNode;
        newNode->next = head;
        head = newNode;
    }
}

template <typename T>
void DoublyLinkedList<T>::print() const
{
    Node<T>* current = head;
    while (current != nullptr)
    {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

template <typename T>
DoublyLinkedList<T>* DoublyLinkedList<T>::clone() const
{
    DoublyLinkedList<T>* newLinkedList = new DoublyLinkedList<T>();
    Node<T>* current = head;
    while (current != nullptr)
    {
        newLinkedList->insertAtBeginning(current->data);
        current = current->next;
    }
    return newLinkedList;
}

template <typename T>
DoublyLinkedList<T>* DoublyLinkedList<T>::operator+(const DoublyLinkedList<T>& other) const
{
    DoublyLinkedList<T>* newList = new DoublyLinkedList<T>();
    Node<T>* current = head;
    while (current != nullptr)
    {
        newList->insertAtBeginning(current->data);
        current = current->next;
    }

    current = other.head;
    while (current != nullptr)
    {
        newList->insertAtBeginning(current->data);
        current = current->next;
    }

    return newList;
}

template <typename T>
DoublyLinkedList<T>* DoublyLinkedList<T>::operator*(const DoublyLinkedList<T>& other) const
{
    DoublyLinkedList<T>* newList = new DoublyLinkedList<T>();
    Node<T>* current = head;
    while (current != nullptr)
    {
        if (other.find(current->data))
        {
            newList->insertAtBeginning(current->data);
        }
        current = current->next;
    }
    return newList;
}

template <typename T>
bool DoublyLinkedList<T>::find(const T& data) const
{
    Node<T>* current = head;
    while (current != nullptr)
    {
        if (current->data == data)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

int main() 
{
    DoublyLinkedList<int> list1;
    list1.insertAtBeginning(3);
    list1.insertAtBeginning(2);
    list1.insertAtBeginning(1);

    DoublyLinkedList<int> list2;
    list2.insertAtBeginning(5);
    list2.insertAtBeginning(4);
    list2.insertAtBeginning(3);

    cout << "List1: ";
    list1.print();

    cout << "List2: ";
    list2.print();

    DoublyLinkedList<int>* clonedList = list1.clone();
    cout << "Cloned List: ";
    clonedList->print();

    DoublyLinkedList<int>* sumList = list1 + list2;
    cout << "Sum List: ";
    sumList->print();

    DoublyLinkedList<int>* intersectionList = list1 * list2;
    cout << "Intersection List: ";
    intersectionList->print();

    return 0;
}
