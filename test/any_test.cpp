//
//  any_test.cpp
//  canvas
//
//  Created by Kimmy  on 3/20/16.
//  Copyright (c) 2016 TDCA. All rights reserved.
//

#include "../include/unittest.h"

#include <memory>
#include <string>

class any
{
    class Object
    {
    public:
        virtual ~Object() = 0;
    };
    

    template<class T>
    class Box: public Object
    {
        T t;
    public:
        Box(const T& t): t(t) {}
        T value() const
        {
            return t;
        }
        
        virtual ~Box() {}
    };
    
    std::shared_ptr<Object> object;
    
public:
    
    template<class T>
    any(const T& t): object{std::make_shared<Box<T>>(t)} {}
    
    template<class T>
    std::shared_ptr<T> cast() const
    {
        if (auto obj = std::dynamic_pointer_cast<Box<T>>(object)) {
            return std::make_shared<T>(obj->value());
        }
        return nullptr;
    }
    
    template<class T>
    any& operator=(const T& value)
    {
        object = std::make_shared<Box<T>>(value);
        return *this;
    }
};

any::Object::~Object()
{
}

TestCase(Any_Test)
{
    any x {1};
    
    auto y = *(x.cast<int>());
    
    TestAssert(y == 1);
    
    x = std::string {"hello"};
    
    TestAssert(*(x.cast<std::string>()) == "hello");
}