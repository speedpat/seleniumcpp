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
