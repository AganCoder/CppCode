#include "jj04-forwardlist.h"
#include <iostream>
#include <forward_list>
#include "utils.h"

using namespace std;
using namespace utils;

void jj04::testForwardlist(long value) 
{
    cout << "\ntest forward_list() ......." << endl;

    forward_list<string> c;
    char buf[10];

    srand(time(NULL));

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
    // cout << "list.size() = " << c.size() << endl;
    cout << "forward_list.max_size = " << c.max_size() << endl;
    cout << "list.front() = " << c.front() << endl;
    // cout << "list.back() = " << c.back() << endl;

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
    c.sort();
    cout << "c.sort(), milli-seconds: " << (clock() - timeStart) << endl;
}

