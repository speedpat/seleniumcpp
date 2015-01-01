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

#include "selenium/switch_to.hpp"
#include "selenium/alert.hpp"
#include "selenium/command_executor.hpp"




namespace selenium
{

SwitchTo::SwitchTo(CommandExecutor& driver)
 : m_driver(driver)
{

}

Alert SwitchTo::alert()
{
  return Alert(m_driver);
}

SwitchTo& SwitchTo::defaultContent()
{
  CommandParameters params;
  params["id"] = Json::nullValue;

  m_driver.execute(Command::SWITCH_TO_FRAME, params);
  return *this;
}

SwitchTo& SwitchTo::frame(const std::string& frameReference)
{
  CommandParameters params;
  params["id"] = frameReference;

  m_driver.execute(Command::SWITCH_TO_FRAME, params);
  return *this;
}

SwitchTo& SwitchTo::frame(int index)
{
  CommandParameters params;
  params["id"] = index;

  m_driver.execute(Command::SWITCH_TO_FRAME, params);
  return *this;
}

SwitchTo& SwitchTo::frame(const WebElement& frameReference)
{
  CommandParameters params;
  CommandParameters elementParam(Json::objectValue);
  elementParam["ELEMENT"] = frameReference.id();
  params["id"] = elementParam;

  m_driver.execute(Command::SWITCH_TO_FRAME, params);
  return *this;
}

SwitchTo& SwitchTo::parentFrame()
{
  m_driver.execute(Command::SWITCH_TO_PARENT_FRAME);
  return *this;
}

SwitchTo& SwitchTo::window(const std::string& windowName)
{
  CommandParameters params;
  params["name"] = windowName;

  m_driver.execute(Command::SWITCH_TO_WINDOW, params);
  return *this;
}

WebElement SwitchTo::activeElement()
{
  return m_driver.execute<WebElement>(Command::GET_ACTIVE_ELEMENT);
}


} /* namespace selenium */


