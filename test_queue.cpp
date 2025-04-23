#include <cassert>
#include "test_queue.h"
#include "PriorityQueue.h"

void testTop() {
    PriorityQueue<int> pq;
    pq.Push(5); pq.Push(3);
    assert(pq.Top() == 5);

    PriorityQueue<int> pq2;
    pq2.Push(1);
    assert(pq2.Top() == 1);

    PriorityQueue<int> pq3;
    pq3.Push(0); pq3.Push(-1);
    assert(pq3.Top() == 0);
}

void testPush() {
    PriorityQueue<int> pq;
    pq.Push(10);
    assert(pq.Top() == 10);

    PriorityQueue<int> pq2;
    pq2.Push(0); pq2.Push(1);
    assert(pq2.Top() == 1);

    PriorityQueue<int> pq3;
    pq3.Push(-5); pq3.Push(-10);
    assert(pq3.Top() == -5);
}

void testPop() {
    PriorityQueue<int> pq;
    pq.Push(5); pq.Push(3);
    pq.Pop();
    assert(pq.Top() == 3);

    PriorityQueue<int> pq2;
    pq2.Push(1);
    pq2.Pop();
    assert(pq2.IsEmpty());

    PriorityQueue<int> pq3;
    pq3.Push(2); pq3.Push(1); pq3.Push(0);
    pq3.Pop();
    assert(pq3.Top() == 1);
}

void testSize() {
    PriorityQueue<int> pq;
    pq.Push(1); pq.Push(2);
    assert(pq.Size() == 2);

    PriorityQueue<int> pq2;
    assert(pq2.Size() == 0);

    PriorityQueue<int> pq3;
    pq3.Push(5); pq3.Pop();
    assert(pq3.Size() == 0);
}

void testIsEmpty() {
    PriorityQueue<int> pq;
    assert(pq.IsEmpty());

    PriorityQueue<int> pq2;
    pq2.Push(1);
    assert(!pq2.IsEmpty());

    PriorityQueue<int> pq3;
    pq3.Push(2); pq3.Pop();
    assert(pq3.IsEmpty());
}

void testConcat() {
    PriorityQueue<int> pq1;
    pq1.Push(1);
    PriorityQueue<int> pq2;
    pq2.Push(2);
    PriorityQueue<int> result = pq1.Concat(pq2);
    assert(result.Size() == 2 && result.Top() == 2);
    PriorityQueue<int> pq3;
    PriorityQueue<int> pq4;
    PriorityQueue<int> result2 = pq3.Concat(pq4);
    assert(result2.IsEmpty());
    PriorityQueue<int> pq5;
    pq5.Push(0);
    PriorityQueue<int> pq6;
    pq6.Push(-1);
    PriorityQueue<int> result3 = pq5.Concat(pq6);
    assert(result3.Top() == 0);
}

void testMap() {
    PriorityQueue<int> pq; pq.Push(1); pq.Push(2);
    auto result = pq.Map([](int& x) {  x *= 2; });
    assert(result.Top() == 4);

    PriorityQueue<int> pq2;
    auto result2 = pq2.Map([](int& x) {  ++x; });
    assert(result2.IsEmpty());

    PriorityQueue<int> pq3; pq3.Push(-1); pq3.Push(0);
    auto result3 = pq3.Map([](int& x) {  x *= x; });
    assert(result3.Top() == 1);
}

void testWhere() {
    PriorityQueue<int> pq; pq.Push(1); pq.Push(2); pq.Push(3);
    auto result = pq.Where([](int x) { return x > 1; });
    assert(result.Top() == 3);

    PriorityQueue<int> pq2;
    auto result2 = pq2.Where([](int x) { return x > 0; });
    assert(result2.IsEmpty());

    PriorityQueue<int> pq3; pq3.Push(-1); pq3.Push(0);
    auto result3 = pq3.Where([](int x) { return x < 0; });
    assert(result3.Top() == -1);
}

