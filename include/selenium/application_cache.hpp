/*
 * application_cache.hpp
 *
 *  Created on: Sep 17, 2014
 *      Author: speedpat
 */

#ifndef APPLICATION_CACHE_HPP_
#define APPLICATION_CACHE_HPP_

#include <selenium/webdriver.hpp>

namespace selenium
{

class ApplicationCache
{
public:
  enum Status
  {
    UNCACHED = 0,
    IDLE = 1,
    CHECKING = 2,
    DOWNLOADING = 3,
    UPDATE_READY = 4,
    OBSOLETE = 5,
  };
  ApplicationCache(WebDriver::Private& driver);
  ~ApplicationCache() = default;

  void get();
  Status getStatus();
  void clear();

private:
  WebDriver::Private& m_driver;

};

} /* namespace selenium */

#endif /* APPLICATION_CACHE_HPP_ */
