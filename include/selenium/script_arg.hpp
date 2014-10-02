/*
 * script_result.hpp
 *
 *  Created on: Sep 24, 2014
 *      Author: speedpat
 */

#ifndef SCRIPT_ARG_HPP_
#define SCRIPT_ARG_HPP_

#include <string>

namespace selenium
{
class WebElement;

class ScriptArg
{
public:
  enum ArgType
  {
    _INT,
    _DOUBLE,
    _STRING,
    _WEBELEMENT,
  };
  ScriptArg(const char* val);
  ScriptArg(std::string val);
  ScriptArg(int val);
  ScriptArg(long val);
  ScriptArg(double val);
  ScriptArg(float val);
  ScriptArg(bool val);
  ScriptArg(const WebElement& val);
  ScriptArg(const ScriptArg& other);

  ArgType type() const;
  operator int() const;
  operator long() const;
  operator float() const;
  operator double() const;
  operator bool() const;
  operator std::string() const;

private:
  ArgType m_type;
  std::string m_stringvalue;
  long m_int_value;
  double m_double_value;
};

} /* namespace selenium */

#endif /* SCRIPT_ARG_HPP_ */
