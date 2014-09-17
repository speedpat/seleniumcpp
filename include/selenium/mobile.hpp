/*
 * mobile.hpp
 *
 *  Created on: Sep 17, 2014
 *      Author: speedpat
 */

#ifndef MOBILE_HPP_
#define MOBILE_HPP_

#include <selenium/webdriver.hpp>

namespace selenium
{

class Mobile
{
public:
  enum ConnectionType
  {
    ALL_NETWORK = 6,
    WIFI_NETWORK = 2,
    DATA_NETWORK = 4,
    AIRPLANE_MODE = 1,
  };

  Mobile(WebDriver::Private& driver);
  ~Mobile() = default;

  ConnectionType getNetworkConnection();
  void setNetworkConnection(ConnectionType type);

private:
  WebDriver::Private& m_driver;
};

} /* namespace selenium */

#endif /* MOBILE_HPP_ */
