/*
 * Copyright (C) 2014 Patrick Heeb
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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
