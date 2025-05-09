#include <iostream>
#include <Core/log/Log.h>
#include <Core/ioc/Container.h>
#include <Core/log/SeverityLevelPolicy.h>
#include <Core/utl/Assert.h>
#include <Core/runtime/BaseRuntime.h>
#include <Core/ecs/Ecs.h>

using namespace hydro;
using namespace std::string_literals;

void Boot()
{
	log::Boot();

	ioc::Get().Register<runtime::IRuntime>([] {
		return std::make_shared<runtime::BaseRuntime>("Base Window");
	});
	
}



int main()
{
	Boot();

	ioc::Get().Resolve<runtime::IRuntime>()->Run();

	return 0;
}