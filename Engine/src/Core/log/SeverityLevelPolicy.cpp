#include "SeverityLevelPolicy.h"
#include "Entry.h"

namespace hydro::log
{

	SeverityLevelPolicy::SeverityLevelPolicy( Level level )
		:
		level_( level )
	{}

	bool SeverityLevelPolicy::TransformFilter( Entry& entry )
	{
		return entry.level_ <= level_;
	}

}