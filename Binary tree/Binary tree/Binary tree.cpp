#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Violation
{
    string date;
    string description;
    int amount;
};

struct Node
{
    string carNumber;
    vector<Violation> violations;
    Node* left;
    Node* right;

    Node(const string& carNumber) : carNumber(carNumber), left(nullptr), right(nullptr) {}
};

class TrafficDatabase
{
private:
    Node* root;

    Node* insert(Node* node, const string& carNumber, const Violation& violation)
    {
        if (node == nullptr)
        {
            return new Node(carNumber);
        }

        if (carNumber < node->carNumber)
        {
            node->left = insert(node->left, carNumber, violation);
        }
        else if (carNumber > node->carNumber)
        {
            node->right = insert(node->right, carNumber, violation);
        }
        else
        {
            node->violations.push_back(violation);
        }
        return node;
    }

    void printInOrder(Node* node) const
    {
        if (node != nullptr)
        {
            printInOrder(node->left);
            cout << "Номер машины: " << node->carNumber << endl;
            for (const Violation& violation : node->violations)
            {
                cout << " Дата: " << violation.date << endl;
                cout << " Описание: " << violation.description << endl;
                cout << " Сумма: " << violation.amount << endl;
            }
            printInOrder(node->right);
        }
    }

    Node* findNode(Node* node, const string& carNumber) const
    {
        if (node == nullptr || node->carNumber == carNumber)
        {
            return node;
        }

        if (carNumber < node->carNumber)
        {
            return findNode(node->left, carNumber);
        }
        else
        {
            return findNode(node->right, carNumber);
        }
    }

    void printRange(Node* node, const std::string& start, const std::string& end) const
    {
        if (node == nullptr)
        {
            return;
        }

        if (start <= node->carNumber && node->carNumber <= end)
        {
            printInOrder(node);
        }

        if (start < node->carNumber)
        {
            printRange(node->left, start, end);
        }

        if (end > node->carNumber)
        {
            printRange(node->right, start, end);
        }
    }

public:
    TrafficDatabase() : root(nullptr) {}

    void addViolation(const std::string& carNumber, const Violation& violation)
    {
        root = insert(root, carNumber, violation);
    }

    void printAll() const
    {
        cout << "Полная база данных:\n";
        printInOrder(root);
    }

    void printByCarNumber(const string& carNumber) const
    {
        Node* node = findNode(root, carNumber);
        if (node != nullptr)
        {
            cout << "Информация по машине " << carNumber << ":\n";
            for (const Violation& violation : node->violations)
            {
                cout << " Дата: " << violation.date << endl;
                cout << " Описание: " << violation.description << endl;
                cout << " Сумма: " << violation.amount << endl;
            }
        }
        else
        {
            cout << "Машина с номером " << carNumber << " не найдена.\n";
        }
    }

    void printByCarNumberRange(const string& start, const string& end) const
    {
        cout << "Информация по машинам в диапазоне " << start << " - " << end << ":\n";
        printRange(root, start, end);
    }
};

int main()
{
    setlocale(LC_ALL, "ru");
    TrafficDatabase database;

    Violation v1 = { "2023-10-26", "Превышение скорости", 1000 };
    database.addViolation("A123BB", v1);

    Violation v2 = { "2023-10-27", "Проезд на красный свет", 1500 };
    database.addViolation("A123BB", v2);

    Violation v3 = { "2023-10-28", "Неправильная парковка", 500 };
    database.addViolation("B456CC", v3);

    database.printAll();

    cout << "\nИнформация по машине A123BB:\n";
    database.printByCarNumber("A123BB");

    cout << "\nИнформация по машинам в диапазоне A123BB - B456CC:\n";
    database.printByCarNumberRange("A123BB", "B456CC");

    return 0;
}
