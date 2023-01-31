#include "virtual.h"

namespace Virtual 
{
    void testVirtual1()
    {
        cout << "sizeof(int) = " << sizeof(int) << endl;
        cout << "sizeof(int *) = " << sizeof(int *) << endl;

        cout << "\n -------- A Test -------" << endl;

        A a;
        cout << "sizeof(a) = " << sizeof(a) << endl;
        cout << "sizeof(A) = " << sizeof(A) << endl;
        a.vfunc1();
        a.vfunc2();

        cout << "\n -------- B Test -------" << endl;
        B b;
        cout << "sizeof(b) = " << sizeof(b) << endl;
        cout << "sizeof(B) = " << sizeof(B) << endl;

        b.vfunc1();
        b.vfunc2();
        b.A::vfunc1();
        b.A::vfunc2();

        cout << "\n -------- C Test -------" << endl;
        C c;
        cout << "sizeof(c) = " << sizeof(c) << endl;
        cout << "sizeof(C) = " << sizeof(C) << endl;

        c.vfunc1();
        c.vfunc2();
        c.B::vfunc1();
        c.B::vfunc2();
        c.A::vfunc1();
        c.A::vfunc2();
    }

    void testVirtual2() 
    {
        typedef void (*func)(void);
        
        cout << "\n -------- A Test -------" << endl;

        cout << "sizeof(func) = " << sizeof(func) << endl;

        A *a = new A;
        {
            func c = *((func *)*(func **)a + 0);
            c();

            func c1 = *((func *)*(func **)a + 1);
            c1();

            a->m_data1 = 100;

            (char *)(*(int *)a) + sizeof(func *)
            
            cout << *(int *)(*(int *)a + ) << endl;
        }
    }
}


