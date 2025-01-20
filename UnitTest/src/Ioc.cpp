#include "gtest_wrapper.h"
#include <Core/ioc/Container.h>
#include <memory>
#include <string>

namespace Ioc
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
		ParameterizedClass(IocParams params) : s{ std::move(params.s) } {}
		std::string s;
	};
	struct Dependant
	{
		std::shared_ptr<Base> pDependency;
		Dependant(std::shared_ptr<Base> pDependency_in) : pDependency{ std::move(pDependency_in) } {}
	};

	using namespace hydro;
	using namespace std::string_literals;

	class IocTests : public ::testing::Test
	{
	protected:
		void SetUp() override
		{
			pIoc = std::make_unique<ioc::Container>();
		}

		void TearDown() override
		{
			pIoc.reset();
		}

		std::unique_ptr<ioc::Container> pIoc;
	};

	TEST_F(IocTests, PolymorphicResolve)
	{
		pIoc->Register<Base>([] { return std::make_shared<Derived>(); });

		EXPECT_EQ(pIoc->Resolve<Base>()->Test(), 42);
	}

	TEST_F(IocTests, SimpleResloveFailure)
	{
		EXPECT_THROW(pIoc->Resolve<Base>(), std::runtime_error);
	}


	TEST_F(IocTests, ParameterizedResolve)
	{
		pIoc->Register<ParameterizedClass>([](ParameterizedClass::IocParams p) {
			return std::make_shared<ParameterizedClass>(std::move(p));
		});
		EXPECT_EQ("pube"s, pIoc->Resolve<ParameterizedClass>({ .s = "pube"s })->s);
	}
	// cascaded resolve, where factories also use container to resolve dependencies
	TEST_F(IocTests, CascadedResolve)
	{
		pIoc->Register<Dependant>([this] {
			return std::make_shared<Dependant>(pIoc->Resolve<Base>());
		});
		pIoc->Register<Base>([this] {
			return std::make_shared<Base>();
		});
		EXPECT_EQ(420, pIoc->Resolve<Dependant>()->pDependency->Test());
	}
	// independent resolve, where resolved instances of the same type are separate objects
	TEST_F(IocTests, IndependentResolve)
	{
		pIoc->Register<ParameterizedClass>([](ParameterizedClass::IocParams p) {
			return std::make_shared<ParameterizedClass>(std::move(p));
		});
		auto pFirst = pIoc->Resolve<ParameterizedClass>({ .s = "first"s });
		auto pSecond = pIoc->Resolve<ParameterizedClass>({ .s = "second"s });
		EXPECT_EQ("first"s, pFirst->s);
		EXPECT_EQ("second"s, pSecond->s);
		// changing one should not affect the other
		pFirst->s = "pube"s;
		EXPECT_EQ("pube"s, pFirst->s);
		EXPECT_NE("pube"s, pSecond->s);
	}
	// replacing existing factory
	TEST_F(IocTests, ReplacementInjection)
	{
		// first make initial registration and check
		pIoc->Register<Dependant>([this] {
			return std::make_shared<Dependant>(pIoc->Resolve<Base>());
		});
		pIoc->Register<Base>([this] {
			return std::make_shared<Base>();
		});
		EXPECT_EQ(420, pIoc->Resolve<Dependant>()->pDependency->Test());
		// replace nested dependency and verify that Dependant with be affected when resolved
		pIoc->Register<Base>([this] {
			return std::make_shared<Derived>();
		});
		EXPECT_EQ(42, pIoc->Resolve<Dependant>()->pDependency->Test());
	}
}