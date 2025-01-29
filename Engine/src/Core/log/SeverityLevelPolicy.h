#pragma once
#include "Policy.h"
#include "Level.h"

namespace hydro::log
{
	class ISeverityLevelPolicy : public IPolicy {};

	class SeverityLevelPolicy : public ISeverityLevelPolicy
	{
	public:
		SeverityLevelPolicy(Level level);
		bool TransformFilter(Entry& entry);
	private:
		Level level_;
	};
}