#pragma once
#include <memory>
#include <vector>


namespace hydro::log
{
	struct Entry;
	class IDriver;
	class IPolicy;

	class IChannel
	{
	public:
		virtual ~IChannel() = default;
		virtual void Submit(Entry&) = 0;
		virtual void AttachDriver(std::shared_ptr<IDriver>) = 0;
		virtual void AttachPolicy(std::shared_ptr<IPolicy>) = 0;
	};

	class Channel : public IChannel
	{
	public:
		Channel(std::vector<std::shared_ptr<IDriver>> driverPtrs = {});
		~Channel();
		virtual void Submit(Entry&) override;
		virtual void AttachDriver(std::shared_ptr<IDriver>) override;
		virtual void AttachPolicy(std::shared_ptr<IPolicy>) override;
	private:
		std::vector<std::shared_ptr<IDriver>> driverPtrs_;
		std::vector<std::shared_ptr<IPolicy>> policyPtrs_;
	};
}