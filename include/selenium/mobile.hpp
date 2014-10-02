/*
 * mobile.hpp
 *
 *  Created on: Sep 17, 2014
 *      Author: speedpat
 */

#ifndef MOBILE_HPP_
#define MOBILE_HPP_


namespace selenium
{

class CommandExecutor;

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

  Mobile(CommandExecutor& driver);
  ~Mobile() = default;

  ConnectionType getNetworkConnection();
  void setNetworkConnection(ConnectionType type);

private:
  CommandExecutor& m_driver;
};

} /* namespace selenium */

#endif /* MOBILE_HPP_ */
