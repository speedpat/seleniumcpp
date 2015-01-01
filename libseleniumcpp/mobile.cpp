/*
 * Copyright (C) 2014 Patrick Heeb
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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

