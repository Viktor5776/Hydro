#include "gtest_wrapper.h"
#include <Core/log/TextFormatter.h>
#include <Core/log/Entry.h>

using namespace hydro;
using namespace std::string_literals;


namespace Log
{
	TEST( LogTextFormatterTests, TestFormat )
	{
		const log::Entry e{
			.level_ = log::Level::Info,
			.note_ = L"Hello there",
			.sourceFile_ = __FILEW__,
			.sourceFunctionName_ = __FUNCTIONW__,
			.sourceLine_ = __LINE__,
			.timestamp_ = std::chrono::system_clock::time_point{
				std::chrono::days{ 10000 }
			}
		};

		EXPECT_EQ( L"@Info {1997-05-19 02:00:00.0000000 GMT+2} Hello there\n  >> at Log::LogTextFormatterTests_TestFormat_Test::TestBody\n     C:\\Users\\vikto\\OneDrive\\Skrivbord\\Hydro\\UnitTest\\src\\LogTextFormatter.cpp(18)\n"s, log::TextFormatter{}.Format( e ) );
	}
}