#ifndef CONFIGURATION_HPP_INCLUDED
#define CONFIGURATION_HPP_INCLUDED

#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>
#include <typeinfo>
#include <unordered_map>
namespace config {

class Configuration {

public:
  void initConfiguration(std::filesystem::path configFile);

  template <typename T> T getValue(std::string key);

private:
  std::unordered_map<std::string, std::string> configurationValues;
};

template <typename T> T Configuration::getValue(std::string key) {
  try {
    std::string value = configurationValues.at(key);
    T result;

    std::istringstream ss(value);
    ss >> result;

    if (!ss.fail())
      return result;
  } catch (std::out_of_range &e) {
    std::cerr << e.what() << '\n';
    throw e;
  } catch (...) {
  }

  throw std::bad_cast();
}

template <> std::string Configuration::getValue(std::string key) {
  try {
    std::string value = configurationValues.at(key);

    return value;
  } catch (std::out_of_range &e) {
    std::cerr << e.what() << '\n';
  }

  throw std::bad_cast();
}

} // namespace config

#endif