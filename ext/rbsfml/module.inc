namespace rb
{

template<typename Base>
Module<Base>::Module(const std::string& name)
: myModule(Qnil)
, myName(name)
, myParent(nullptr)
{
	myModule = rb_define_module(myName.c_str());
}

template<typename Base>
Module<Base>::Module(const std::string& name, Module& parent)
: myModule(Qnil)
, myName(name)
, myParent(&parent)
{
	myModule = rb_define_module_under(parent.myModule, myName.c_str());
}

template<typename Base>
template<typename FunctionSignature>
void Module<Base>::defineFunction(const std::string& name, FunctionSignature function)
{
	rb_define_singleton_method(myModule, name.c_str(), reinterpret_cast<VALUE (*)(...)>(function), 0);
}

}