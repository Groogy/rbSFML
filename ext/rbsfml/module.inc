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
std::array<void*, MaxFunctions> Module<Base, MaxFunctions>::ourFunctions;

template<typename Base, int MaxFunctions>
Module<Base, MaxFunctions>::Module(const std::string& name)
: myModule(Qnil)
, myName(name)
, myParent(nullptr)
{
	myModule = rb_define_module(myName.c_str());
}

template<typename Base, int MaxFunctions>
Module<Base, MaxFunctions>::Module(const std::string& name, Module& parent)
: myModule(Qnil)
, myName(name)
, myParent(&parent)
{
	myModule = rb_define_module_under(parent.myModule, myName.c_str());
}

template<typename Base, int MaxFunctions>
template<int ID, typename ReturnType, typename ...Args>
void Module<Base, MaxFunctions>::defineFunction(const std::string& name, ReturnType(*function)(Args...))
{
	static_assert(ID < MaxFunctions, "Unsupported amount of functions");
	typedef ReturnType(*FunctionSignature)(Args...);

	ourFunctions[ID] = reinterpret_cast<void*>(function);
	auto wrapFunc = &Module::wrapperFunction<ID, FunctionSignature, FunctionCaller<ReturnType, Args...>, Args...>;
	rb_define_singleton_method(myModule, name.c_str(), reinterpret_cast<RubyCallback>(wrapFunc), sizeof...(Args));
}

template<typename Base, int MaxFunctions>
template<int ID, typename FunctionSignature, typename CallerSignature>
CallerSignature Module<Base, MaxFunctions>::createCaller()
{
	void* rawPointer = ourFunctions[ID];
	FunctionSignature functionPointer = reinterpret_cast<FunctionSignature>(rawPointer);
	CallerSignature caller = { functionPointer };
	return caller;
}

template<typename Base, int MaxFunctions>
template<int ID, typename FunctionSignature, typename CallerSignature>
VALUE Module<Base, MaxFunctions>::wrapperFunction(VALUE self)
{
	CallerSignature caller = createCaller<ID, FunctionSignature, CallerSignature>();
	return caller();
}

template<typename Base, int MaxFunctions>
template<int ID, typename FunctionSignature, typename CallerSignature, typename Arg1>
VALUE Module<Base, MaxFunctions>::wrapperFunction(VALUE self, VALUE arg1)
{
	CallerSignature caller = createCaller<ID, FunctionSignature, CallerSignature>();
	return caller(Value(arg1).to<Arg1>());
}

template<typename Base, int MaxFunctions>
template<int ID, typename FunctionSignature, typename CallerSignature, typename Arg1, typename Arg2>
VALUE Module<Base, MaxFunctions>::wrapperFunction(VALUE self, VALUE arg1, VALUE arg2)
{
	CallerSignature caller = createCaller<ID, FunctionSignature, CallerSignature>();
	return caller(Value(arg1).to<Arg1>(), Value(arg2).to<Arg2>());
}

template<typename Base, int MaxFunctions>
template<int ID, typename FunctionSignature, typename CallerSignature, typename Arg1, typename Arg2, typename Arg3>
VALUE Module<Base, MaxFunctions>::wrapperFunction(VALUE self, VALUE arg1, VALUE arg2, VALUE arg3)
{
	CallerSignature caller = createCaller<ID, FunctionSignature, CallerSignature>();
	return caller(Value(arg1).to<Arg1>(), Value(arg2).to<Arg2>(), Value(arg3).to<Arg3>());
}

template<typename Base, int MaxFunctions>
template<int ID, typename FunctionSignature, typename CallerSignature, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
VALUE Module<Base, MaxFunctions>::wrapperFunction(VALUE self, VALUE arg1, VALUE arg2, VALUE arg3, VALUE arg4)
{
	CallerSignature caller = createCaller<ID, FunctionSignature, CallerSignature>();
	return caller(Value(arg1).to<Arg1>(), Value(arg2).to<Arg2>(), Value(arg3).to<Arg3>(), Value(arg4).to<Arg4>());
}

template<typename Base, int MaxFunctions>
template<int ID, typename FunctionSignature, typename CallerSignature, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
VALUE Module<Base, MaxFunctions>::wrapperFunction(VALUE self, VALUE arg1, VALUE arg2, VALUE arg3, VALUE arg4, VALUE arg5)
{
	CallerSignature caller = createCaller<ID, FunctionSignature, CallerSignature>();
	return caller(Value(arg1).to<Arg1>(), Value(arg2).to<Arg2>(), Value(arg3).to<Arg3>(), Value(arg4).to<Arg4>(), Value(arg5).to<Arg5>());
}

template<typename Base, int MaxFunctions>
template<int ID, typename FunctionSignature, typename CallerSignature, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6>
VALUE Module<Base, MaxFunctions>::wrapperFunction(VALUE self, VALUE arg1, VALUE arg2, VALUE arg3, VALUE arg4, VALUE arg5, VALUE arg6)
{
	CallerSignature caller = createCaller<ID, FunctionSignature, CallerSignature>();
	return caller(Value(arg1).to<Arg1>(), Value(arg2).to<Arg2>(), Value(arg3).to<Arg3>(), Value(arg4).to<Arg4>(), Value(arg5).to<Arg5>(), Value(arg6).to<Arg6>());
}

}