#include <iostream>
#include <Core/log/Log.h>
#include <Core/ioc/Container.h>
#include <Core/log/SeverityLevelPolicy.h>
#include <Core/utl/Assert.h>

using namespace hydro;
using namespace std::string_literals;

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

	int x = 0, y = 1;
	hass(x > y).msg(L"Test").watch(x, y, rand());
	return 0;
}