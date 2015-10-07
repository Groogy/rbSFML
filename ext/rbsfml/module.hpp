#include <ruby.h>
#include <string>

namespace rb
{
	template<typename Base>
	class Module
	{
	public:
		Module(const std::string& name);
		Module(const std::string& name, Module& parent);

		template<typename FunctionSignature>
		void defineFunction(const std::string& name, FunctionSignature function);

	private:
		VALUE myModule;
		std::string myName;
		Module* myParent;
	};
}

#include "module.inc"