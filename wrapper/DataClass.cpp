
#include "DataClass.hpp"
#include "Object.hpp"
#include "callback_dataclass.hpp"

namespace rb
{
    
    template<typename T, typename Allocator>
    DataClass<T, Allocator> DataClass<T, Allocator>::Define(const char* name, Class super)
    {
        VALUE klass = rb_define_class(name, super);
        rb_define_alloc_func(klass, priv::callback_alloc<T, Allocator>);
        return klass;
    }
    
    template<typename T, typename Allocator>
    DataClass<T, Allocator> DataClass<T, Allocator>::Define(Module under, const char* name, Class super)
    {
        VALUE klass = rb_define_class_under(under, name, super);
        rb_define_alloc_func(klass, priv::callback_alloc<T, Allocator>);
        return klass;
    }
    
    template<typename T, typename Allocator>
    template<typename... Args>
    T& DataClass<T, Allocator>::New(Args... args)
    {
        Object obj = rb_class_new_instance(sizeof...(args), (VALUE[]){args...}, value);
        return obj.data<T>();
    }
    
    template<typename T, typename Allocator>
    template<typename... Args>
    DataClass<T, Allocator>& DataClass<T, Allocator>::Public(const char* name)
    {
        call("public", ruby_cast<Object>(name));
        return *this;
    }
    
    template<typename T, typename Allocator>
    template<typename... Args>
    DataClass<T, Allocator>& DataClass<T, Allocator>::Public(const char* name, const char* name2, const Args&... args)
    {
        Public(name);
        return Public(name2, args...);
    }
    
    template<typename T, typename Allocator>
    template<typename... Args>
    DataClass<T, Allocator>& DataClass<T, Allocator>::Protected(const char* name)
    {
        call("protected", ruby_cast<Object>(name));
        return *this;
    }
    
    template<typename T, typename Allocator>
    template<typename... Args>
    DataClass<T, Allocator>& DataClass<T, Allocator>::Protected(const char* name, const char* name2, const Args&... args)
    {
        Protected(name);
        return Protected(name2, args...);
    }
    
    template<typename T, typename Allocator>
    template<typename... Args>
    DataClass<T, Allocator>& DataClass<T, Allocator>::Private(const char* name)
    {
        call("private", ruby_cast<Object>(name));
        return *this;
    }
    
    template<typename T, typename Allocator>
    template<typename... Args>
    DataClass<T, Allocator>& DataClass<T, Allocator>::Private(const char* name, const char* name2, const Args&... args)
    {
        Private(name);
        return Private(name2, args...);
    }
    
#define define_method(func, name, argc) \
    switch (m_next_method) \
    { \
        case PUBLIC:    rb_define_method          (value, name, func, argc); break; \
        case PROTECTED: rb_define_protected_method(value, name, func, argc); break; \
        case PRIVATE:   rb_define_private_method  (value, name, func, argc); break; \
    }
    
    template<typename T, typename Allocator>
    template<Object(T::*Func)(int, Object[])>
    DataClass<T, Allocator>& DataClass<T, Allocator>::def(const char* name)
    {
        auto f = priv::callback<T, Func>;
        define_method((VALUE(*)(...))f, name, -1);
        return *this;
    }
    
    template<typename T, typename Allocator>
    template<Object(T::*Func)()>
    DataClass<T, Allocator>& DataClass<T, Allocator>::def(const char* name)
    {
        auto f = priv::callback<T, Func>;
        define_method((VALUE(*)(...))f, name, 0);
        return *this;
    }
    
    template<typename T, typename Allocator>
    template<Object(T::*Func)(Object)>
    DataClass<T, Allocator>& DataClass<T, Allocator>::def(const char* name)
    {
        auto f = priv::callback<T, Func>;
        define_method((VALUE(*)(...))f, name, 1);
        return *this;
    }
    
    template<typename T, typename Allocator>
    template<Object(T::*Func)(Object, Object)>
    DataClass<T, Allocator>& DataClass<T, Allocator>::def(const char* name)
    {
        auto f = priv::callback<T, Func>;
        define_method((VALUE(*)(...))f, name, 2);
        return *this;
    }
    
    template<typename T, typename Allocator>
    template<Object(T::*Func)(Object, Object, Object)>
    DataClass<T, Allocator>& DataClass<T, Allocator>::def(const char* name)
    {
        auto f = priv::callback<T, Func>;
        define_method((VALUE(*)(...))f, name, 3);
        return *this;
    }
    
    template<typename T, typename Allocator>
    template<Object(T::*Func)(Object, Object, Object, Object)>
    DataClass<T, Allocator>& DataClass<T, Allocator>::def(const char* name)
    {
        auto f = priv::callback<T, Func>;
        define_method((VALUE(*)(...))f, name, 4);
        return *this;
    }
    
#undef define_method
    
}
