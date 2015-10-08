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
VALUE Module<Base, MaxFunctions>::wrapperFunction(VALUE self)
{
	void* rawPointer = ourFunctions[ID];
	FunctionSignature functionPointer = reinterpret_cast<FunctionSignature>(rawPointer);
	CallerSignature caller = { functionPointer };
	caller();
	return Value(caller.returnValue).to<VALUE>();
}

template<typename Base, int MaxFunctions>
template<int ID, typename FunctionSignature, typename CallerSignature, typename Arg1>
VALUE Module<Base, MaxFunctions>::wrapperFunction(VALUE self, VALUE arg1)
{
	void* rawPointer = ourFunctions[ID];
	FunctionSignature functionPointer = reinterpret_cast<FunctionSignature>(rawPointer);
	CallerSignature caller = { functionPointer };
	caller(Value(arg1).to<Arg1>());
	return Value(caller.returnValue).to<VALUE>();
}

}