#include "Polynomial.h"
#include <cassert>
using namespace std;

void Test_DefaultConstructor_Polynomial()
{
    Polynomial<int> polynomial;
    assert(polynomial.Get_Size() == 0);

    std::cout << "Test_DefaultConstructor_Polynomial: OK\n";
}

void Test_SizeConstructor_Polynomial()
{
    Polynomial<int> polynomial(5);
    assert(polynomial.Get_Size() == 5);

    std::cout << "Test_SizeConstructor_Polynomial: OK\n";
}

void Test_CopyConstructor_Polynomial()
{
    Polynomial<int> polynomial1(3);
    polynomial1.Set(0, 0);
    polynomial1.Set(1, 1);
    polynomial1.Set(2, 2);

    Polynomial<int> polynomial2(polynomial1);
    assert(polynomial2.Get_Size() == 3);
    assert(polynomial2.Get(0) == 0);
    assert(polynomial2.Get(1) == 1);
    assert(polynomial2.Get(2) == 2);


    std::cout << "Test_CopyConstructor_Polynomial: OK\n";
}

void Test_Evaluate_Polynomial()
{
    Polynomial<int> polynomial(3);
    polynomial.Set(0, 0);
    polynomial.Set(1, 1);
    polynomial.Set(2, 2);

    assert (polynomial.EvaluateAtPoint(2) == 10);
    std::cout << "Test_Evaluate_Polynomial: OK\n";
}

void Test_Addition_Polynomial()
{
    Polynomial<int> polynomial1(3);
    polynomial1.Set(0, 0);
    polynomial1.Set(1, 1);
    polynomial1.Set(2, 2);

    Polynomial<int> polynomial2(3);
    polynomial2.Set(0, 0);
    polynomial2.Set(1, 1);
    polynomial2.Set(2, 2);

    Polynomial<int> polynomial3 = polynomial1 + polynomial2;
    

    assert (polynomial3.Get(0) == 0);
    assert (polynomial3.Get(1) == 2);
    assert (polynomial3.Get(2) == 4);
    std::cout << "Test_Evaluate_Polynomial: OK\n";
}

void Test_SelfAddition_Polynomial()
{
    Polynomial<int> polynomial1(3);
    polynomial1.Set(0, 0);
    polynomial1.Set(1, 1);
    polynomial1.Set(2, 2);

    Polynomial<int> polynomial2(3);
    polynomial2.Set(0, 0);
    polynomial2.Set(1, 1);
    polynomial2.Set(2, 2);

    polynomial1 += polynomial2;
    

    assert (polynomial1.Get(0) == 0);
    assert (polynomial1.Get(1) == 2);
    assert (polynomial1.Get(2) == 4);
    std::cout << "Test_SelfAddition_Polynomial: OK\n";
}

void Test_Multiplication_Polynomial()
{
    Polynomial<int> polynomial1(3);
    polynomial1.Set(0, 0);
    polynomial1.Set(1, 1);
    polynomial1.Set(2, 2);

    Polynomial<int> polynomial2(3);
    polynomial2.Set(0, 0);
    polynomial2.Set(1, 1);
    polynomial2.Set(2, 2);

    Polynomial<int> polynomial3 = polynomial2 * polynomial1;
    

    assert (polynomial3.Get(0) == 0);
    assert (polynomial3.Get(1) == 0);
    assert (polynomial3.Get(2) == 1);
    assert (polynomial3.Get(3) == 4);
    assert (polynomial3.Get(4) == 4);
    std::cout << "Test_Multiplication_Polynomial: OK\n";
}

void Test_SelfMultiplication_Polynomial()
{
    Polynomial<int> polynomial1(3);
    polynomial1.Set(0, 0);
    polynomial1.Set(1, 1);
    polynomial1.Set(2, 2);

    Polynomial<int> polynomial2(3);
    polynomial2.Set(0, 0);
    polynomial2.Set(1, 1);
    polynomial2.Set(2, 2);

    polynomial2 *= polynomial1;
    

    assert (polynomial2.Get(0) == 0);
    assert (polynomial2.Get(1) == 0);
    assert (polynomial2.Get(2) == 1);
    assert (polynomial2.Get(3) == 4);
    assert (polynomial2.Get(4) == 4);
    std::cout << "Test_SelfMultiplication_Polynomial: OK\n";
}

int main()
{
    Test_DefaultConstructor_Polynomial();
    Test_SizeConstructor_Polynomial();
    Test_CopyConstructor_Polynomial();
    Test_Evaluate_Polynomial();
    Test_Addition_Polynomial();
    Test_SelfAddition_Polynomial();
    Test_Multiplication_Polynomial();
    Test_SelfMultiplication_Polynomial();
}