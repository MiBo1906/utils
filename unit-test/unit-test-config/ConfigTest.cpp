#include "config/Configuration.hpp"
#include "gtest/gtest.h"
#include <stdlib.h>

TEST(Configuration, testReadNonExistingFile) {
  config::Configuration conf;

  EXPECT_THROW(conf.initConfiguration("/tmp/config.ini"),
               std::filesystem::filesystem_error);
}

TEST(Configuration, testReadExistingFile) {
  config::Configuration conf;

  EXPECT_NO_THROW(conf.initConfiguration("/tmp/configuration.ini"));
}

TEST(Configuration, testReadIntFromConfig) {
  config::Configuration conf;

  EXPECT_NO_THROW(conf.initConfiguration("/tmp/configuration.ini"));

  int value = conf.getValue<int>("test");

  EXPECT_EQ(value, 1);
}

TEST(Configuration, testReadStringFromConfig) {
  config::Configuration conf;

  EXPECT_NO_THROW(conf.initConfiguration("/tmp/configuration.ini"));

  std::string value = conf.getValue<std::string>("str");

  EXPECT_EQ(value, "Hallo");
}

TEST(Configuration, testReadBadCast) {
  config::Configuration conf;

  EXPECT_NO_THROW(conf.initConfiguration("/tmp/configuration.ini"));

  EXPECT_THROW(conf.getValue<int>("str"), std::bad_cast);
}

TEST(Configuration, testReadNonExistingValue) {
  config::Configuration conf;

  EXPECT_NO_THROW(conf.initConfiguration("/tmp/configuration.ini"));

  EXPECT_THROW(conf.getValue<int>("data"), std::out_of_range);
}

TEST(Configuration, testEnvironmentOverridesValue) {
  config::Configuration conf;
  setenv("test", "2", true);

  EXPECT_NO_THROW(conf.initConfiguration("/tmp/configuration.ini"));

  int value = conf.getValue<int>("test");

  EXPECT_EQ(value, 2);

  unsetenv("test");

  config::Configuration conf1;
  EXPECT_NO_THROW(conf1.initConfiguration("/tmp/configuration.ini"));

  value = conf1.getValue<int>("test");

  EXPECT_EQ(value, 1);
}