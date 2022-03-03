//
// Created by mango on 2022/3/3.
//

#ifndef AOP_ASPECT_H
#define AOP_ASPECT_H

#include <functional>

/**
 * 切面代理类,自行实现Before/After方法
 */
struct Aspect
{
    Aspect(const Aspect&) = delete;
    void operator=(const Aspect&) = delete;

    template<class Func>
    explicit Aspect(const Func &f) : m_func(f) {}

    template<class T>
    void Invoke(T &&value)
    {
        value.Before();
        m_func();   // 切面类的切点
        value.After();
    }

    template<typename Head, typename... Tail>
    void Invoke(Head &&head, Tail &&...tail)// 支持切面组合 Head Tail 并不要求派生于某个基类
    {
        head.Before();
        Invoke(std::forward<Tail>(tail)...);
        head.After();
    }

private:
    std::function<void()> m_func;
};

template<typename... AP>
void Invoke(const std::function<void()> &f)
{
    Aspect msp(f);  // 构造切面（组合）的代理对象
    msp.Invoke(AP()...);
}

#endif//AOP_ASPECT_H
