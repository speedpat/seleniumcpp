/*
 * conditions.hpp
 *
 *  Created on: Sep 15, 2014
 *      Author: speedpat
 */

#ifndef EXPECTED_CONDITION_HPP_
#define EXPECTED_CONDITION_HPP_

#include <boost/optional.hpp>

#include <selenium/webdriver.hpp>

namespace selenium
{

namespace conditions
{


template <typename T, class Predicate,
  typename param1 = ::boost::none_t,
  typename param2 = ::boost::none_t,
  typename param3 = ::boost::none_t >
class ExpectedCondition
{
public:
  typedef T return_type;
  typedef Predicate predicate_type;
  ExpectedCondition()
  : m_predicate()
  {

  }

  ExpectedCondition(const param1& p)
   : m_predicate(p)
  {

  }

  ExpectedCondition(const param1& p1, const param2& p2)
   : m_predicate(p1, p2)
  {

  }

  ExpectedCondition(const param1& p1, const param2& p2, const param3& p3)
   : m_predicate(p1, p2, p3)
  {

  }

  virtual ~ExpectedCondition() = default;

  virtual bool apply(WebDriver& driver, ::boost::optional<return_type>& retval)
  {
    ::boost::optional<return_type> res = m_predicate.apply(driver);
    if (res)
    {
      retval = res;
      return true;
    }
    return false;
  }
private:
  Predicate m_predicate;
};

} /* namespace conditions */

} /* namespace selenium */

#endif /* EXPECTED_CONDITION_HPP_ */
