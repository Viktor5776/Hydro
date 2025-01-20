#include <iostream>
#include <Core/log/EntryBuilder.h>
#include <Core/log/Channel.h>
#include <Core/log/MsvcDebugDriver.h>
#include <Core/log/TextFormatter.h>
#include <Core/log/SeverityLevelPolicy.h>

using namespace hydro;

#define hydrolog log::EntryBuilder{ __FILEW__, __FUNCTIONW__, __LINE__ }.chan( pChan.get() )

int main()
{
	std::unique_ptr<log::IChannel> pChan = std::make_unique<log::Channel>(
		std::vector<std::shared_ptr<log::IDriver>>{
		std::make_shared<log::MsvcDebugDriver>(std::make_unique<log::TextFormatter>())
	}
	);
	pChan->AttachPolicy(std::make_unique<log::SeverityLevelPolicy>(log::Level::Error));
	hydrolog.fatal(L"Hello There!");
	hydrolog.warn(L"huh");
	hydrolog.error(L"oops!");

	return 0;
}