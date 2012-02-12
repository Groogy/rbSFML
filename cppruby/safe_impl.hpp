#pragma once

namespace rb
{
    
    namespace safe
    {
        
        int _NUM2INT_impl(VALUE v)
        {
            return NUM2INT(v);
        }
        
        VALUE _INT2NUM_impl(int i)
        {
            return INT2NUM(i);
        }
        
        long _NUM2LONG_impl(VALUE v)
        {
            return NUM2LONG(v);
        }
        
        VALUE _LONG2NUM_impl(long l)
        {
            return LONG2NUM(l);
        }
        
        long long _NUM2LL_impl(VALUE v)
        {
            return NUM2LL(v);
        }
        
        VALUE _LL2NUM_impl(long long ll)
        {
            return LL2NUM(ll);
        }
        
        unsigned int _NUM2UINT_impl(VALUE v)
        {
            return NUM2UINT(v);
        }
        
        VALUE _UINT2NUM_impl(unsigned int ui)
        {
            return UINT2NUM(ui);
        }
        
        unsigned long _NUM2ULONG_impl(VALUE v)
        {
            return NUM2ULONG(v);
        }
        
        VALUE _ULONG2NUM_impl(unsigned long ul)
        {
            return ULONG2NUM(ul);
        }
        
        unsigned long long _NUM2ULL_impl(VALUE v)
        {
            return NUM2ULL(v);
        }
        
        VALUE _ULL2NUM_impl(unsigned long long ull)
        {
            return ULL2NUM(ull);
        }
        
        double _NUM2DBL_impl(VALUE v)
        {
            return NUM2DBL(v);
        }
        
        VALUE _DBL2NUM_impl(double d)
        {
            return DBL2NUM(d);
        }
        
        VALUE _StringValue_impl(VALUE v)
        {
            return StringValue(v);
        }
        
        char* _StringValuePtr_impl(VALUE v)
        {
            return StringValuePtr(v);
        }
        
        char* _StringValueCStr_impl(VALUE v)
        {
            return StringValueCStr(v);
        }
        
        VALUE _rb_str_new_impl(const char* ptr, long len)
        {
            return rb_str_new(ptr, len);
        }
        
    }
    
}
