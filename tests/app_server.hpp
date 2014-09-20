/*
 * app_server.hpp
 *
 *  Created on: Sep 20, 2014
 *      Author: speedpat
 */

#ifndef APP_SERVER_HPP_
#define APP_SERVER_HPP_

#include <string>
namespace selenium
{

class AppServer
{
public:
  AppServer() = default;
  virtual ~AppServer() = default;

  virtual const std::string whereIs(const std::string& relativeUrl) const = 0;
};

} /* namespace selenium */

#endif /* APP_SERVER_HPP_ */
