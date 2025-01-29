#pragma once
#include "Channel.h"
#include "EntryBuilder.h"

namespace hydro::log
{
	IChannel* GetDefaultChannel();

	void Boot();

#ifdef HYDRO_RELEASE
	inline constexpr int defaultTraceSkip = 2;
#else
	inline constexpr int defaultTraceSkip = 6;
#endif
}



#define hydrolog hydro::log::EntryBuilder{ __FILEW__, __FUNCTIONW__, __LINE__ }.chan( hydro::log::GetDefaultChannel() ).trace_skip(log::defaultTraceSkip)