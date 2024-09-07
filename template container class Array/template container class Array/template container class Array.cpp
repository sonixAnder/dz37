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
class Array
{
private:
    Node<T>* head;
    int size;
    int growFactor;
    int usedSize;

public:
    Array() : head(nullptr), size(0), growFactor(1), usedSize(0) {}

    Array(int initialSize, int grow = 1) : head(nullptr), size(initialSize), growFactor(grow), usedSize(0)
    {
        if (size > 0)
        {
            head = new Node<T>(T()); // Инициализация первого элемента
            usedSize = 1;
            Node<T>* current = head;
            for (int i = 1; i < size; ++i)
            {
                current->next = new Node<T>(T());
                current->next->prev = current;
                current = current->next;
                usedSize++;
            }
        }
    }

    ~Array()
    {
        RemoveAll();
    }

    int GetSize() const { return size; }

    void SetSize(int newSize, int grow = 1)
    {
        if (newSize < size)
        {
            Node<T>* current = head;
            while (current != nullptr && usedSize > newSize)
            {
                Node<T>* temp = current;
                current = current->next;
                delete temp;
                usedSize--;
            }
            if (current != nullptr)
            {
                current->prev = nullptr;
            }
            head = current;
        }
        else if (newSize > size)
        {
            Node<T>* current = head;
            for (int i = size; i < newSize; ++i)
            {
                current->next = new Node<T>(T());
                current->next->prev = current;
                current = current->next;
                size++;
            }
        }
        size = newSize;
        growFactor = grow;
    }

    int GetUpperBound() const { return usedSize - 1; }

    bool IsEmpty() const { return usedSize == 0; }

    void FreeExtra()
    {
        if (usedSize < size)
        {
            Node<T>* current = head;
            while (current != nullptr && usedSize < size)
            {
                Node<T>* temp = current;
                current = current->next;
                delete temp;
                size--;
            }
            if (current != nullptr)
            {
                current->prev = nullptr;
            }
            head = current;
        }
    }

    void RemoveAll()
    {
        Node<T>* current = head;
        while (current != nullptr)
        {
            Node<T>* temp = current;
            current = current->next;
            delete temp;
        }
        head = nullptr;
        size = 0;
        usedSize = 0;
    }

    T& GetAt(int index)
    {
        if (index < 0 || index >= usedSize)
        {
            cerr << "Invalid index!" << endl;
            throw out_of_range("Index out of range");
        }

        Node<T>* current = head;
        for (int i = 0; i < index; ++i)
        {
            current = current->next;
        }
        return current->data;
    }

    void SetAt(int index, const T& value)
    {
        if (index < 0 || index >= usedSize)
        {
            cerr << "Invalid index!" << endl;
            throw out_of_range("Index out of range");
        }

        Node<T>* current = head;
        for (int i = 0; i < index; ++i)
        {
            current = current->next;
        }
        current->data = value;
    }

    T& operator[](int index)
    {
        return GetAt(index);
    }

    const T& operator[](int index) const
    {
        return GetAt(index);
    }

    void Add(const T& value)
    {
        if (usedSize >= size)
        {
            SetSize(size + growFactor);
        }

        Node<T>* current = head;
        while (current->next != nullptr)
        {
            current = current->next;
        }

        current->next = new Node<T>(value);
        current->next->prev = current;
        usedSize++;
    }

    void Append(const Array& other)
    {
        Node<T>* current = head;
        while (current->next != nullptr)
        {
            current = current->next;
        }

        Node<T>* otherCurrent = other.head;
        while (otherCurrent != nullptr)
        {
            current->next = new Node<T>(otherCurrent->data);
            current->next->prev = current;
            current = current->next;
            otherCurrent = otherCurrent->next;
            usedSize++;
        }
    }

    Array& operator=(const Array& other)
    {
        if (this != &other)
        {
            RemoveAll();
            SetSize(other.size, other.growFactor);
            Node<T>* otherCurrent = other.head;
            Node<T>* current = head;
            while (otherCurrent != nullptr)
            {
                current->data = otherCurrent->data;
                current = current->next;
                otherCurrent = otherCurrent->next;
                usedSize++;
            }
        }
        return *this;
    }

    T* GetData()
    {
        if (IsEmpty())
        {
            return nullptr;
        }
        Node<T>* current = head;
        T* data = new T[usedSize];
        for (int i = 0; i < usedSize; ++i)
        {
            data[i] = current->data;
            current = current->next;
        }
        return data;
    }

    void InsertAt(int index, const T& value)
    {
        if (index < 0 || index > usedSize)
        {
            cerr << "Invalid index!" << endl;
            throw out_of_range("Index out of range");
        }

        if (index == usedSize)
        {
            Add(value);
        }
        else {
            Node<T>* current = head;
            for (int i = 0; i < index; ++i)
            {
                current = current->next;
            }

            Node<T>* newNode = new Node<T>(value);
            newNode->next = current;
            newNode->prev = current->prev;
            if (current->prev != nullptr)
            {
                current->prev->next = newNode;
            }
            else
            {
                head = newNode;
            }
            current->prev = newNode;
            usedSize++;
        }
    }

    void RemoveAt(int index)
    {
        if (index < 0 || index >= usedSize)
        {
            cerr << "Invalid index!" << endl;
            throw out_of_range("Index out of range");
        }

        Node<T>* current = head;
        for (int i = 0; i < index; ++i)
        {
            current = current->next;
        }

        if (current->prev != nullptr)
        {
            current->prev->next = current->next;
        }
        else
        {
            head = current->next;
        }

        if (current->next != nullptr)
        {
            current->next->prev = current->prev;
        }

        delete current;
        usedSize--;
    }
};

int main()
{
    Array<int> arr(5, 3);

    cout << "Size: " << arr.GetSize() << endl;
    cout << "Upper Bound: " << arr.GetUpperBound() << endl;

    arr.Add(1);
    arr.Add(2);
    arr.Add(3);
    arr.Add(4);

    cout << "Size: " << arr.GetSize() << endl;
    cout << "Upper Bound: " << arr.GetUpperBound() << endl;

    arr.Add(5);
    cout << "Size: " << arr.GetSize() << endl;
    cout << "Upper Bound: " << arr.GetUpperBound() << endl;

    cout << "Array: ";
    for (int i = 0; i <= arr.GetUpperBound(); ++i)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    arr.RemoveAt(2);
    cout << "Array: ";
    for (int i = 0; i <= arr.GetUpperBound(); ++i)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
