/*
 * script_result.hpp
 *
 *  Created on: Sep 24, 2014
 *      Author: speedpat
 */

#ifndef SCRIPT_ARG_HPP_
#define SCRIPT_ARG_HPP_

#include <string>
#include <json/json.h>

namespace selenium
{
class WebElement;

class ScriptArg : public Json::Value
{
public:
  ScriptArg(Json::ValueType type = Json::nullValue);
  ScriptArg(const char* val);
  ScriptArg(const std::string& val);
  ScriptArg(int val);
  ScriptArg(long val);
  ScriptArg(double val);
  ScriptArg(float val);
  ScriptArg(bool val);
  ScriptArg(const WebElement& val);
  ScriptArg(const ScriptArg& other);
  ScriptArg(const Json::Value& value);
  template <typename T>
  ScriptArg(const std::vector<T>& arg)
  : Json::Value(Json::arrayValue)
  {
    for (auto elem: arg)
    {
      append(elem);
    }
  }

  operator int() const;
  operator long() const;
  operator float() const;
  operator double() const;
  operator bool() const;
  operator std::string() const;

};

} /* namespace selenium */

#endif /* SCRIPT_ARG_HPP_ */
