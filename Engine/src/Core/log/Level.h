#pragma once
#include <string>

namespace hydro::log
{
	enum class Level
	{
		None,
		Fatal,
		Error,
		Warn,
		Info,
		Debug,
		Verbose,
	};
	std::wstring GetLevelName( Level );
}