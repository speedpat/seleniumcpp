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
  CommandParameters keysParam;
  CommandParameters keyParam;
  for (char key: keys)
  {
    keyParam.put("", key);
    keysParam.push_back(CommandParameters::value_type("", keyParam));

  }
  params.put_child("text", keysParam);
  m_driver.execute(Command::SET_ALERT_VALUE, params);

}


} /* namespace selenium */
