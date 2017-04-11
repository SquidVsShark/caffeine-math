/*
  Array
  --
  Stack based array that can by dynamically resized.
  Sorta a mix between a vector and an array.

  This was designed only with POD types in mind. Will not be safe for
  non pod types.

  Copyright: public-domain
*/
#ifndef ARRAY_INCLUDED_E3E1A14B_B476_40C7_9453_ECD5F3F344F2
#define ARRAY_INCLUDED_E3E1A14B_B476_40C7_9453_ECD5F3F344F2


#include "alloc.hpp"
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <new>


// -------------------------------------------------------- [ Array Config ] --


#ifndef LIB_NS_NAME
#define LIB_NS_NAME lib
#endif


// ------------------------------------------------------ [ Array Template ] --


namespace LIB_NS_NAME {


template<
  typename T,
  size_t _init_capacity = 32,
  malloc_fn _malloc     = malloc,
  realloc_fn _realloc   = realloc,
  free_fn _free         = free
>
class array
{
public:


  // ------------------------------------------------------ [ Constructors ] --


  explicit array()
  : m_stack_data()
  , m_begin(m_stack_data)
  , m_end(m_begin)
  , m_capacity(m_begin + (_init_capacity ? _init_capacity : 1))
  {
    static_assert(__is_pod(T), "array is for POD types only");
  }

  explicit array(T *begin, T *end)
  : array()
  {
    const size_t cap = end - begin;
    resize(cap);

    memcpy(m_begin, begin, sizeof(T) * cap);
  }

  template<typename ...Args>
  array(const Args &...args)
  : m_stack_data{args...}
  , m_begin(m_stack_data)
  , m_end(m_begin + sizeof...(args))
  , m_capacity(m_begin + (_init_capacity ? _init_capacity : 1))
  {
    static_assert(__is_pod(T), "array is for POD types only");
  }


  // -------------------------------------------------------- [ Destructor ] --


  ~array()
  {
    if(m_begin != m_stack_data)
    {
      _free(m_begin);
    }
  }


  // ------------------------------------------------ [ Capacity Modifiers ] --


  void
  reserve(const size_t new_size)
  {
    const size_t curr_size = size();
    const size_t curr_cap = capacity();

    if(new_size < curr_cap)
    {
      return;
    }

    if(m_stack_data == m_begin)
    {
      m_begin = (T*)_malloc(sizeof(T) * new_size);
      memcpy(m_begin, m_stack_data, sizeof(T) * curr_size);
    }
    else
    {
      m_begin = (T*)_realloc(m_begin, sizeof(T) * new_size);
    }

    m_end      = m_begin + curr_size;
    m_capacity = m_begin + new_size;
  }

  void
  resize(const size_t new_size)
  {
    reserve(new_size);
    const size_t curr_size = size();
    m_end = m_begin + (new_size > curr_size ? new_size : curr_size);
  }


  // ----------------------------------------------------- [ Push / Insert ] --


  void
  push_back(T &&item)
  {
    m_end < m_capacity ?
      _fast_push(static_cast<T&&>(item)) :
      _slow_push(static_cast<T&&>(item));
  }
  
  void
  push_back(const T &item)
  {
    m_end < m_capacity ?
        _fast_push(static_cast<T>(item)) :
        _slow_push(static_cast<T>(item));
  }

  template<typename ...Args>
  void
  emplace_back(Args&& ...args)
  {
    m_end < m_capacity ?
      _fast_emplace(args...) :
      _slow_emplace(args...);
  }
  
  T*
  insert(const size_t i, const T &item)
  {
    _insert_space(i, 1);
    
    m_begin[i] = item;
    m_end += 1;
  
    return &m_begin[i];
  }
  
  
  T*
  insert(const size_t i, const T *start, const size_t count)
  {
    _insert_space(i, count);

    memcpy(m_begin + i, start, sizeof(T) * count);
    m_end += count;
    
    return &m_begin[i];
  }
  
//  template<typename ...Args>
//  T*
//  insert(const size_t i, Args&& ...args)
//  {
//    if(m_end == m_capacity)
//    {
//      reserve(size() << 1);
//    }
//
//    if(i < size())
//    {
//      const size_t insert_index = i + 1;
//      const size_t size_to_end  = size() - i;
//
//      memmove(m_begin + insert_index, m_begin + i, size_to_end * sizeof(T));
//      m_end += 1;
//
//      new(&m_begin[i]) T{args...};
//    }
//
//    return &m_begin[i];
//  }


