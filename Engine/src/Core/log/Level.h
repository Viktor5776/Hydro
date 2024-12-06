#pragma once
#include <string>

namespace hydro::log
{
	enum class Level
	{
		Trace,
		Debug,
		Info,
		Warn,
		Error,
		Fatal,
	};
	std::wstring GetLevelName( Level );
}