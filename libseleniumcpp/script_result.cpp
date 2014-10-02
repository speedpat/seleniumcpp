/*
 * script_result.cpp
 *
 *  Created on: Sep 24, 2014
 *      Author: speedpat
 */

#include "selenium/command_executor.hpp"
#include "selenium/webelement.hpp"
#include "selenium/script_result.hpp"

namespace selenium
{


ScriptResult::ScriptResult(CommandExecutor& driver, std::string val)
: m_value(val), m_driver(driver)
{

}

ScriptResult::operator int() const throw (std::invalid_argument, std::out_of_range)
{
  return std::stoi(m_value);
}
ScriptResult::operator float() const
{
  return std::stof(m_value);
}
ScriptResult::operator double() const
{
  return std::stod(m_value);
}

ScriptResult::operator long() const throw (std::invalid_argument, std::out_of_range)
{
  return std::stol(m_value);
}

ScriptResult::operator bool() const
{
  std::string lower = m_value;
  std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
  if (lower == "true")
  {
    return true;
  }
  else if (lower == "false")
  {
    return false;
  }

  int res = this->operator int();

  return res != 0;
}

ScriptResult::operator WebElement() const
{
  return WebElement(m_driver, m_value);
}

ScriptResult::operator std::string() const
{
  return m_value;
}

} /* namespace selenium */
