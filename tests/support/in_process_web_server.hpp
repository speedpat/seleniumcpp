/*
 * in_process_web_server.hpp
 *
 *  Created on: Sep 18, 2014
 *      Author: speedpat
 */

#ifndef IN_PROCESS_WEB_SERVER_HPP_
#define IN_PROCESS_WEB_SERVER_HPP_

#include <thread>

#include "app_server.hpp"

namespace selenium
{



class InProcessWebServer : public virtual AppServer
{
public:
  InProcessWebServer(unsigned int port, const std::string& basedir);
  virtual ~InProcessWebServer();

  void stop();
  bool isRunning();

  virtual const std::string whereIs(const std::string& relativePath) const;

private:
  struct WebServer;
  void run();
  std::string m_hostName;
  WebServer* m_webServer;
  std::thread m_serverThread;
};

} /* namespace selenium */

#endif /* IN_PROCESS_WEB_SERVER_HPP_ */
