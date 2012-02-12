#pragma once

#include "Object.hpp"
#include "Global.hpp"
#include "conversions.hpp"

namespace rb
{
    
    class Exception : public Object, public std::exception
    {
    
    public:
    
        Exception() : Object(Class(rb_eException).New()) {}
        Exception(VALUE v) : Object(v) {}
        Exception(BasicObject o) : Object(o) {}
        Exception(const char* msg) : Object(Class(rb_eException).New(ruby_cast<Object>(msg))) {}
        
        virtual const char* what() throw()
        {
            return ruby_cast<char*>(call("message"));
        }
        
    };
    
}
