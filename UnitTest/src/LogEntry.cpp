#include "gtest_wrapper.h"
#include <Core/log/EntryBuilder.h>
#include <Core/log/Channel.h>
#include <Core/log/Policy.h>

using namespace hydro;
using namespace std::string_literals;

#define hydrolog log::EntryBuilder{ __FILEW__, __FUNCTIONW__, __LINE__ }

class MockChannel : public log::IChannel
{
public:
	void Submit( log::Entry& e ) override
	{
		entry_ = e;
	}
	void AttachDriver( std::shared_ptr<log::IDriver> ) override {}
	void AttachPolicy( std::unique_ptr<log::IPolicy> ) override {}
	log::Entry entry_;
};

namespace Log
{
	TEST( LogEntryTests, ShowOffFluent )
	{
		MockChannel chan;
		hydrolog.level( log::Level::Info ).note( L"HI" ).chan( &chan );
		EXPECT_EQ( L"HI"s, chan.entry_.note_ );
		EXPECT_EQ( log::Level::Info, chan.entry_.level_ );
		EXPECT_EQ( 28, chan.entry_.sourceLine_ );
	}

	// testing simplified level/note
	TEST( LogEntryTests, SimplifiedLevelNote )
	{
		MockChannel chan;
		hydrolog.info( L"HI" ).chan( &chan );
		EXPECT_EQ( L"HI"s, chan.entry_.note_ );
		EXPECT_EQ( log::Level::Info, chan.entry_.level_ );
		EXPECT_EQ( 38, chan.entry_.sourceLine_ );
	}
}