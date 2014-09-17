/*
 * switch_to.hpp
 *
 *  Created on: Sep 17, 2014
 *      Author: speedpat
 */

#ifndef SWITCH_TO_HPP_
#define SWITCH_TO_HPP_

#include <selenium/webdriver.hpp>

namespace selenium
{
class Alert;

class SwitchTo
{
public:
  SwitchTo(WebDriver::Private& driver);
  virtual ~SwitchTo() = default;

  Alert alert();
  void defaultContent();
  void frame(const std::string& reference);
  void frame(const WebElement& element);
  void parentFrame();
  void window(const std::string& windowName);
  WebElement activeElement();


private:
  WebDriver::Private& m_driver;
};

} /* namespace selenium */

#endif /* SWITCH_TO_HPP_ */
