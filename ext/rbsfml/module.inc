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
std::array<CallerBase*, MaxFunctions> Module<Base, MaxFunctions>::ourFunctions;
template<typename Base, int MaxFunctions>
VALUE Module<Base, MaxFunctions>::myDefinition(Qnil);
template<typename Base, int MaxFunctions>
std::string Module<Base, MaxFunctions>::myName;
template<typename Base, int MaxFunctions>
Value Module<Base, MaxFunctions>::myNamespace;

template<typename Base, int MaxFunctions>
Module<Base, MaxFunctions> Module<Base, MaxFunctions>::defineModule(const std::string& name)
{
	myDefinition = rb_define_module(name.c_str());
	myName = name;
	return Module();
}

template<typename Base, int MaxFunctions>
Module<Base, MaxFunctions> Module<Base, MaxFunctions>::defineModuleUnder(const std::string& name, const Value& otherModule)
{
	myDefinition = rb_define_module_under(otherModule.to<VALUE>(), name.c_str());
	myName = name;
	myNamespace = otherModule;
	return Module();
}

template<typename Base, int MaxFunctions>
const std::string& Module<Base, MaxFunctions>::getName()
{
	return myName;
}

template<typename Base, int MaxFunctions>
Module<Base, MaxFunctions>::Module()
{
}

template<typename Base, int MaxFunctions>
bool Module<Base, MaxFunctions>::isDefined() const
{
	return myDefinition != Qnil;
}

template<typename Base, int MaxFunctions>
template<int ID, typename ReturnType, typename ...Args>
void Module<Base, MaxFunctions>::defineFunction(const std::string& name, ReturnType(*function)(Args...))
{
	static_assert(ID < MaxFunctions, "Unsupported amount of functions");
	typedef ReturnType(*FunctionSignature)(Args...);

	createCaller<ID, FunctionSignature, FunctionCaller<ReturnType, Args...>>(function);
	auto wrapFunc = &Module::wrapperFunction<ID, FunctionSignature, FunctionCaller<ReturnType, Args...>, Value, Args...>;
	rb_define_singleton_method(myDefinition, name.c_str(), reinterpret_cast<RubyCallback>(wrapFunc), sizeof...(Args));
}

template<typename Base, int MaxFunctions>
template<int ID, typename ReturnType, typename ...Args>
void Module<Base, MaxFunctions>::defineMethod(const std::string& name, ReturnType(Base::*function)(Args...))
{
	static_assert(ID < MaxFunctions, "Unsupported amount of functions");
	typedef ReturnType(Base::*FunctionSignature)(Args...);

	createCaller<ID, FunctionSignature, MethodCaller<ReturnType, Args...>>(function);
	auto wrapFunc = &Module::wrapperFunction<ID, FunctionSignature, MethodCaller<ReturnType, Args...>, Value, Args...>;
	rb_define_method(myDefinition, name.c_str(), reinterpret_cast<RubyCallback>(wrapFunc), sizeof...(Args));
}

template<typename Base, int MaxFunctions>
template<int ID, typename ReturnType, typename ...Args>
void Module<Base, MaxFunctions>::defineMethod(const std::string& name, ReturnType(Base::*function)(Args...)const)
{
	static_assert(ID < MaxFunctions, "Unsupported amount of functions");
	typedef ReturnType(Base::*FunctionSignature)(Args...)const;

	createCaller<ID, FunctionSignature, ConstMethodCaller<ReturnType, Args...>>(function);
	auto wrapFunc = &Module::wrapperFunction<ID, FunctionSignature, ConstMethodCaller<ReturnType, Args...>, Value, Args...>;
	rb_define_method(myDefinition, name.c_str(), reinterpret_cast<RubyCallback>(wrapFunc), sizeof...(Args));
}

template<typename Base, int MaxFunctions>
template<int ID, typename ReturnType, typename ...Args>
void Module<Base, MaxFunctions>::defineMethod(const std::string& name, ReturnType(*function)(Args...))
{
	static_assert(ID < MaxFunctions, "Unsupported amount of functions");
	typedef ReturnType(*FunctionSignature)(Args...);

	createCaller<ID, FunctionSignature, StaticMethodCaller<ReturnType, Args...>>(function);
	auto wrapFunc = &Module::wrapperFunction<ID, FunctionSignature, StaticMethodCaller<ReturnType, Args...>, Args...>;
	rb_define_method(myDefinition, name.c_str(), reinterpret_cast<RubyCallback>(wrapFunc), sizeof...(Args)-1);
}

