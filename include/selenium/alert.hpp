/*
 * alert.hpp
 *
 *  Created on: Sep 17, 2014
 *      Author: speedpat
 */

#ifndef ALERT_HPP_
#define ALERT_HPP_

#include "selenium/webdriver.hpp"

namespace selenium
{

class Alert
{
public:
  Alert(WebDriver::Private& driver);
  ~Alert() = default;

  std::string text();
  void dismiss();
  void accept();
  void sendKeys(const std::string& keys);

private:
  WebDriver::Private& m_driver;
};

} /* namespace selenium */

#endif /* ALERT_HPP_ */
