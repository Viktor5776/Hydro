#pragma once 
#include <exception> 
#include <string> 

namespace hydro::utl
{
	class IException : public std::exception {};


	class BufferedException : public IException
	{
	public:
		BufferedException() = default;
		BufferedException(std::string msg);
		BufferedException(const std::wstring& msg);
		const char* what() const override;
	private:
		std::string message_;
		mutable std::string buffer_;
	};
}

#define ZH_EX_DEF_FROM(NewType, BaseType) class NewType : public BaseType {using Base = BaseType; public: using Base::Base;} 
#define ZH_EX_DEF(NewType) ZH_EX_DEF_FROM(NewType, hydro::utl::BufferedException)