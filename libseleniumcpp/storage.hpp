/*
 * storage.hpp
 *
 *  Created on: Sep 17, 2014
 *      Author: speedpat
 */

#ifndef STORAGE_HPP_
#define STORAGE_HPP_

#include <selenium/webdriver.hpp>

namespace selenium
{

class Storage
{
public:
  Storage(WebDriver::Private& driver);
  ~Storage() = default;

  std::string getItem();
  void setItem(const std::string& key, const std::string& value);
  void removeItem(const std::string& key);
  std::vector<std::string> getKeys();
  void clear();
  int size();

private:
  WebDriver::Private& m_driver;
};

} /* namespace selenium */

#endif /* STORAGE_HPP_ */
