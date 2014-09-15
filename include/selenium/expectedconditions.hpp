/*
 * expectedconditions.hpp
 *
 *  Created on: Sep 15, 2014
 *      Author: speedpat
 */

#ifndef EXPECTEDCONDITIONS_HPP_
#define EXPECTEDCONDITIONS_HPP_

#include <boost/optional.hpp>

#include <selenium/exceptions.hpp>
#include <selenium/webelement.hpp>
#include <selenium/webdriver.hpp>

namespace selenium
{


struct VisibilityOfElementPred
{
  VisibilityOfElementPred(const WebElement& element)
   : m_element(element)
  {

  }

  ::boost::optional<WebElement> apply(WebDriver& driver)
  {
    return ::boost::optional<WebElement>(::boost::none);
  }
  WebElement m_element;

};

template <typename T, class Predicate, typename param1 = ::boost::none_t >
class ExpectedCondition
{
public:
  typedef T return_type;
  typedef Predicate predicate_type;
  ExpectedCondition()
  : m_predicate()
  {

  }
  ExpectedCondition(const T& t)
  : m_predicate(t)
  {

  }

  ExpectedCondition(Predicate p)
   : m_predicate(p)
  {

  }

  ExpectedCondition(const param1& p)
   : m_predicate(p)
  {

  }

  virtual ~ExpectedCondition() = default;

  virtual ::boost::optional<T> apply(WebDriver& driver)
  {
    ::boost::optional<T> res = m_predicate.apply(driver);
    return res;
  }
private:
  Predicate m_predicate;
};

class ExpectedConditions
{
public:
  typedef ExpectedCondition<WebElement, VisibilityOfElementPred> VisibilityOfElement;

private:
  ExpectedConditions() = delete;
  ~ExpectedConditions() = default;
};

} /* namespace selenium */

#endif /* EXPECTEDCONDITIONS_HPP_ */
