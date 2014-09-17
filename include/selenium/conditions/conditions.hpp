/*
 * conditions.hpp
 *
 *  Created on: Sep 15, 2014
 *      Author: speedpat
 */

#ifndef CONDITIONS_HPP_
#define CONDITIONS_HPP_

#include <boost/optional.hpp>

#include <selenium/exceptions.hpp>
#include <selenium/webelement.hpp>
#include <selenium/webdriver.hpp>
#include <selenium/alert.hpp>
#include <selenium/switch_to.hpp>

namespace selenium
{

namespace conditions
{

struct WebElementPredicate
{
  WebElementPredicate(const WebElement& element)
   : m_element(element)
  {

  }

  WebElement m_element;
};

struct VisibilityOfElementPredicate : public WebElementPredicate
{
  VisibilityOfElementPredicate(const WebElement& element)
   : WebElementPredicate(element)
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

struct VisibilityOfElementLocatedPredicate : public PresenceOfElementLocatedPredicate
{
  VisibilityOfElementLocatedPredicate(const By& locator,
      const std::string& value)
      : PresenceOfElementLocatedPredicate(locator, value)
  {
  }

  VisibilityOfElementLocatedPredicate(const By& locator, const char* value)
      : PresenceOfElementLocatedPredicate(locator, value)
  {
  }

  ::boost::optional<WebElement> apply(WebDriver& driver)
  {
    ::boost::optional<WebElement> element = PresenceOfElementLocatedPredicate::apply(driver);
    try
    {
      if (element && element->isDisplayed())
      {
        return ::boost::optional<WebElement>(element);
      }
    }
    catch (StaleElementReferenceException& e)
    {
      // ignore
    }
    return ::boost::optional<WebElement>(::boost::none);
  }
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


struct TextToBePresentInElementPredicate : public PresenceOfElementLocatedPredicate
{
  TextToBePresentInElementPredicate(const By& locator, const std::string& value, const std::string& text)
      : PresenceOfElementLocatedPredicate(locator, value), m_text(text)
  {
  }

  TextToBePresentInElementPredicate(const By& locator, const char* value, const char* text)
      : PresenceOfElementLocatedPredicate(locator, value), m_text(text)
  {
  }

  ::boost::optional<std::string> apply(WebDriver& driver)
  {
    try
    {
      ::boost::optional<WebElement> element = PresenceOfElementLocatedPredicate::apply(driver);
      if (element)
      {
        std::string text = element->text();
        if (text.find(m_text) != std::string::npos)
        {
          return ::boost::optional<std::string>(text);
        }
        return ::boost::optional<std::string>(::boost::none);
      }
    }
    catch (StaleElementReferenceException& e)
    {
      // ignore
    }
    return ::boost::optional<std::string>(::boost::none);
  }

  std::string m_text;
};

struct TextToBePresentInElementValuePredicate : public PresenceOfElementLocatedPredicate
{
  TextToBePresentInElementValuePredicate(const By& locator, const std::string& value, const std::string& text)
      : PresenceOfElementLocatedPredicate(locator, value), m_text(text)
  {
  }

  TextToBePresentInElementValuePredicate(const By& locator, const char* value, const char* text)
      : PresenceOfElementLocatedPredicate(locator, value), m_text(text)
  {
  }

  ::boost::optional<std::string> apply(WebDriver& driver)
  {
    try
    {
      ::boost::optional<WebElement> element = PresenceOfElementLocatedPredicate::apply(driver);
      if (element)
      {
        std::string text = element->getAttribute("value");
        if (text.find(m_text) != std::string::npos)
        {
          return ::boost::optional<std::string>(text);
        }
        return ::boost::optional<std::string>(::boost::none);
      }
    }
    catch (StaleElementReferenceException& e)
    {
      // ignore
    }
    return ::boost::optional<std::string>(::boost::none);
  }

