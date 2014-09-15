/*
 * wait.cpp
 *
 *  Created on: Sep 15, 2014
 *      Author: speedpat
 */

#include <chrono>
#include <selenium/wait.hpp>

namespace selenium
{

Wait::Wait(WebDriver& driver, unsigned int timeout, unsigned int sleeper)
 : m_timeout(timeout), m_sleeper(sleeper), m_driver(driver)
{

}

Wait::~Wait()
{
}


bool Wait::until_(std::function<bool(WebDriver& driver)> function) throw (TimeoutException)
{
  std::chrono::steady_clock::time_point timeout = std::chrono::steady_clock::now() + std::chrono::seconds(m_timeout);
  while (timeout > std::chrono::steady_clock::now())
  {
    if (function(m_driver))
    {
      return true;
    }
    {
      std::unique_lock<std::mutex> lock(m_mutex);
      m_cond.wait_for(lock, std::chrono::milliseconds(m_sleeper));
    }
  }
  throw TimeoutException("");
}

} /* namespace selenium */
