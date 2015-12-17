#include "string_functions.h"
#include <gtest/gtest.h>

namespace
{
	const std::wstring goodRegString{L"C:\\Program Files (x86)\\CMake\\bin;C:\\Python27;"
		L"C:\\Program Files (x86)\\Vim\\vim74;C:\\Qt\\4.8.7\\bin;E:\\Dev\\Libs\\external\\dllsDebug;"
		L"E:\\Dev\\Libs\\external\\dllsRelease;"
	};

	const StringListT goodPaths { L"C:\\Program Files (x86)\\CMake\\bin",
							  L"C:\\Python27",
							  L"C:\\Program Files (x86)\\Vim\\vim74",
							  L"C:\\Qt\\4.8.7\\bin",
							  L"E:\\Dev\\Libs\\external\\dllsDebug",
							  L"E:\\Dev\\Libs\\external\\dllsRelease"};
}

TEST(StringFunctionsTests, shouldSplitRegistryStringInSeveralPaths)
{
	const auto computedPaths = fromRegistryString(goodRegString);
	ASSERT_EQ(6, computedPaths.size());
	ASSERT_EQ(goodPaths, computedPaths);
}

TEST(StringFunctionsTests, shouldGetEmptyVectorWithEmptyString)
{
	const StringListT computedPaths = fromRegistryString(L"");
	ASSERT_TRUE(computedPaths.empty());
}

TEST(StringFunctionsTests, shouldGetEmptyVectorWithInvalidSeparator)
{
	const StringListT computedPaths = fromRegistryString(goodRegString, L'_');
	ASSERT_EQ(0, computedPaths.size());
}

TEST(StringFunctionsTests, shouldJoinSeveralPathsIntoRegistryString)
{

	const auto computedRegString = toRegistryString(goodPaths);
	ASSERT_EQ(computedRegString, goodRegString);
}
