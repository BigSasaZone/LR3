#include "test_deque.h"
#include <cassert>
#include "SegmentDeque.h"
#include <functional>

void DqtestOperatorSquareBrackets() {
    SegmentDeque<int> dq(2); dq[0] = 1; dq[1] = 2;
    assert(dq[0] == 1 && dq[1] == 2);


    SegmentDeque<int> dq2(1); dq2[0] = 0;
    assert(dq2[0] == 0);
    
    SegmentDeque<int> dq3(64); dq3[63] = 5;
    assert(dq3[63] == 5);
}

void DqtestPushBack() {
    SegmentDeque<int> dq;
    dq.PushBack(1);
    assert(dq.GetSize() == 1);
    assert(dq[0] == 1);
    SegmentDeque<int> dq2(64);
    assert(dq2.GetSize() == 64);
    dq2.PushBack(2);
    assert(dq2.GetSize() == 65);
    SegmentDeque<int> dq3;
    dq3.PushBack(0);
    dq3.PushBack(-1);
    assert(dq3.GetSize() == 2);
    assert(dq3[1] == -1);
}

void DqtestPushFront() {
    SegmentDeque<int, 4> dq;

    // Первый элемент
    dq.PushFront(10);
    assert(dq.GetSize() == 1);
    assert(dq[0] == 10);

    // Второй элемент
    dq.PushFront(20);
    assert(dq.GetSize() == 2);
    assert(dq[0] == 20);
    assert(dq[1] == 10);

    // Добавление элементов до заполнения сегмента
    dq.PushFront(30);
    dq.PushFront(40);
    assert(dq.GetSize() == 4);
    assert(dq[0] == 40 && dq[3] == 10);

    // Добавление элемента, требующего новый сегмент
    dq.PushFront(50);
    assert(dq.GetSize() == 5);
    assert(dq[0] == 50 && dq[1] == 40);
}

void DqtestInsertAt() {
    SegmentDeque<int> dq; dq.PushBack(1); dq.PushBack(3);
    dq.InsertAt(2, 1);
    assert(dq[1] == 2 && dq[2] == 3);

    SegmentDeque<int> dq2;
    dq2.InsertAt(5, 0);
    assert(dq2[0] == 5);

    SegmentDeque<int> dq3(64); dq3[63] = 6;
    dq3.InsertAt(7, 63);
    assert(dq3[63] == 7 && dq3[64] == 6);
}

void DqtestSort() {
    SegmentDeque<int> dq; dq.PushBack(3); dq.PushBack(1); dq.PushBack(2);
    dq.Sort(std::less<int>());
    assert(dq[0] == 1 && dq[1] == 2 && dq[2] == 3);

    SegmentDeque<int> dq2;
    dq2.Sort(std::less<int>());
    assert(dq2.GetSize() == 0);

    SegmentDeque<int> dq3; dq3.PushBack(0); dq3.PushBack(-1);
    dq3.Sort(std::less<int>());
    assert(dq3[0] == -1 && dq3[1] == 0);
}

void DqtestMap() {
    SegmentDeque<int> dq;
    dq.PushBack(1);
    dq.PushBack(2);
    auto doubled = dq.Map([](const int& x) { return x * 2; });
    assert(doubled[0] == 2 && doubled[1] == 4);
    SegmentDeque<int> dq2;
    dq2.PushBack(3);
    dq2.PushBack(4);
    auto incremented = dq2.Map([](int x) { return x + 1; });
    assert(incremented[0] == 4 && incremented[1] == 5);
}

void DqtestWhere() {
    SegmentDeque<int> dq;
    dq.PushBack(1);
    dq.PushBack(2);
    dq.PushBack(3);
    SegmentDeque<int> filtered = dq.Where([](int x) { return x > 1; });
    assert(filtered[0] == 2 && filtered[1] == 3);

    SegmentDeque<int> dq2;
    SegmentDeque<int> filtered2 = dq2.Where([](int x) { return x > 0; });
    assert(filtered2.GetSize() == 0);

    SegmentDeque<int> dq3;
    dq3.PushBack(-1);
    dq3.PushBack(0);
    dq3.PushBack(1);
    SegmentDeque<int> filtered3 = dq3.Where([](int x) { return x < 0; });
    assert(filtered3[0] == -1);
}

void DqtestTakeDeque() {
    SegmentDeque<int> dq;
    dq.PushBack(1);
    dq.PushBack(2);
    dq.PushBack(3);
    SegmentDeque<int> result = dq.TakeDeque(1, 2); // Исправлено: 3 -> 2
    assert(result[0] == 2 && result[1] == 3);

    SegmentDeque<int> dq2;
    dq2.PushBack(1);
    SegmentDeque<int> result2 = dq2.TakeDeque(0, 0); // Исправлено: 1 -> 0
    assert(result2[0] == 1);

    SegmentDeque<int> dq3;
    dq3.PushBack(0);
    dq3.PushBack(-1);
    dq3.PushBack(2);
    SegmentDeque<int> result3 = dq3.TakeDeque(0, 2);
    assert(result3[0] == 0 && result3[1] == -1);
}

void DqtestConcat() {
    SegmentDeque<int> dq1;
    dq1.PushBack(1);
    SegmentDeque<int> dq2;
    dq2.PushBack(2);
    SegmentDeque<int> result = dq1.Concat(dq2);
    assert(result[0] == 1 && result[1] == 2);

    SegmentDeque<int> dq3;
    SegmentDeque<int> dq4;
    SegmentDeque<int> result2 = dq3.Concat(dq4);
    assert(result2.GetSize() == 0);

    SegmentDeque<int> dq5;
    dq5.PushBack(0);
    SegmentDeque<int> dq6;
    dq6.PushBack(-1);
    SegmentDeque<int> result3 = dq5.Concat(dq6);
    assert(result3[0] == 0 && result3[1] == -1);
}

