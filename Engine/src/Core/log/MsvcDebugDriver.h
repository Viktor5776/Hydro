#pragma once
#include "Driver.h"

namespace hydro::log
{
	class MsvcDebugDriver : public ITextDriver
	{
	public:
		MsvcDebugDriver(std::unique_ptr<ITextFormatter> pFormatter_ = {});
		void Submit(const Entry& e) override;
		void SetFormmater(std::unique_ptr<ITextFormatter> pFormatter) override;
	private:
		std::unique_ptr<ITextFormatter> pFormatter_;
	};
}