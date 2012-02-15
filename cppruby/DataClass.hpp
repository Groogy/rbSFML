#pragma once

#include "Class.hpp"
#include "callback_dataclass.hpp"

namespace rb
{
    
    template<typename T>
    class RbAllocator : public std::allocator<T>
    {
    public:
        
        T* allocate(std::size_t amount)
        {
            void* ptr = xmalloc(amount * sizeof(T));
            if (ptr == NULL) throw std::bad_alloc();
            return reinterpret_cast<T*>(ptr);
        }

        void deallocate(T* obj, std::size_t amount)
        {
            (void)amount;
            xfree(reinterpret_cast<void*>(obj));
        }
        
    };

    template<typename T, typename Allocator = RbAllocator<T>>
    class DataClass;
    template<typename T, typename Allocator>
    class DataClass : public Module
    {
        
        enum {PUBLIC, PROTECTED, PRIVATE} m_next_method;
        
    public:
        
        DataClass() {}
        DataClass(VALUE v) : Module(v) {}
        DataClass(BasicObject o) : Module(o) {}
        
        static DataClass<T, Allocator> Define(const char* name, Class super = rb_cObject);
        static DataClass<T, Allocator> Define(Module under, const char* name, Class super = rb_cObject);
        
        template<typename... Args>
        T& New(Args... args);
        
        DataClass<T, Allocator>& Public()    {m_next_method = PUBLIC;    return *this;}
        DataClass<T, Allocator>& Protected() {m_next_method = PROTECTED; return *this;}
        DataClass<T, Allocator>& Private()   {m_next_method = PRIVATE;   return *this;}
        
        template<typename... Args>
        DataClass<T, Allocator>& Public(const char* name);
        template<typename... Args>
        DataClass<T, Allocator>& Public(const char* name, const char* name2, const Args&... args);
        
        template<typename... Args>
        DataClass<T, Allocator>& Protected(const char* name);
        template<typename... Args>
        DataClass<T, Allocator>& Protected(const char* name, const char* name2, const Args&... args);
        
        template<typename... Args>
        DataClass<T, Allocator>& Private(const char* name);
        template<typename... Args>
        DataClass<T, Allocator>& Private(const char* name, const char* name2, const Args&... args);
        
        template<Object(T::*Func)(int, Object[])>
        DataClass<T, Allocator>& def(const char* name);
        template<Object(T::*Func)()>
        DataClass<T, Allocator>& def(const char* name);
        template<Object(T::*Func)(Object)>
        DataClass<T, Allocator>& def(const char* name);
        template<Object(T::*Func)(Object, Object)>
        DataClass<T, Allocator>& def(const char* name);
        template<Object(T::*Func)(Object, Object, Object)>
        DataClass<T, Allocator>& def(const char* name);
        template<Object(T::*Func)(Object, Object, Object, Object)>
        DataClass<T, Allocator>& def(const char* name);
		
		DataClass<T, Allocator>& alias( const char* newName, const char* originalName );
        
    };
    
}
