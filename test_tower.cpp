#include <cassert>
#include "HanonianTowers.h"
#include "test_tower.h"
#include <iostream>



void testTower() {
    Stack<Ring> from; from.Push(Ring(2)); from.Push(Ring(1));
    Stack<Ring> to;
    Stack<Ring> help;
    Tower(2, from, to, help);
    assert(to.Size() == 2 && to.Top().GetOrder() == 1);

    Stack<Ring> from2; from2.Push(Ring(1));
    Stack<Ring> to2;
    Stack<Ring> help2;
    Tower(1, from2, to2, help2);
    assert(to2.Size() == 1 && to2.Top().GetOrder() == 1);

    Stack<Ring> from3;
    Stack<Ring> to3;
    Stack<Ring> help3;
    Tower(0, from3, to3, help3);
    assert(to3.Empty());
}


