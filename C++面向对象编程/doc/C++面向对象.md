## QA

+ conversion function, 转换函数
    ```C++
    class Fraction {
    public:
        Fraction(int num, int den=1): m_numeration(num), m_denominator(den) {}
        operator double() const {
            return (double)(m_numerator / m_denominator);
        }
    private:
        int m_numerator;    // 分子
        int m_denominator;  // 分母
    }

    Fraction f(3,5);
    double d = 4 + f;
    ```

+ non-explicit-one argument ctor

    ```c++
    class Fraction
    {
    public:
        Fraction(int num, int den=1): m_numerator(num), 

    }

    ```
+ conversion function vs non explicit one argument ctor 

    explicit: 明白的、明确的, 大多时候用在构造函数的前面
    ```c++


    ```

+ pointer-like classes 关于智能指针

```c++
template<class T>
class shared_ptr
{
public:
    T& operator*() const { return *px; }
    T*
}
```

+ pointer-like classes 关于迭代器, 迭代器拿 data
  
+ function-like classes 所谓模仿函数， 重写操作符 (), operator()


+ 函数模板，类模板
+ 模板特化： specialization
+ 模板偏特化
+ 模板模板

--------
+ reference: 引用底层使用指针实现的，但是从逻辑上来说引用为被引用变量的别名

    - 假象1：sizeof(r) == sizeof(x)
    - 假象2：&x == &r;
    - 简单理解为 reference 为封装很好的指针，多用于参数传递

+ reference 调用方式

    ```c++
    void func1(Cls* pobj) { pobj->xxxx(); }
    void func2(Cls obj) { obj.xxx(); }
    void func3(Cls& obj) { obj.xxx(); }

    Cls obj;
    func1(&obj);
    func2(obj);
    func3(obj)

    ```

+ QA: C++函数签名部分怎么判断
+ QA: const 修饰函数是否作为函数签名中的一部分
+ QA: 继承后构造函数和析构函数调用