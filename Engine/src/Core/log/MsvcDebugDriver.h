#pragma once
#include "Driver.h"

namespace hydro::log
{
	class IMsvcDebugDriver : public ITextDriver {};

	class MsvcDebugDriver : public IMsvcDebugDriver
	{
	public:
		MsvcDebugDriver(std::shared_ptr<ITextFormatter> pFormatter_ = {});
		void Submit(const Entry& e) override;
		void SetFormatter(std::shared_ptr<ITextFormatter> pFormatter) override;
		void Flush() override;
	private:
		std::shared_ptr<ITextFormatter> pFormatter_;
	};
}