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

#include <algorithm>

#include "selenium/command_executor.hpp"
#include "selenium/webelement.hpp"
#include "selenium/script_result.hpp"
#include "log.hpp"

namespace selenium
{

ScriptResult ScriptResult::create(CommandExecutor& driver, const Response& value)
{
  LOG(value.size());
  if (value.isObject() && !value["ELEMENT"].isNull())
  {
    std::string elementId = value["ELEMENT"].asString();
    return ScriptResult(driver, elementId);
  }
  if (value.isArray())
  {
    return ScriptResult(driver, value);
  }

  return ScriptResult(driver, value);
}

ScriptResult::ScriptResult(CommandExecutor& driver, const Response& response)
 : Json::Value(response), m_driver(driver)
{

}

ScriptResult& ScriptResult::operator =(const ScriptResult& other)
{
  Json::Value::operator =(other);
  this->m_driver = other.m_driver;
  return *this;
}

ScriptResult::iterator ScriptResult::begin()
{
  return iterator(*this, Json::Value::begin());
}

ScriptResult::iterator ScriptResult::end()
{
  return iterator(*this, Json::Value::end());
}

ScriptResult::const_iterator ScriptResult::begin() const
{
  return const_iterator(*this, Json::Value::begin());
}

ScriptResult::const_iterator ScriptResult::end() const
{
  return const_iterator(*this, Json::Value::end());
}


ScriptResult::operator int() const throw (std::runtime_error)
{
  return asInt();
}
ScriptResult::operator float() const throw (std::runtime_error)
{
  return asFloat();
}
ScriptResult::operator double() const throw (std::runtime_error)
{
  return asDouble();
}

ScriptResult::operator long() const  throw (std::runtime_error)
{
  return asInt64();
}

ScriptResult::operator long long int() const throw (std::runtime_error)
{
  return asLargestInt();
}

ScriptResult::operator bool() const throw (std::runtime_error)
{
  bool value = asBool();
  LOG(toStyledString() << " asBool is " << value);
  return asBool();
}

ScriptResult::operator WebElement() const throw (std::runtime_error)
{
  return WebElement(m_driver, asString());
}

ScriptResult::operator WebElements() const
{
  WebElements elements;
  for (Response::iterator it = Response::begin(); it != Response::end(); ++it)
  {
    Response element = *it;
    if (element.isObject() && !element["ELEMENT"].isNull())
    {
      std::string elementId = element["ELEMENT"].asString();
      elements.push_back(WebElement(m_driver, elementId));
    }
  }
  return elements;
}

ScriptResult::operator std::string() const throw (std::runtime_error)
{
  return asString();
}

ScriptResult::operator const char*() const throw (std::runtime_error)
{
  return asCString();
}

bool ScriptResult::operator==(const int& value) const
{
  try
  {
    return operator int() == value;
  }
   catch (const std::exception& e)
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
   catch (const std::exception& e)
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
   catch (const std::exception& e)
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
   catch (const std::exception& e)
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
   catch (const std::exception& e)
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
   catch (const std::exception& e)
  {
     LOG(e.what())
    return false;
  }
}

bool ScriptResult::operator==(const WebElement& value) const
{
  try
  {
    return operator WebElement() == value;
  }
   catch (const std::exception& e)
  {
    return false;
  }
}

bool ScriptResult::operator==(const std::string& value) const
{
  return asString() == value;
}

bool ScriptResult::operator==(const char* value) const
{
  return asString() == value;
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
