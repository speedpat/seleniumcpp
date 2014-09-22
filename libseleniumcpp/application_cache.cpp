/*
 * application_cache.cpp
 *
 *  Created on: Sep 17, 2014
 *      Author: speedpat
 */

#include "selenium/application_cache.hpp"

#include "log.hpp"

#include "webdriver_private.hpp"

namespace selenium
{

ApplicationCache::ApplicationCache(WebDriver::Private& driver)
 : m_driver(driver)
{

}

void ApplicationCache::get()
{
  //TODO PHE check api
}

ApplicationCache::Status ApplicationCache::getStatus()
{
  return m_driver.execute<ApplicationCache::Status>(Command::GET_APP_CACHE_STATUS);
}

void ApplicationCache::clear()
{
  m_driver.execute(Command::CLEAR_APP_CACHE);
}


struct ApplicationCacheStatusTranslator
{
  typedef std::string internal_type;
  typedef ApplicationCache::Status external_type;

  // Converts a string to Status
  ::boost::optional<external_type> get_value(const internal_type& str)
  {
    LOG("get value: " << str);
    std::string value = ::boost::to_upper_copy(str);
    int intVal = 0;
    try
    {
      intVal = std::stoi(value);
    }
    catch (std::invalid_argument& e)
    {
      return ::boost::optional<external_type>(::boost::none);
    }
    catch (std::out_of_range& e)
    {
      return ::boost::optional<external_type>(::boost::none);
    }
    switch (intVal)
    {
      case 0:
        {
        return ::boost::optional<external_type>(ApplicationCache::UNCACHED);
      }
      case 1:
        {
        return ::boost::optional<external_type>(ApplicationCache::IDLE);
      }
      case 2:
        {
        return ::boost::optional<external_type>(ApplicationCache::CHECKING);
      }
      case 3:
        {
        return ::boost::optional<external_type>(ApplicationCache::DOWNLOADING);
      }
      case 4:
        {
        return ::boost::optional<external_type>(ApplicationCache::UPDATE_READY);
      }
      case 5:
        {
        return ::boost::optional<external_type>(ApplicationCache::OBSOLETE);
      }

      default:
        {
        return ::boost::optional<external_type>(::boost::none);
      }
    }
  }

  // Converts a Status to string
  ::boost::optional<internal_type> put_value(const external_type& e)
  {
    std::stringstream str;
    str << e;
    return ::boost::optional<internal_type>(str.str());
  }
};

} /* namespace selenium */


namespace boost {
namespace property_tree {

template<typename Ch, typename Traits, typename Alloc>
struct translator_between<std::basic_string< Ch, Traits, Alloc >,  selenium::ApplicationCache::Status>
{
    typedef selenium::ApplicationCacheStatusTranslator type;
};



} // namespace property_tree
} // namespace boost
