
#include "BasicObject.hpp"

namespace rb
{
    
    template<typename... Args>
    Object BasicObject::call(Identifier method, Args... args)
    {
        BasicObject oargs[] = {args...};
        int argc = sizeof...(args);
        return rb_funcall2(value, method.id, argc, (VALUE*)oargs);
    }
    
    template<typename... Args>
    Object BasicObject::public_call(Identifier method, Args... args)
    {
        BasicObject oargs[] = {args...};
        int argc = sizeof...(args);
        return rb_funcall3(value, method.id, argc, (VALUE*)oargs);
    }
    
    bool operator==(BasicObject left, BasicObject right)
    {
        return left.call("==", right);
    }
    
    bool operator!=(BasicObject left, BasicObject right)
    {
        return left.call("!=", right);
    }
    
}
