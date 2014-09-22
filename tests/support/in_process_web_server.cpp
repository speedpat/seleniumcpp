/*
 * in_process_web_server.cpp
 *
 *  Created on: Sep 18, 2014
 *      Author: speedpat
 */

#include <string>
#include <iostream>
#include <fstream>

#include <boost/network/protocol/http/server.hpp>

#include "in_process_web_server.hpp"

namespace selenium
{

struct InProcessWebServer::WebServer
{
  WebServer(unsigned int port, const std::string& basedir)
      : m_server(http_server::options(*this)
          .address("localhost")
          .port(std::to_string(port))
          .reuse_address(true)),
        m_running(false),
        m_port(port),
        m_basedir(basedir)
        {

        }

  ~WebServer()
  {
    m_server.stop();
  }

  typedef ::boost::network::http::server<WebServer> http_server;

  void operator()(
      http_server::request const & req,
      http_server::response & res
  )
  {
    req.destination;
    std::ifstream fin(m_basedir + req.destination);

    res.status = http_server::response::ok;
    std::stringstream str;
    str << fin.rdbuf();
    res.content = str.str();
    fin.close();
  }

  void run()
  {
    try
    {
      m_running = true;
      m_server.run();
    }
    catch (std::runtime_error& e)
    {
      std::cout << e.what() << std::endl;
    }
    m_running = false;
  }

  void stop()
  {
    m_server.stop();
  }

  bool isRunning()
  {
    return m_running;
  }

  void log(const std::string& log)
  {
    std::cout << log << std::endl;
  }

  http_server m_server;
  bool m_running;
  unsigned int m_port;
  std::string m_basedir;

};


InProcessWebServer::InProcessWebServer(unsigned int port, const std::string& basedir)
 : m_hostName("localhost"), m_webServer(new WebServer(port, basedir)), m_serverThread(std::bind(&InProcessWebServer::run, this))
{

}

InProcessWebServer::~InProcessWebServer()
{
  m_webServer->stop();
  if (m_serverThread.joinable())
  {
    m_serverThread.join();
  }
  delete m_webServer;

}


const std::string InProcessWebServer::whereIs(const std::string& relativePath) const
{
  return "http://" + m_hostName + ":" + std::to_string(m_webServer->m_port) +  "/" + relativePath;
}

void InProcessWebServer::stop()
{
  m_webServer->stop();
}

void InProcessWebServer::run()
{
  m_webServer->run();
}

bool InProcessWebServer::isRunning()
{
  return m_webServer->isRunning();
}
} /* namespace selenium */
