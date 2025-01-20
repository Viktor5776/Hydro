#include "StackTrace.h"
#include "backward.hpp"
#include <sstream>
#include "String.h"

namespace hydro::utl
{
	StackTrace::StackTrace()
	{
		backward::TraceResolver workAround; // https://github.com/bombela/backward-cpp/issues/206
		pTrace = std::make_unique<backward::StackTrace>();
		pTrace->load_here(64);
	}

	StackTrace::StackTrace( const StackTrace& src)
		:
		pTrace( std::make_unique<backward::StackTrace>(*pTrace) )
	{}

	StackTrace& StackTrace::operator=( const StackTrace& src)
	{
		pTrace = std::make_unique<backward::StackTrace>( *pTrace );
		return *this;
	}

	StackTrace::~StackTrace()
	{
	}

	std::wstring StackTrace::Print() const
	{
		std::ostringstream oss;
		backward::Printer printer;
		printer.print( *pTrace, oss );
		return utl::ToWide(oss.str());
	}

}