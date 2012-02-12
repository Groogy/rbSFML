#pragma once

#include "Identifier.hpp"

namespace rb
{
    
    class Object;
    class BasicObject;
    class BasicObject
    {
    public:
        
        VALUE value;
        
        BasicObject() {};
        BasicObject(VALUE v) : value(v) {};
        
        template<typename... Args>
        Object call(Identifier method, Args... args);
        template<typename... Args>
        Object public_call(Identifier method, Args... args);
        
        explicit operator bool() const { return RTEST(value); }
        operator VALUE()       { return value; }
        operator RBasic*()     { return (RBasic*)    value; }
        operator RObject*()    { return (RObject*)   value; }
        operator RClass*()     { return (RClass*)    value; }
        operator RFloat*()     { return (RFloat*)    value; }
        operator RString*()    { return (RString*)   value; }
        operator RArray*()     { return (RArray*)    value; }
        operator RRegexp*()    { return (RRegexp*)   value; }
        operator RHash*()      { return (RHash*)     value; }
        operator RFile*()      { return (RFile*)     value; }
        operator RRational*()  { return (RRational*) value; }
        operator RComplex*()   { return (RComplex*)  value; }
        operator RData*()      { return (RData*)     value; }
        operator RTypedData*() { return (RTypedData*)value; }
        operator RStruct*()    { return (RStruct*)   value; }
        operator RBignum*()    { return (RBignum*)   value; }
        
    };
    
    bool operator==(BasicObject left, BasicObject right);
    bool operator!=(BasicObject left, BasicObject right);
    
}
