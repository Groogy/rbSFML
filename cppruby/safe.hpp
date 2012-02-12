#pragma once

#include "safe_impl.hpp"

namespace rb
{
    
    namespace safe
    {
        
        int _NUM2INT(VALUE v)
        {
            int i;
            priv::rescue<int, VALUE, _NUM2INT_impl>(&i, &v);
            return i;
        }
        
        VALUE _INT2NUM(int i)
        {
            VALUE v;
            priv::rescue<VALUE, int, _INT2NUM_impl>(&v, &i);
            return v;
        }
        
        long _NUM2LONG(VALUE v)
        {
            long l;
            priv::rescue<long, VALUE, _NUM2LONG_impl>(&l, &v);
            return l;
        }
        
        VALUE _LONG2NUM(long l)
        {
            VALUE v;
            priv::rescue<VALUE, long, _LONG2NUM_impl>(&v, &l);
            return v;
        }
        
        long long _NUM2LL(VALUE v)
        {
            long long ll;
            priv::rescue<long long, VALUE, _NUM2LL_impl>(&ll, &v);
            return ll;
        }
        
        VALUE _LL2NUM(long long ll)
        {
            VALUE v;
            priv::rescue<VALUE, long long, _LL2NUM_impl>(&v, &ll);
            return v;
        }
        
        unsigned int _NUM2UINT(VALUE v)
        {
            unsigned int ui;
            priv::rescue<unsigned int, VALUE, _NUM2UINT_impl>(&ui, &v);
            return ui;
        }
        
        VALUE _UINT2NUM(unsigned int ui)
        {
            VALUE v;
            priv::rescue<VALUE, unsigned int, _UINT2NUM_impl>(&v, &ui);
            return v;
        }
        
        unsigned long _NUM2ULONG(VALUE v)
        {
            unsigned long ul;
            priv::rescue<unsigned long, VALUE, _NUM2ULONG_impl>(&ul, &v);
            return ul;
        }
        
        VALUE _ULONG2NUM(unsigned long ul)
        {
            VALUE v;
            priv::rescue<VALUE, unsigned long, _ULONG2NUM_impl>(&v, &ul);
            return v;
        }
        
        unsigned long long _NUM2ULL(VALUE v)
        {
            unsigned long long ull;
            priv::rescue<unsigned long long, VALUE, _NUM2ULL_impl>(&ull, &v);
            return ull;
        }
        
        VALUE _ULL2NUM(unsigned long long ull)
        {
            VALUE v;
            priv::rescue<VALUE, unsigned long long, _ULL2NUM_impl>(&v, &ull);
            return v;
        }
        
        double _NUM2DBL(VALUE v)
        {
            double d;
            priv::rescue<double, VALUE, _NUM2DBL_impl>(&d, &v);
            return d;
        }
        
        VALUE _DBL2NUM(double d)
        {
            VALUE v;
            priv::rescue<VALUE, double, _DBL2NUM_impl>(&v, &d);
            return v;
        }
        
        VALUE _StringValue(VALUE v)
        {
            VALUE s;
            priv::rescue<VALUE, VALUE, _StringValue_impl>(&s, &v);
            return s;
        }
        
        char* _StringValuePtr(VALUE v)
        {
            char* s;
            priv::rescue<char*, VALUE, _StringValuePtr_impl>(&s, &v);
            return s;
        }
        
        char* _StringValueCStr(VALUE v)
        {
            char* s;
            priv::rescue<char*, VALUE, _StringValueCStr_impl>(&s, &v);
            return s;
        }
        
        VALUE _rb_str_new(const char* ptr, long len)
        {
            VALUE str;
            priv::rescue<VALUE, const char*, long, _rb_str_new_impl>(&str, &ptr, &len);
            return str;
        }
        
    }
    
}
