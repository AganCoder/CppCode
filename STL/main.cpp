// #include "jj00-STL.h"
// #include "jj01-array.h"
// #include "jj02-vector.h"
// #include "jj03-list.h"
#include "jj04-forwardlist.h"

#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    // jj00::textSTL();
    // jj01::testArray();
    // jj02::testVector(2);
    // jj03::testList(1000000);
    jj04::testForwardlist(1000000);

    std::cout << "Hello world" << std::endl;

    return 0;
} 