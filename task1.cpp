#include <iostream>
#include <vector>
#include <deque>

using namespace std;

class Stack {
private:
    vector<int> data;

public:
    Stack& operator+=(int value) {
        data.push_back(value);
        return *this;
    }

    Stack& operator-=(int) {
        if (!data.empty()) data.pop_back();
        return *this;
    }

    bool operator==(const Stack& other) const {
        return data == other.data;
    }

    bool operator!=(const Stack& other) const {
        return !(*this == other);
    }

    Stack& operator=(const Stack& other) {
        if (this != &other) data = other.data;
        return *this;
    }

    Stack operator+(const Stack& other) const {
        Stack result = *this;
        result.data.insert(result.data.end(), other.data.begin(), other.data.end());
        return result;
    }

    void print() const {
        cout << "Stack: ";
        for (int val : data) cout << val << " ";
        cout << endl;
    }
};

class Queue {
private:
    deque<int> data;

public:
    Queue& operator+=(int value) {
        data.push_back(value);
        return *this;
    }

    Queue& operator-=(int) {
        if (!data.empty()) data.pop_front();
        return *this;
    }

    bool operator==(const Queue& other) const {
        return data == other.data;
    }

    bool operator!=(const Queue& other) const {
        return !(*this == other);
    }

    Queue& operator=(const Queue& other) {
        if (this != &other) data = other.data;
        return *this;
    }

    Queue operator+(const Queue& other) const {
        Queue result = *this;
        result.data.insert(result.data.end(), other.data.begin(), other.data.end());
        return result;
    }

    void print() const {
        cout << "Queue: ";
        for (int val : data) cout << val << " ";
        cout << endl;
    }
};

class SinglyLinkedList {
private:
    struct Node {
        int value;
        Node* next;
        Node(int val) : value(val), next(nullptr) {}
    };

    Node* head;

public:

    SinglyLinkedList() : head(nullptr) {}
    

    ~SinglyLinkedList() { clear(); }


    SinglyLinkedList(const SinglyLinkedList& other) : head(nullptr) {
        Node* current = other.head;
        while (current) {
            *this += current->value;
            current = current->next;
        }
    }


    SinglyLinkedList& operator=(const SinglyLinkedList& other) {
        if (this != &other) {
            clear();  // Clear existing nodes
            Node* current = other.head;
            while (current) {
                *this += current->value;
                current = current->next;
            }
        }
        return *this;
    }


    SinglyLinkedList& operator+=(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next) current = current->next;
            current->next = newNode;
        }
        return *this;
    }


    SinglyLinkedList& operator-=(int) {
        if (!head) return *this;
        if (!head->next) {
            delete head;
            head = nullptr;
        } else {
            Node* current = head;
            while (current->next && current->next->next) current = current->next;
            delete current->next;
            current->next = nullptr;
        }
        return *this;
    }


    bool operator==(const SinglyLinkedList& other) const {
        Node* current1 = head;
        Node* current2 = other.head;
        while (current1 && current2) {
            if (current1->value != current2->value) return false;
            current1 = current1->next;
            current2 = current2->next;
        }
        return current1 == nullptr && current2 == nullptr;
    }


    bool operator!=(const SinglyLinkedList& other) const {
        return !(*this == other);
    }


    SinglyLinkedList operator+(const SinglyLinkedList& other) const {
        SinglyLinkedList result = *this;
        Node* current = other.head;
        while (current) {
            result += current->value;
            current = current->next;
        }
        return result;
    }


    void print() const {
        cout << "SinglyLinkedList: ";
        Node* current = head;
        while (current) {
            cout << current->value << " ";
            current = current->next;
        }
        cout << endl;
    }

private:

    void clear() {
        Node* current = head;
        while (current) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        head = nullptr;
    }
};

int main() {

    Stack stack1, stack2;
    stack1 += 10;
    stack1 += 20;
    stack2 += 30;
    stack2 += 40;

    Stack stack3 = stack1 + stack2;
    stack3.print();
    stack3 -= 1;
    stack3.print();


    Queue queue1, queue2;
    queue1 += 1;
    queue1 += 2;
    queue2 += 3;
    queue2 += 4;

    Queue queue3 = queue1 + queue2;
    queue3.print();
    queue3 -= 1;
    queue3.print();


    SinglyLinkedList list1, list2;
    list1 += 5;
    list1 += 6;
    list2 += 7;
    list2 += 8;

    SinglyLinkedList list3 = list1 + list2;
    list3.print();
    list3 -= 1;
    list3.print();

    return 0;
}