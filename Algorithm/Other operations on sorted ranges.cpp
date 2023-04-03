#include <iostream>
#include <algorithm>
#include <vector>

// 主要使用 C++11 可以使用的 API (2/4)
// https://en.cppreference.com/w/cpp/algorithm

int main(int argc, char **argv)
{
    // 1. merge: 合并两个顺序集合到一个新的集合里面去
    {
        std::vector<int> v1 {1, 3, 5, 7, 9};
        std::vector<int> v2 {2, 3, 4, 6, 8, 10};
        std::vector<int> dst;
        std::cout << "merge: ";
        std::merge(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(dst));
        std::copy(dst.begin(), dst.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    }

    // 2. inplace_merge：两个顺序集合存储在一个容器中，可以使用 inplace_merge 来合并
    {
        std::vector<int> v1 { 5,10,15,20,25,7,17,27,37,47,57 };
        std::inplace_merge(v1.begin(), v1.begin() + 5, v1.end());   

        std::cout << "inplace_merge: ";
        std::copy(v1.begin(), v1.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    }
}
