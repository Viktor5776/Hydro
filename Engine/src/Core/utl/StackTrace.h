#pragma once
#include <memory>
#include <string>

namespace backward
{
	class StackTrace;
}

namespace hydro::utl
{
	class StackTrace
	{
	public:
		StackTrace();
		StackTrace(const StackTrace&);
		StackTrace& operator=(const StackTrace&);
		~StackTrace();
		std::wstring Print() const;
	private:
		std::unique_ptr<backward::StackTrace> pTrace;
	};
}