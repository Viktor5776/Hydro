#pragma once
#include "Policy.h"
#include "Level.h"

namespace hydro::log
{
	class SeverityLevelPolicy : public IPolicy
	{
	public:
		SeverityLevelPolicy(Level level);
		bool TransformFilter(Entry& entry);
	private:
		Level level_;
	};
}