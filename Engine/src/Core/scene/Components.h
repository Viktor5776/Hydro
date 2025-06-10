#pragma once
#include <string>

namespace hydro
{
	struct TagComponent
	{
		std::string Tag;

		TagComponent(const std::string& tag)
			: Tag(tag)
		{}
	};
}