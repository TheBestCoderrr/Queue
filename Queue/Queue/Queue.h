#pragma once
#include "Node.h"

template<class T>
class Queue {
public:
    Queue();
    ~Queue();
    Queue(const Queue<T>& other);
    bool IsEmpty();
    bool IsFull();
    void Enqueue(T v);
    void Dequeue();
    void clear();
    T front() const;
    T back() const;
    Queue& operator=(const Queue<T>& other);
private:
    Node<T>* head;
    Node<T>* tail;
    size_t counter;
template<class T> friend ostream& operator<<(ostream& out, const Queue<T>& queue);
};

template<class T>
Queue<T>::Queue() : head(nullptr), tail(nullptr), counter(0) {}

template<class T>
Queue<T>::~Queue() { clear(); }

template<class T>
Queue<T>::Queue(const Queue<T>& other) : Queue() { *this = other; }

template<class T>
void Queue<T>::Enqueue(T v)
{
    Node<T>* temp = new Node<T>(v);
    if (tail)
        tail->setNext(temp);
    else
        head = temp;
    tail = temp;
    ++counter;
}

template<class T>
void Queue<T>::Dequeue()
{
    if (!head) return;
    Node<T>* temp = head;
    head = head->getNext();
    delete temp;
    if (!head) tail = nullptr;
    --counter;
}

template<class T>
void Queue<T>::clear() { while (head) Dequeue(); }

template<class T>
bool Queue<T>::IsEmpty() { return counter == 0; }

template<class T>
bool Queue<T>::IsFull() { return counter != 0; }

template<class T>
T Queue<T>::front() const { return head->getValue(); }

template<class T>
T Queue<T>::back() const { return tail->getValue(); }

template<class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other)
{
    if (this == &other) return *this;
    clear();
    Node<T>* cur = other.head;
    while (cur) {
        Enqueue(cur->getValue());
        cur = cur->getNext();
    }
    return *this;
}

template<class T>
ostream& operator<<(ostream& out, const Queue<T>& queue){
    Node<T>* cur = queue.head;
    while (cur) {
        out << cur->getValue() << '\t';
        cur = cur->getNext();
    }
    return out;
}