#include "MsvcDebugDriver.h"
#include "TextFormatter.h"
//MSVC specific may not work on other compilers
#include <Windows.h>

namespace hydro::log
{

	MsvcDebugDriver::MsvcDebugDriver(std::shared_ptr<ITextFormatter> pFormatter_)
		:
		pFormatter_(std::move(pFormatter_))
	{}

	void MsvcDebugDriver::Submit(const Entry& e)
	{
		if (pFormatter_) {
			OutputDebugStringW(pFormatter_->Format(e).c_str());
		}
	}

	void MsvcDebugDriver::SetFormatter(std::shared_ptr<ITextFormatter> pFormatter)
	{
		pFormatter_ = std::move(pFormatter);
	}

}
