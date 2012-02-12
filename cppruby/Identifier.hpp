#pragma once

namespace rb
{
    
    class Identifier
    {
    public:
        
        ID id;
        
        Identifier(const char* name) : id(rb_intern(name)) {}
        
        Identifier(ID name) : id(name) {}
        
        operator ID() const { return id; }
        
    };
    
}
