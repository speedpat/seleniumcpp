/*
 * storage.cpp
 *
 *  Created on: Sep 17, 2014
 *      Author: speedpat
 */

#include "storage.hpp"

namespace selenium
{

Storage::Storage(WebDriver::Private& driver)
 : m_driver(driver)
{
}

std::string Storage::getItem()
{
  return m_driver.execute<std::string>(Command::GET_LOCAL_STORAGE_ITEM);
}

void Storage::setItem(const std::string& key, const std::string& value)
{
  CommandParameters params;
  params.put("key", key);
  params.put("value", value);

  m_driver.execute(Command::SET_LOCAL_STORAGE_ITEM, params);
}

void Storage::removeItem(const std::string& key)
{
  CommandParameters params;
  params.put("key", key);

  m_driver.execute(Command::DELETE_LOCAL_STORAGE_ITEM);
}

std::vector<std::string> Storage::getKeys()
{
  return m_driver.execute<std::vector<std::string> >(Command::GET_LOCAL_STORAGE_KEYS);
}

void Storage::clear()
{
  m_driver.execute(Command::CLEAR_LOCAL_STORAGE);
}

int Storage::size()
{
  return m_driver.execute<int>(Command::GET_LOCAL_STORAGE_SIZE);
}

} /* namespace selenium */
