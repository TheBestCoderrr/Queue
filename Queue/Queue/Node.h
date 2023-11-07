#pragma once
#include <iostream>
using namespace std;

template<class T>
class Node
{
public:
    explicit    Node(T v, Node* n = nullptr) :value(v), next(n) {};
    T getValue() const { return value; }
    void setValue(T v) { value = v; }
    Node* getNext() const { return next; }
    void setNext(Node* n) { next = n; }
private:
    T value;
    Node* next;
};

template<class T>
ostream& operator<<(ostream& out, const Node<T>& node) {
    out << node.getValue() << endl;
    return out;
}