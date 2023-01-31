#include <iostream>
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
    int x = 0;
    int* p = &x;
    int& r = x;
    int x2 = 5;

    r = x2;

    cout << r << endl;

    return 0;
}
