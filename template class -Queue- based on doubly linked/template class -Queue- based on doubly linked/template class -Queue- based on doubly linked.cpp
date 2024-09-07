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
class Queue
{
private:
    Node<T>* front;
    Node<T>* rear;
    int size;

public:
    Queue() : front(nullptr), rear(nullptr), size(0) {}

    bool isEmpty() const { return front == nullptr; }

    void enqueue(const T& data)
    {
        Node<T>* newNode = new Node<T>(data);
        if (isEmpty())
        {
            front = rear = newNode;
        }
        else {
            rear->next = newNode;
            newNode->prev = rear;
            rear = newNode;
        }
        size++;
    }

    T dequeue()
    {
        if (isEmpty())
        {
            cout << "Queue is empty!" << endl;
            return T(); // Возвращаем значение по умолчанию
        }

        T value = front->data;
        Node<T>* temp = front;
        front = front->next;

        if (front != nullptr)
        {
            front->prev = nullptr;
        }
        else
        {
            rear = nullptr;
        }

        delete temp;
        size--;
        return value;
    }

    T peek() const
    {
        if (isEmpty())
        {
            cout << "Queue is empty!" << endl;
            return T(); // Возвращаем значение по умолчанию
        }
        return front->data;
    }

    int getSize() const { return size; }

    void print() const
    {
        Node<T>* current = front;
        cout << "Queue: ";
        while (current != nullptr)
        {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

int main()
{
    Queue<int> myQueue;

    myQueue.enqueue(10);
    myQueue.enqueue(20);
    myQueue.enqueue(30);

    myQueue.print(); // Вывод: Queue: 10 20 30

    cout << "Front element: " << myQueue.peek() << endl; // Вывод: Front element: 10

    cout << "Dequeued: " << myQueue.dequeue() << endl; // Вывод: Dequeued: 10

    myQueue.print(); // Вывод: Queue: 20 30

    cout << "Size: " << myQueue.getSize() << endl; // Вывод: Size: 2

    return 0;
}
