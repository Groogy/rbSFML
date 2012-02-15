#pragma once

#include "Module.hpp"

namespace rb
{
    
    class Class;
    class Class : public Module
    {
        
        enum {PUBLIC, PROTECTED, PRIVATE} m_next_method;
        
    public:
        
        Class() : m_next_method(PUBLIC) {}
        Class(VALUE v) : Module(v), m_next_method(PUBLIC) {}
        Class(BasicObject o) : Module(o), m_next_method(PUBLIC) {}
        
        static Class Define(const char* name, Class super = rb_cObject);
        static Class Define(Module under, const char* name, Class super = rb_cObject);
        
        template<typename... Args>
        Object New(Args... args);
        
        Class& Public()    {m_next_method = PUBLIC;    return *this;}
        Class& Protected() {m_next_method = PROTECTED; return *this;}
        Class& Private()   {m_next_method = PRIVATE;   return *this;}
        
        template<typename... Args>
        Class& Public(const char* name);
        template<typename... Args>
        Class& Public(const char* name, const char* name2, const Args&... args);
        
        template<typename... Args>
        Class& Protected(const char* name);
        template<typename... Args>
        Class& Protected(const char* name, const char* name2, const Args&... args);
        
        template<typename... Args>
        Class& Private(const char* name);
        template<typename... Args>
        Class& Private(const char* name, const char* name2, const Args&... args);
        
        template<Object(*Func)(int, Object[], Object)>
        Class& def(const char* name);
        template<Object(*Func)(Object)>
        Class& def(const char* name);
        template<Object(*Func)(Object, Object)>
        Class& def(const char* name);
        template<Object(*Func)(Object, Object, Object)>
        Class& def(const char* name);
        template<Object(*Func)(Object, Object, Object, Object)>
        Class& def(const char* name);
        template<Object(*Func)(Object, Object, Object, Object, Object)>
        Class& def(const char* name);
		
		Class& alias( const char* newName, const char* originalName );
        
    };
    
}
