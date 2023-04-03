#include <iostream>
#include <algorithm>
#include <vector>

// 主要使用 C++11 可以使用的 API (5/14)
// https://en.cppreference.com/w/cpp/algorithm

struct Employee
{
    int age;
    std::string name; // Does not participate in comparisons
};

bool operator<(const Employee &lhs, const Employee &rhs)
{
    return lhs.age < rhs.age;
}

int main(int argc, char **argv)
{
    // 1. is_sorted: 判断是否是升序排序
    {
        std::vector<int> v1 = {1, 2, 3, 4};
        bool r1 = std::is_sorted(v1.begin(), v1.end());
        std::cout << "is_sorted " << std::boolalpha << r1 << std::endl; // 0(false)
    }

    // 2. is_sorted_until
    {
        std::vector<int> v1 = {1, 2, 3, 4, 3, 2, 1, 3};
        auto is_sorted_until = std::is_sorted_until(v1.begin(), v1.end());
        std::cout << "is_sorted_until = " << *is_sorted_until << ", index = " << is_sorted_until - v1.cbegin() << std::endl;
    }

    // 3. sort: 排序
    {
        std::vector<int> v1 = {1, 2, 3, 4, 3, 2, 1, 3};
        std::sort(v1.begin(), v1.end());
        std::cout << "sort: ";
        std::copy(v1.begin(), v1.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    }

    // 4. partial_sort: 找出其中排序好的数据，例如.在 100 w 个数据中，找出最小的 10 个
    {
        std::vector<int> v1{5, 7, 4, 2, 8, 6, 1, 9, 0, 3};
        std::partial_sort(v1.begin(), v1.begin() + 4, v1.end()); // 0 1 2 3 8 7 6 9 5 4 // 取 4 个值[0, 1, 2, 3], 其他的未排序

        std::cout << "partial_sort: ";
        std::copy(v1.begin(), v1.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    }

    // 5. stable_sort： 排序，并保持相对位置
    {
        std::vector<Employee> v =
            {
                {108, "Zaphod"},
                {32, "Arthur"},
                {108, "Ford"},
            };

        std::stable_sort(v.begin(), v.end());

        std::cout << "stable_sort: ";
        for (const Employee &e : v)
            std::cout << e.age << "-" << e.name << " ";

        std::cout << std::endl;
    }
}