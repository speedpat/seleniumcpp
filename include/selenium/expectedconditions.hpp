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


struct VisibilityOfElementPredicate
{
  VisibilityOfElementPredicate(const WebElement& element)
   : m_element(element)
  {

  }

  ::boost::optional<WebElement> apply(WebDriver& driver)
  {
    try
    {
      if (m_element.isDisplayed())
      {
        return ::boost::optional<WebElement>(m_element);
      }
    }
    catch (StaleElementReferenceException& e)
    {
      // ignore
    }
    return ::boost::optional<WebElement>(::boost::none);
  }
  WebElement m_element;

};

struct TitleIsPredicate
{
  TitleIsPredicate(const std::string& title)
   : m_title(title) {}

  TitleIsPredicate(const char* title)
   : m_title(title) {}

  ::boost::optional<bool> apply(WebDriver& driver)
  {
    std::string title = driver.title();
    if (title == m_title)
    {
      return  ::boost::optional<bool>(true);
    }
    else
    {
      return ::boost::optional<bool>(::boost::none);
    }
  }
  std::string m_title;
};

struct TitleContainsPredicate
{
  TitleContainsPredicate(const std::string& title)
      : m_title(title)
  {
  }

  TitleContainsPredicate(const char* title)
      : m_title(title)
  {
  }

  ::boost::optional<bool> apply(WebDriver& driver)
  {
    std::string title = driver.title();
    if (title.find(m_title) != std::string::npos)
    {
      return ::boost::optional<bool>(true);
    }
    else
    {
      return ::boost::optional<bool>(::boost::none);
    }
  }
  std::string m_title;
};

struct PresenceOfElementLocatedPredicate
{
  PresenceOfElementLocatedPredicate(const By& locator, const std::string& value)
      : m_locator(locator), m_value(value)
  {
  }

  PresenceOfElementLocatedPredicate(const By& locator, const char* value)
      : m_locator(locator), m_value(value)
  {
  }

  ::boost::optional<WebElement> apply(WebDriver& driver)
  {
    WebElement element = driver.findElement(m_locator, m_value);
    return ::boost::optional<WebElement>(element);
  }

  const By& m_locator;
  std::string m_value;
};

struct VisibilityOfElementLocatedPredicate
{
  VisibilityOfElementLocatedPredicate(const By& locator,
      const std::string& value)
      : m_locator(locator), m_value(value)
  {
  }

  VisibilityOfElementLocatedPredicate(const By& locator, const char* value)
      : m_locator(locator), m_value(value)
  {
  }

  ::boost::optional<WebElement> apply(WebDriver& driver)
  {
    WebElement element = driver.findElement(m_locator, m_value);
    try
    {
      if (element.isDisplayed())
      {
        return ::boost::optional<WebElement>(element);
      }
      else
      {
        return ::boost::optional<WebElement>(::boost::none);
      }
    }
    catch (StaleElementReferenceException& e)
    {
      return ::boost::optional<WebElement>(::boost::none);
    }
  }

  const By& m_locator;
  std::string m_value;

};

struct PresenceOfAllElementsLocatedPredicate
{
  PresenceOfAllElementsLocatedPredicate(const By& locator, const std::string& value)
      : m_locator(locator), m_value(value)
  {
  }

  PresenceOfAllElementsLocatedPredicate(const By& locator, const char* value)
      : m_locator(locator), m_value(value)
  {
  }

  ::boost::optional<WebElements> apply(WebDriver& driver)
  {
    WebElements elements = driver.findElements(m_locator, m_value);
    return ::boost::optional<WebElements>(elements);
  }

  const By& m_locator;
  std::string m_value;
};

struct FindElementPredicate
{
  FindElementPredicate(const By& locator, const std::string& value)
   : m_locator(locator), m_value(value)
  {

  }

  FindElementPredicate(const By& locator, const char* value)
      : m_locator(locator), m_value(value)
  {
  }

  WebElement findElement(WebDriver& driver)
  {
    return driver.findElement(m_locator, m_value);
  }

  const By& m_locator;
  std::string m_value;
};

struct TextToBePresentInElementPredicate : public FindElementPredicate
{
  TextToBePresentInElementPredicate(const By& locator, const std::string& value, const std::string& text)
      : FindElementPredicate(locator, value), m_text(text)
  {
  }

  TextToBePresentInElementPredicate(const By& locator, const char* value, const char* text)
      : FindElementPredicate(locator, value), m_text(text)
  {
  }

  ::boost::optional<std::string> apply(WebDriver& driver)
  {
    try
    {
      WebElement element = findElement(driver);
      std::string text = element.text();
      if (text.find(m_text) != std::string::npos)
      {
        return ::boost::optional<std::string>(text);
      }
      return ::boost::optional<std::string>(::boost::none);
    }
    catch (StaleElementReferenceException& e)
    {
      // ignore
    }
    return ::boost::optional<std::string>(::boost::none);
  }

  std::string m_text;
};

struct InvisibilityOfElementLocatedPredicate : public PresenceOfElementLocatedPredicate
{
  InvisibilityOfElementLocatedPredicate(const By& locator, const std::string& value)
   : PresenceOfElementLocatedPredicate(locator, value)
  {

  }

  InvisibilityOfElementLocatedPredicate(const By& locator, const char* value)
   : PresenceOfElementLocatedPredicate(locator, value)
  {

  }

  ::boost::optional<bool> apply(WebDriver& driver)
  {
    WebElement element = PresenceOfElementLocatedPredicate::apply(driver);
    try
    {
      if (!element.isDisplayed())
      {
        return ::boost::optional<bool>(true);
      }
      else
      {
        return ::boost::optional<bool>(false);
      }
    }
    catch (NoSuchElementException& e)
    {
      return ::boost::optional<bool>(true);
    }
    catch (StaleElementReferenceException& e)
    {
      return ::boost::optional<bool>(true);
    }
  }

};

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

class ExpectedConditions
{
public:
  typedef ExpectedCondition<WebElement, VisibilityOfElementPredicate, WebElement> VisibilityOfElement;
  typedef ExpectedCondition<bool, TitleIsPredicate, std::string> TitleIs;
  typedef ExpectedCondition<bool, TitleContainsPredicate, std::string> TitleContains;
  typedef ExpectedCondition<WebElement, PresenceOfElementLocatedPredicate, const By&, std::string> PresenceOfElementLocated;
  typedef ExpectedCondition<WebElements, PresenceOfAllElementsLocatedPredicate, const By&, std::string> PresenceOfAllElementsLocated;
  typedef ExpectedCondition<std::string, TextToBePresentInElementPredicate, const By&, std::string, std::string> TextToBePresentInElement;
  typedef ExpectedCondition<bool, InvisibilityOfElementLocatedPredicate, const By&, std::string> InvisibilityOfElementLocated;
private:
  ExpectedConditions() = delete;
  ~ExpectedConditions() = default;
};

} /* namespace selenium */

#endif /* EXPECTEDCONDITIONS_HPP_ */
