
#include "Module.hpp"

namespace rb
{
    
    Module Module::Define(const char* name)
    {
        return rb_define_module(name);
    }
    
    Module Module::Define(Module under, const char* name)
    {
        return rb_define_module_under(under, name);
    }
	
	#define define_method(func, name, argc) \
		rb_define_method          (value, name, func, argc)
	
	template<Object(*Func)(int, Object[], Object)>
    Module& Module::def(const char* name)
    {
        auto f = priv::callback<Func>;
        define_method((VALUE(*)(...))f, name, -1);
        return *this;
    }
    
    template<Object(*Func)(Object)>
    Module& Module::def(const char* name)
    {
        auto f = priv::callback<Func>;
        define_method((VALUE(*)(...))f, name, 0);
        return *this;
    }
    
    template<Object(*Func)(Object, Object)>
    Module& Module::def(const char* name)
    {
        auto f = priv::callback<Func>;
        define_method((VALUE(*)(...))f, name, 1);
        return *this;
    }
    
    template<Object(*Func)(Object, Object, Object)>
    Module& Module::def(const char* name)
    {
        auto f = priv::callback<Func>;
        define_method((VALUE(*)(...))f, name, 2);
        return *this;
    }
    
    template<Object(*Func)(Object, Object, Object, Object)>
    Module& Module::def(const char* name)
    {
        auto f = priv::callback<Func>;
        define_method((VALUE(*)(...))f, name, 3);
        return *this;
    }
    
    template<Object(*Func)(Object, Object, Object, Object, Object)>
    Module& Module::def(const char* name)
    {
        auto f = priv::callback<Func>;
        define_method((VALUE(*)(...))f, name, 4);
        return *this;
    }
    
	Module& Module::include( Module module )
	{
		rb_include_module( value, module );
	}
}

#undef define_method