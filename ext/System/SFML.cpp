/* rbSFML
 * Copyright (c) 2010 Henrik Valter Vogelius Hansson - groogy@groogy.se
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from
 * the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software in
 *    a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 */

#define SYSTEM_SFML_CPP
#include <System/SFML.hpp>

void rbSFML::Init(VALUE SFML)
{
    rb_define_class_under(SFML, "Error", rb_eRuntimeError);
    
    rb_define_const(SFML, "SFML_VERSION",    rb_str_new2(SFML_VERSION   ));
    rb_define_const(SFML, "BINDING_VERSION", rb_str_new2(BINDING_VERSION));
    
    SetRaiseExceptions(SFML, Qtrue);
    
    rb_define_module_function(SFML, "raise_exceptions",  GetRaiseExceptions, 0);
    rb_define_module_function(SFML, "raise_exceptions=", SetRaiseExceptions, 1);
    rb_define_module_function(SFML, "system?",           SystemLoaded,       0);
    rb_define_module_function(SFML, "window?",           WindowLoaded,       0);
    rb_define_module_function(SFML, "graphics?",         GraphicsLoaded,     0);
    rb_define_module_function(SFML, "audio?",            AudioLoaded,        0);
    rb_define_module_function(SFML, "memory_usage",      GetMemoryUsage,     0);
}

// SFML.raise_exceptions
VALUE rbSFML::GetRaiseExceptions(VALUE self)
{
    if (!rb_cvar_defined(self, rb_intern("@@raise_exceptions")))
        return Qfalse;
    return rb_cv_get(self, "@@raise_exceptions");
}

// SFML.raise_exceptions=(flag)
VALUE rbSFML::SetRaiseExceptions(VALUE self, VALUE flag)
{
    rb_cv_set(self, "@@raise_exceptions", flag);
    return Qnil;
}

// SFML.system?
VALUE rbSFML::SystemLoaded(VALUE self)
{
    return Qtrue; // You can't call this method without system.
}

// SFML.window?
VALUE rbSFML::WindowLoaded(VALUE self)
{
    return RBOOL(rb_cvar_defined(self, rb_intern("@@window")));
}

// SFML.graphics?
VALUE rbSFML::GraphicsLoaded(VALUE self)
{
    return RBOOL(rb_cvar_defined(self, rb_intern("@@graphics")));
}

// SFML.audio?
VALUE rbSFML::AudioLoaded(VALUE self)
{
    return RBOOL(rb_cvar_defined(self, rb_intern("@@audio")));
}

// Internal
struct GetMemoryUsageInfo
{
    size_t mem_usage;
    VALUE* list_ptr;
    size_t list_len;
};

// Internal
static VALUE GetMemoryUsageIterator(VALUE obj, VALUE data)
{
    GetMemoryUsageInfo* info = (GetMemoryUsageInfo*)data;
    for (size_t i = 0; i < info->list_len; ++i)
    {
        if (CLASS_OF(obj) == info->list_ptr[i])
        {
            VALUE usage = rb_funcall(obj, rb_intern("memory_usage"), 0);
            info->mem_usage += NUM2SIZET(usage);
            return Qnil;
        }
    }
    
    return Qnil;
}

// SFML.memory_usage
VALUE rbSFML::GetMemoryUsage(VALUE self)
{
    void* tbl = rb_mod_const_at(self, 0);
    VALUE list = rb_const_list(tbl);
    
    GetMemoryUsageInfo info;
    info.mem_usage = 0;
    info.list_ptr = RARRAY_PTR(list);
    info.list_len = RARRAY_LEN(list);
    
    for (size_t i = 0; i < info.list_len; ++i)
        info.list_ptr[i] = rb_const_get(self, SYM2ID(info.list_ptr[i]));
    
    VALUE rb_mObjSpace = rb_const_get(rb_cObject, rb_intern("ObjectSpace"));
    rb_block_call(rb_mObjSpace, rb_intern("each_object"), 0, NULL,
                  (VALUE(*)(...))GetMemoryUsageIterator, (VALUE)&info);
    
    return SIZET2NUM(info.mem_usage);
}
