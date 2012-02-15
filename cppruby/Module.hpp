#pragma once

#include "Object.hpp"
#include "Identifier.hpp"

namespace rb
{
    
    class Module;
    class Module : public Object
    {
    public:
        
        Module() {}
        Module(VALUE v) : Object(v) {}
        Module(BasicObject o) : Object(o) {}
        
        static Module Define(const char* name);
        static Module Define(Module under, const char* name);
		
		template<Object(*Func)(int, Object[], Object)>
        Module& def(const char* name);
        template<Object(*Func)(Object)>
        Module& def(const char* name);
        template<Object(*Func)(Object, Object)>
        Module& def(const char* name);
        template<Object(*Func)(Object, Object, Object)>
        Module& def(const char* name);
        template<Object(*Func)(Object, Object, Object, Object)>
        Module& def(const char* name);
        template<Object(*Func)(Object, Object, Object, Object, Object)>
        Module& def(const char* name);
		
		Module& include( Module module );
        
    };
    
}
