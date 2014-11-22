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

#ifndef WAIT_HPP_
#define WAIT_HPP_

#include <memory>
#include <mutex>
#include <condition_variable>

#include <boost/optional.hpp>

#include <selenium/webdriver.hpp>
#include <selenium/exceptions.hpp>

namespace selenium
{

class Wait
{
public:
  Wait(WebDriver& driver, unsigned int timeout = 10000 , unsigned int sleeper = 100);
  ~Wait() = default;

  template <class Condition, typename T = typename Condition::return_type>
  typename Condition::return_type until(Condition cond) throw (TimeoutException)
  {
    std::chrono::steady_clock::time_point timeout = std::chrono::steady_clock::now() + std::chrono::seconds(m_timeout);
    while (timeout > std::chrono::steady_clock::now())
    {
      try
      {
        ::boost::optional<typename Condition::return_type> ret;
        bool res = cond.apply(m_driver, ret);
        if (res)
        {
          return ret.get();
        }
      }
      catch (NoSuchElementException& e)
      {
        //ignore
      }
      {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_cond.wait_for(lock, std::chrono::milliseconds(m_sleeper));
      }
    }
    throw TimeoutException("timeout");
  }

private:
  int m_timeout;
  int m_sleeper;
  std::mutex m_mutex;
  std::condition_variable m_cond;
  WebDriver& m_driver;
};

} /* namespace selenium */

#endif /* WAIT_HPP_ */
