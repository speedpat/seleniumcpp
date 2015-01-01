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


