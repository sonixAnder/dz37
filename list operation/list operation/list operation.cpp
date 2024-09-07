#include <iostream>
using namespace std;

template <typename T>
struct Node
{
    T data;
    Node* next;

    Node(T data) : data(data), next(nullptr) {}
};

template <typename T>
class LinkedList
{
private:
    Node<T>* head;

public:
    LinkedList() : head(nullptr) {}

    void insertAtBeginning(const T& data);
    void print() const;

    LinkedList<T>* clone() const;
    LinkedList<T>* operator+(const LinkedList<T>& other) const;
    LinkedList<T>* operator*(const LinkedList<T>& other) const;

private:
    bool find(const T& data) const;
};


template <typename T>
void LinkedList<T>::insertAtBeginning(const T& data)
{
    Node<T>* newNode = new Node<T>(data);
    newNode->next = head;
    head = newNode;
}

template <typename T>
void LinkedList<T>::print() const
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
LinkedList<T>* LinkedList<T>::clone() const
{
    LinkedList<T>* newLinkedList = new LinkedList<T>();
    Node<T>* current = head;
    while (current != nullptr) {
        newLinkedList->insertAtBeginning(current->data);
        current = current->next;
    }
    return newLinkedList;
}

template <typename T>
LinkedList<T>* LinkedList<T>::operator+(const LinkedList<T>& other) const
{
    LinkedList<T>* newList = new LinkedList<T>();
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
LinkedList<T>* LinkedList<T>::operator*(const LinkedList<T>& other) const
{
    LinkedList<T>* newList = new LinkedList<T>();
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
bool LinkedList<T>::find(const T& data) const
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
    LinkedList<int> list1;
    list1.insertAtBeginning(3);
    list1.insertAtBeginning(2);
    list1.insertAtBeginning(1);

    LinkedList<int> list2;
    list2.insertAtBeginning(5);
    list2.insertAtBeginning(4);
    list2.insertAtBeginning(3);

    cout << "List1: ";
    list1.print();

    cout << "List2: ";
    list2.print();

    LinkedList<int>* clonedList = list1.clone();
    cout << "Cloned List: ";
    clonedList->print();

    LinkedList<int>* sumList = list1 + list2;
    cout << "Sum List: ";
    sumList->print();

    LinkedList<int>* intersectionList = list1 * list2;
    cout << "Intersection List: ";
    intersectionList->print();

    return 0;
}
