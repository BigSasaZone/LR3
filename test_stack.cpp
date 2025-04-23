#include <cassert>
#include <iostream>
#include "Stack.h"
#include "test_stack.h"

void SttestPush() {
    Stack<int> s;
    s.Push(5);
    assert(s.Top() == 5);

    Stack<int> s2;
    s2.Push(0); s2.Push(1);
    assert(s2.Top() == 1);

    Stack<int> s3;
    s3.Push(-1);
    assert(s3.Top() == -1);
}

void SttestPop() {
    Stack<int> s;
    s.Push(5); s.Push(3);
    assert(s.Pop() == 3);

    Stack<int> s2;
    s2.Push(1);
    assert(s2.Pop() == 1);

    Stack<int> s3;
    s3.Push(2); s3.Push(0);
    assert(s3.Pop() == 0);
}

void SttestTop() {
    Stack<int> s;
    s.Push(4);
    assert(s.Top() == 4);

    Stack<int> s2;
    s2.Push(0); s2.Push(-1);
    assert(s2.Top() == -1);

    Stack<int> s3;
    s3.Push(5); s3.Push(5);
    assert(s3.Top() == 5);
}

void SttestSize() {
    Stack<int> s;
    s.Push(1); s.Push(2);
    assert(s.Size() == 2);

    Stack<int> s2;
    assert(s2.Size() == 0);

    Stack<int> s3;
    s3.Push(3); s3.Pop();
    assert(s3.Size() == 0);
}

void SttestEmpty() {
    Stack<int> s;
    assert(s.Empty());

    Stack<int> s2;
    s2.Push(1);
    assert(!s2.Empty());

    Stack<int> s3;
    s3.Push(2); s3.Pop();
    assert(s3.Empty());
}

void SttestClear() {
    Stack<int> s;
    s.Push(1); s.Push(2);
    s.Clear();
    assert(s.Empty());

    Stack<int> s2;
    s2.Clear();
    assert(s2.Size() == 0);

    Stack<int> s3;
    s3.Push(0); s3.Clear(); s3.Push(1);
    assert(s3.Size() == 1);
}

