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
