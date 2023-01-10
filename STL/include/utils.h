#ifndef __UTIL__
#define __UTIL__

#include <string>

using namespace std;

namespace utils 
{
    long get_a_target_long();
    string get_a_target_string();
    int compareLongs(const void* a, const void* b);
    int compareString(const void* a, const void* b);
}

#endif // __UTIL__