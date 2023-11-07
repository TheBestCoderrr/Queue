#include "Queue.h"
#include "PriorityQueue.h"

int main() {
    PriorityQueue<int> q;
    q.InsertWithPriority(10);
    q.InsertWithPriority(6);
    q.InsertWithPriority(30);
    q.InsertWithPriority(20);
    q.InsertWithPriority(5);
    q.InsertWithPriority(7);
    q.InsertWithPriority(6);
    cout << q << endl;
    q.clear();

    q.InsertBack(10);
    q.InsertBack(30);
    q.InsertBack(50);
    q.InsertBack(20);
    cout << q << endl;
    q.PullHighestPriorityElement();
    cout << q << endl;
    cout << q.Peek() << endl;
}