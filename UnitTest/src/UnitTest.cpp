#include <gtest/gtest.h>
#include <Core/ioc/Container.h>

namespace IocTests
{
	struct Base
	{
		virtual int Test() { return 420; }
		virtual ~Base() = default;
	};

	struct Derived : public Base
	{
		int Test() override { return 42; }
	};

	TEST( IocTest, Test )
	{
		using namespace hydro;

		ioc::Get().Register<Base>( [] {return std::make_shared<Derived>(); } );

		EXPECT_EQ( ioc::Get().Resolve<Base>()->Test(), 42 );
	}
}