#pragma once
#include "Entry.h"

namespace hydro::log
{
	class IChannel;
	class EntryBuilder : private Entry
	{
	public:
		EntryBuilder(const wchar_t* sourceFile, const wchar_t* sourceFunctionName, int sourceLine);
		EntryBuilder& note(std::wstring note);
		EntryBuilder& level(Level);
		EntryBuilder& verbose(std::wstring note = L"");
		EntryBuilder& debug(std::wstring note = L"");
		EntryBuilder& info(std::wstring note = L"");
		EntryBuilder& warn(std::wstring note = L"");
		EntryBuilder& error(std::wstring note = L"");
		EntryBuilder& fatal(std::wstring note = L"");
		EntryBuilder& chan(IChannel*);
		EntryBuilder& trace_skip(int depth);
		~EntryBuilder();
	private:
		IChannel* pDest_ = nullptr;
		int traceSkipDepth = 6;
	};
}