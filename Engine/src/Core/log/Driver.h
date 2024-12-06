#pragma once

namespace hydro::log
{
	struct Entry;

	class IDriver
	{
	public:
		virtual ~IDriver() = default;
		virtual void Submit( const Entry& ) = 0;
	};
}