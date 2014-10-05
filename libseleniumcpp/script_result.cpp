/*
 * script_result.cpp
 *
 *  Created on: Sep 24, 2014
 *      Author: speedpat
 */

#include "selenium/command_executor.hpp"
#include "selenium/webelement.hpp"
#include "selenium/script_result.hpp"
#include "log.hpp"

namespace selenium
{

ScriptResult ScriptResult::create(CommandExecutor& driver, const Response& value)
{
  LOG(value.size());
  if (value.find("ELEMENT") != value.not_found())
  {
    std::string elementId = value.get<std::string>("ELEMENT");
    return ScriptResult(driver, elementId);
  }
  if (value.size() > 0)
  {
    return ScriptResult(driver, value);
  }

  return ScriptResult(driver, value.data());
}


ScriptResult::ScriptResult(CommandExecutor& driver, const std::string& val)
: m_value(val), m_driver(driver)
{

}

ScriptResult::ScriptResult(CommandExecutor& driver, const Response& array)
 : m_array(array), m_driver(driver)
{

}

bool ScriptResult::isNull() const
{
  std::string val = m_value;
  std::transform(val.begin(), val.end(), val.begin(), ::tolower);
  return val == "null";
}

bool ScriptResult::isArray() const
{
  return m_array.size() > 0;
}

ScriptResult::iterator ScriptResult::begin()
{
  return iterator(*this, m_array.begin());
}

ScriptResult::iterator ScriptResult::end()
{
  return iterator(*this, m_array.end());
}

ScriptResult::const_iterator ScriptResult::begin() const
{
  return const_iterator(*this, m_array.begin());
}

ScriptResult::const_iterator ScriptResult::end() const
{
  return const_iterator(*this, m_array.end());
}

unsigned int ScriptResult::size() const
{
  return m_array.size();
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

ScriptResult::operator long long int() const throw (std::invalid_argument, std::out_of_range)
{
  return std::stoll(m_value);
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

bool ScriptResult::operator==(const int& value) const
{
  try
  {
    return operator int() == value;
  }
  catch (std::exception& e)
  {
    return false;
  }
}

bool ScriptResult::operator==(const long& value) const
{
  try
  {
    return operator long() == value;
  }
  catch (std::exception& e)
  {
    return false;
  }
}

bool ScriptResult::operator==(const long long int& value) const
{
  try
  {
    return operator long long int() == value;
  }
  catch (std::exception& e)
  {
    return false;
  }
}

bool ScriptResult::operator==(const float& value) const
{
  try
  {
    return operator float() == value;
  }
  catch (std::exception& e)
  {
    return false;
  }
}

bool ScriptResult::operator==(const double& value) const
{
  try
  {
    return operator double() == value;
  }
  catch (std::exception& e)
  {
    return false;
  }
}

bool ScriptResult::operator==(const bool& value) const
{
  try
  {
    return operator bool() == value;
  }
  catch (std::exception& e)
  {
    return false;
  }
}

bool ScriptResult::operator==(const WebElement& value) const
{
  try
  {
    return operator WebElement() == value;
  }
  catch (std::exception& e)
  {
    return false;
  }
}

bool ScriptResult::operator==(const std::string& value) const
{
  return m_value == value;
}

bool ScriptResult::operator==(const char* value) const
{
  return m_value == value;
}

bool operator==(const int& value, const ScriptResult& res)
{
  return res.operator==(value);
}
bool operator==(const long& value, const ScriptResult& res)
{
  return res.operator==(value);
}
bool operator==(const long long int& value, const ScriptResult& res)
{
  return res.operator==(value);
}

bool operator==(const float& value, const ScriptResult& res)
{
  return res.operator==(value);
}

bool operator==(const double& value, const ScriptResult& res)
{
  return res.operator==(value);
}

bool operator==(const bool& value, const ScriptResult& res)
{
  return res.operator==(value);
}

bool operator==(const WebElement& value, const ScriptResult& res)
{
  return res.operator==(value);
}

bool operator==(const std::string& value, const ScriptResult& res)
{
  return res.operator==(value);
}

bool operator==(const char* value, const ScriptResult& res)
{
  return res.operator== (value);
}

} /* namespace selenium */
