
#include "Class.hpp"
#include "callback_class.hpp"

namespace rb
{
    
    Class Class::Define(const char* name, Class super)
    {
        return rb_define_class(name, super);
    }
    
    Class Class::Define(Module under, const char* name, Class super)
    {
        return rb_define_class_under(under, name, super);
    }
    
    template<typename... Args>
    Object Class::New(Args... args)
    {
        return rb_class_new_instance(sizeof...(args), (VALUE[]){args...}, value);
    }
    
    template<typename... Args>
    Class& Class::Public(const char* name)
    {
        call("public", ruby_cast<Object>(name));
        return *this;
    }
    
    template<typename... Args>
    Class& Class::Public(const char* name, const char* name2, const Args&... args)
    {
        Public(name);
        return Public(name2, args...);
    }
    
    template<typename... Args>
    Class& Class::Protected(const char* name)
    {
        call("protected", ruby_cast<Object>(name));
        return *this;
    }
    
    template<typename... Args>
    Class& Class::Protected(const char* name, const char* name2, const Args&... args)
    {
        Protected(name);
        return Protected(name2, args...);
    }
    
    template<typename... Args>
    Class& Class::Private(const char* name)
    {
        call("private", ruby_cast<Object>(name));
        return *this;
    }
    
    template<typename... Args>
    Class& Class::Private(const char* name, const char* name2, const Args&... args)
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
    
    template<Object(*Func)(int, Object[], Object)>
    Class& Class::def(const char* name)
    {
        auto f = priv::callback<Func>;
        define_method((VALUE(*)(...))f, name, -1);
        return *this;
    }
    
    template<Object(*Func)(Object)>
    Class& Class::def(const char* name)
    {
        auto f = priv::callback<Func>;
        define_method((VALUE(*)(...))f, name, 0);
        return *this;
    }
    
    template<Object(*Func)(Object, Object)>
    Class& Class::def(const char* name)
    {
        auto f = priv::callback<Func>;
        define_method((VALUE(*)(...))f, name, 1);
        return *this;
    }
    
    template<Object(*Func)(Object, Object, Object)>
    Class& Class::def(const char* name)
    {
        auto f = priv::callback<Func>;
        define_method((VALUE(*)(...))f, name, 2);
        return *this;
    }
    
    template<Object(*Func)(Object, Object, Object, Object)>
    Class& Class::def(const char* name)
    {
        auto f = priv::callback<Func>;
        define_method((VALUE(*)(...))f, name, 3);
        return *this;
    }
    
    template<Object(*Func)(Object, Object, Object, Object, Object)>
    Class& Class::def(const char* name)
    {
        auto f = priv::callback<Func>;
        define_method((VALUE(*)(...))f, name, 4);
        return *this;
    }
	
	Class& Class::alias( const char* newName, const char* originalName )
	{
		rb_define_alias( value, newName, originalName );
		return *this;
	}
    
#undef define_method
    
}
