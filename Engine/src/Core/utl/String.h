#pragma once
#include <string>

namespace hydro::utl
{
	std::wstring ToWide(const std::string& str);
	std::string ToNarrow(const std::wstring& str);
}