template<typename Base, int MaxFunctions>
template<int ID>
void Module<Base, MaxFunctions>::defineMethod(const std::string& name, Value(*function)(Value, const std::vector<Value>&))
{
	static_assert(ID < MaxFunctions, "Unsupported amount of functions");
	typedef Value(*FunctionSignature)(Value, const std::vector<Value>&);

	createCaller<ID, FunctionSignature, VariadicMethodCaller>(function);
	auto wrapFunc = &Module::variadicWrapperFunction<ID>;
	rb_define_method(myDefinition, name.c_str(), reinterpret_cast<RubyCallback>(wrapFunc), -1);
}

template<typename Base, int MaxFunctions>
void Module<Base, MaxFunctions>::includeModule(const rb::Value& value)
{
	rb_include_module(myDefinition, value.to<VALUE>());
}

template<typename Base, int MaxFunctions>
void Module<Base, MaxFunctions>::aliasMethod(const std::string& method, const std::string& alias)
{
	rb_define_alias(myDefinition, alias.c_str(), method.c_str());
}

template<typename Base, int MaxFunctions>
void Module<Base, MaxFunctions>::defineAttribute(const std::string& attribute, bool reader, bool writer)
{
	rb_define_attr(myDefinition, attribute.c_str(), reader, writer);
}

template<typename Base, int MaxFunctions>
void Module<Base, MaxFunctions>::defineConstant(const std::string& name, const Value& constant)
{
	rb_define_const(myDefinition, name.c_str(), constant.to<VALUE>());
}

template<typename Base, int MaxFunctions>
template<int ID, typename FunctionSignature, typename CallerSignature>
void Module<Base, MaxFunctions>::createCaller(FunctionSignature function)
{
	ourFunctions[ID] =  new CallerSignature(function);
}

template<typename Base, int MaxFunctions>
template<int ID, typename FunctionSignature, typename CallerSignature>
CallerSignature& Module<Base, MaxFunctions>::getCaller()
{
	CallerSignature* caller = static_cast<CallerSignature*>(ourFunctions[ID]);
	return *caller;
}

template<typename Base, int MaxFunctions>
template<int ID>
VALUE Module<Base, MaxFunctions>::variadicWrapperFunction(int argc, VALUE* argv, VALUE self)
{
	typedef Value(*FunctionSignature)(Value, const std::vector<Value>&);
	VariadicMethodCaller& caller = getCaller<ID, FunctionSignature, VariadicMethodCaller>();
	std::vector<Value> arguments;
	for(int index = 0; index < argc; index++)
	{
		arguments.push_back(Value(argv[index]));
	}
	return caller(Value(self), arguments);
}

template<typename Base, int MaxFunctions>
template<int ID, typename FunctionSignature, typename CallerSignature, typename Self>
VALUE Module<Base, MaxFunctions>::wrapperFunction(VALUE self)
{
	CallerSignature& caller = getCaller<ID, FunctionSignature, CallerSignature>();
	return caller(Value(self));
}

template<typename Base, int MaxFunctions>
template<int ID, typename FunctionSignature, typename CallerSignature, typename Self, typename Arg1>
VALUE Module<Base, MaxFunctions>::wrapperFunction(VALUE self, VALUE arg1)
{
	CallerSignature& caller = getCaller<ID, FunctionSignature, CallerSignature>();
	return caller(Value(self), Value(arg1).to<Arg1>());
}

template<typename Base, int MaxFunctions>
template<int ID, typename FunctionSignature, typename CallerSignature, typename Self, typename Arg1, typename Arg2>
VALUE Module<Base, MaxFunctions>::wrapperFunction(VALUE self, VALUE arg1, VALUE arg2)
{
	CallerSignature& caller = getCaller<ID, FunctionSignature, CallerSignature>();
	return caller(Value(self), Value(arg1).to<Arg1>(), Value(arg2).to<Arg2>());
}

template<typename Base, int MaxFunctions>
template<int ID, typename FunctionSignature, typename CallerSignature, typename Self, typename Arg1, typename Arg2, typename Arg3>
VALUE Module<Base, MaxFunctions>::wrapperFunction(VALUE self, VALUE arg1, VALUE arg2, VALUE arg3)
{
	CallerSignature& caller = getCaller<ID, FunctionSignature, CallerSignature>();
	return caller(Value(self), Value(arg1).to<Arg1>(), Value(arg2).to<Arg2>(), Value(arg3).to<Arg3>());
}

