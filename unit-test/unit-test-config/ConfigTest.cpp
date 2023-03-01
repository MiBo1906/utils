#include "gtest/gtest.h"
#include "config/Configuration.hpp"

TEST(Configuration, testReadNonExistingFile) 
{
    config::Configuration conf;

    EXPECT_THROW(conf.initConfiguration("/tmp/config.ini"),std::filesystem::filesystem_error);
}