#include "Log.h"
#include "../ioc/Singletons.h"
#include "../ioc/Container.h"
#include "SeverityLevelPolicy.h"
#include "MsvcDebugDriver.h"
#include "SimpleFileDriver.h"
#include "TextFormatter.h"

namespace hydro::log
{
    IChannel* hydro::log::GetDefaultChannel()
    {
		static std::shared_ptr<IChannel> channelChachePtr = ioc::Sing().Resolve<IChannel>();
        return channelChachePtr.get();
    }

    void Boot()
    {
		// container
		ioc::Get().Register<log::IChannel>([] {
			std::vector<std::shared_ptr<log::IDriver>> drivers{
				ioc::Get().Resolve<log::IMsvcDebugDriver>(),
				ioc::Get().Resolve<log::ISimpleFileDriver>()
			};
			auto pChan = std::make_shared<log::Channel>(std::move(drivers));
			pChan->AttachPolicy(ioc::Get().Resolve<log::ISeverityLevelPolicy>());
			return pChan;
		});
		ioc::Get().Register<log::IMsvcDebugDriver>([] {
			return std::make_shared<log::MsvcDebugDriver>(ioc::Get().Resolve<log::ITextFormatter>());
		});
		ioc::Get().Register<log::ISimpleFileDriver>([] {
			return std::make_shared<log::SimpleFileDriver>("logs\\log.txt", ioc::Get().Resolve<log::ITextFormatter>());
		});
		ioc::Get().Register<log::ITextFormatter>([] {
			return std::make_shared<log::TextFormatter>();
		});
		ioc::Get().Register<log::ISeverityLevelPolicy>([] {
			return std::make_shared<log::SeverityLevelPolicy>(log::Level::Error);
		});

		// Singleton
		ioc::Sing().RegisterPassthru<log::IChannel>();
    }
}