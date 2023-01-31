#ifndef __VIRTUAL_
#define __VIRTUAL_

#include <iostream>

using namespace std;

namespace Virtual 
{
    class A 
    {
    public:
        virtual void vfunc1() { cout << "A vfunc1" << endl;};
        virtual void vfunc2() { cout << "A vfunc2" << endl;};
        void func1() {} ;
        void func2() {};
        int m_data1, m_data2;
    };

    class B : public A 
    {
    public:
        virtual void vfunc1() { cout << "B vfunc1" << endl; } ;
        void func1() {};
    private:
        int m_data3;
    };

    class C: public B 
    {
    public:
        virtual void vfunc2() { cout << "C vfunc2" << endl; };
        void func2() {};
    private:
        int m_data1, m_data4;
    };

    void testVirtual1();
    void testVirtual2();
}

#endif // __VIRTUAL_