#include "pathreader.h"
#include <gtest/gtest.h>

TEST(PathReaderTests, shouldReadWithDefaultInstance)
{
    CPathReader instance;
    StringListT paths;

    ASSERT_TRUE(instance.Read(paths));
    EXPECT_GT(paths.size(), 0);
}
