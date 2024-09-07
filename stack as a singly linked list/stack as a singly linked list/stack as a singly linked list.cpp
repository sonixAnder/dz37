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
class Stack
{
private:
    Node<T>* top;
    int size;

public:
    Stack() : top(nullptr), size(0) {}

    bool isEmpty() const { return top == nullptr; }

    void push(const T& data)
    {
        Node<T>* newNode = new Node<T>(data);
        newNode->next = top;
        top = newNode;
        size++;
    }

    void pop()
    {
        if (isEmpty())
        {
            cout << "Stack is empty!" << endl;
            return;
        }

        Node<T>* temp = top;
        top = top->next;
        delete temp;
        size--;
    }

    T peek() const
    {
        if (isEmpty())
        {
            cout << "Stack is empty!" << endl;
            return T(); // Возвращаем значение по умолчанию
        }
        return top->data;
    }

    int getSize() const { return size; }

    void print() const
    {
        Node<T>* current = top;
        cout << "Stack: ";
        while (current != nullptr)
        {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    // Увеличиваем размер стека, переместив элементы в новый список
    void resize(int newSize)
    {
        if (newSize <= size)
        {
            return; // Новый размер не должен быть меньше текущего
        }

        Node<T>* oldTop = top;
        Node<T>* newTop = nullptr;
        int oldSize = size;

        // Перемещаем элементы в новый список
        for (int i = 0; i < oldSize; i++)
        {
            T data = oldTop->data;
            push(data);
            oldTop = oldTop->next;
        }

        // Удаляем старый список
        while (oldTop != nullptr)
        {
            Node<T>* temp = oldTop;
            oldTop = oldTop->next;
            delete temp;
        }

        size = newSize;
    }
};

int main()
{
    Stack<int> myStack;

    myStack.push(10);
    myStack.push(20);
    myStack.push(30);

    myStack.print(); // Вывод: Stack: 30 20 10

    cout << "Top element: " << myStack.peek() << endl; // Вывод: Top element: 30

    myStack.pop();
    myStack.print(); // Вывод: Stack: 20 10

    cout << "Size: " << myStack.getSize() << endl; // Вывод: Size: 2

    myStack.resize(5); // Увеличиваем размер стека до 5
    cout << "Size after resize: " << myStack.getSize() << endl; // Вывод: Size after resize: 5

    myStack.push(40); // Добавляем новый элемент
    myStack.push(50); // Добавляем новый элемент
    myStack.print(); // Вывод: Stack: 50 40 20 10 0

    return 0;
}