  // -------------------------------------------------------- [ Pop / Erase ] --


  void
  pop_back()
  {
    if(size())
    {
      m_end -= 1;
    }
  }


  void
  erase(const size_t i)
  {
    const size_t curr_size = size();

    if(i < curr_size)
    {
      const size_t index_to_erase = i;
      const size_t start_index    = i + 1;
      const size_t size_to_end    = (sizeof(T) * curr_size) - (sizeof(T) * i);

      memmove(m_begin + index_to_erase, m_begin + start_index, size_to_end);

      m_end -= 1;
    }
  }
  
  void
  erase(const size_t start, const size_t count)
  {
    const size_t curr_size = size();

    if((start + count) <= curr_size)
    {
      const size_t index_to_erase = start;
      const size_t start_index    = start + count;
      const size_t size_to_end    = (sizeof(T) * curr_size) - (sizeof(T) * start);

      memmove(m_begin + index_to_erase, m_begin + start_index, size_to_end);

      m_end -= (count);
    }
  }

  void
  clear()
  {
    m_end = m_begin;
  }


  // --------------------------------------------------- [ Element Access ] --


  T& operator[](const size_t i)             { return m_begin[i]; }
  const T& operator[](const size_t i) const { return m_begin[i]; }

  T* data()             { return m_begin; }
  T const* data() const { return m_begin; }

  T* begin()             { return m_begin; }
  T const* begin() const { return m_begin; }

  T* end()             { return m_end; }
  T const* end() const { return m_end; }

  T& front()             { return *m_begin; };
  const T& front() const { return *m_begin; };

  T& back()             { return *(m_end - 1); };
  const T& back() const { return *(m_end - 1); };

  T& at(const size_t i)
  {
    return m_begin[i >= size() ? size() - 1 : i];
  }

  const T& at(const size_t i) const
  {
    return m_begin[i >= size() ? size() - 1 : i];
  }
  
  const T& top() const { return *(m_end - 1); }
  T& top() { return *(m_end - 1); }


  // --------------------------------------------------- [ Various Getters ] --


  bool empty() const        { return (m_end == m_begin); }
  size_t size() const       { return (m_end - m_begin); }
  size_t capacity() const   { return (m_capacity - m_begin); }


private:


  // --------------------------------------------------- [ Private Methods ] --


  void _fast_push(T &&item)
  {
    new(m_end) T(item);
    m_end += 1;
  }

  void _fast_push(const T &item)
  {
    new(m_end) T(item);
    m_end += 1;
  }

  void _slow_push(T &&item)
  {
    reserve(size() << 1);
    _fast_push(static_cast<T&&>(item));
  }

  void _slow_push(const T &item)
  {
    reserve(size() << 1);
    _fast_push(item);
  }

  template<typename ...Args>
  void _fast_emplace(Args &&...args)
  {
    new(m_end) T{args...};
    m_end += 1;
  }

  template<typename ...Args>
  void _slow_emplace(Args &&...args)
  {
    reserve(capacity() << 1);
    _fast_emplace(args...);
  }
  
  void _insert_space(const size_t i, const size_t count)
  {
    if(m_end + count > m_capacity)
    {
      reserve(capacity() << 1);
    }
    
    const size_t insert_index = i + count;
    const size_t size_to_end  = size() - i;
    
    memmove(m_begin + insert_index, m_begin + i, size_to_end * sizeof(T));
  }

private:

  T       m_stack_data[_init_capacity ? _init_capacity : 1];
  T*      m_begin;
  T*      m_end;
  T*      m_capacity;

};


} // ns


#endif // inc guard
