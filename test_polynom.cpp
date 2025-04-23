#include <cassert>
#include <iostream>
#include "Polynomial.h"
#include "test_polynom.h"

void PolynomTestAddition() {
    Polynom<int> p1;
    p1 += Polynom<int>().ProdScalar(5);
    p1 += Polynom<int>().ProdScalar(3);
    assert(p1.ValueInPoint(1) == 8);

    Polynom<int> p2;
    p2 += Polynom<int>().ProdScalar(1);
    assert(p2.ValueInPoint(1) == 1);

    Polynom<int> p3;
    p3 += Polynom<int>().ProdScalar(0);
    assert(p3.ValueInPoint(1) == 0);

    Polynom<int> p4(1, 2);
    p4 += Polynom<int>().ProdScalar(3);
    assert(p4.ValueInPoint(2) == 7);
}

void PolynomTestSubtraction() {
    Polynom<int> p1;
    p1 += Polynom<int>().ProdScalar(5);
    p1 -= Polynom<int>().ProdScalar(3);
    assert(p1.ValueInPoint(1) == 2);

    Polynom<int> p2;
    p2 -= Polynom<int>().ProdScalar(1);
    assert(p2.ValueInPoint(1) == -1);

    Polynom<int> p3;
    assert(p3.ValueInPoint(1) == 0);

    Polynom<int> p4(1, 4);
    p4 -= Polynom<int>().ProdScalar(2);
    assert(p4.ValueInPoint(2) == 6);
}

void PolynomTestMultiplication() {
    Polynom<int> p1;
    p1 += Polynom<int>().ProdScalar(2);
    p1 *= Polynom<int>().ProdScalar(3);
    assert(p1.ValueInPoint(1) == 6);

    Polynom<int> p2;
    p2 *= Polynom<int>().ProdScalar(5);
    assert(p2.ValueInPoint(1) == 0);

    Polynom<int> p3;
    p3 += Polynom<int>().ProdScalar(1);
    p3 *= Polynom<int>().ProdScalar(0);
    assert(p3.ValueInPoint(1) == 0);

    Polynom<int> p4(1, 2);
    p4 *= Polynom<int>().ProdScalar(3);
    assert(p4.ValueInPoint(2) == 12);
}

void PolynomTestScalarMultiplication() {
    Polynom<int> p1;
    p1 += Polynom<int>().ProdScalar(2);
    Polynom<int> result = p1.ProdScalar(3);
    assert(result.ValueInPoint(1) == 6);
    
    Polynom<int> p3;
    p3 += Polynom<int>().ProdScalar(-1);
    Polynom<int> result3 = p3.ProdScalar(2);
    assert(result3.ValueInPoint(1) == -2);

    Polynom<int> p4(2, 3);
    Polynom<int> result4 = p4.ProdScalar(2);
    assert(result4.ValueInPoint(2) == 24);
}

void PolynomTestValueInPoint() {
    Polynom<int> p1;
    p1 += Polynom<int>().ProdScalar(5);
    assert(p1.ValueInPoint(2) == 5);

    Polynom<int> p2;
    assert(p2.ValueInPoint(3) == 0);

    Polynom<int> p3(1, 2);
    p3 += Polynom<int>().ProdScalar(3);
    assert(p3.ValueInPoint(2) == 7);

    Polynom<int> p4(2, 3);
    assert(p4.ValueInPoint(2) == 12);
}

void PolynomTestSuperPosition() {
    Polynom<int> p1;
    p1 += Polynom<int>().ProdScalar(2);
    Polynom<int> p2;
    p2 += Polynom<int>().ProdScalar(3);
    Polynom<int> result = p1.SuperPosition(p2);
    assert(result.ValueInPoint(1) == 2);

    Polynom<int> p3;
    Polynom<int> result2 = p3.SuperPosition(p2);
    assert(result2.ValueInPoint(1) == 0);

    Polynom<int> p4(1, 1);
    Polynom<int> result3 = p4.SuperPosition(p2);
    assert(result3.ValueInPoint(1) == 3);

    Polynom<int> p5(2, 1);
    Polynom<int> result4 = p5.SuperPosition(p2);
    assert(result4.ValueInPoint(1) == 9);
}

void PolynomTestPower() {
    Polynom<int> p1;
    p1 += Polynom<int>().ProdScalar(2);
    Polynom<int> result = Polynom<int>::Power(p1, 2);
    assert(result.ValueInPoint(1) == 4);

    Polynom<int> p2;
    Polynom<int> result2 = Polynom<int>::Power(p2, 3);
    assert(result2.ValueInPoint(1) == 0);

    Polynom<int> p3;
    p3 += Polynom<int>().ProdScalar(1);
    Polynom<int> result3 = Polynom<int>::Power(p3, 0);
    assert(result3.ValueInPoint(1) == 1);

    Polynom<int> p4(1, 2);
    Polynom<int> result4 = Polynom<int>::Power(p4, 2);
    assert(result4.ValueInPoint(2) == 16);
}