template<typename Base, int MaxFunctions>
template<int ID, typename FunctionSignature, typename CallerSignature, typename Self, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
VALUE Module<Base, MaxFunctions>::wrapperFunction(VALUE self, VALUE arg1, VALUE arg2, VALUE arg3, VALUE arg4)
{
	CallerSignature& caller = getCaller<ID, FunctionSignature, CallerSignature>();
	return caller(Value(self), Value(arg1).to<Arg1>(), Value(arg2).to<Arg2>(), Value(arg3).to<Arg3>(), Value(arg4).to<Arg4>());
}

template<typename Base, int MaxFunctions>
template<int ID, typename FunctionSignature, typename CallerSignature, typename Self, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
VALUE Module<Base, MaxFunctions>::wrapperFunction(VALUE self, VALUE arg1, VALUE arg2, VALUE arg3, VALUE arg4, VALUE arg5)
{
	CallerSignature& caller = getCaller<ID, FunctionSignature, CallerSignature>();
	return caller(Value(self), Value(arg1).to<Arg1>(), Value(arg2).to<Arg2>(), Value(arg3).to<Arg3>(), Value(arg4).to<Arg4>(), Value(arg5).to<Arg5>());
}

template<typename Base, int MaxFunctions>
template<int ID, typename FunctionSignature, typename CallerSignature, typename Self, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6>
VALUE Module<Base, MaxFunctions>::wrapperFunction(VALUE self, VALUE arg1, VALUE arg2, VALUE arg3, VALUE arg4, VALUE arg5, VALUE arg6)
{
	CallerSignature& caller = getCaller<ID, FunctionSignature, CallerSignature>();
	return caller(Value(self), Value(arg1).to<Arg1>(), Value(arg2).to<Arg2>(), Value(arg3).to<Arg3>(), Value(arg4).to<Arg4>(), Value(arg5).to<Arg5>(), Value(arg6).to<Arg6>());
}

template<typename Base, int MaxFunctions>
template<int ID, typename FunctionSignature, typename CallerSignature, typename Self, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7>
VALUE Module<Base, MaxFunctions>::wrapperFunction(VALUE self, VALUE arg1, VALUE arg2, VALUE arg3, VALUE arg4, VALUE arg5, VALUE arg6, VALUE arg7)
{
	CallerSignature& caller = getCaller<ID, FunctionSignature, CallerSignature>();
	return caller(Value(self), Value(arg1).to<Arg1>(), Value(arg2).to<Arg2>(), Value(arg3).to<Arg3>(), Value(arg4).to<Arg4>(), Value(arg5).to<Arg5>(),
	              Value(arg6).to<Arg6>(), Value(arg7).to<Arg7>()
	);
}

template<typename Base, int MaxFunctions>
template<int ID, typename FunctionSignature, typename CallerSignature, typename Self, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8>
VALUE Module<Base, MaxFunctions>::wrapperFunction(VALUE self, VALUE arg1, VALUE arg2, VALUE arg3, VALUE arg4, VALUE arg5, VALUE arg6, VALUE arg7, VALUE arg8)
{
	CallerSignature& caller = getCaller<ID, FunctionSignature, CallerSignature>();
	return caller(Value(self), Value(arg1).to<Arg1>(), Value(arg2).to<Arg2>(), Value(arg3).to<Arg3>(), Value(arg4).to<Arg4>(), Value(arg5).to<Arg5>(),
	              Value(arg6).to<Arg6>(), Value(arg7).to<Arg7>(), Value(arg8).to<Arg8>()
	);
}

template<typename Base, int MaxFunctions>
template<int ID, typename FunctionSignature, typename CallerSignature, typename Self, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9>
VALUE Module<Base, MaxFunctions>::wrapperFunction(VALUE self, VALUE arg1, VALUE arg2, VALUE arg3, VALUE arg4, VALUE arg5, VALUE arg6, VALUE arg7, VALUE arg8, VALUE arg9)
{
	CallerSignature& caller = getCaller<ID, FunctionSignature, CallerSignature>();
	return caller(Value(self), Value(arg1).to<Arg1>(), Value(arg2).to<Arg2>(), Value(arg3).to<Arg3>(), Value(arg4).to<Arg4>(), Value(arg5).to<Arg5>(),
	              Value(arg6).to<Arg6>(), Value(arg7).to<Arg7>(), Value(arg8).to<Arg8>(), Value(arg9).to<Arg9>()
	);
}

}