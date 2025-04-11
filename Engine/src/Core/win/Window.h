#pragma once
#include <string>

namespace hydro::win
{
	class IWindow
	{
	public:
		virtual	~IWindow() = default;
		virtual void SetName(const std::string& name) = 0;
		virtual void SetPos(std::pair<int, int> pos) = 0;
		virtual void SetSize(std::pair<int, int> size) = 0;
	};
}