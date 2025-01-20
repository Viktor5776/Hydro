#pragma once
#include <string>

namespace hydro::log
{
	struct Entry;

	class ITextFormatter
	{
	public:
		virtual ~ITextFormatter() = default;
		virtual std::wstring Format(const Entry&) = 0;
	};

	class TextFormatter : public ITextFormatter
	{
	public:
		std::wstring Format(const Entry& e) override;
	};
}