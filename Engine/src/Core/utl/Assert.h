#pragma once  
#include <string>  
#include <sstream>  
#include <optional>  
#include "StackTrace.h"  
#include <format>  
#include "Macro.h"  
#include "Exception.h"
#include "NoReturn.h"
#include <tuple>
#include "String.h"

namespace hydro::utl
{
	ZH_EX_DEF(FailedAssertion);

	class Assertion
	{
	public:
		// types
		enum class Consequence
		{
			Log,
			Terminate,
			Exception,
		};
		// functions
		Assertion(std::wstring expression, const wchar_t* file, const wchar_t* function, int line, Consequence consequence = Consequence::Terminate);
		~Assertion();
		Assertion& msg(const std::wstring& message);

		template<typename... Args>
		Assertion& watch(Args&&... args)
		{
			int arg_index = 1;
			(watch_impl(std::forward<Args>(args), ("arg" + std::to_string(arg_index++)).c_str()), ...);
			return *this;
		}
		[[noreturn]]
		void ex();
	private:
		template<typename T>
		void watch_impl(T&& val, const char* name)
		{
			stream_ << L"   " << ToWide(name) << L" => " << std::forward<T>(val) << L"\n";
		}
	private:
		const wchar_t* file_;
		const wchar_t* function_;
		int line_ = -1;
		int skip_depth_ = 0;
		Consequence consequence_;
		std::wostringstream stream_;
	};
}

#ifndef ZH_HYDROASS_ACTIVE  
#ifdef HYDRO_RELEASE
#define ZH_HYDROASS_ACTIVE   false  
#else  
#define ZH_HYDROASS_ACTIVE   true  
#endif  
#endif  


#define hass(expr) ( !ZH_HYDROASS_ACTIVE || bool(expr) ) ? void(0) : (void)hydro::utl::Assertion{ ZH_WSTR(expr), __FILEW__, __FUNCTIONW__, __LINE__ }

#define hchk(expr) bool(expr) ? void(0) : (void)hydro::utl::Assertion{ ZH_WSTR(expr), __FILEW__, __FUNCTIONW__, __LINE__, ZH_HYDROASS_ACTIVE ? hydro::utl::Assertion::Consequence::Terminate : hydro::utl::Assertion::Consequence::Log }

#define hchk_fail (void)hydro::utl::Assertion{ L"[Always Fail]", __FILEW__, __FUNCTIONW__, __LINE__, ZH_HYDROASS_ACTIVE ? hydro::utl::Assertion::Consequence::Terminate : hydro::utl::Assertion::Consequence::Log }