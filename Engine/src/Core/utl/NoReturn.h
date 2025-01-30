#pragma once

namespace hydro::utl
{
	[[noreturn]]
	void NoReturnImpl_();

}

#define no_return hydro::utl::NoReturnImpl_()