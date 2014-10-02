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

ScriptArg::ScriptArg(const char* val)
    : m_type(_STRING), m_int_value(0), m_stringvalue(val), m_double_value(0)
{
  LOG("create char*");
}

ScriptArg::ScriptArg(std::string val)
    : m_type(_STRING), m_int_value(0), m_stringvalue(val), m_double_value(0)
{
  LOG("create string");
}

ScriptArg::ScriptArg(int val)
    : m_type(_INT), m_int_value(val), m_double_value(0)
{
  LOG("create int");
}

ScriptArg::ScriptArg(long val)
    : m_type(_INT), m_int_value(val), m_double_value(0)
{
  LOG("create long");
}

ScriptArg::ScriptArg(double val)
    : m_type(_DOUBLE), m_int_value(0), m_double_value(val)
{
  LOG("create double");
}

ScriptArg::ScriptArg(float val)
    : m_type(_DOUBLE), m_int_value(0), m_double_value(val)
{
  LOG("create float");
}

ScriptArg::ScriptArg(bool val)
    : m_type(_STRING), m_int_value(val), m_stringvalue(val ? "true" : "false"),
        m_double_value(0)
{
  LOG("create bool");
}

ScriptArg::ScriptArg(const WebElement& val)
    : m_type(_WEBELEMENT), m_int_value(0), m_stringvalue(val.id()),
        m_double_value(0)
{
  LOG("create WebElement");
}

ScriptArg::ScriptArg(const ScriptArg& other)
    : m_type(other.m_type), m_int_value(other.m_int_value),
        m_stringvalue(other.m_stringvalue), m_double_value(other.m_double_value)
{
  LOG("copy element " << m_type);
}

ScriptArg::ArgType  ScriptArg::type() const
{
  return m_type;
}

ScriptArg::operator int() const
{
  return m_int_value;
}

ScriptArg::operator long() const
{
  return m_int_value;
}

ScriptArg::operator float() const
{
  return m_double_value;
}

ScriptArg::operator double() const
{
  return m_double_value;
}

ScriptArg::operator bool() const
{
  return m_int_value;
}

ScriptArg::operator std::string() const
{
  return m_stringvalue;
}
} /* namespace selenium */
