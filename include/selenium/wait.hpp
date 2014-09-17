/*
 * wait.hpp
 *
 *  Created on: Sep 15, 2014
 *      Author: speedpat
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
