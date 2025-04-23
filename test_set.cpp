#include <cassert>
#include <iostream>
#include "RedBlackTree.h"
#include "test_set.h"

void SettestInsert() {
    Set<int> s; s.Insert(5); s.Insert(3);
    assert(s.Size() == 2 && s.Find(5) != s.end());

    Set<int> s2; s2.Insert(1);
    assert(s2.Size() == 1 && s2.Find(1) != s2.end());

    Set<int> s3; s3.Insert(0); s3.Insert(0);
    assert(s3.Size() == 1);
}

void SettestSize() {
    Set<int> s; s.Insert(1); s.Insert(2);
    assert(s.Size() == 2);

    Set<int> s2;
    assert(s2.Size() == 0);

    Set<int> s3; s3.Insert(5); s3.Insert(5);
    assert(s3.Size() == 1);
}

void SettestBegin() {
    Set<int> s; s.Insert(3); s.Insert(1); s.Insert(4);
    assert(*s.begin() == 1);

    Set<int> s2; s2.Insert(5);
    assert(*s2.begin() == 5);

    Set<int> s3;
    assert(s3.begin() == s3.end());
}

void SettestEnd() {
    Set<int> s; s.Insert(1);
    assert(s.end() != s.begin());

    Set<int> s2;
    assert(s2.end() == s2.begin());

    Set<int> s3; s3.Insert(5); s3.Insert(6);
    assert(s3.end() != s3.Find(6));
}

void SettestFind() {
    Set<int> s; s.Insert(5); s.Insert(3);
    assert(*s.Find(5) == 5);

    Set<int> s2;
    assert(s2.Find(1) == s2.end());

    Set<int> s3; s3.Insert(0); s3.Insert(-1);
    assert(*s3.Find(-1) == -1);
}

void SettestStitch() {
    Set<int> s; s.Insert(1); s.Insert(2); s.Insert(3);
    s.Stitch();
    assert(s.begin().GetPtr()->next != nullptr);

    Set<int> s2;
    s2.Stitch();
    assert(s2.begin() == s2.end());

    Set<int> s3; s3.Insert(5);
    s3.Stitch();
    assert(s3.begin().GetPtr()->next == nullptr);
}

void SettestGoForward() {
    Set<int> s; s.Insert(1); s.Insert(2); s.Insert(3);
    DynamicArray<int> arr = s.GoForward();
    assert(arr[0] == 1 && arr[1] == 2 && arr[2] == 3);

    Set<int> s2;
    DynamicArray<int> arr2 = s2.GoForward();
    assert(arr2.GetLenght() == 0);

    Set<int> s3; s3.Insert(0);
    DynamicArray<int> arr3 = s3.GoForward();
    assert(arr3[0] == 0);
}

void SettestRead() {
    Set<int> s; s.Insert(1); s.Insert(2);
    std::string result = s.Read("{L}(C)[R]");
    assert(!result.empty());

    Set<int> s2;
    std::string result2 = s2.Read("(L)[C]{R}");
    assert(result2.empty());

    Set<int> s3; s3.Insert(5);
    std::string result3 = s3.Read("[C]{R}(L)");
    assert(!result3.empty());
}

void SettestGetSubTree() {
    Set<int> s; s.Insert(5); s.Insert(3); s.Insert(7);
    Set<int> sub = s.GetSubTree(3);
    assert(sub.Size() == 1 && *sub.begin() == 3);

    Set<int> s2; s2.Insert(1);
    Set<int> sub2 = s2.GetSubTree(1);
    assert(sub2.Size() == 1);

    Set<int> s3;
    Set<int> sub3 = s3.GetSubTree(0);
    assert(sub3.Size() == 0);
}

void SettestIsSubTree() {
    Set<int> s; s.Insert(5); s.Insert(3);
    Set<int> sub; sub.Insert(3);
    assert(s.IsSubTree(sub));
 
    Set<int> s2;
    Set<int> sub2;
    assert(s2.IsSubTree(sub2));

    Set<int> s3; s3.Insert(1); s3.Insert(2);
    Set<int> sub3; sub3.Insert(3);
    assert(!s3.IsSubTree(sub3));
}

void SettestMap() {
    Set<int> s; s.Insert(1); s.Insert(2);
    Set<int> result = s.Map([](int x) { return x * 2; });
    assert(*result.begin() == 2 && *result.Find(4) == 4);

    Set<int> s2;
    Set<int> result2 = s2.Map([](int x) { return x + 1; });
    assert(result2.Size() == 0);

    Set<int> s3; s3.Insert(-1); s3.Insert(0);
    Set<int> result3 = s3.Map([](int x) { return x * x; });
    assert(*result3.begin() == 0 && *result3.Find(1) == 1);
}

void SettestWhere() {
    Set<int> s; s.Insert(1); s.Insert(2); s.Insert(3);
    Set<int> result = s.Where([](int x) { return x > 1; });
    assert(result.Size() == 2 && *result.begin() == 2);

    Set<int> s2;
    Set<int> result2 = s2.Where([](int x) { return x > 0; });
    assert(result2.Size() == 0);

    Set<int> s3; s3.Insert(-1); s3.Insert(0);
    Set<int> result3 = s3.Where([](int x) { return x < 0; });
    assert(result3.Size() == 1 && *result3.begin() == -1);
}


