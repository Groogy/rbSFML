#pragma once

namespace rb
{
    
    namespace priv
    {
        
        template<Object(*Func)(int, Object[])>
        VALUE callback_noself(int argc, VALUE argv[], VALUE self)
        {
            (void)self;
            RBPROTECT
            ({
                return Func(argc, reinterpret_cast<Object*>(argv));
            })
        }
        
        template<Object(*Func)()>
        VALUE callback_noself(VALUE self)
        {
            (void)self;
            RBPROTECT
            ({
                return Func();
            })
        }
        
        template<Object(*Func)(Object)>
        VALUE callback_noself(VALUE self, VALUE arg1)
        {
            (void)self;
            RBPROTECT
            ({
                return Func(arg1);
            })
        }
        
        template<Object(*Func)(Object, Object)>
        VALUE callback_noself(VALUE self, VALUE arg1, VALUE arg2)
        {
            (void)self;
            RBPROTECT
            ({
                return Func(arg1, arg2);
            })
        }
        
        template<Object(*Func)(Object, Object, Object)>
        VALUE callback_noself(VALUE self, VALUE arg1, VALUE arg2, VALUE arg3)
        {
            (void)self;
            RBPROTECT
            ({
                return Func(arg1, arg2, arg3);
            })
        }
        
        template<Object(*Func)(Object, Object, Object, Object)>
        VALUE callback_noself(VALUE self, VALUE arg1, VALUE arg2, VALUE arg3, VALUE arg4)
        {
            (void)self;
            RBPROTECT
            ({
                return Func(arg1, arg2, arg3, arg4);
            })
        }
        
    }
    
}
