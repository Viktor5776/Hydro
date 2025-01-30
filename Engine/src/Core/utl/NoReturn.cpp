#include "NoReturn.h"
#include "Assert.h"

namespace hydro::utl
{
	void NoReturnImpl_()
	{
		hass(false).msg(L"Reached no_return guard!");
	}
}
