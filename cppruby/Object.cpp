
#include "Object.hpp"
#include "Class.hpp"
#include "conversions.hpp"

namespace rb
{
    
    Object Object::ivar_defined(Identifier var)
    {
        return rb_ivar_defined(value, var);
    }
    
    Object Object::ivar(Identifier var)
    {
        return rb_ivar_get(value, var);
    }
    
    Object Object::ivar(Identifier var, Object obj)
    {
        return rb_ivar_set(value, var, obj);
    }
    
    Object Object::compare(Object other)
    {
        return call("<=>", other);
    }
    
    Object Object::case_equal(Object other)
    {
        return call("===", other);
    }
    
    Class Object::class_of()
    {
        return rb_obj_class(value);
    }
    
    Object Object::clone()
    {
        return call("clone");
    }
    
    Object Object::display(Object out)
    {
        return rb_io_write(out, value);
    }
    
    Object Object::dup()
    {
        return call("dup");
    }
    
    Object Object::is_equal(Object other)
    {
        return call("equal?", other);
    }
    
    Object Object::is_eql(Object other)
    {
        return call("eql?", other);
    }
    
    Object Object::extend(Module module)
    {
        return call("extend", module);
    }
    
    Object Object::freeze()
    {
        return rb_obj_freeze(value);
    }
    
    Object Object::is_frozen()
    {
        return rb_obj_frozen_p(value);
    }
    
    Object Object::hash()
    {
        return call("hash");
    }
    
    Object Object::inspect()
    {
        return call("inspect");
    }
    
    Object Object::is_instance_of(Class klass)
    {
        return rb_obj_is_instance_of(value, klass);
    }
    
    Object Object::is_instance_variable_defined(Object var)
    {
        return call("instance_variable_defined?", var);
    }
    
    Object Object::instance_variable_get(Object var)
    {
        return call("instance_variable_get", var);
    }
    
    Object Object::instance_variable_set(Object var, Object obj)
    {
        return call("instance_variable_set", var, obj);
    }
    
    Object Object::instance_variables()
    {
        return rb_obj_instance_variables(value);
    }
    
    Object Object::is_a(Module module)
    {
        return rb_obj_is_kind_of(value, module);
    }
    
    Object Object::is_kind_of(Module module)
    {
        return rb_obj_is_kind_of(value, module);
    }
    
    Object Object::method(Object name)
    {
        return rb_obj_method(value, name);
    }
    
    Object Object::methods()
    {
        return call("methods");
    }
    
    Object Object::is_nil()
    {
        return value == Qnil;
    }
    
    Object Object::object_id()
    {
        return rb_obj_id(value);
    }
    
    Object Object::public_method(Object name)
    {
        return call("public_method", name);
    }
    
    Object Object::public_methods()
    {
        return call("public_methods");
    }
    
    template<typename... Args>
    Object Object::public_send(Object method, const Args&... args)
    {
        return public_call(method, args...);
    }
    
    Object Object::private_method(Object name)
    {
        return call("private_method", name);
    }
    
    Object Object::private_methods()
    {
        return call("private_methods");
    }
    
    Object Object::protected_method(Object name)
    {
        return call("protected_method", name);
    }
    
    Object Object::protected_methods()
    {
        return call("protected_methods");
    }
    
    Object Object::respond_to(Object method, Object include_private)
    {
        return call("respond_to?", method, include_private);
    }
    
    Object Object::respond_to_missing(Object method, Object include_private)
    {
        return call("respond_to_missing?", method, include_private);
    }
    
    template<typename... Args>
    Object Object::send(Object method, const Args&... args)
    {
        return call(method, args...);
    }
    
    Class Object::singleton_class() 
    {
        return rb_singleton_class(value);
    }
    
    Object Object::singleton_methods(Object all)
    {
        return rb_obj_singleton_methods(1, (VALUE[]){all}, value);
    }
    
    Object Object::taint()
    {
        return rb_obj_taint(value);
    }
    
    Object Object::is_tainted()
    {
        return rb_obj_tainted(value);
    }
    
    Object Object::tap(std::function<void(Object)> block)
    {
        block(value);
        return value;
    }
    
    Object Object::to_s()
    {
        return call("to_s");
    }
    
    Object Object::trust()
    {
        return rb_obj_trust(value);
    }
    
    Object Object::untaint()
    {
        return rb_obj_untaint(value);
    }
    
    Object Object::untrust()
    {
        return rb_obj_untrust(value);
    }
    
    Object Object::is_untrusted()
    {
        return rb_obj_untrusted(value);
    }
    
    std::ostream& operator<<(std::ostream& stream, Object obj)
    {
        stream << ruby_cast<char*>(obj.to_s());
        return stream;
    }
    
    bool operator!(Object left)
    {
        return left.call("!");
    }
    
    bool operator<(Object left, Object right)
    {
        return left.call("<", right);
    }
    
    bool operator>(Object left, Object right)
    {
        return left.call(">", right);
    }
    
}
