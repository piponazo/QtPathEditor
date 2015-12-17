#include "string_functions.h"
#include <sstream>
#include <regex>

StringListT fromRegistryString(const std::wstring &string, wchar_t separator)
{
	// tokenize using RegExp
	StringListT strList;

	std::wregex reSeparator(std::wstring(L"[^") + separator + std::wstring(L"]+"));
	std::wsregex_token_iterator begin( string.begin(), string.end(), reSeparator);
	std::wsregex_token_iterator end;

	std::copy( begin, end, std::back_inserter( strList));
	strList.erase(std::remove_if(strList.begin(), strList.end(), [](const std::wstring str){
		return str.empty() || str[0] == 0; }), strList.end());
	return strList;
}

std::wstring toRegistryString(const StringListT &paths, wchar_t separator)
{
	std::wstring sSeparator( 1, separator);
	std::wostringstream ss;
	std::copy( paths.begin(), paths.end(), std::ostream_iterator<StringListT::value_type,
			   StringListT::value_type::value_type>( ss, sSeparator.c_str()));
	return ss.str();
}
