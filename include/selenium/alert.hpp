/*
 * alert.hpp
 *
 *  Created on: Sep 17, 2014
 *      Author: speedpat
 */

#ifndef ALERT_HPP_
#define ALERT_HPP_

#include <string>

namespace selenium
{

class CommandExecutor;

class Alert
{
public:
  Alert(CommandExecutor& driver);
  Alert(const Alert& other);
  ~Alert() = default;

  std::string text();
  void dismiss();
  void accept();
  void sendKeys(const std::string& keys);

  Alert& operator=(const Alert& other);

private:
  CommandExecutor& m_driver;
};

} /* namespace selenium */

#endif /* ALERT_HPP_ */
