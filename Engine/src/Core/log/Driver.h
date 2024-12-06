#pragma once
#include <memory>

namespace hydro::log
{
	struct Entry;
	class ITextFormatter;

	class IDriver
	{
	public:
		virtual ~IDriver() = default;
		virtual void Submit( const Entry& ) = 0;
	};

	class ITextDriver : public IDriver
	{
	public:
		virtual void SetFormmater( std::unique_ptr<ITextFormatter> ) = 0;
	};
}