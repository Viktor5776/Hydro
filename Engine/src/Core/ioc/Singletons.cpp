#include "Singletons.h"

namespace hydro::ioc
{
	Singletons& Sing()
	{
		static Singletons sing;
		return sing;
	}
}