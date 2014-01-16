/* 
 * File:   driver.hpp
 * Author: andrewkubera
 *
 * Created on January 6, 2014, 9:35 PM
 */

#pragma once

#include <vector>
#include <string>
#include <regex>

#include "cppdb.hpp"

#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

// the default path to look for drivers
const fs::path driver_path_default("./build/drivers/");

CPPDB_NAMESPACE_BEGIN

class Driver
{
public:

    Driver()
    {
    };

    Driver(const Driver& orig)
    {
    };

    virtual ~Driver()
    {
    };

    virtual int Connect(const std::string& host, const std::string& database, cppdb::port_t port, const std::string& username, const std::string& password) = 0;

    static void LoadDrivers(const std::string& path = driver_path_default.string())
    {

    };

    static std::vector<std::string> GetDriverNames()
    {
        // regex to match driver libraries (lib_<NAME>_driver.*)
        const std::regex driver_file_regex("lib_[^_]*)_driver.*");
//        try {
//            driver_file_regex = std::regex("lib_([^_]*)_driver.*");
//        } catch (std::regex_error e) {
//            driver_file_regex = std::regex(R"(lib_([^_]*)_driver\..*)");
//        }

        fs::path driver_path(driver_path_default);

        if (!fs::is_directory(driver_path)) {
            std::cerr << "Error : Path " << fs::absolute(driver_path) << " is not a directory." << std::endl;
            exit(EXIT_FAILURE);
        }

        std::vector<std::string> res;

        fs::directory_iterator path_it(driver_path), end;

        // loop through each subdirectory in 'driver_path'
        for (; path_it != end; path_it++) {
            // if not a regular file, move on
            if (!fs::is_regular_file(path_it->path())) {
                continue;
            }

            // get filename from path iterator
            auto filename = path_it->path().filename().string();

            // store matches into a string match result
            std::smatch sm;
                std::cout << filename << std::endl;
            // if it matches - add it to the result
            if (std::regex_match(filename, sm, driver_file_regex)) {
                std::cout << " matches. count " << sm.size() << std::endl;
                res.push_back(sm[1]);
            }

        }
        return res;
    };

protected:

};

CPPDB_NAMESPACE_END
