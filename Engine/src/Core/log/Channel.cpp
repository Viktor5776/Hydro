#include "Channel.h"
#include "Driver.h"
#include "Policy.h"

namespace hydro::log
{

	Channel::Channel(std::vector<std::shared_ptr<IDriver>> driverPtrs)
		:
		driverPtrs_(std::move(driverPtrs))
	{}

	Channel::~Channel()
	{}

	void Channel::Submit(Entry& entry)
	{
		for (auto& pPolicy : policyPtrs_) {
			if (!pPolicy->TransformFilter(entry)) {
				return;
			}
		}
		for (auto& pDriver : driverPtrs_) {
			pDriver->Submit(entry);
		}
	}

	void Channel::Flush()
	{
		for (auto& pDriver : driverPtrs_) {
			pDriver->Flush();
		}
	}

	void Channel::AttachDriver(std::shared_ptr<IDriver> pDriver)
	{
		driverPtrs_.push_back(std::move(pDriver));
	}

	void Channel::AttachPolicy(std::shared_ptr<IPolicy> pPolicy)
	{
		policyPtrs_.push_back(std::move(pPolicy));
	}

}