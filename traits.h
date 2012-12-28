
#ifndef __TRAITS_H
#define __TRAITS_H

class Object;

struct __true_t {};
struct __false_t {};

template<class T>
struct __base_traits{
    typedef typename T::base base;
    typedef __false_t is_pod_t;
    static const int is_pod = 0;
    static const int is_scalar = T::is_scalar;
};

template<>
struct __base_traits<char>{
    typedef Object base;
    typedef __true_t is_pod_t;
    static const int is_pod = 1;
    static const int is_scalar = 0;
};

template<>
struct __base_traits<unsigned char>{
    typedef Object base;
    typedef __true_t is_pod_t;
    static const int is_pod = 1;
    static const int is_scalar = 0;
};

template<>
struct __base_traits<short>{
    typedef Object base;
    typedef __true_t is_pod_t;
    static const int is_pod = 1;
    static const int is_scalar = 0;
};

template<>
struct __base_traits<unsigned short>{
    typedef Object base;
    typedef __true_t is_pod_t;
    static const int is_pod = 1;
    static const int is_scalar = 0;
};

template<>
struct __base_traits<int>{
    typedef Object base;
    typedef __true_t is_pod_t;
    static const int is_pod = 1;
    static const int is_scalar = 0;
};

template<>
struct __base_traits<unsigned int>{
    typedef Object base;
    typedef __true_t is_pod_t;
    static const int is_pod = 1;
    static const int is_scalar = 0;
};

template<>
struct __base_traits<long>{
    typedef Object base;
    typedef __true_t is_pod_t;
    static const int is_pod = 1;
    static const int is_scalar = 0;
};

template<>
struct __base_traits<unsigned long>{
    typedef Object base;
    typedef __true_t is_pod_t;
    static const int is_pod = 1;
    static const int is_scalar = 0;
};


template<>
struct __base_traits<float>{
    typedef Object base;
    typedef __true_t is_pod_t;
    static const int is_pod = 1;
    static const int is_scalar = 0;
};


template<>
struct __base_traits<double>{
    typedef Object base;
    typedef __true_t is_pod_t;
    static const int is_pod = 1;
    static const int is_scalar = 0;
};

template<class T>
struct traits{
    typedef typename __base_traits<T>::base base;
    typedef typename __base_traits<T>::is_pod_t is_pod_t;
    typedef __true_t is_ptr_t;
    typedef T orig;
    typedef T* ptr;
    typedef T& ref;
    typedef const T cst;
    typedef const T* cptr;
    typedef const T& cref;
    static const int is_pod = __base_traits<T>::is_pod;
    static const int is_scalar = __base_traits<T>::is_scalar;
    static const int is_ptr = 0;
};

template<class T>
struct traits<T*>{
    typedef typename __base_traits<T>::base base;
    typedef typename __base_traits<T>::is_pod_t is_pod_t;
    typedef __true_t is_ptr_t;
    typedef T orig;
    typedef T* ptr;
    typedef T& ref;
    typedef const T cst;
    typedef const T* cptr;
    typedef const T& cref;
    static const int is_pod = __base_traits<T>::is_pod;
    static const int is_scalar = __base_traits<T>::is_scalar;
    static const int is_ptr = 1;
};

template<class T>
struct traits<const T*>{
    typedef typename __base_traits<T>::base base;
    typedef typename __base_traits<T>::is_pod_t is_pod_t;
    typedef __true_t is_ptr_t;
    typedef T orig;
    typedef T* ptr;
    typedef T& ref;
    typedef const T cst;
    typedef const T* cptr;
    typedef const T& cref;
    static const int is_pod = __base_traits<T>::is_pod;
    static const int is_scalar = __base_traits<T>::is_scalar;
    static const int is_ptr = 1;
};


#endif