  std::string m_text;
};

struct FrameToBeAvailableAndSwitchToIt
{

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
    ::boost::optional<WebElement> element = PresenceOfElementLocatedPredicate::apply(driver);
    try
    {
      if (element && !element->isDisplayed())
      {
        return ::boost::optional<bool>(true);
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
    return ::boost::optional<bool>(::boost::none);
  }

};

struct ElementToBeClickablePredicate : public VisibilityOfElementLocatedPredicate
{
  ElementToBeClickablePredicate(const By& locator,
      const std::string& value)
      : VisibilityOfElementLocatedPredicate(locator, value)
  {
  }

  ElementToBeClickablePredicate(const By& locator, const char* value)
      : VisibilityOfElementLocatedPredicate(locator, value)
  {
  }

  ::boost::optional<WebElement> apply(WebDriver& driver)
  {
    ::boost::optional<WebElement> element = VisibilityOfElementLocatedPredicate::apply(driver);
    try
    {
      if (element && element->isEnabled())
      {
        return ::boost::optional<WebElement>(element);
      }
    }
    catch (StaleElementReferenceException& e)
    {
      // ignore
    }
    return ::boost::optional<WebElement>(::boost::none);
  }
};

struct StalenessOfPredicate : public WebElementPredicate
{
  StalenessOfPredicate(WebElement& element)
   : WebElementPredicate(element)
  {

  }

  ::boost::optional<bool> apply(WebDriver& driver)
  {
    try
    {
      m_element.isEnabled();
    }
    catch (StaleElementReferenceException& e)
    {
      return ::boost::optional<bool>(true);
    }
    return ::boost::optional<bool>(::boost::none);
  }

};

struct ElementIsSelectedPredicate : public WebElementPredicate
{
  ElementIsSelectedPredicate(WebElement& element)
   : WebElementPredicate(element)
  {

  }

  ::boost::optional<bool> apply(WebDriver& driver)
  {
    return m_element.isSelected();
  }
};

struct ElementSelectionStatePredicate : public WebElementPredicate
{
  ElementSelectionStatePredicate(WebElement& element, bool selected)
   : WebElementPredicate(element), m_selected(selected)
  {

  }

  ::boost::optional<bool> apply(WebDriver& driver)
  {
    return m_element.isSelected() == m_selected;
  }

  bool m_selected;
};


struct ElementLocatedIsSelectedPredicate : public PresenceOfElementLocatedPredicate
{
  ElementLocatedIsSelectedPredicate(const By& locator,
      const std::string& value)
      : PresenceOfElementLocatedPredicate(locator, value)
  {
  }

  ElementLocatedIsSelectedPredicate(const By& locator,
      const char* value)
      : PresenceOfElementLocatedPredicate(locator, value)
  {
  }

  ::boost::optional<bool> apply(WebDriver& driver)
  {
    ::boost::optional<WebElement> element =
        PresenceOfElementLocatedPredicate::apply(driver);
    if (element && element->isSelected())
    {
      return ::boost::optional<bool>(true);
    }
    return ::boost::optional<bool>(::boost::none);
  }

};


struct ElementLocatedSelectionStateToBePredicate : public PresenceOfElementLocatedPredicate
{
  ElementLocatedSelectionStateToBePredicate(const By& locator,
      const std::string& value, bool selected)
      : PresenceOfElementLocatedPredicate(locator, value), m_selected(selected)
  {
  }

  ElementLocatedSelectionStateToBePredicate(const By& locator,
      const char* value, bool selected)
      : PresenceOfElementLocatedPredicate(locator, value), m_selected(selected)
  {
  }

  ::boost::optional<bool> apply(WebDriver& driver)
  {
    ::boost::optional<WebElement> element =
        PresenceOfElementLocatedPredicate::apply(driver);
    if (element && element->isSelected() == m_selected)
    {
      return ::boost::optional<bool>(true);
    }
    return ::boost::optional<bool>(::boost::none);
  }

  bool m_selected;
};

struct AlertIsPresentPredicate
{
  ::boost::optional<Alert> apply(WebDriver& driver)
  {
    Alert alert = driver.switchTo().alert();
    alert.text();
    return ::boost::optional<Alert>(alert);
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

} /* namespace conditions */

} /* namespace selenium */

#endif /* CONDITIONS_HPP_ */
