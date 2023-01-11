#include "jj02-vector.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include "utils.h"

using namespace std;
using namespace utils;

namespace jj02
{
    void testVector(long value) 
    {
        cout << "\ntest vector() ......." << endl;

        vector<string> c;
        char buf[10];

        srand(time(NULL));

        clock_t timeStart = clock();

        for (int i = 0; i < value; i++) {
            try {
                snprintf(buf, 10, "%d", rand());
                c.push_back(string(buf));
            } catch (const std::exception& e) {
                cout << "i = " << i << " " << e.what() << endl;
                abort();
            }
        }

        cout << "milli-seconds:" << ( clock() - timeStart ) << endl;
        cout << "vector.size() = " << c.size() << endl;
        cout << "vector.capacity = " << c.capacity() << endl;
        cout << "vector.front() = " << c.front() << endl;
        cout << "vector.back() = " << c.back() << endl;
        cout << "vector.data() = " << c.data() << endl;

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

        {
            timeStart = clock();
            sort(c.begin(), c.end());

            cout << c[0] << " " << c[1] << " " << "target = " << target << endl;            

            string *pItem = (string *)bsearch(&target, (c.data()), c.size(), sizeof(string), compareString);

            cout << "sort() + bsearch(), milli-seconds: " << (clock() - timeStart) << endl;

            if ( pItem != NULL )
                cout << "found, " << pItem << ", value = " << *pItem << endl;
            else 
                cout << "not found!" << endl;
        }
    }
}