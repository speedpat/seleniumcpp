/*
 * cookie.cpp
 *
 *  Created on: Sep 24, 2014
 *      Author: speedpat
 */

#include "log.hpp"
#include "selenium/cookie.hpp"

namespace selenium
{

const std::string Cookie::s_emptyValue = "";

Cookie::Cookie()
{
  LOG("empty");
}

Cookie::Cookie(const std::string& key, const std::string& value) : Cookie(key, value, "/")
{
  LOG(key << "," << value);
}

Cookie::Cookie(const std::string& key, const std::string& value,
    const std::string& path) : Cookie(key, value, path, std::chrono::system_clock::time_point())
{
  LOG(key << "," << value << "," << path);
}

Cookie::Cookie(const std::string& key, const std::string& value,
    const std::string& path,
    const std::chrono::system_clock::time_point& expiry) : Cookie(key, value, "", path, expiry)
{
  LOG(key << "," << value << "," << path << ",expiry");
}

Cookie::Cookie(const std::string& key, const std::string& value,
    const std::string& domain, const std::string& path,
    const std::chrono::system_clock::time_point& expiry) : Cookie(key, value, domain, path, expiry, false)
{
  LOG(key << "," << value << "," << domain << "," << path << ",expiry");
}

Cookie::Cookie(const std::string& key, const std::string& value,
    const std::string& domain, const std::string& path,
    const std::chrono::system_clock::time_point& expiry, bool isSecure) : Cookie(key, value, domain, path, expiry, isSecure, false)
{
  LOG(key << "," << value << "," << domain << "," << path << ",expiry, secure:" << (isSecure ? "true" : "false"));
}

Cookie::Cookie(const std::string& key, const std::string& value,
    const std::string& domain, const std::string& path,
    const std::chrono::system_clock::time_point& expiry, bool isSecure,
    bool httpOnly)
{
  LOG(key << "," << value << "," << domain << "," << path << ",expiry, secure:" << (isSecure ? "true" : "false") << ",httpOnly:" << (httpOnly ? "true" : "false"));
  (*this)["name"] = key;
  (*this)["value"] = value;
  (*this)["path"] = path.empty() ? "/" : path;

  if (!domain.empty())
  {
    (*this)["domain"] = domain;
  }

  if (expiry > std::chrono::system_clock::time_point())
  {

    std::chrono::nanoseconds elapsed = expiry
        - std::chrono::system_clock::time_point();
    unsigned long count = std::chrono::duration_cast<std::chrono::seconds>(
        elapsed).count();
    (*this)["expiry"] = std::to_string(count);
  }

  (*this)["secure"] = std::to_string(isSecure);
  (*this)["httpOnly"] = std::to_string(httpOnly);
}

Cookie::Cookie(const Cookie& cookie)
 : std::map<std::string, std::string>(cookie)
   {

   }

const std::string& Cookie::getName() const
{
  return findValue("name");
}

void Cookie::setName(const std::string& name)
{
  (*this)["name"] = name;
}

const std::string& Cookie::getValue() const
{
  return findValue("value");
}

void Cookie::setValue(const std::string& value)
{
  (*this)["value"] = value;
}

const std::string& Cookie::getPath() const
{
  return findValue("path");
}

void Cookie::setPath(const std::string& path)
{
  (*this)["path"] = path.empty() ? "/" : path;
}

const std::string& Cookie::getDomain() const
{
  return findValue("domain");
}

void Cookie::setDomain(const std::string& domain)
{
  if (!domain.empty())
  {
    (*this)["domain"] = domain;
  }
  else
  {
    this->erase("domain");
  }
}

const std::chrono::system_clock::time_point Cookie::getExpiry() const
{
  if (find("expiry") != end())
  {
    unsigned long expiry = std::stoul(findValue("expiry"));
    std::chrono::seconds secs = std::chrono::seconds(expiry);
    return std::chrono::system_clock::time_point() + secs;
  }
  return std::chrono::system_clock::time_point();
}

void Cookie::setExpiry(const std::chrono::system_clock::time_point& expiry)
{
  if (expiry > std::chrono::system_clock::time_point())
  {

    std::chrono::nanoseconds elapsed = expiry
        - std::chrono::system_clock::time_point();
    unsigned long count = std::chrono::duration_cast<std::chrono::seconds>(
        elapsed).count();
    (*this)["expiry"] = std::to_string(count);
  }
  else
  {
    erase("expiry");
  }
}

const std::string& Cookie::findValue(const std::string& key) const
{
  Cookie::const_iterator pos = find(key);
  if (pos != end())
  {
    return pos->second;
  }
  return s_emptyValue;
}

const bool Cookie::isSecure() const
{
  if (find("secure") != end())
  {
    int secure = std::stoi(findValue("secure"));
    return secure == 1;
  }
  return false;
}

void Cookie::secure(bool secure)
{
  (*this)["secure"] = std::to_string(secure);
}

const bool Cookie::httpOnly() const
{
  if (find("httpOnly") != end())
  {
    int secure = std::stoi(findValue("httpOnly"));
    return secure == 1;
  }
  return false;
}

void Cookie::httpOnly(bool httpOnly)
{
  (*this)["httpOnly"] = std::to_string(httpOnly);
}


} /* namespace selenium*/

