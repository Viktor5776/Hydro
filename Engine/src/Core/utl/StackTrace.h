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
		StackTrace(size_t skip = 0);
		StackTrace(const StackTrace&);
		StackTrace(StackTrace&&) noexcept;
		StackTrace& operator=(const StackTrace&);
		StackTrace& operator=(StackTrace&&) noexcept;
		~StackTrace();
		std::wstring Print() const;
	private:
		std::unique_ptr<backward::StackTrace> pTrace;
	};
}