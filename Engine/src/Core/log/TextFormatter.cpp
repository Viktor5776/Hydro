#include "TextFormatter.h"
#include "Entry.h"
#include <format>
#include <sstream>


namespace hydro::log
{

	std::wstring TextFormatter::Format(const Entry& e)
	{
		std::wostringstream oss;
		oss << std::format(L"@{} {{{}}} {}\n  >> at {}\n     {}({})\n",
			GetLevelName(e.level_),
			std::chrono::zoned_time{ std::chrono::current_zone(), e.timestamp_ },
			e.note_,
			e.sourceFunctionName_,
			e.sourceFile_,
			e.sourceLine_
		);
		if (e.trace_) {
			oss << e.trace_->Print() << std::endl;
		}
		return oss.str();
	}

}