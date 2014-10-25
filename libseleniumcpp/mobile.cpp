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


template <>
struct response_value_handler<Mobile::ConnectionType>
{
  Mobile::ConnectionType get_value(CommandExecutor& driver, const CommandParameters& params, Response& response)
  {
    std::string str = response["value"].asString();

    LOG("get value: " << str);
    std::string value = ::boost::to_upper_copy(str);
    int intVal = 0;
    try
    {
      intVal = std::stoi(value);
    }
    catch (const std::invalid_argument& e)
    {
      return Mobile::ALL_NETWORK;
    }
    catch (const std::out_of_range& e)
    {
      return Mobile::ALL_NETWORK;
    }
    switch (intVal)
    {
      case 1:
        {
        return Mobile::AIRPLANE_MODE;
      }
      case 2:
        {
        return Mobile::WIFI_NETWORK;
      }
      case 4:
        {
        return Mobile::DATA_NETWORK;
      }
      case 6:
        {
        return Mobile::ALL_NETWORK;
      }
      default:
        {
        return Mobile::ALL_NETWORK;
      }
    }

  }

};

Mobile::ConnectionType Mobile::getNetworkConnection()
{
  return m_driver.execute<Mobile::ConnectionType>(Command::GET_NETWORK_CONNECTION);
}

void Mobile::setNetworkConnection(Mobile::ConnectionType type)
{
  CommandParameters params;
  CommandParameters typeParam;
  params["name"] = "network_connection";
  typeParam["type"] = type;
  params["parameters"] = typeParam;

  m_driver.execute(Command::SET_NETWORK_CONNECTION, params);
}


} /* namespace selenium */

