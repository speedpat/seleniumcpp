/*
 * alert.cpp
 *
 *  Created on: Sep 17, 2014
 *      Author: speedpat
 */

#include "selenium/alert.hpp"
#include "webdriver_private.hpp"

namespace selenium
{

Alert::Alert(WebDriver::Private& driver)
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
  params.add("text", keys);
  m_driver.execute(Command::SET_ALERT_VALUE, params);

}


} /* namespace selenium */
