/*
 * mobile.cpp
 *
 *  Created on: Sep 17, 2014
 *      Author: speedpat
 */

#include <boost/algorithm/string.hpp>

#include "log.hpp"
#include "selenium/command_executor.hpp"
#include "selenium/mobile.hpp"

namespace selenium
{

Mobile::Mobile(CommandExecutor& driver)
 : m_driver(driver)
{

}


Mobile::ConnectionType Mobile::getNetworkConnection()
{
  return m_driver.execute<Mobile::ConnectionType>(Command::GET_NETWORK_CONNECTION);
}

void Mobile::setNetworkConnection(Mobile::ConnectionType type)
{
  CommandParameters params;
  CommandParameters typeParam;
  params.put("name", "network_connection");
  typeParam.put("type", type);
  params.add_child("parameters", typeParam);

  m_driver.execute(Command::SET_NETWORK_CONNECTION, params);
}

struct ConnectionTypeTranslator
{
    typedef std::string            internal_type;
    typedef Mobile::ConnectionType      external_type;

    // Converts a string to ConnectionType
    ::boost::optional<external_type> get_value(const internal_type& str)
    {
      LOG("get value: " << str);
        std::string value = ::boost::to_upper_copy(str);
        int intVal = 0;
        try {
          intVal = std::stoi(value);
        }
        catch (std::invalid_argument& e)
        {
          return ::boost::optional<external_type>(::boost::none);
        }
        catch (std::out_of_range& e)
        {
          return ::boost::optional<external_type>(::boost::none);
        }
        switch (intVal)
        {
          case 1:
          {
            return ::boost::optional<external_type>(Mobile::AIRPLANE_MODE);
          }
          case 2:
          {
            return ::boost::optional<external_type>(Mobile::WIFI_NETWORK);
          }
          case 4:
          {
            return ::boost::optional<external_type>(Mobile::DATA_NETWORK);
          }
          case 6:
          {
            return ::boost::optional<external_type>(Mobile::ALL_NETWORK);
          }
          default:
          {
            return ::boost::optional<external_type>(::boost::none);
          }
        }
    }

    // Converts a ScreenOrientation to string
    ::boost::optional<internal_type> put_value(const external_type& e)
    {
      std::stringstream str;
      str << e;
      return ::boost::optional<internal_type>(str.str());
    }
};


} /* namespace selenium */



namespace boost {
namespace property_tree {

template<typename Ch, typename Traits, typename Alloc>
struct translator_between<std::basic_string< Ch, Traits, Alloc >,  selenium::Mobile::ConnectionType>
{
    typedef selenium::ConnectionTypeTranslator type;
};



} // namespace property_tree
} // namespace boost
