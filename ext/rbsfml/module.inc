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