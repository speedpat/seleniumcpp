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

#include "log.hpp"
#include "selenium/webelement.hpp"
#include "selenium/script_arg.hpp"

namespace selenium
{
ScriptArg::ScriptArg(Json::ValueType type)
    : Json::Value(type)
{

}

ScriptArg::ScriptArg(const char* val)
    : Json::Value(val)
{
  LOG("create char*");
}

ScriptArg::ScriptArg(const std::string& val)
    : Json::Value(val)
{
  LOG("create string");
}

ScriptArg::ScriptArg(int val)
    : Json::Value(val)
{
  LOG("create int");
}

ScriptArg::ScriptArg(long val)
    : Json::Value((Json::Int64)val)
{
  LOG("create long");
}

ScriptArg::ScriptArg(double val)
    :Json::Value(val)
{
  LOG("create double");
}

ScriptArg::ScriptArg(float val)
:Json::Value(val)
{
  LOG("create float");
}

ScriptArg::ScriptArg(bool val)
:Json::Value(val)
{
  LOG("create bool");
}

ScriptArg::ScriptArg(const WebElement& val)
  : Json::Value(Json::objectValue)
{
  LOG("create WebElement");
  (*this)["ELEMENT"] = val.id();
}

ScriptArg::ScriptArg(const ScriptArg& other)
    : Json::Value(other)
{
  LOG("copy element " << type());
}

ScriptArg::ScriptArg(const Json::Value& value)
 : Json::Value(value)
{

}


ScriptArg::operator int() const
{
  return asInt();
}

ScriptArg::operator long() const
{
  return asInt64();
}

ScriptArg::operator float() const
{
  return asFloat();
}

ScriptArg::operator double() const
{
  return asDouble();
}

ScriptArg::operator bool() const
{
  return asBool();
}

ScriptArg::operator std::string() const
{
  return asString();
}
} /* namespace selenium */
