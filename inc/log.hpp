/**
 * @file log.hpp
 * @author Henri Buyse <a href="mailto:henri.buyse@gmail.com">henri.buyse@gmail.com</a>
 *
 * @brief Header containing a function to initiate the logs
 */

#ifndef LOG_HPP_
#define LOG_HPP_

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>


namespace logging   = boost::log;
namespace sinks     = boost::log::sinks;
namespace src       = boost::log::sources;
namespace expr      = boost::log::expressions;
namespace attrs     = boost::log::attributes;
namespace keywords  = boost::log::keywords;



/**
 * @brief Initialization of the logs
 * @details function that initializes the logs. It initializes:
 *          - the name of the log files (log_%N.log),
 *          - the log rotation based on size or date (rotate files every 10 MiB or at midnight),
 *          - the format of the logging message.
 */
void init_log(void)
{
    boost::log::add_file_log(
        boost::log::keywords::file_name = "log_%N.log",
        boost::log::keywords::rotation_size = 10 * 1024 * 1024,
        boost::log::keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
        boost::log::keywords::format = "[%TimeStamp%] > %Message%"
        );

    boost::log::core::get()->set_filter
    (
        boost::log::trivial::severity >= boost::log::trivial::info
    );
}



/**
 * @brief Function to test the log
 * @details [long description]
 */
void test_log(void)
{
    init_log();
    logging::add_common_attributes();

    using namespace logging::trivial;
    src::severity_logger<severity_level>     lg;

    BOOST_LOG_SEV(lg, trace) << "A trace severity message";
    BOOST_LOG_SEV(lg, debug) << "A debug severity message";
    BOOST_LOG_SEV(lg, info) << "An informational severity message";
    BOOST_LOG_SEV(lg, warning) << "A warning severity message";
    BOOST_LOG_SEV(lg, error) << "An error severity message";
    BOOST_LOG_SEV(lg, fatal) << "A fatal severity message";
}
#endif