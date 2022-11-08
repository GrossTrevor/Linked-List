#pragma once
#include <iostream>
#include <vector>
using namespace std;
template <typename T>

class LinkedList {
public:
    struct Node {
        Node* next = nullptr;
        Node* prev = nullptr;
        T data;
    };

    LinkedList() {
        numNodes = 0;
        head = nullptr;
        tail = nullptr;
    }

    ~LinkedList() {
        Clear();
    }

    Node* createIterator() {
        iterator = Head();
        return iterator;
    }

    void AddHead(const T& dat) {
        Node* tempH = new Node();
        tempH->data = dat;
        tempH->next = nullptr;
        tempH->prev = nullptr;

        if (head == nullptr) {
            head = tempH;
            tail = tempH;
            head->next = nullptr;
            head->prev = nullptr;
        }
        else {
            head->prev = tempH;
            if (numNodes == 1)
                tail->prev = tempH;
            tempH->next = head;
            head = tempH;
        }
        numNodes++;
        tempH = nullptr;
    }

    void AddTail(const T& dat) {
        Node* tempL = new Node();
        tempL->data = dat;
        tempL->next = nullptr;
        tempL->prev = nullptr;

        if (tail == nullptr) {
            head = tempL;
            tail = tempL;
            tail->next = nullptr;
            tail->prev = nullptr;
        }
        else {
            tail->next = tempL;
            if (numNodes == 1)
                head->next = tempL;
            tempL->prev = tail;
            tail = tempL;
        }
        numNodes++;
        tempL = nullptr;
    }

    void AddNodesHead(const T* dat, unsigned int count) {
        for (int x = (int)count - 1; x >= 0; x--)
            AddHead(dat[x]);
    }

    void AddNodesTail(const T* dat, unsigned int count) {
        for (unsigned int x = 0; x < count; x++)
            AddTail(dat[x]);
    }

    unsigned int NodeCount() const {
        return numNodes;
    }

    void PrintForward() const {
        Node* iterator = head;
        while (iterator != nullptr) {
            cout << iterator->data << endl;
            iterator = iterator->next;
        }
    }
    void PrintReverse() const {
        Node* iterator = tail;
        while (iterator != nullptr) {
            cout << iterator->data << endl;
            iterator = iterator->prev;
        }
    }

    Node* Head() {
        return head;
    }

    const Node* Head() const {
        return head;
    }

    Node* Tail() {
        return tail;
    }

    const Node* Tail() const {
        return tail;
    }

    void Clear() {
        Node* temp = head;
        Node* tempNext;
        for (unsigned int x = 0; x < numNodes; x++) {
            tempNext = temp->next;
            delete temp;
            temp = tempNext;
        }
        numNodes = 0;
        head = nullptr;
        tail = nullptr;
    }

    Node* GetNode(unsigned int index) {
        Node* temp = head;
        if (index > numNodes)
            throw "out_of_range";
        else {
            for (unsigned int x = 0; x < index; x++) {
                temp = temp->next;
            }
        }
        return temp;
    }

    const Node* GetNode(unsigned int index) const {
        Node* temp = head;
        if (index > numNodes)
            throw "out_of_range";
        else {
            for (unsigned int x = 0; x < index; x++) {
                temp = temp->next;
            }
        }
        return temp;
    }

    T& operator[](unsigned int index) {
        Node* temp = head;
        if (index > numNodes)
            throw "out_of_range";
        else {
            for (unsigned int x = 0; x < index; x++) {
                temp = temp->next;
            }
        }
        return temp->data;
    }

    const T& operator[](unsigned int index) const {
        Node* temp = head;
        if (index > numNodes)
            throw "out_of_range";
        else {
            for (unsigned int x = 0; x < index; x++) {
                temp = temp->next;
            }
        }
        return temp->data;
    }

    void FindAll(vector<Node*>& outData, const T& value) const {
        Node* iterator = head;
        for (unsigned int x = 0; x < numNodes; x++) {
            if (iterator->data == value) {
                outData.push_back(iterator);
            }
            iterator = iterator->next;
        }
        iterator = nullptr;
    }

    Node* Find(const T& dat) {
        Node* iterator = head;
        for (unsigned int x = 0; x < numNodes; x++) {
            if (iterator->data == dat)
                return iterator;
            iterator = iterator->next;
        }
        return nullptr;
    }

    const Node* Find(const T& dat) const {
        Node* iterator = head;
        for (unsigned int x = 0; x < numNodes; x++) {
            if (iterator->data == dat)
                return iterator;
            iterator = iterator->next;
        }
        return nullptr;
    }

