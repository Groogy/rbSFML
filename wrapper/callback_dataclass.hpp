#pragma once

#include "Exception_protect.hpp"

namespace rb
{
    
    namespace priv
    {
        
        template<typename T, typename Allocator = std::allocator<T>>
        void callback_free(void* ptr)
        {
            RBPROTECT
            ({
                T* obj = reinterpret_cast<T*>(ptr);
                obj->T::~T();
                Allocator().deallocate(obj, 1);
            })
        }
        
        template<typename T, typename Allocator = std::allocator<T>>
        VALUE callback_alloc(VALUE klass)
        {
            T* obj;
            RBPROTECT
            ({
                obj = Allocator().allocate(1);
                new(obj) T();
            })
            VALUE v = rb_data_object_alloc(klass, obj, NULL, callback_free<T, Allocator>);
            #pragma GCC diagnostic ignored "-Wuninitialized"
            obj->value = v;
            #pragma GCC diagnostic warning "-Wuninitialized"
            return v;
        }
        
        template<typename T, Object(T::*Func)(int, Object[])>
        VALUE callback(int argc, VALUE argv[], VALUE self)
        {
            T& obj = Object(self).data<T>();
            RBPROTECT
            ({
                return (obj.*Func)(argc, reinterpret_cast<Object*>(argv));
            })
            return Nil;
        }
        
        template<typename T, Object(T::*Func)()>
        VALUE callback(VALUE self)
        {
            T& obj = Object(self).data<T>();
            RBPROTECT
            ({
                return (obj.*Func)();
            })
            return Nil;
        }
        
        template<typename T, Object(T::*Func)(Object)>
        VALUE callback(VALUE self, VALUE arg1)
        {
            T& obj = Object(self).data<T>();
            RBPROTECT
            ({
                return (obj.*Func)(arg1);
            })
            return Nil;
        }
        
        template<typename T, Object(T::*Func)(Object, Object)>
        VALUE callback(VALUE self, VALUE arg1, VALUE arg2)
        {
            T& obj = Object(self).data<T>();
            obj->value = self;
            RBPROTECT
            ({
                return (obj.*Func)(arg1, arg2);
            })
            return Nil;
        }
        
        template<typename T, Object(T::*Func)(Object, Object, Object)>
        VALUE callback(VALUE self, VALUE arg1, VALUE arg2, VALUE arg3)
        {
            T& obj = Object(self).data<T>();
            RBPROTECT
            ({
                return (obj.*Func)(arg1, arg2, arg3);
            })
            return Nil;
        }
        
        template<typename T, Object(T::*Func)(Object, Object, Object, Object)>
        VALUE callback(VALUE self, VALUE arg1, VALUE arg2, VALUE arg3, VALUE arg4)
        {
            T& obj = Object(self).data<T>();
            RBPROTECT
            ({
                return (obj.*Func)(arg1, arg2, arg3, arg4);
            })
            return Nil;
        }
        
    }
    
}
