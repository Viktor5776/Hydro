#include <iostream>
#include <Core/log/Log.h>
#include <Core/ioc/Container.h>
#include <Core/log/SeverityLevelPolicy.h>

using namespace hydro;

void Boot()
{
	log::Boot();

	ioc::Get().Register<log::ISeverityLevelPolicy>([] {
		return std::make_shared<log::SeverityLevelPolicy>(log::Level::Warn);
	});
}

int main()
{
	Boot();

	hydrolog.fatal(L"Hello There!");
	hydrolog.warn(L"huh");
	hydrolog.error(L"oops!");

	return 0;
}