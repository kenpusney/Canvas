
#ifndef __MARCO_ENUM_H__
#define __MARCO_ENUM_H__

#include "marco/list.h"

#define __TOK_DICT(e) __##e##_dict

#define define_literal_enum(E, args...) \
    enum class E : unsigned int {\
        args\
    };\
    constexpr const char* __TOK_DICT(E)[] = { __STRINGIFY_ALL(args) };\
    inline constexpr const char * repr(const E& token){ \
        return __TOK_DICT(E)[static_cast<unsigned int>(token)];  \
    }

#endif