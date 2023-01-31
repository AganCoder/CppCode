
#include <iostream>

using namespace std;

class Base 
{
public:
    Base() {
        cout << "Base constructor" << endl;
    }

    ~Base() {
        cout << "Base destructor" << endl;
    }
};

class Derived : public Base {
public:
    Derived() {
        cout << "Derived constructor" << endl;
    }

    ~Derived() {
        cout << "Derived destructor" << endl;
    }
};


int main(int argc, char const *argv[])
{
    {
        Derived *base = new Derived();

        delete base;
    }

    return 0;
}
