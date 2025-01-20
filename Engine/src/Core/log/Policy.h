#pragma once

namespace hydro::log
{
	struct Entry;

	class IPolicy
	{
	public:
		virtual ~IPolicy() = default;
		virtual bool TransformFilter( Entry& ) = 0;
	};
}