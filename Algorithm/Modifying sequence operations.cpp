#include <iostream>
#include <algorithm>
#include <vector>

// 主要使用 C++11 可以使用的 API (/63)
// https://en.cppreference.com/w/cpp/algorithm

using namespace std;

int gen() 
{
    static int value = 0;
    value++;

    return value * value;
}

int main(int argc, char **argv)
{
    // 1. copy: 将集合元素复制到目标位置，注意提前分配好对应的 size, 返回复制后元素区间的最后一个位置
    // https://www.cnblogs.com/heyonggang/p/3265142.html
    {
        std::vector<int> v1 {1, 2, 3, 4 ,5};
        std::vector<int> v2;

        v2.resize(v1.size()); // 需要重新分配空间
        auto copy = std::copy(v1.cbegin(), v1.cend(), v2.begin());

        typedef ostream_iterator<int> OstreamItr;

        if( copy == v2.cend() ) 
        {
            std::copy(v2.cbegin(), v2.cend(),  OstreamItr(std::cout, " "));
            std::cout << std::endl;
        }            
        else 
            std::cout << "copy fail" << std::endl;
    }

    // 2. copy_if  将集合元素复制到目标位置，但是会执行一些列操作
    {
        std::vector<int> v1 {1, 2, 3, 4 ,5};
        std::vector<int> v2;

        v2.resize(v1.size()); // 需要重新分配空间
        auto copy_if = std::copy_if(v1.cbegin(), v1.cend(), v2.begin(), [](const int& i) { return i > 3; });
        
        typedef ostream_iterator<int> OstreamItr;
        std::copy(v2.begin(), copy_if,  OstreamItr(std::cout, " "));
        std::cout << std::endl;
    }

    // 3. copy_n  将集合前 n 个元素复制到目标位置，但是会执行一些列操作
    {
        std::vector<int> v1 {1, 2, 3, 4 ,5};
        std::vector<int> v2;

        v2.resize(v1.size()); // 需要重新分配空间
        auto copy_n = std::copy_n(v1.cbegin(), 2, v2.begin());
        
        typedef ostream_iterator<int> OstreamItr;
        std::copy(v2.begin(), copy_n,  OstreamItr(std::cout, " "));
        std::cout << std::endl;
    }

    // 4. copy_backward: 反者 copy,  
    {
        std::vector<int> v1 {1, 2, 3, 4 ,5};
        std::vector<int> v2;

        v2.resize(v1.size() + 1); // 此处分配空间大一些，所以 index 为 0 的位置填默认值 0

        // 这边返回值返回的是最后一个元素被填充的位置，可能并不是 v2 的起始位置
        auto copy_backward = std::copy_backward(v1.cbegin(), v1.cend(), v2.end());

        typedef ostream_iterator<int> OstreamItr;

        // 注意这里
        if( copy_backward == v2.end() - v1.size()) 
        {
            std::copy(v2.cbegin(), v2.cend(),  OstreamItr(std::cout, " "));
            std::cout << std::endl;
        }            
        else 
            std::cout << "copy_backward fail" << std::endl;
    }

    // 5. move: 跟 copy 效果类似，但是实现是通过右值移动来实现
    // 6. move_backward: 逆序 move，跟 copy_backward 类似
    // TODO: 实现有点不一致
    {
        std::vector<int> v1 {2, 1, 3, 4 ,5};
        std::vector<int> v2;
        v2 = std::move(v1);

        typedef ostream_iterator<int> OstreamItr;
        std::copy(v2.begin(), v2.end(),  OstreamItr(std::cout, " "));
        std::cout << std::endl;
    }
    
    // 7. fill, 以某个值填充一个集合
    // 8. fill_n, 填充集合里面 n 个元素值为指定值
    {
        std::vector<int> v1 {1, 2, 3, 4 ,5};
        std::fill(v1.begin(), v1.end(), 2);
        std::copy(v1.cbegin(), v1.cend(), std::ostream_iterator<int>(std::cout, " ")); // 2 2 2 2 2 
        std::cout << std::endl;

        std::fill_n(v1.begin(), 3, -1);
        std::copy(v1.cbegin(), v1.cend(), std::ostream_iterator<int>(std::cout, " ")); // -1 -1 -1 2 2
        std::cout << std::endl;
    }

    // 9. transform： 转换，类似于 swift 里面的 map 转换方法
    {
        std::vector<int> v1 {5, 4, 3, 2, 1};

        std::transform(v1.cbegin(), v1.cend(), v1.begin(), [](int i) { return i * i; } ); 
        std::copy(v1.cbegin(), v1.cend(), std::ostream_iterator<int>(std::cout, " ")); // 25 16 9 4 1
        std::cout << std::endl;
    }

    // 10. generate：生成器，给集合内的索引生成对应的内容
    // 11. generate_n: 生成前 N 个元素的值，
    {
        std::vector<int> v1 {5, 4, 3, 2, 1};

        int i = 0;
        std::generate(v1.begin(), v1.end(), [&i]() { i++; return i * i; } ); 
        std::copy(v1.cbegin(), v1.cend(), std::ostream_iterator<int>(std::cout, " "));//  1 4 9 16 25 
        std::cout << std::endl;

        i = 10;
        std::generate_n(v1.begin(), 2, [&i]() { i+=10; return i * i; } ); 
        std::copy(v1.cbegin(), v1.cend(), std::ostream_iterator<int>(std::cout, " "));//  400 900 9 16 25
        std::cout << std::endl;
    }

    // 12. remove: 删除元素 
    // 13. remove_if： 删除满足条件的元素
    // 注意返回值，返回值返回的是新的 end
    {
        std::vector<int> v1 {5, 4, 3, 3, 2, 2, 1};
        v1.erase(std::remove(v1.begin(), v1.end(), 3), v1.cend());
        std::copy(v1.cbegin(), v1.cend(), std::ostream_iterator<int>(std::cout, " ")); //  5 4 2 2 1
        std::cout << std::endl;

        v1.erase(std::remove_if(v1.begin(), v1.end(), [](int& i) {  return i < 3; }), v1.cend());
        std::copy(v1.cbegin(), v1.cend(), std::ostream_iterator<int>(std::cout, " ")); //  5 4
        std::cout << std::endl;
    }

    // 14. remove_copy 与 12 类似，不过 copy 了一份数据
    // 15. remove_copy_if 与 13类似，不过 copy 了一份数据
    {
        std::vector<int> v1 {5, 4, 3, 3, 2, 2, 1};
        std::vector<int> v2;
        v2.resize(v1.size());

        v2.erase(std::remove_copy(v1.begin(), v1.end(), v2.begin(), 3), v2.end());
        std::copy(v2.cbegin(), v2.cend(), std::ostream_iterator<int>(std::cout, " ")); //  5 4 2 2 1
        std::cout << std::endl;

        // 此处依旧使用的是 v1 来进行 copy
        v2.erase(std::remove_copy_if(v1.begin(), v1.end(), v2.begin(), [](int& i) {  return i < 3; }), v2.cend());
        std::copy(v2.cbegin(), v2.cend(), std::ostream_iterator<int>(std::cout, " ")); // 5 4 3 3
        std::cout << std::endl;
    }

    // 16. replace：替换
    // 17. replace_if： 根据条件替换
    {
        std::vector<int> v1 {5, 4, 3, 3, 2, 2, 1};
        std::replace(v1.begin(), v1.end(), 3, 30); // 将 3 换成 30
        std::copy(v1.cbegin(), v1.cend(), std::ostream_iterator<int>(std::cout, " ")); //  5 4 30 30 2 2 1
        std::cout << std::endl;
        
        std::replace_if(v1.begin(), v1.end(), [](int& i) {  return i < 3; }, -1); // 将 < 3 的全部换成 -1
        std::copy(v1.cbegin(), v1.cend(), std::ostream_iterator<int>(std::cout, " ")); // 5 4 30 30 -1 -1 -1
        std::cout << std::endl;
    }

    // 18. replace_copy: 会 copy 一份替换
    // 19. replace_copy_if： 会 copy 一份替换掉
    {
        std::vector<int> v1 {5, 4, 3, 3, 2, 2, 1};
        std::vector<int> v2;
        v2.resize(v1.size());

        v2.erase(std::replace_copy(v1.begin(), v1.end(), v2.begin(), 3, 30), v2.end());
        std::copy(v2.cbegin(), v2.cend(), std::ostream_iterator<int>(std::cout, " ")); // 5 4 30 30 2 2 1 
        std::cout << std::endl;

        // 此处依旧使用的是 v1 来进行 copy
        v2.erase(std::replace_copy_if(v1.begin(), v1.end(), v2.begin(), [](int& i) {  return i < 3; }, -1), v2.cend());
        std::copy(v2.cbegin(), v2.cend(), std::ostream_iterator<int>(std::cout, " ")); // 5 4 3 3 -1 -1 -1
        std::cout << std::endl;
    }
    

    return EXIT_SUCCESS;
}