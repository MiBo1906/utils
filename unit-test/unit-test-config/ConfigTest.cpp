#include "config/Configuration.hpp"
#include "gtest/gtest.h"
#include <filesystem>
#include <fstream>
#include <stdlib.h>
class ConfigTestFixture : public ::testing::Test {
public:
  ConfigTestFixture() {
    if (!std::filesystem::exists("/tmp/configuration.ini")) {
      std::fstream file("/tmp/configuration.ini", std::ios_base::out);
      if (file.is_open()) {
        file.write("test:1\nstr:Hallo\ndata:\n", 23);
        file.flush();
        file.close();
      }
    }
  }

  void SetUp() {
    // code here will execute just before the test ensues
  }

  void TearDown() {
    // code here will be called just after the test completes
    // ok to through exceptions from here if need be
  }

  ~ConfigTestFixture() {
    // cleanup any pending stuff, but no exceptions allowed
  }

  // put in any custom data members that you need
};

TEST_F(ConfigTestFixture, testReadNonExistingFile) {
  config::Configuration conf;

  EXPECT_THROW(conf.initConfiguration("/tmp/config.ini"),
               std::filesystem::filesystem_error);
}

TEST_F(ConfigTestFixture, testReadExistingFile) {
  config::Configuration conf;

  EXPECT_NO_THROW(conf.initConfiguration("/tmp/configuration.ini"));
}

TEST_F(ConfigTestFixture, testReadIntFromConfig) {
  config::Configuration conf;

  EXPECT_NO_THROW(conf.initConfiguration("/tmp/configuration.ini"));

  int value = conf.getValue<int>("test");

  EXPECT_EQ(value, 1);
}

TEST_F(ConfigTestFixture, testReadStringFromConfig) {
  config::Configuration conf;

  EXPECT_NO_THROW(conf.initConfiguration("/tmp/configuration.ini"));

  std::string value = conf.getValue<std::string>("str");

  EXPECT_EQ(value, "Hallo");
}

TEST_F(ConfigTestFixture, testReadBadCast) {
  config::Configuration conf;

  EXPECT_NO_THROW(conf.initConfiguration("/tmp/configuration.ini"));

  EXPECT_THROW(conf.getValue<int>("str"), std::bad_cast);
}

TEST_F(ConfigTestFixture, testReadNonExistingValue) {
  config::Configuration conf;

  EXPECT_NO_THROW(conf.initConfiguration("/tmp/configuration.ini"));

  EXPECT_THROW(conf.getValue<int>("data"), std::out_of_range);
}

TEST_F(ConfigTestFixture, testEnvironmentOverridesValue) {
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