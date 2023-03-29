#include <iostream>
#include <algorithm>
#include <vector>

// 主要使用 C++11 可以使用的 API (5/10)
// https://en.cppreference.com/w/cpp/algorithm


int main(int argc, char **argv)
{
    // 1. is_partitioned: 谓词判断返回 True 的在 返回 false 的之前
    // 例如：判断是否是奇数： [1, 2, 3, 4], 就不是，因为 2 返回 false， 而 3 在 2 之后
    // [1, 3, 2, 4] 这就是，因为奇数全部在第一个偶数2 之前出现了
    {
        std::vector<int> v1 = {1, 2, 3, 4};
        bool  r1 = std::is_partitioned(v1.cbegin(), v1.cend(), [](const int& i){ return i % 2 == 1; });
        std::cout << r1 << std::endl; // 0(false)

        std::vector<int> v2 = {1, 3, 2, 4};
        bool r2 = std::is_partitioned(v2.cbegin(), v2.cend(), [](const int& i){ return i % 2 == 1; });
        std::cout << r2 << std::endl; // 1(true)
    }

    // 2. partition，分成两组，谓词判断为 true 的在前面，false 的在后面，返回值为第二组的元素的地址 C++17
    // 例如：[1, 2, 3, 4, 5, 6, 7, 8, 9], 谓词判断是否为奇数，那么奇数就在前面，偶数在后面
    // 注意：这个不保证元素的相对位置
    {
        std::vector<int> v1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        auto it = std::partition(v1.begin(), v1.end(), [](int & i) { return i % 2 == 0; });

        std::cout << "partition: ";
        std::copy(v1.begin(), it, std::ostream_iterator<int>(std::cout, " ")); // 8 2 6 4
        std::cout << " * ";
        std::copy(it, v1.end(), std::ostream_iterator<int>(std::cout, " ")); // 5 3 7 1 9
        std::cout << std::endl;
    }

    // 3. partition_copy,跟 partition 相同，不改变原集合，参数有两个起始地址
    {
        std::vector<int> v1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        std::vector<int> v2 = v1;
        std::vector<int> v3 = v1;
        std::fill(v2.begin(), v2.end(), 0);
        std::fill(v3.begin(), v3.end(), 0);
        auto pair = std::partition_copy(v1.begin(), v1.end(), v2.begin(), v3.begin(), [](const int& i) { return i % 2 == 0; });

        v2.erase(pair.first, v2.end());
        v3.erase(pair.second, v3.end());

        std::cout << "partition_copy: ";
        std::copy(v2.begin(), v2.end(), std::ostream_iterator<int>(std::cout, " ")); // 2 4 6 8
        std::cout << " * ";
        std::copy(v3.begin(), v3.end(), std::ostream_iterator<int>(std::cout, " ")); // 1 3 5 7 9
        std::cout << std::endl;
    }

    // 4. stable_partition, 与 partition 功能类似，但是会保证元素相对位置
    {
        std::vector<int> v1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        auto it = std::stable_partition(v1.begin(), v1.end(), [](int & i) { return i % 2 == 0; });

        std::cout << "stable_partition: ";
        std::copy(v1.begin(), it, std::ostream_iterator<int>(std::cout, " ")); // 8 2 6 4
        std::cout << " * ";
        std::copy(it, v1.end(), std::ostream_iterator<int>(std::cout, " ")); // 5 3 7 1 9
        std::cout << std::endl;
    }

    // 5. partition_point: 值得是 partition 的 last


}