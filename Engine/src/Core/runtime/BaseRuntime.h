#pragma once
#include <string>
#include "Runtime.h"

namespace hydro::runtime
{
	class BaseRuntime : public IRuntime
	{
	public:
		BaseRuntime(const std::string& name);
		int Run() override;
	};
}