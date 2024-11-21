#include "Container.h"

namespace hydro::ioc
{
	Container& Get() noexcept
	{
		static Container container;
		return container;
	}
}
