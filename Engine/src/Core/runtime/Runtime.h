#pragma once

namespace hydro::runtime
{
	class IRuntime
	{
	public:
		virtual	~IRuntime() = default;
		virtual int Run() = 0;
	};
}