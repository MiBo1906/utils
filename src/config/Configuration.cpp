#include "config/Configuration.hpp"
#include <cstdlib>
#include <fstream>
#include <system_error>

config::Configuration::Configuration():
    configurationValues() {
}
 
config::Configuration::~Configuration() {

}

void config::Configuration::initConfiguration(std::filesystem::path configFile) {

    try
    {
        if(std::filesystem::exists(configFile)) {
            
            std::fstream stream(configFile.string(), std::ios::in);

            if(stream.good()) {
                std::string input;
                
                while (!stream.eof()) {
                    std::getline(stream,input);
                    std::size_t found = input.find(":");
                    if(found != std:: string::npos && found < input.length()) {
                        std::string key = input.substr(0,found-1);
                        std::string value = input.substr(found+1);

                        if(std::getenv(key.c_str()) != nullptr) {
                            value = std::string(std::getenv(key.c_str()));
                        }

                        configurationValues.emplace(key,value);
                    }
                    input.clear();
                }
            }
        }
        else {
            throw std::filesystem::filesystem_error("Failure in initConfiguration",configFile,std::error_code(2,std::system_category()));
        }
    }
    catch(const std::filesystem::filesystem_error& e)
    {
        std::cerr << e.what() << '\n';
        throw e;
    }
    
}