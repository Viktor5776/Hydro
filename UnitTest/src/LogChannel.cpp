#include "gtest_wrapper.h"
#include <Core/log/EntryBuilder.h>
#include <Core/log/Channel.h>
#include <Core/log/Driver.h>
#include <Core/log/SeverityLevelPolicy.h>

using namespace hydro;
using namespace std::string_literals;

#define hydrolog log::EntryBuilder{ __FILEW__, __FUNCTIONW__, __LINE__ }

class MockDriver : public log::IDriver
{
public:
	void Submit( const log::Entry& e ) override
	{
		entry_ = e;
	}
	log::Entry entry_;
};

namespace Log
{
	TEST( LogChannelTests, TestForwarding )
	{
		log::Channel chan;
		auto pDriver1 = std::make_shared<MockDriver>();
		auto pDriver2 = std::make_shared<MockDriver>();

		chan.AttachDriver( pDriver1 );
		chan.AttachDriver( pDriver2 );

		hydrolog.info( L"HI" ).chan( &chan );

		EXPECT_EQ( L"HI"s, pDriver1->entry_.note_ );
		EXPECT_EQ( log::Level::Info, pDriver1->entry_.level_ );
		EXPECT_EQ( L"HI"s, pDriver2->entry_.note_ );
		EXPECT_EQ( log::Level::Info, pDriver2->entry_.level_ );
	}

	TEST( LogChannelTests, TestPolicyFiltering )
	{
		log::Channel chan;
		auto pDriver1 = std::make_shared<MockDriver>();
		chan.AttachDriver( pDriver1 );

		chan.AttachPolicy( std::make_unique<log::SeverityLevelPolicy>( log::Level::Info ) );
		hydrolog.info( L"HI" ).chan( &chan );
		EXPECT_EQ( L"HI"s, pDriver1->entry_.note_ );
		EXPECT_EQ( log::Level::Info, pDriver1->entry_.level_ );
		hydrolog.debug( L"HELLO" ).chan( &chan );
		EXPECT_EQ( L"HI"s, pDriver1->entry_.note_ );
		EXPECT_EQ( log::Level::Info, pDriver1->entry_.level_ );
	}
}