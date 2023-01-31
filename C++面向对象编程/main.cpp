#include<iostream>
#include<string>
#include "virtual.h"

using namespace std;

class A 
{    
public:
    int m_data1;

    A(): m_data1(0), m_data2(0) 
    {
        cout << "A constructor, &m_data1 = " << &m_data1 << ", m_data2 = " << &m_data2 << endl;
    }
    
    ~A() 
    {
        cout << "A destructor" << endl;
    }

    int add(int a) {
        m_data1 += a;
        return m_data1;
    }

    int add(int a, int b) {
        m_data1 += (a + b);
        return m_data1;
    }

private:
    int m_data2;
};

class B: public A 
{
public:
    int m_data1;

    B(): m_data1(1), m_data2(1) 
    {        
        cout << "B constructor, &m_data1 = " << &m_data1 << ", m_data2 = " << &m_data2 << endl;
        cout << "B constructor, &A::m_data1 = " << &(A::m_data1) << endl;
    }

    ~B() 
    {
        cout << "B destructor" << endl;
    }

    int add()
    {
        m_data1 += 1;

        return m_data1;
    }

private:
    int m_data2;
};

int main(int argc, char const *argv[])
{

    // A a;
    // cout << "sizeof(a) = " << sizeof(a) << endl;
    // cout << "sizeof(A) = " << sizeof(A) << endl;

    // B b;
    // cout << "sizeof(b) = " << sizeof(b) << endl;
    // cout << "sizeof(B) = " << sizeof(B) << endl;

    // cout << b.m_data1 << endl;
    // cout << b.A::m_data1 << endl;


    // b.add();

    // 会隐藏掉同名的函数
    // b.add(2);
    // b.add(2, 3);


    // Virtual::testVirtual1();
    Virtual::testVirtual2();
    

    return 0;
}
