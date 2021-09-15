/*****************************************************************************************
 * 
 * https://www.boost.org/doc/libs/1_77_0/libs/log/doc/html/index.html
 * 
 * IMPORTANT. to compile succeded, it must be included the Macro
 *  
 *          DBOOST_LOG_DYN_LINK
 * int you COMPILE COMMAND, not linke step.
 * 
 * $g++ -g -std=c++17 -MD -DBOOST_LOG_DYN_LINK -lboost_json -lboost_log -lpthread ...
 * 
 * ----
 * 
 * Also, its possible deffine the MACRO
 * 
 * #define BOOST_LOG_DYN_LINK 1
 * 
 * at the first line of main.cpp
 * 
 * I created macros to simplify the invocation of each method
 * 
 * 
 * For formats of Log Filea Name:
 * https://www.boost.org/doc/libs/1_77_0/libs/log/doc/html/log/detailed/sink_backends.html#log.detailed.sink_backends.text_file
 * 
 * 
 ******************************************************************************************/

#ifndef BOOSTLOH_H

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

#define LT_TRACE    BOOST_LOG_TRIVIAL(trace)
#define LT_DEBUG    BOOST_LOG_TRIVIAL(debug)
#define LT_INFO     BOOST_LOG_TRIVIAL(info)
#define LT_WARN     BOOST_LOG_TRIVIAL(warning)
#define LT_ERROR    BOOST_LOG_TRIVIAL(error)
#define LT_FATAL    BOOST_LOG_TRIVIAL(fatal)

#endif