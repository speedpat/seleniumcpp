/*
 * switch_to.hpp
 *
 *  Created on: Sep 17, 2014
 *      Author: speedpat
 */

#ifndef SWITCH_TO_HPP_
#define SWITCH_TO_HPP_

#include <string>

namespace selenium
{
class Alert;
class CommandExecutor;
class WebElement;

class SwitchTo
{
public:
  SwitchTo(CommandExecutor& driver);
  virtual ~SwitchTo() = default;

  Alert alert();
  void defaultContent();
  SwitchTo& frame(const std::string& reference);
  SwitchTo& frame(const WebElement& element);
  SwitchTo& parentFrame();
  SwitchTo& window(const std::string& windowName);
  WebElement activeElement();


private:
  CommandExecutor& m_driver;
};

} /* namespace selenium */

#endif /* SWITCH_TO_HPP_ */
