#include <cstdlib>
#include <cstdio>
#include <exception>
#include "mem_pool.hpp"

template <typename T>
T *create(int n)
{
    T *ptr = (T *)malloc(sizeof(T) * n);
    T *beg = ptr;
    T *end = ptr + n;
    printf("%p %p\n", beg, end);
    printf("%ld\n", end - beg); // 步长
    return ptr;
}

template <typename T>
T *create2(int n)
{
    T *ptr = new T[n];
    T *beg = ptr;
    T *end = beg + n;
    printf("%p %p\n", beg, end);
    return ptr;
}

class T
{
public:
    T()
    {
        *m_c = 'c';
    }
    char *c()
    {
        return m_c;
    }

private:
    char *m_c = (char *)malloc(1);
};

#include <iostream>

class Sub
{
public:
    Sub()
    {
        std::cout << "sub" << std::endl;
    }
    ~Sub()
    {
        std::cout << "~sub" << std::endl;
    }
};

class A
{
private:
    static Sub *sub;
};

Sub *A::sub = new Sub();

int main(int argc, char *argv[])
{
    // char *beg = (char *)malloc(sizeof(char) * 10);
    // char *end = beg + 10;
    // sprintf(beg, "test");
    // printf("%p %p\n", beg, end);
    // printf("%c\n", *(beg + 3));

    // auto *ptr = create<int>(1);

    // auto *ptr2 = create2<char>(10);
    // delete[] ptr2;

    // sprintf(ptr, "test");
    // printf("%s\n", ptr);

    // try {
    //     throw 1;
    // }
    // catch (std::exception &e) {
    //     printf("%s\n", e.what());
    // }
    // while (1) {
    // }

    // try {
    //     throw 1;
    // }
    // catch (int a) {
    //     printf("%d\n", a);
    // }

    // T t;
    // *t.c() = 'a';

    // printf("%c\n", *t.c());

    // MemPool<int> mempool;

    MemBlock<char> memblock(10);

    auto *ptr = memblock.allocate(10);
    if (ptr) {
        printf("ptr not nullptr\n");
        sprintf(ptr, "123456789");
        printf("%s\n", ptr);
    }


    return 0;
}