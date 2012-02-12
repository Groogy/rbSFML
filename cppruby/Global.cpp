
#include "Global.hpp"

namespace rb
{
    
    template<typename... Args>
    Object p(const Args&... args)
    {
        return mKernel.call("p", args...);
    }
    
    template<typename... Args>
    Object print(const Args&... args)
    {
        return mKernel.call("print", args...);
    }
    
    template<typename... Args>
    Object puts(const Args&... args)
    {
        return mKernel.call("puts", args...);
    }
    
}
