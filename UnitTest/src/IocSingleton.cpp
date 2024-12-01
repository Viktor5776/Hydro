#include "gtest_wrapper.h"
#include <Core/ioc/Container.h>
#include <Core/ioc/Singletons.h>
#include <memory>
#include <string>

namespace Infrastructure
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

	struct ParameterizedClass
	{
		struct IocParams
		{
			std::string s;
		};
		ParameterizedClass( IocParams params ) : s{ std::move( params.s ) } {}
		std::string s;
	};
	struct Dependant
	{
		std::shared_ptr<Base> pDependency;
		Dependant( std::shared_ptr<Base> pDependency_in ) : pDependency{ std::move( pDependency_in ) } {}
	};

	using namespace hydro;
	using namespace std::string_literals;

	class IocSingletonTests : public ::testing::Test
	{
	protected:
		void SetUp() override
		{
			pIoc = std::make_unique<ioc::Container>();
			pSing = std::make_unique<ioc::Singletons>();
		}

		void TearDown() override
		{
			pIoc.reset();
			pSing.reset();
		}

		std::unique_ptr<ioc::Container> pIoc;
		std::unique_ptr<ioc::Singletons> pSing;
	};

	TEST_F( IocSingletonTests, PolymorphicResolveDirect )
	{
		pSing->Register<Base>( [] {return std::make_shared<Derived>(); } );
		EXPECT_EQ( 42, pSing->Resolve<Base>()->Test() );
	}
	// registering a service with a derived implementation, and resolving derived
	// indirect creation using ioc container
	TEST_F( IocSingletonTests, PolymorphicResolveIndirect )
	{
		pIoc->Register<Base>( [] {return std::make_shared<Derived>(); } );
		pSing->Register<Base>( [this] {return pIoc->Resolve<Base>(); } );
		EXPECT_EQ( 42, pSing->Resolve<Base>()->Test() );
	}
	// trying to resolve a service without registering
	TEST_F( IocSingletonTests, SimpleResolveFailure )
	{
		EXPECT_THROW( pSing->Resolve<Base>(), std::runtime_error );
	}
	// dependent resolve, where resolved instances of the same type are the object
	TEST_F( IocSingletonTests, DependentResolve )
	{
		pSing->Register<ParameterizedClass>( [] {
			return std::make_shared<ParameterizedClass>( ParameterizedClass::IocParams{ .s = "first"s } );
		} );
		auto pFirst = pSing->Resolve<ParameterizedClass>();
		auto pSecond = pSing->Resolve<ParameterizedClass>();
		EXPECT_EQ( "first"s, pFirst->s );
		EXPECT_EQ( "first"s, pSecond->s );
		// changing one should affect the other
		pFirst->s = "pube"s;
		EXPECT_EQ( "pube"s, pFirst->s );
		EXPECT_EQ( "pube"s, pSecond->s );
	}
}