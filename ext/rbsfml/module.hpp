#include <ruby.h>
#include <string>
#include <array>

#include "Value.hpp"

namespace rb
{
	template<typename Base, int MaxFunctions = 16>
	class Module
	{
	public:
		Module(const std::string& name);
		Module(const std::string& name, Module& parent);

		template<int ID, typename ReturnType, typename ...Args>
		void defineFunction(const std::string& name, ReturnType(*function)(Args...));

	private:
		typedef VALUE(*RubyCallback)(...);

		template<typename ReturnType, typename ...Args>
		struct FunctionCaller
		{
			VALUE operator()(Args... args) 
			{ 
				Value returnValue(function(args...));
				return returnValue.to<VALUE>();
			}

			ReturnType(*function)(Args... args);
		};

		template<typename ...Args>
		struct FunctionCaller<void, Args...>
		{
			VALUE operator()(Args... args)
			{
				function(args...);
				return Qnil;
			}

			void(*function)(Args... args);
		};

		template<int ID, typename FunctionSignature, typename CallerSignature>
		static CallerSignature createCaller();

		template<int ID, typename FunctionSignature, typename CallerSignature>
		static VALUE wrapperFunction(VALUE self);

		template<int ID, typename FunctionSignature, typename CallerSignature, typename Arg1>
		static VALUE wrapperFunction(VALUE self, VALUE arg1);

		template<int ID, typename FunctionSignature, typename CallerSignature, typename Arg1, typename Arg2>
		static VALUE wrapperFunction(VALUE self, VALUE arg1, VALUE arg2);

		template<int ID, typename FunctionSignature, typename CallerSignature, typename Arg1, typename Arg2, typename Arg3>
		static VALUE wrapperFunction(VALUE self, VALUE arg1, VALUE arg2, VALUE arg3);

		template<int ID, typename FunctionSignature, typename CallerSignature, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
		static VALUE wrapperFunction(VALUE self, VALUE arg1, VALUE arg2, VALUE arg3, VALUE arg4);

		template<int ID, typename FunctionSignature, typename CallerSignature, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
		static VALUE wrapperFunction(VALUE self, VALUE arg1, VALUE arg2, VALUE arg3, VALUE arg4, VALUE arg5);

		template<int ID, typename FunctionSignature, typename CallerSignature, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6>
		static VALUE wrapperFunction(VALUE self, VALUE arg1, VALUE arg2, VALUE arg3, VALUE arg4, VALUE arg5, VALUE arg6);

		static std::array<void*, MaxFunctions> ourFunctions;

		VALUE myModule;
		std::string myName;
		Module* myParent;
	};
}

#include "module.inc"