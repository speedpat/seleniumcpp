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

#include "selenium/alert.hpp"
#include "selenium/command_executor.hpp"

namespace selenium
{

Alert::Alert(CommandExecutor& driver)
 : m_driver(driver)
{
}

Alert::Alert(const Alert& other)
 : m_driver(other.m_driver)
{

}

Alert& Alert::operator=(const Alert& other)
{
  m_driver = other.m_driver;
  return *this;
}

std::string Alert::text()
{
  return m_driver.execute<std::string>(Command::GET_ALERT_TEXT);
}

void Alert::dismiss()
{
  m_driver.execute(Command::DISMISS_ALERT);
}

void Alert::accept()
{
  m_driver.execute(Command::ACCEPT_ALERT);
}

void Alert::sendKeys(const std::string& keys)
{
  CommandParameters params;
  params["text"] = keys;
  m_driver.execute(Command::SET_ALERT_VALUE, params);

}


} /* namespace selenium */
