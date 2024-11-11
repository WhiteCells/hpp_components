#ifndef _MEM_POOL_H_
#define _MEM_POOL_H_

#include <cstdlib>

// malloc(10)
// 
// MemPool::allocate(10)
template <typename T>
class MemPage;

template <typename T>
class MemBlock;

template <typename T>
class MemPool
{
public:
    MemPool(std::size_t block_size) :
        m_page(new MemPage<T>(block_size)),
        m_block_size(block_size)
    {
    }
    ~MemPool()
    {
        clear();
    }

    void clear()
    {
        while (m_page) {
            MemPage<T> *tmp = m_page;
            m_page = m_page->m_next;
            delete tmp;
        }
        m_page = nullptr;
    }

    T *allocate()
    {
        
    }

private:
    MemPage<T> *m_page;
    std::size_t m_block_size;
};

template <typename T>
class MemPage
{
public:
    MemPage(std::size_t block_size) :
        m_block(new MemBlock<T>(block_size)),
        m_next(nullptr)
    {
    }
    ~MemPage()
    {
        delete m_block;
    }

private:
    MemBlock<T> *m_block;
    MemPage *m_next;
};

template <typename T>
class MemBlock
{
public:
    explicit MemBlock(std::size_t size) :
        m_beg(new T[size]),
        m_last(m_beg),
        m_end(m_beg + size)
    {
    }

    ~MemBlock()
    {
        delete[] m_beg;
    }

    std::size_t remainT() const
    {
        return m_end - m_last;
    }

    std::size_t remainByte() const
    {
        return remainT() * T_byte();
    }

    std::size_t T_byte() const
    {
        return sizeof(T);
    }

    T *allocate()
    {
        if (m_last <= m_end) {
            return m_last++;
        }
        return nullptr;
    }

    T *allocate(std::size_t size)
    {
        if (m_last + size <= m_end) {
            T *allocate_beg = m_last;
            m_last += size;
            return allocate_beg;
        }
        return nullptr;
    }

private:
    T *m_beg;
    T *m_last;
    T *m_end;
};

#endif // _MEM_POOL_H_