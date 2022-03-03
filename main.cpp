#include <iostream>
#include "Aspect.h"

/*
 * 切面方法类
 */
struct AA
{
    void Before() { std::cout << "Before from A" << std::endl; }
    void After() { std::cout << "After from A" << std::endl; }
};

/**
 * 测试类
 */
struct TT
{
    void g() { std::cout << "real g function" << std::endl; }
    void h(int a) { std::cout << "real h function " << a << std::endl; }
};

int main()
{
    TT tt;
    std::function<void(int)> ff = std::bind(&TT::h, &tt, std::placeholders::_1);

    // 织入
    int a = 3;
    Invoke<AA>([&ff, a]() { ff(a); });

    Invoke<AA, AA>([&tt]() { tt.g(); });

    return 0;
}
