/**
 * 
 * IMPORTANT. Check the comments at boostlog.h to 
 * build succeded the sample.
 * 
 * // Header-Only: FROM https://www.boost.org/doc/libs/1_75_0/libs/json/doc/html/json/overview.html#json.overview.requirements
 * This remove the need to link the library on link step (-lboost_json), which raises an error in OSX.
 */

#include <boost/json/src.hpp> 
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <thread>
#include <cassert>
#include <boost/version.hpp>
#include <boost/json.hpp>
#include "boostlog.h"
#include "mythread.h"

namespace json = boost::json;
namespace logging   = boost::log;
namespace src       = boost::log::sources;
namespace sinks     = boost::log::sinks;
namespace expr      = boost::log::expressions;
namespace keywords  = boost::log::keywords;

void initLogs(std::string logPath);
void printJSON(json::value &vl, json::string_view key, std::string ph);
json::value parseJson(std::istream &is, json::error_code &ec);

void initLogs(std::string logPath)
{
    logging::trivial::severity_level lvlLog= logging::trivial::fatal;
    
    LT_TRACE << "****************************************************************\n";
    LT_TRACE << "LogPath:\n";
    LT_TRACE << logPath << ":\n";
    LT_TRACE << "****************************************************************\n";

    logging::add_file_log 
    (
        keywords::file_name = logPath,
        keywords::rotation_size = 10 * 1024 * 1024,
        keywords::max_files = 10,
        keywords::open_mode = std::ios_base::app,//std::ios_base::app|std::ios_base::out,
        keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
        //keywords::format = "%LineID%\t%TimeStamp%\t[%ProcessID%:%ProcessID%]\t%Severity%\t%Message%"  
        keywords::format = "%TimeStamp%\t%Severity%\t%Message%"
    );
    logging::add_console_log
    (
        std::cout,
        keywords::format = "%Severity%\t%Message%"
    );
    logging::add_common_attributes();
    
    
    int opt;
    std::cout << "\nSpecify the log level: \n"
              << "\t1: TRACE the lowest level\n"
              << "\t2: DEBUG\n"
              << "\t3: INFO\n"
              << "\t4: WARN\n"
              << "\t5: ERROR\n"
              << "\t6: FATAL the uppest level\n"
              << "FATAL is the default value.\n";
    
    std::cin >> opt;

    switch (opt)
    {
    case 1:
        lvlLog= logging::trivial::trace;
        break;
    case 2:
        lvlLog= logging::trivial::debug;
        break;
    case 3:
        lvlLog= logging::trivial::info;
        break;
    case 4:
        lvlLog= logging::trivial::warning;
        break;
    case 5:
        lvlLog= logging::trivial::error;
        break;
    case 6:
        lvlLog= logging::trivial::fatal;
        break;
    default:
        break;
    }

    //Setting the severity log to a minimal level
    logging::core::get()->set_filter
    (
        logging::trivial::severity >= lvlLog
    );
}

json::value parseJson(std::istream &is, json::error_code &ec)
{
    json::stream_parser p;

    is.seekg(0, is.end);
    size_t length = is.tellg();
    is.seekg(0, is.beg);

    char buf[length];
    is.read((char*)buf, length);
    LT_TRACE << "Parsing JSON file of [" << length << "] bytes";

    p.write(buf, length, ec);
    p.finish(ec);

    if (ec)
        return nullptr;


    json::value vval;

    try{
        vval = p.release();
    }
    catch(const std::exception &e)
    {
        LT_FATAL << "Error in parsing JSON file: " << e.what();
    }
    LT_TRACE << "Parsing JSON ended.";

    return vval;
}

void printJSON(json::value &vl, json::string_view key, std::string ph)
{
    //LT_TRACE << "\n" << ph;
    auto kind = vl.kind();
    if (kind == json::kind::object)
    {
        LT_DEBUG << "Object: [" << key << "]:";
        ph += "\t";
        json::object &obj = vl.get_object();

        for (auto it = obj.begin(); it != obj.end(); it++)
            printJSON(it->value(), it->key(), ph);

    }
    else if (kind == json::kind::array)
    {
        json::array &arr = vl.get_array();
        int idx = 0;
        size_t cpcty = arr.capacity();

        for (size_t idx = 0; idx < cpcty; idx++)
        {
            std::stringstream sdx;
            sdx << idx;
            printJSON(arr.at(idx), sdx.str(), ph);
        }
    }
    else if (kind == json::kind::string)
    {
        std::string dd = vl.get_string().c_str();
        LT_DEBUG << "String: [" << key << "]: [" << vl.get_string() << "] vs [" << dd << "]";
    }
    else if (kind == json::kind::double_)
        LT_DEBUG << "Double: [" << key << "]: [" << vl.get_double() << "]";
    else if (kind == json::kind::bool_)
        LT_DEBUG << "Bool: [" << key << "]: [" << (vl.get_bool() ? "true":"false") << "]";
    else if (kind == json::kind::int64)
        LT_DEBUG << "Integer: [" << key << "]: [" << vl.get_int64() << "]";
    else if (kind == json::kind::uint64)
        LT_DEBUG << "UInteger: [" << key << "]: [" << vl.get_uint64() << "]";
    else if (kind == json::kind::null)
        LT_DEBUG << "UInteger: [" << key << "]: -NULL-";    
    else
        LT_DEBUG << "--NA--[" << key << "]";
}

int main(int argc, char* argv[])
{
    json::error_code ec;

    initLogs(argv[1]);

    LT_INFO << "-------------------------------------------------";
    LT_INFO << "BOOST Version: " << BOOST_VERSION << "\tShort: " << BOOST_LIB_VERSION;
    LT_INFO << "-------------------------------------------------";
    //std::string fpath = "../extrafiles/sample.json";
    std::string fpath = "/Users/jorgeomarmedratorres/Documents/JOMT/vsworkspace/boost_jsonlogs/extrafiles/sample.json";

    LT_TRACE << "A trace severity message";
    LT_DEBUG << "A debug severity message";
    LT_INFO << "An informational severity message";
    LT_WARN << "A warning severity message";
    LT_ERROR << "An error severity message";
    LT_FATAL << "A fatal severity message";
    LT_INFO << "...................................";
    LT_INFO << "Reading json file [" << fpath << "]:";
    
    
    std::fstream fs;
    fs.open(fpath, std::fstream::in);
    if(fs)
    {
        json::value cfg = parseJson(fs, ec);
        printJSON(cfg, "", "");
        std::cout << std::endl;
    }
    else
        LT_WARN << "It was not possible to open the json file [" << fpath << "]:";

    LT_INFO << "...................................";
    LT_INFO << "Running 10 threads";
    
    jomt::MyThread* mt[10];
    std::thread* t[10];
    for(int i=0; i<10; i++)
    {
        std::stringstream nm;
        nm << "Thread" << (i+1);

        mt[i] = new jomt::MyThread(nm.str());
        t[i] = new std::thread(&jomt::MyThread::run, *mt[i]);
    }

    for(int i=0; i<10; i++)
        t[i]->join();

    LT_INFO << "|--- FINISH ---|";
    return 0;
}
