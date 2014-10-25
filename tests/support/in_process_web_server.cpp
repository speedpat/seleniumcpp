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
#include <boost/tokenizer.hpp>

#include <selenium/cookie.hpp>

#include "log.hpp"
#include "in_process_web_server.hpp"

namespace selenium
{

struct InProcessWebServer::WebServer
{
  WebServer(unsigned int port, const std::string& basedir)
      : m_server(http_server::options(*this)
          .address("testhost.test.ch")
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

  void addCookie(http_server::response& res, Cookie cookie)
  {

    std::string name=cookie.getName();
    std::string value=cookie.getValue();
    int version=0; //cookie.getVersion();

    // Check arguments
    if (name.empty())
       return;

    // Format value and params
    std::stringstream buf;
    std::string name_value_params;
        buf << name;
        buf << '=';
        buf << value;
        if (!value.empty())

        if (version>0)
        {
            buf << ";Version=";
            buf << version;
        }
        std::string path=cookie.getPath();
        if (!path.empty())
        {
            buf << ";Path=";
            buf << path;
        }
        std::string domain=cookie.getDomain();
        if (!domain.empty())
        {
            buf << ";Domain=";
            std::transform(domain.begin(), domain.end(), domain.begin(), ::tolower);
            buf << domain ;// lowercase for IE
        }
/*        Cookie::TimePoint maxAge = cookie.getExpiry();
        std::chrono::nanoseconds secs = Cookie::TimePoint() + maxAge;
        if (maxAge.count() >=0)
        {
            if (version==0)
            {
                buf << ";Expires=";
                if (maxAge==0)
                    buf << "__01Jan1970";
                else
                    formatDate(buf,System.currentTimeMillis()+1000L*maxAge,true;
            }
            else
            {
                buf << ";Max-Age=");
                // buf << cookie.getMaxAge());
            }
        }
        else if (version>0)
        {
            buf << ";Discard";
        }*/
        if (cookie.isSecure())
        {
            buf << ";Secure";
        }
        if (cookie.httpOnly())
            buf << ";HttpOnly";

        name_value_params = buf.str();

        ::boost::network::add_header(res, "Set-Cookie", name_value_params);

  }

  void operator()(
      http_server::request const & req,
      http_server::response & res
  )
  {
    std::string cookie = "/common/cookie";
    if (std::equal(cookie.begin(), cookie.end(), req.destination.begin()))
    {
      ::boost::network::uri::uri destUri("http://localhost");
      destUri.append(req.destination);
      if (destUri.is_valid())
      {
        std::string query = destUri.query();
        typedef ::boost::char_separator<char> separator_type;
        typedef ::boost::tokenizer<separator_type> tokenizer_type;

        separator_type commandSeparator("&");
        tokenizer_type tokenizer(query.begin(), query.end(), commandSeparator);
        std::map<std::string, std::string> parameters;

        for (tokenizer_type::const_iterator token = tokenizer.begin(); token != tokenizer.end(); ++token)
        {
          std::vector<std::string> tokens;
          ::boost::split(tokens, *token, boost::is_any_of("="));
          if (tokens.size() == 2)
          {
            std::string name = tokens[0];
            std::string value = tokens[1];

            parameters[name] = value;
          }
        }

        ::boost::network::add_header(res, "Content-Type", "text/html");
        ::boost::network::add_header(res, "Cache-Control", "no-cache");
        ::boost::network::add_header(res, "Pragma", "no-cache");
        // res << ::boost::network::header("Expires:  0"; // EEE, dd MMM yyyy HH:mm:ss 'GMT'
        std::string action = parameters["action"];
        if (action == "add")
        {
          std::string name = parameters["name"];
          std::string value = parameters["value"];
          std::string domain = parameters["domain"];
          std::string path = parameters["path"];
          std::string expiry = parameters["expiry"];
          std::string secure = parameters["secure"];
          std::string httpOnly = parameters["httpOnly"];



          Cookie::TimePoint tp_expiry;
          if (!expiry.empty())
          {
            try
            {
              tp_expiry = Cookie::TimePoint() + std::chrono::seconds(std::stoul(expiry));
            }
            catch (std::invalid_argument& e)
            {

            }
            catch (std::out_of_range& e)
            {

            }
          }

          bool b_secure = false;
          try
          {
            b_secure = (std::stoi(secure) == 1);
          }
          catch (std::invalid_argument& e)
          {

          }
          catch (std::out_of_range& e)
          {

          }

          bool b_httpOnly = false;
          try
          {
            b_httpOnly = (std::stoi(httpOnly) == 1);
          }
          catch (std::invalid_argument& e)
          {

          }
          catch (std::out_of_range& e)
          {

          }

          Cookie cookie(name, value, domain, path, tp_expiry, b_secure, b_httpOnly);

          addCookie(res, cookie);
          res.content += response("cookie added", name);
        }
        else if (action == "delete")
        {
          std::string name = parameters["name"];
          http_server::request::headers_container_type& headers = req.headers;
          for (http_server::request::header_type header: headers)
          {
            if (header.name == "Set-Cookie")
            {
              separator_type separator(";=");
              tokenizer_type tok(header.value, separator);
              for (tokenizer_type::const_iterator it = tok.begin(); it != tok.end(); ++it)
              {
                 std::string token = *it;
                 if (token == "name")
                 {
                   ++it;
                   if (it != tok.end())
                   {
                     token = *it;
                     if (token == name)
                     {
                       Cookie toDelete(name, "");
                       toDelete.setExpiry(Cookie::TimePoint());
                       addCookie(res, toDelete);
                       res.content += response("cookie removed", name);
                       return;
                     }
                   }
                 }
              }
            }
          }

        }
        else if (action == "deleteAll")
        {
          std::string name = parameters["name"];
          http_server::request::headers_container_type& headers = req.headers;
          for (http_server::request::header_type header: headers)
          {
            if (header.name == "Set-Cookie")
            {
              separator_type separator(";=");
              tokenizer_type tok(header.value, separator);
              for (tokenizer_type::const_iterator it = tok.begin(); it != tok.end(); ++it)
              {
                 std::string token = *it;
                 if (token == "name")
                 {
                   ++it;
                   if (it != tok.end())
                   {
                     name = *it;
                       Cookie toDelete(name, "");
                       toDelete.setExpiry(Cookie::TimePoint());
                       addCookie(res, toDelete);
                   }
                 }
              }
            }
          }
         res.content += response("all cookies removed", name);
         return;
        }
        else
        {
          res.content += response("unknown action", "");
        }

      }
      return;
    }

    std::ifstream fin(m_basedir + req.destination);

    if (!fin.good())
    {
      res.status = http_server::response::not_found;
      return;
    }

    res.status = http_server::response::ok;
    std::stringstream str;
    str << fin.rdbuf();
    res.content = str.str();
    fin.close();
  }

  std::string response(const std::string& message, const std::string& message2)
  {
    std::stringstream str;
    str << "<html><head><title>Done</title></head><body>" << message << " : " << message2 << "</body></html>";
    return str.str();
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
 : m_hostName("testhost.test.ch"), m_webServer(new WebServer(port, basedir)), m_serverThread(std::bind(&InProcessWebServer::run, this))
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
  std::string slash = "/";
  return "http://"
    //  + m_hostName + ":" + std::to_string(m_webServer->m_port)
      + std::string("testhost.test.ch:8787/common")
      + (relativePath.size() > 0 && std::equal(slash.begin(), slash.end(), relativePath.begin()) ? "" : "/" ) + relativePath;
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
