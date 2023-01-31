#include "jj05-deque.h"
#include <iostream>
#include <deque>
#include "utils.h"

using namespace std;
using namespace utils;

void jj05::testDeque(long value) 
{
    cout << "\ntest queue() ......." << endl;

    deque<string> c;
    char buf[10];

    clock_t timeStart = clock();

    for (int i = 0; i < value; i++) {
        try {
            snprintf(buf, 10, "%d", rand());
            c.push_front(string(buf));
        } catch (const std::exception& e) {
            cout << "i = " << i << " " << e.what() << endl;
            abort();
        }
    }

    cout << "milli-seconds:" << ( clock() - timeStart ) << endl;
    cout << "deque.size() = " << c.size() << endl;
    cout << "deque.max_size = " << c.max_size() << endl;
    cout << "deque.front() = " << c.front() << endl;
    cout << "deque.back() = " << c.back() << endl;

    string target = get_a_target_string();

    cout << "target = " << target << endl;
    {
        timeStart = clock();
        auto pItem = ::find(c.begin(), c.end(), target);

        cout << "::find(), milli-seconds: " << (clock() - timeStart) << endl;

        if ( pItem != c.end() )
            cout << "found! \n"  << *pItem << endl;
        else 
            cout << "not found!\n" << endl;
    }

    timeStart = clock();
    ::sort(c.begin(), c.end());
    cout << "::sort(), milli-seconds: " << (clock() - timeStart) << endl;
}

