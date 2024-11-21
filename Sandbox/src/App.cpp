#include <iostream>
#include <Core/ioc/Container.h>

struct Base
{
	virtual int Test() { return 420; }
	virtual ~Base() = default;
};

struct Derived : public Base
{
	int Test() override { return 42; }
};

int main()
{
	using namespace hydro;

	ioc::Get().Register<Base>( [] {return std::make_shared<Derived>(); } );

	std::cout << ioc::Get().Resolve<Base>()->Test() << std::endl;
}