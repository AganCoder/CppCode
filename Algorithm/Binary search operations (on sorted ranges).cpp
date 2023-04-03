#include <iostream>
#include <algorithm>
#include <vector>

int main(int argc, char **argv)
{
    // 1. lower_bound: 顺序集合中，找到第一个不满足小于指定值
    {
        std::vector<int> v1 {1, 2, 3, 4, 6};
        auto iter = std::lower_bound(v1.begin(), v1.end(), 3);
        std::cout << "lower_bound: " << *(iter) << ", index: " << iter - v1.begin()  << std::endl;
    }

    // 2. upper_bound: 顺序集合中，找到第一个小于指定值
    {
        std::vector<int> v1 {1, 2, 3, 4, 6};
        auto iter = std::upper_bound(v1.begin(), v1.end(), 3);
        std::cout << "lower_bound: " << *(iter) << ", index: " << iter - v1.begin()  << std::endl;
    }


    // 3. binary_search: 二分查找法查找是否包含对应元素
    {
        std::vector<int> v1 {1, 2, 3, 4, 6};
        std::cout << "binary_search: " << std::boolalpha << std::binary_search(v1.begin(), v1.end(), 3)<< std::endl;
    }

    // 4. equal_range: 在一个顺序集合中，找到匹配某个元素范围
    {
        std::vector<int> v1 {1, 2, 3, 3, 4, 6};
        auto pair = std::equal_range(v1.begin(), v1.end(), 3);

        std::cout << "equal_range: index = " << pair.first - v1.begin() << " - "<< pair.second - v1.begin() << std::endl;

    }
}