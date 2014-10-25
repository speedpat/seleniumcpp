/*
 * script_arg.cpp
 *
 *  Created on: Sep 24, 2014
 *      Author: speedpat
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
