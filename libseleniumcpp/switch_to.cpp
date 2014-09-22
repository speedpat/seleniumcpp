/*
 * switch_to.cpp
 *
 *  Created on: Sep 17, 2014
 *      Author: speedpat
 */

#include "selenium/switch_to.hpp"
#include "selenium/alert.hpp"

#include "webdriver_private.hpp"

namespace selenium
{

SwitchTo::SwitchTo(WebDriver::Private& driver)
 : m_driver(driver)
{

}

Alert SwitchTo::alert()
{
  return Alert(m_driver);
}

void SwitchTo::defaultContent()
{
  CommandParameters params;
  params.add("id", "");

  m_driver.execute(Command::SWITCH_TO_FRAME, params);
}

SwitchTo& SwitchTo::frame(const std::string& frameReference)
{
  CommandParameters params;
  params.add("id", frameReference);

  m_driver.execute(Command::SWITCH_TO_FRAME, params);
  return *this;
}

SwitchTo& SwitchTo::frame(const WebElement& frameReference)
{
  CommandParameters params;
  params.add("id", frameReference);

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
  params.add("name", windowName);

  m_driver.execute(Command::SWITCH_TO_WINDOW, params);
  return *this;
}

WebElement SwitchTo::activeElement()
{
  return m_driver.execute<WebElement>(Command::GET_ACTIVE_ELEMENT);
}

} /* namespace selenium */
