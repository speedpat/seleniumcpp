/*
 * cookie.hpp
 *
 *  Created on: Sep 23, 2014
 *      Author: speedpat
 */

#ifndef COOKIE_HPP_
#define COOKIE_HPP_

#include <string>
#include <map>
#include <chrono>

namespace selenium
{

class Cookie : public std::map<std::string, std::string>
{
public:
  Cookie();
  Cookie(const std::string& key, const std::string& value);
  Cookie(const std::string& key, const std::string& value,
      const std::string& path);
  Cookie(const std::string& key, const std::string& value,
      const std::string& path, const std::chrono::system_clock::time_point& expiry);
  Cookie(const std::string& key, const std::string& value,
      const std::string& domain, const std::string& path,
      const std::chrono::system_clock::time_point& expiry);
  Cookie(const std::string& key, const std::string& value,
      const std::string& domain, const std::string& path,
      const std::chrono::system_clock::time_point& expiry, bool isSecure);
  Cookie(const std::string& key, const std::string& value,
      const std::string& domain, const std::string& path,
      const std::chrono::system_clock::time_point& expiry, bool isSecure, bool httpOnly);

  Cookie(const Cookie& cookie);

  const std::string& getName() const;
  void setName(const std::string& name);

  const std::string& getValue() const;
  void setValue(const std::string& value);

  const std::string& getPath() const;
  void setPath(const std::string& path);

  const std::string& getDomain() const;
  void setDomain(const std::string& domain);

  const std::chrono::system_clock::time_point getExpiry() const;
  void setExpiry(const std::chrono::system_clock::time_point& expiry);

  const bool isSecure() const;
  void secure(bool secure);

  const bool httpOnly() const;
  void httpOnly(bool httpOnly);

private:
  const std::string& findValue(const std::string& key) const;
  static const std::string s_emptyValue;
};

} /* namespace selenium*/

#endif /* COOKIE_HPP_ */
