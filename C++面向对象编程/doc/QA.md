## QA

+ inline 的使用
+ 构造函数默认参数，初值列（initialization list）
+ class 分为带指针和不带指针的，对于不带指针的，可以不用写析构函数
+ 构造函数重载（overloading）

    ```c++
    class complex 
    {
    public:
        complex(double r = 0, double i = 0)
            : re(r), im(i) 
        { };
    }

    ```

+ 构造函数放在 private 区域，表示该对象不能够被外接创建对象-单例对象

    ```C++
    // 单例对象

    class A {
    public:
        static A& getInstance();

    private:
        A();
        A(const A& rhs);
    }

    A& A::getInstance() 
    {
        static A a;
        return a;
    }

    ```

+ 常量成员函数-不会改变 class 内部数据，如果不会改变，就在函数后加 const

    ```C++

    class complex 
    {
    public:
        double real() const { return re; }
    }

    // 调用
    complex c1(2, 1);
    cout << c1.real();

    // 如果不加 const 
    const complex c1(2, 1);
    c1.real(); // 如果不加，就会出错


    ```

+ 值传递和引用传递
+ 引用传递（const reference）
+ 友元函数（friend）
+ 同一个 class 的各个 objects 互为 friends
    ```c++

    class complex 
    {
    public: 
        int func(const complex& param) { return param.re + param.im};
    }


    complex c1(2, 1);
    complex c2; 

    c2.func(c1);

    ```

+ 操作符重载（operator overloading）之一成员函数： this  ?? 其他成员函数是否有 this

    ```c++
    inline complex& complex::operator += (const complex &r) {
        return __doapl(this, r);
    }


    ```
    操作符重载需要考虑连串使用的情况， 例如 C1 += C2 += C3;

+ 操作符重载（operator overloading）之2-非成员函数（无 this）

    ```c++

    inline complex operator + (const complex &x,  const complex &y) {
        return complex( real(x) + real(y), imag(x) + imag(y));
    }

    inline complex operator + (const complex &x,  double y) {
        return complex( real(x) + y, imag(x) );
    }    
    ```

## 
+ strlen 不包含 '\0' 字符串，'\0' 的 ASCII 码值为 0 
+ class with pointer member 必须有 **拷贝构造**和**拷贝赋值**

    ```c++
    inline String& String::operator= (const String& str)
    {
        // 检测自我赋值，self assignment
        if (this == &st)
            return *this;
        

        delete[] m_data;
        m_data = new char[ strlen(str.m_data) + 1 ];
        strcpy(m_data, str.m_data);

        return *this;
    }

    ```


+ 浅拷贝和深拷贝
+ 栈内的对象，又被称值为 auto object，声明周期在结束后结束
+ static object,作用域为整个程序
+ global object，在作用域是整个程序
+ new： 先分配内存 memory，再调用构造函数
+ delete： 先调用析构函数，再释放 memory，动态数组 delete 方式