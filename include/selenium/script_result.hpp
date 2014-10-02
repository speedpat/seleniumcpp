/*
 * script_result.hpp
 *
 *  Created on: Sep 24, 2014
 *      Author: speedpat
 */

#ifndef SCRIPT_RESULT_HPP_
#define SCRIPT_RESULT_HPP_

namespace selenium
{
class CommandExecutor;

class ScriptResult
{
public:
  ScriptResult(CommandExecutor& driver, std::string val);
  ScriptResult(const ScriptResult& other);

  operator int() const throw (std::invalid_argument, std::out_of_range);
  operator long() const throw (std::invalid_argument, std::out_of_range);
  operator float() const;
  operator double() const;
  operator bool() const;
  operator WebElement() const;
  operator std::string() const;

private:
  std::string m_value;
  CommandExecutor& m_driver;
};

} /* namespace selenium */

#endif /* SCRIPT_RESULT_HPP_ */
