/* rbSFML
 * Copyright (c) 2015 Henrik Valter Vogelius Hansson - groogy@groogy.se
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

namespace rb
{

template<typename Base, int MaxFunctions>
Value Class<Base, MaxFunctions>::myParent(Qnil);

template<typename Base, int MaxFunctions>
Class<Base, MaxFunctions> Class<Base, MaxFunctions>::defineClass(const std::string& name, const Value& parent)
{
	Module<Base, MaxFunctions>::myDefinition = rb_define_class(name.c_str(), parent.to<VALUE>());
	Module<Base, MaxFunctions>::myName = name;
	Module<Base, MaxFunctions>::myParent = parent;

	rb_define_alloc_func(Module<Base, MaxFunctions>::myDefinition, &allocate);

	return Class();
}

template<typename Base, int MaxFunctions>
Class<Base, MaxFunctions> Class<Base, MaxFunctions>::defineClassUnder(const std::string& name, const Value& otherModule, const Value& parent)
{
	Module<Base, MaxFunctions>::myDefinition = rb_define_class_under(otherModule.to<VALUE>(), name.c_str(), parent.to<VALUE>());
	Module<Base, MaxFunctions>::myName = name;
	Module<Base, MaxFunctions>::myNamespace = otherModule;
	myParent = parent;

	rb_define_alloc_func(Module<Base, MaxFunctions>::myDefinition, &allocate);

	return Class();
}

template<typename Base, int MaxFunctions>
Class<Base, MaxFunctions>::Class()
: Module<Base, MaxFunctions>()
{
}

template<typename Base, int MaxFunctions>
Base* Class<Base, MaxFunctions>::newObject()
{
	static ID newSymbol = rb_intern("new");
	return Value(rb_funcall(Module<Base, MaxFunctions>::myDefinition, newSymbol, 0)).to<Base*>();
}

template<typename Base, int MaxFunctions>
Base* Class<Base, MaxFunctions>::allocate()
{
	void* memory = xmalloc(sizeof(Base));
	if(memory == nullptr) rb_memerror();
	Base* object = new(memory) Base;
	return object;
}

template<typename Base, int MaxFunctions>
VALUE Class<Base, MaxFunctions>::allocate(VALUE klass)
{
	Base* memory = allocate();
	VALUE object = rb_data_object_alloc(klass, memory, NULL, &free);
	return object;
}

template<typename Base, int MaxFunctions>
void Class<Base, MaxFunctions>::free(void* memory)
{
	Base* object = static_cast<Base*>(memory);
	object->~Base();
	xfree(memory);
}

}