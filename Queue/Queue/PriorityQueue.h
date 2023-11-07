#pragma once
#include "Node.h"

template<class T>
class PriorityQueue {
public:
    PriorityQueue();
    ~PriorityQueue();
    PriorityQueue(const PriorityQueue<T>& other);
    bool IsEmpty();
    bool IsFull();
    void InsertFront(T v);
    void InsertBack(T v);
    void InsertWithPriority(T v);
    void PullBack();
    void PullFront();
    void PullHighestPriorityElement();
    void clear();
    T front() const;
    T back() const;
    T Peek() const;
    PriorityQueue& operator=(const PriorityQueue<T>& other);
private:
    Node<T>* head;
    Node<T>* tail;
    size_t counter;
template<class T> friend ostream& operator<<(ostream& out, const PriorityQueue<T>& queue);
};

template<class T>
PriorityQueue<T>::PriorityQueue() : head(nullptr), tail(nullptr), counter(0) {}

template<class T>
PriorityQueue<T>::~PriorityQueue() { clear(); }

template<class T>
PriorityQueue<T>::PriorityQueue(const PriorityQueue<T>& other){ *this = other; }

template<class T>
void PriorityQueue<T>::InsertFront(T v)
{
    head = new Node<T>(v, head);
    counter++;
}

template<class T>
void PriorityQueue<T>::InsertBack(T v)
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
void PriorityQueue<T>::InsertWithPriority(T v)
{
    if (!head) {
        InsertBack(v);
        return;
    }
    if (v < head->getValue()) {
        InsertFront(v);
        return;
    }
    if (v > tail->getValue()) {
        InsertBack(v);
        return;
    }
    Node<T>* cur = head->getNext();
    Node<T>* prev = head;
    while (true) {
        if (v < cur->getValue()) {
            Node<T>* temp = new Node<T>(v, prev->getNext());
            prev->setNext(temp);
            ++counter;
            break;
        }
        cur = cur->getNext();
        prev = prev->getNext();
    }
}

template<class T>
void PriorityQueue<T>::PullBack()
{
    if (!head) return;
    else if (head == tail) {
        delete head;
        head = nullptr;
        counter = 0;
        return;
    }
    Node<T>* temp = head;
    while (temp->getNext() != tail)
        temp = temp->getNext();
    tail = temp;
    tail->setNext(nullptr);
    delete temp->getNext();
    --counter;
}

template<class T>
void PriorityQueue<T>::PullFront()
{
    if (!head) return;
    Node<T>* temp = head;
    head = head->getNext();
    delete temp;
    --counter;
    if (!head) tail = nullptr;
}

template<class T>
void PriorityQueue<T>::PullHighestPriorityElement()
{
    if (!head) return;
    if (counter == 1) {
        PullFront();
        return;
    }
    Node<T>* maxCur = head;
    Node<T>* cur = head->getNext();
    Node<T>* prev = nullptr;
    Node<T>* temp = head;
    while (cur) {
        if (maxCur->getValue() < cur->getValue()) {
            maxCur = cur;
            prev = temp;
        }
        temp = temp->getNext();
        cur = cur->getNext();
    }
    prev->setNext(maxCur->getNext());
    delete maxCur;
    if (!prev->getNext())
        tail = head;
    --counter;
}

template<class T>
void PriorityQueue<T>::clear() { while (head) PullHighestPriorityElement(); }

template<class T>
bool PriorityQueue<T>::IsEmpty() { return counter == 0; }

template<class T>
bool PriorityQueue<T>::IsFull() { return counter != 0; }

template<class T>
T PriorityQueue<T>::front() const { return head->getValue(); }

template<class T>
T PriorityQueue<T>::back() const { return tail->getValue(); }

template<class T>
T PriorityQueue<T>::Peek() const
{
    Node<T>* maxCur = head;
    Node<T>* cur = head->getNext();
    while (cur) {
        if (maxCur->getValue() < cur->getValue())
            maxCur = cur;
        cur = cur->getNext();
    }
    return maxCur->getValue();
}

template<class T>
PriorityQueue<T>& PriorityQueue<T>::operator=(const PriorityQueue<T>& other)
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
ostream& operator<<(ostream& out, const PriorityQueue<T>& queue) {
    Node<T>* cur = queue.head;
    while (cur) {
        out << cur->getValue() << '\t';
        cur = cur->getNext();
    }
    return out;
}