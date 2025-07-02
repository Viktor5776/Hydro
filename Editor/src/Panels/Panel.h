#pragma once
#include <string>

namespace hydro::editor
{
	class Panel
	{
	public:
		virtual ~Panel() = default;
		virtual void Render() = 0;
		virtual std::string GetName() const = 0;
		bool isOpen = true;
	};
}