/*
 * application_cache.cpp
 *
 *  Created on: Sep 17, 2014
 *      Author: speedpat
 */

#include <boost/algorithm/string.hpp>

#include "log.hpp"
#include "selenium/command_executor.hpp"
#include "selenium/application_cache.hpp"



namespace selenium
{

ApplicationCache::ApplicationCache(CommandExecutor& driver)
 : m_driver(driver)
{

}

void ApplicationCache::get()
{
  //TODO PHE check api
}

template <>
struct response_value_handler<ApplicationCache::Status>
{
  ApplicationCache::Status get_value(CommandExecutor& driver, const CommandParameters& params, Response& response)
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
       return ApplicationCache::UNCACHED;
     }
     catch (const std::out_of_range& e)
     {
       return ApplicationCache::UNCACHED;
     }
     switch (intVal)
     {
       case 0:
         {
         return ApplicationCache::UNCACHED;
       }
       case 1:
         {
         return ApplicationCache::IDLE;
       }
       case 2:
         {
         return ApplicationCache::CHECKING;
       }
       case 3:
         {
         return ApplicationCache::DOWNLOADING;
       }
       case 4:
         {
         return ApplicationCache::UPDATE_READY;
       }
       case 5:
         {
         return ApplicationCache::OBSOLETE;
       }

       default:
         {
         return ApplicationCache::UNCACHED;
       }
     }

  }
};

ApplicationCache::Status ApplicationCache::getStatus()
{
  return m_driver.execute<ApplicationCache::Status>(Command::GET_APP_CACHE_STATUS);
}

void ApplicationCache::clear()
{
  m_driver.execute(Command::CLEAR_APP_CACHE);
}


} /* namespace selenium */


