#include <iostream>
#include <algorithm>
#include <vector>

// 主要使用 C++11 可以使用的 API (16/37)
// https://en.cppreference.com/w/cpp/algorithm

using namespace std;

int main(int argc, char **argv)
{
    std::vector<int> v1 {1, 2, 3, 4 ,5};

    // 1. all_of: 所有满足
    if(  all_of(v1.cbegin(), v1.cend(), [](int i) {  return i < 10;  }) )
    {
        std::cout << "all of true" <<  std::endl;
    }

    // 2. any_of： 其中任一满足
    if(  any_of(v1.cbegin(), v1.cend(), [](int i) {  return i > 2;  }) )
    {
        std::cout << "any of true" <<  std::endl;
    }

    // 3. none_of: 没有任何一个满足
    if(  none_of(v1.cbegin(), v1.cend(), [](int i) {  return i > 5;  }) )
    {
        std::cout << "none of true" <<  std::endl;
    }

    // 4. for_each: 遍历
    for_each(v1.cbegin(), v1.cend(), [](const int &i) { std::cout << i << " "; }); // 1 2 3 4 5
    std::cout << std::endl;

    // 5. for_each_n: 遍历前 n 个  `C++17`
    // for_each_n(v1.cbegin(), 3, [](const int &i) { std::cout << i << " "; }); // 1 2 3

    // 6. count: 统计 2 的个数
    auto count = std::count(v1.cbegin(), v1.cend(), 2); // 2
    std::cout << count << std::endl;
    
    // 7. count_if: 计算满足条件个数
    auto count_if = std::count_if(v1.cbegin(), v1.cend(), [](int i) { return i > 3; }); // 2
    std::cout << count_if << std::endl;

    // 8. mismatch: 找两个集合里面第一个不匹配项，返回值是 std::pair, 里面是第一个不匹配的迭代器
    // 如果全部匹配了，那么其中一个迭代器肯定到 last 了
    {
        std::vector<int> v1 = {1, 2, 3, 4};
        std::vector<int> v2 = {3, 2, 4};

        // a: 第一个集合是 v1 = {1, 2, 3, 4} 第二个集合是 v2 = {2, 3, 4}
        std::pair<decltype(v1)::const_iterator, decltype(v2)::const_iterator> m1 = std::mismatch(v1.cbegin(), v1.cend(), v1.cbegin() + 1 );        
        std::cout << "mismatch:  *std::pair.first = " << *(m1.first) << ", index =" <<  m1.first - v1.cbegin() << " , *std::pair.second = " << *(m1.second) << ", index = " << m1.second - ( v1.cbegin() + 1)  << std::endl; 

        // b: 第一个集合是 v1 = {1, 2, 3, 4} 第二个集合是 v2 = {3, 2, 4}
        auto m2 = std::mismatch(v1.cbegin(), v1.cend(), v2.cbegin() );  
        std::cout << "mismatch:  *std::pair.first = " << *(m2.first) << ", index =" <<  m2.first - v1.cbegin() << " , *std::pair.second = " << *(m2.second) << ", index = " << m2.second - v2.cbegin()  << std::endl; 

        // c. 
        auto m3 = std::mismatch(v1.cbegin(), v1.cend(), v1.cbegin() );  
        if( m3.first != v1.cend() && m3.second != v1.cend() ) // 需要判断集合没有到结尾，如果要判断是否完全一样，还需要判断 Size是否相同才行
            std::cout << "mismatch:  *std::pair.first = " << *(m3.first) << ", index =" <<  m3.first - v1.cbegin() << " , *std::pair.second = " << *(m3.second) << ", index = " << m3.second - v1.cbegin()  << std::endl; 
        else if( v1.size() == v1.size() )
            std::cout << "all match" << std::endl;
        else
            std::cout << "one reach to the end" << std::endl;
    }

    
    // 9. find: 查找元素，返回第一个找到的元素迭代器地址, 如果没找到，那么返回集 last(第二个参数的地址)
    auto find = std::find(v1.cbegin(), v1.cend(), 10);
    if( find != v1.cend() ) 
        std::cout << *find << ", index =" << find - v1.cbegin() << std::endl;
    else 
        std::cout << "not find" << std::endl;
    

    // 10. find_if: 根据某个条件查找元素,返回值为找到的地址，如果没找到，就返回last(第二个参数的地址)
    auto find_if = std::find_if(v1.cbegin(), v1.cend(), [](const int& i) { return i > 4; });
    if( find_if != v1.cend() ) 
        std::cout << *find_if << ", index =" << find_if - v1.cbegin() << std::endl;
    else
        std::cout << "not find_if" << std::endl;

    // 11. find_if_not, 与 find_if 相反
    auto find_if_not = std::find_if_not(v1.cbegin(), v1.cend(), [](const int& i) { return i > 4; }); // 第一个不大于4的值
    if( find_if_not != v1.cend() ) 
        std::cout << *find_if_not << ", index =" << find_if_not - v1.cbegin() << std::endl;
    else
        std::cout << "not find_if_not" << std::endl;

    // 12. find_end: 查找第一个集合 `中` 第二个集合 `最后一次` 出现的位置, 如果没有，返回第一个集合的 last
    {
        const std::vector<int> v1 = {1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3};
        const std::vector<int> v2 = {1, 2};

        auto find_end = std::find_end( v1.begin(), v1.end(), v2.begin(),  v2.end()); // 在 v1 = {1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3} 中查找最后一次出现 v2 = {1, 2} 位置
        if( find_end != v1.end() )
            std::cout << "find_end index = " << find_end - v1.begin() << std::endl; 
        else
            std::cout << "not find_end" << std::endl;

     }

    // 13. find_first_of: 逐步遍历第一个集合元素，查看是否在第二个集合中出现，找到了就直接返回迭代器
    {
        const std::vector<int> v1 = {1, 2, 3};
        const std::vector<int> v2 = {3, 2, 1};

        auto find_first_of = std::find_first_of(v1.cbegin(), v1.cend(), v2.cbegin(), v2.cend());
        if( find_first_of != v1.cend() )
            std::cout << "find_first_of index " << find_first_of - v1.cbegin() << std::endl;
        else
            std::cout << "not find_first_of" << std::endl;

    }
    
    // 14 adjacent_find: 查找集合中，第一个重复的元素，[1, 2, 3, 3, 4, 4, 5] 返回 index = 2 位置上的元素 3 的迭代器
    {
        const std::vector<int> v1 = {1, 2, 3, 3, 4, 4, 5};
        auto adjacent_find = std::adjacent_find(v1.begin(), v1.end());

        if( adjacent_find != v1.cend() )
            std::cout << "adjacent_find index " << adjacent_find - v1.cbegin() << std::endl;
        else
            std::cout << "not adjacent_find" << std::endl;              
    }

    // 15 search: 查找第二个集合在第一个集合中出现的为之，例如 v1 = {1, 2, 2, 3, 4, 4, 2}, v2 = {2, 3}, 则返回 index = 2 位置的元素的 2 的迭代器
    {
        const std::vector<int> v1 = {1, 2, 2, 3, 4, 4, 2};
        const std::vector<int> v2 = {2, 3};
        auto search = std::search(v1.cbegin(), v1.cend(), v2.cbegin(), v2.cend());

        if( search != v1.cend() )
            std::cout << "search index " << search - v1.cbegin() << std::endl;
        else
            std::cout << "not search" << std::endl;
    }

    // 16. search_n：在序列中，查找连续 Count 个的重复值，如果 count = 0，返回 first，如果没找到，就返回 last
    {
        const std::vector<int> v1 = {1, 3, 3, 3, 4, 4, 2};
        std::size_t count = 2;
        auto search_n = std::search_n(v1.cbegin(), v1.cend(), count, 3); // 查找连续重复 2 次的数字 3

        if( count != 0 && search_n != v1.cend() )
            std::cout << "search_n index " << search_n - v1.cbegin() << std::endl;
        else
            std::cout << "not search_n" << std::endl;
    }

    return EXIT_SUCCESS;
}