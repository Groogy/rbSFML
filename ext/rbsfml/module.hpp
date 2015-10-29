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

 #ifndef RBSFML_MODULE_HPP_
 #define RBSFML_MODULE_HPP_

#include <ruby.h>
#include <string>
#include <array>
#include <vector>

#include "value.hpp"
#include "error.hpp"

namespace rb
{
	typedef VALUE(*RubyCallback)(...);

	struct CallerBase {};

	template<typename Base, int MaxFunctions = 32>
	class Module
	{
	public:
		static Module defineModule(const std::string& name);
		static Module defineModuleUnder(const std::string& name, const Value& otherModule);

		static const std::string& getName();

		Module();

		bool isDefined() const;

		template<int ID, typename ReturnType, typename ...Args>
		void defineFunction(const std::string& name, ReturnType(*function)(Args...));

		template<int ID, typename ReturnType, typename ...Args>
		void defineMethod(const std::string& name, ReturnType(Base::*function)(Args...));
		template<int ID, typename ReturnType, typename ...Args>
		void defineMethod(const std::string& name, ReturnType(Base::*function)(Args...)const);
		template<int ID, typename ReturnType, typename ...Args>
		void defineMethod(const std::string& name, ReturnType(*function)(Args...));

		template<int ID>
		void defineMethod(const std::string& name, Value(*function)(Value, const std::vector<Value>&));

		void includeModule(const rb::Value& value);

		void aliasMethod(const std::string& method, const std::string& alias);

		void defineAttribute(const std::string& attribute, bool reader, bool writer);

		void defineConstant(const std::string& name, const Value& constant);

	protected:
		friend class Value;

		template<typename ReturnType, typename ...Args>
		struct FunctionCaller : public CallerBase
		{
			FunctionCaller(ReturnType(*f)(Args... args)) : function(f) {}

			VALUE operator()(Value self, Args... args) 
			{ 
				Value returnValue = Value::create(function(args...));
				return returnValue.to<VALUE>();
			}

			ReturnType(*function)(Args... args);
		};

		template<typename ...Args>
		struct FunctionCaller<void, Args...> : public CallerBase
		{
			FunctionCaller(void(*f)(Args... args)) : function(f) {}

			VALUE operator()(Value self, Args... args)
			{
				function(args...);
				return Qnil;
			}

			VALUE self;
			void(*function)(Args... args);
		};

		template<typename ReturnType, typename ...Args>
		struct MethodCaller : public CallerBase
		{
			MethodCaller(ReturnType(Base::*f)(Args... args)) : function(f) {}

			VALUE operator()(Value self, Args... args) 
			{ 
				if(self.isFrozen())
					rb::modifiedFrozen(self);
				Base* object = nullptr;
				Data_Get_Struct(self.to<VALUE>(), Base, object);
				Value returnValue = Value::create((object->*function)(args...));
				return returnValue.to<VALUE>();
			}

			ReturnType(Base::*function)(Args... args);
		};

		template<typename ...Args>
		struct MethodCaller<void, Args...> : public CallerBase
		{
			MethodCaller(void(Base::*f)(Args... args)) : function(f) {}

			VALUE operator()(Value self, Args... args)
			{
				if(self.isFrozen())
					rb::modifiedFrozen(self);

				Base* object = nullptr;
				Data_Get_Struct(self.to<VALUE>(), Base, object);
				(object->*function)(args...);
				return Qnil;
			}

			void(Base::*function)(Args... args);
		};

		template<typename ReturnType, typename ...Args>
		struct ConstMethodCaller : public CallerBase
		{
			ConstMethodCaller(ReturnType(Base::*f)(Args... args)const) : function(f) {}

			VALUE operator()(Value self, Args... args) 
			{ 
				Base* object = nullptr;
				Data_Get_Struct(self.to<VALUE>(), Base, object);
				Value returnValue = Value::create((object->*function)(args...));
				return returnValue.to<VALUE>();
			}

			ReturnType(Base::*function)(Args... args)const;
		};

		template<typename ...Args>
		struct ConstMethodCaller<void, Args...> : public CallerBase
		{
			ConstMethodCaller(void(Base::*f)(Args... args)const) : function(f) {}

			VALUE operator()(Value self, Args... args)
			{
				Base* object = nullptr;
				Data_Get_Struct(self.to<VALUE>(), Base, object);
				(object->*function)(args...);
				return Qnil;
			}

			void(Base::*function)(Args... args)const;
		};

		template<typename ReturnType, typename ...Args>
		struct StaticMethodCaller : public CallerBase
		{
			StaticMethodCaller(ReturnType(*f)(Args... args)) : function(f) {}

			VALUE operator()(Args... args) 
			{ 
				Value returnValue = Value::create(function(args...));
				return returnValue.to<VALUE>();
			}

			ReturnType(*function)(Args... args);
		};

		template<typename ...Args>
		struct StaticMethodCaller<void, Args...> : public CallerBase
		{
			StaticMethodCaller(void(*f)(Args... args)) : function(f) {}

			VALUE operator()(Args... args)
			{
				function(args...);
				return Qnil;
			}

			void(*function)(Args... args);
		};

		struct VariadicMethodCaller : public CallerBase
		{
			VariadicMethodCaller(Value(*f)(Value, const std::vector<Value>&)) : function(f) {}

			VALUE operator()(Value self, const std::vector<Value>& args) 
			{ 
				Value returnValue = Value::create(function(Value(self), args));
				return returnValue.to<VALUE>();
			}

			Value(*function)(Value, const std::vector<Value>&);
		};

		template<int ID, typename FunctionSignature, typename CallerSignature>
		static void createCaller(FunctionSignature function);

		template<int ID, typename FunctionSignature, typename CallerSignature>
		static CallerSignature& getCaller();

		template<int ID>
		static VALUE variadicWrapperFunction(int argc, VALUE* argv, VALUE self);

		template<int ID, typename FunctionSignature, typename CallerSignature, typename Self>
		static VALUE wrapperFunction(VALUE self);

		template<int ID, typename FunctionSignature, typename CallerSignature, typename Self, typename Arg1>
		static VALUE wrapperFunction(VALUE self, VALUE arg1);

		template<int ID, typename FunctionSignature, typename CallerSignature, typename Self, typename Arg1, typename Arg2>
		static VALUE wrapperFunction(VALUE self, VALUE arg1, VALUE arg2);

		template<int ID, typename FunctionSignature, typename CallerSignature, typename Self, typename Arg1, typename Arg2, typename Arg3>
		static VALUE wrapperFunction(VALUE self, VALUE arg1, VALUE arg2, VALUE arg3);

		template<int ID, typename FunctionSignature, typename CallerSignature, typename Self, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
		static VALUE wrapperFunction(VALUE self, VALUE arg1, VALUE arg2, VALUE arg3, VALUE arg4);

		template<int ID, typename FunctionSignature, typename CallerSignature, typename Self, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
		static VALUE wrapperFunction(VALUE self, VALUE arg1, VALUE arg2, VALUE arg3, VALUE arg4, VALUE arg5);

		template<int ID, typename FunctionSignature, typename CallerSignature, typename Self, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6>
		static VALUE wrapperFunction(VALUE self, VALUE arg1, VALUE arg2, VALUE arg3, VALUE arg4, VALUE arg5, VALUE arg6);

		static std::array<CallerBase*, MaxFunctions> ourFunctions;
		static VALUE myDefinition;
		static std::string myName;
		static Value myNamespace;
	};
}

#include "module.inc"

#endif // RBSFML_MODULE_HPP_