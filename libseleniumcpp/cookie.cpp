/*
 * cookie.cpp
 *
 *  Created on: Sep 24, 2014
 *      Author: speedpat
 */

#include <boost/algorithm/string/predicate.hpp>

#include "log.hpp"
#include "selenium/cookie.hpp"

namespace selenium
{

const std::string Cookie::s_emptyString = "";
const Json::Value Cookie::s_emptyValue = Json::Value();

Cookie::Cookie()
{
  LOG("empty");
}

Cookie::Cookie(const std::string& key, const std::string& value) : Cookie(key, value, "/")
{
  LOG(key << "," << value);
}

Cookie::Cookie(const std::string& key, const std::string& value,
    const std::string& path) : Cookie(key, value, path, TimePoint())
{
  LOG(key << "," << value << "," << path);
}

Cookie::Cookie(const std::string& key, const std::string& value,
    const std::string& path,
    const TimePoint& expiry) : Cookie(key, value, "", path, expiry)
{
  LOG(key << "," << value << "," << path << ",expiry");
}

Cookie::Cookie(const std::string& key, const std::string& value,
    const std::string& domain, const std::string& path,
    const TimePoint& expiry) : Cookie(key, value, domain, path, expiry, false)
{
  LOG(key << "," << value << "," << domain << "," << path << ",expiry");
}

Cookie::Cookie(const std::string& key, const std::string& value,
    const std::string& domain, const std::string& path,
    const TimePoint& expiry, bool isSecure) : Cookie(key, value, domain, path, expiry, isSecure, false)
{
  LOG(key << "," << value << "," << domain << "," << path << ",expiry, secure:" << (isSecure ? "true" : "false"));
}

Cookie::Cookie(const std::string& key, const std::string& value,
    const std::string& domain, const std::string& path,
    const TimePoint& expiry, bool isSecure,
    bool httpOnly)
{
  LOG(key << "," << value << "," << domain << "," << path << ",expiry, secure:" << (isSecure ? "true" : "false") << ",httpOnly:" << (httpOnly ? "true" : "false"));
  (*this)["name"] = key;
  (*this)["value"] = value;
  if (::boost::starts_with(path, "/"))
  {
    (*this)["path"] = path;
  }
  else
  {
    (*this)["path"] = std::string("/") + path;
  }

  if (!domain.empty())
  {
    (*this)["domain"] = domain;
  }

  if (expiry > TimePoint())
  {

    std::chrono::seconds elapsed = expiry
        - TimePoint();
    unsigned long count = elapsed.count();
    (*this)["expiry"] = (Json::Value::UInt64)count;
  }

  (*this)["secure"] = isSecure;
  (*this)["httpOnly"] = httpOnly;
}

Cookie::Cookie(const Cookie& cookie)
 : std::map<std::string, Json::Value>(cookie)
   {

   }

const std::string Cookie::getName() const
{
  const Json::Value& name = findValue("name");
  if (!name.isNull())
  {
    return name.asString();
  }
  return s_emptyString;
}

void Cookie::setName(const std::string& name)
{
  (*this)["name"] = name;
}

const std::string Cookie::getValue() const
{
  const Json::Value& value = findValue("value");
  if (!value.isNull())
  {
    return value.asString();
  }
  return s_emptyString;
}

void Cookie::setValue(const std::string& value)
{
  (*this)["value"] = value;
}

const std::string Cookie::getPath() const
{
  const Json::Value& path = findValue("path");
  if (!path.isNull())
  {
    return path.asString();
  }
  return s_emptyString;
}

void Cookie::setPath(const std::string& path)
{
  (*this)["path"] = path.empty() ? "/" : path;
}

const std::string Cookie::getDomain() const
{
  const Json::Value& domain = findValue("domain");
  if (!domain.isNull())
  {
    return domain.asString();
  }
  return s_emptyString;
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

const Cookie::TimePoint Cookie::getExpiry() const
{
  if (find("expiry") != end())
  {
    const Json::Value& expiryValue = findValue("expiry");
    unsigned long expiry = expiryValue.asUInt64();
    std::chrono::seconds secs = std::chrono::seconds(expiry);
    return TimePoint(secs);
  }
  return TimePoint();
}

void Cookie::setExpiry(const Cookie::TimePoint& expiry)
{
  if (expiry > TimePoint())
  {
    std::chrono::seconds elapsed = expiry.time_since_epoch();
    unsigned long count = elapsed.count();
    (*this)["expiry"] = (Json::Value::UInt64)count;
  }
  else
  {
    erase("expiry");
  }
}

const Json::Value& Cookie::findValue(const std::string& key) const
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
    const Json::Value& secure = findValue("secure");
    return secure.isBool() && secure.asBool();
  }
  return false;
}

void Cookie::secure(bool secure)
{
  if (secure)
  {
    (*this)["secure"] = secure;
  }
  else
  {
    erase("secure");
  }

}

const bool Cookie::httpOnly() const
{
  if (find("httpOnly") != end())
  {
    const Json::Value& httpOnly = findValue("httpOnly");
    return httpOnly.isBool() && httpOnly.asBool();
  }
  return false;
}

void Cookie::httpOnly(bool httpOnly)
{
  if (httpOnly)
  {
    (*this)["httpOnly"] = httpOnly;
  }
  else
  {
    erase("httpOnly");
  }

}


} /* namespace selenium*/