    LinkedList<T>& operator=(const LinkedList<T>& rhs) {
        numNodes = 0;
        for (unsigned int x = 0; x < rhs.NodeCount(); x++) {
            AddTail(rhs.GetNode(x)->data);
        }
        return *this;
    }

    LinkedList(const LinkedList<T>& list) {
        numNodes = 0;
        for (unsigned int x = 0; x < list.NodeCount(); x++) {
            AddTail(list.GetNode(x)->data);
        }
    }

    void InsertAt(const T& dat, unsigned int index) {
        if (index > numNodes)
            throw "out_of_range";
        else if (index == 0)
            AddHead(dat);
        else if (index == numNodes)
            AddTail(dat);
        else {
            Node* temp = new Node();
            temp->data = dat;
            iterator = createIterator();
            for (unsigned int x = 0; x < index; x++)
                iterator = iterator->next;
            temp->prev = iterator->prev;
            temp->next = iterator;
            iterator->prev->next = temp;
            iterator->prev = temp;
            numNodes++;
        }
    }

    void InsertAfter(Node* node, const T& dat) {
        Node* temp = new Node();
        temp->data = dat;
        temp->next = node->next;
        temp->prev = node;
        node->next->prev = temp;
        node->next = temp;
        numNodes++;
    }

    void InsertBefore(Node* node, const T& dat) {
        Node* temp = new Node();
        temp->data = dat;
        temp->prev = node->prev;
        temp->next = node;
        node->prev->next = temp;
        node->prev = temp;
        numNodes++;
    }

    bool operator==(const LinkedList<T>& rhs) const {
        Node* iterator = head;
        if (numNodes != rhs.numNodes)
            return false;
        for (unsigned int x = 0; x < numNodes; x++) {
            if (iterator->data != rhs.GetNode(x)->data)
                return false;
        }
        return true;
    }

    bool RemoveHead() {
        if (head == nullptr) {
            return false;
        }
        else if (head->next == nullptr) {
            Node* temp = head;
            delete temp;
            head = nullptr;
            tail = nullptr;
            numNodes--;
            return true;
        }
        else {
            Node* temp = head;
            head->next->prev = nullptr;
            head = head->next;
            delete temp;
            numNodes--;
            return true;
        }
    }

    bool RemoveTail() {
        if (tail == nullptr) {
            return false;
        }
        else if (tail->prev == nullptr) {
            Node* temp = tail;
            delete temp;
            tail = nullptr;
            head = nullptr;
            numNodes--;
            return true;
        }
        else {
            Node* temp = tail;
            tail->prev->next = nullptr;
            tail = tail->prev;
            delete temp;
            numNodes--;
            return true;
        }
    }

    bool RemoveAt(unsigned int index) {
        if (index > numNodes) {
            return false;
        }
        else {
            iterator = createIterator();
            unsigned int indexCounter = 0;
            while (indexCounter != index) {
                iterator = iterator->next;
                indexCounter++;
            }
            if (iterator->prev == nullptr) {
                iterator->next->prev = nullptr;
            }
            else if (iterator->next == nullptr) {
                iterator->prev->next = nullptr;
            }
            else {
                iterator->prev->next = iterator->next;
                iterator->next->prev = iterator->prev;
            }
            delete iterator;
            numNodes--;
            return true;
        }
    }

    unsigned int Remove(const T& data) {
        unsigned int removed = 0;
        Node* iterator = head;
        Node* temp;

        while (iterator != nullptr) {
            temp = iterator->next;
            if (iterator->data == data) {
                if (iterator->prev == nullptr) {
                    iterator->next->prev = nullptr;
                }
                else if (iterator->next == nullptr) {
                    iterator->prev->next = nullptr;
                }
                else {
                    iterator->prev->next = iterator->next;
                    iterator->next->prev = iterator->prev;
                }
                delete iterator;
                removed++;
            }
            iterator = temp;
        }
        numNodes -= removed;
        return removed;
    }

    void PrintForwardRecursive(const Node* node) {
        cout << node->data << endl;
        if (node->next != nullptr)
            PrintForwardRecursive(node->next);
    }

    void PrintReverseRecursive(const Node* node) {
        cout << node->data << endl;
        if (node->prev != nullptr)
            PrintReverseRecursive(node->prev);
    }

private:
    unsigned int numNodes;
    Node* head = nullptr;
    Node* tail = nullptr;
    Node* iterator;
};