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
  PresenceOfElementLocatedPredicate(const Locator& locator)
      : m_locator(locator)
  {
  }

  ::boost::optional<WebElement> apply(WebDriver& driver)
  {
    WebElement element = driver.findElement(m_locator);
    return ::boost::optional<WebElement>(element);
  }

  const Locator& m_locator;
};

struct VisibilityOfElementLocatedPredicate : public PresenceOfElementLocatedPredicate
{
  VisibilityOfElementLocatedPredicate(const Locator& locator)
      : PresenceOfElementLocatedPredicate(locator)
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
  PresenceOfAllElementsLocatedPredicate(const Locator& locator)
      : m_locator(locator)
  {
  }

  ::boost::optional<WebElements> apply(WebDriver& driver)
  {
    WebElements elements = driver.findElements(m_locator);
    return ::boost::optional<WebElements>(elements);
  }

  const Locator& m_locator;
};


struct TextToBePresentInElementPredicate : public PresenceOfElementLocatedPredicate
{
  TextToBePresentInElementPredicate(const Locator& locator, const std::string& text)
      : PresenceOfElementLocatedPredicate(locator), m_text(text)
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
  TextToBePresentInElementValuePredicate(const Locator& locator, const std::string& text)
      : PresenceOfElementLocatedPredicate(locator), m_text(text)
  {
  }

  ::boost::optional<std::string> apply(WebDriver& driver)
  {
    try
    {
      ::boost::optional<WebElement> element = PresenceOfElementLocatedPredicate::apply(driver);
      if (element)
      {
        Response res = element->getAttribute("value");
        std::string text = res.asString();

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
  InvisibilityOfElementLocatedPredicate(const Locator& locator)
   : PresenceOfElementLocatedPredicate(locator)
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
  ElementToBeClickablePredicate(const Locator& locator)
      : VisibilityOfElementLocatedPredicate(locator)
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
  StalenessOfPredicate(const WebElement& element)
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
  ElementSelectionStatePredicate(const WebElement& element, bool selected)
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
  ElementLocatedIsSelectedPredicate(const Locator& locator)
      : PresenceOfElementLocatedPredicate(locator)
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
  ElementLocatedSelectionStateToBePredicate(const Locator& locator, bool selected)
      : PresenceOfElementLocatedPredicate(locator), m_selected(selected)
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
    try {
      Alert alert = driver.switchTo().alert();
      alert.text();
      return ::boost::optional<Alert>(alert);
    } catch (NoAlertPresentException& e)
    {
      return ::boost::optional<Alert>(::boost::none);
    }
  }

};

struct ElementTextToBeEqualPredicate : public WebElementPredicate
{
  ElementTextToBeEqualPredicate(const WebElement element, const std::string& text)
   : WebElementPredicate(element), m_text(text)
  {

  }

  ::boost::optional<std::string> apply(WebDriver& driver)
  {
    const std::string text = m_element.text();
    std::cerr << "  text: " << text << std::endl;
    std::cerr << "m_text: " << m_text << std::endl;
    if (text == m_text)
    {
      return ::boost::optional<std::string>(text);
    }
    return ::boost::optional<std::string>(::boost::none);
  }

  std::string m_text;
};

struct ElementTextToBeEqualLocatedPredicate : public PresenceOfElementLocatedPredicate
{
  ElementTextToBeEqualLocatedPredicate(const Locator& locator, const std::string& text)
   : PresenceOfElementLocatedPredicate(locator), m_text(text)
  {

  }

  ::boost::optional<std::string> apply(WebDriver& driver)
  {
    ::boost::optional<WebElement> element =
        PresenceOfElementLocatedPredicate::apply(driver);
    if (element)
    {
      const std::string text = element->text();
      std::cerr << "  text: " << text << std::endl;
      std::cerr << "m_text: " << m_text << std::endl;
      if (text == m_text)
      {
        return ::boost::optional<std::string>(text);
      }
    }
    return ::boost::optional<std::string>(::boost::none);
  }

  std::string m_text;
};

struct ElementValueToBeEqualPredicate : public WebElementPredicate
{
  ElementValueToBeEqualPredicate(const WebElement element, const std::string& text)
   : WebElementPredicate(element), m_text(text)
  {

  }

  ::boost::optional<std::string> apply(WebDriver& driver)
  {

    Response res = m_element.getAttribute("value");
    std::string text = res.asString();
    std::cerr << "  text: " << text << std::endl;
    std::cerr << "m_text: " << m_text << std::endl;
    if (text == m_text)
    {
      return ::boost::optional<std::string>(text);
    }
    return ::boost::optional<std::string>(::boost::none);
  }

  std::string m_text;
};

struct ElementTextToContainPredicate : public WebElementPredicate
{
  ElementTextToContainPredicate(const WebElement element, const std::string& text)
   : WebElementPredicate(element), m_text(text)
  {

  }

  ::boost::optional<std::string> apply(WebDriver& driver)
  {
    const std::string text = m_element.text();
    if (text.find(m_text) != std::string::npos)
    {
      return ::boost::optional<std::string>(text);
    }
    return ::boost::optional<std::string>(::boost::none);
  }

  std::string m_text;
};

} /* namespace conditions */

} /* namespace selenium */

#endif /* CONDITIONS_HPP_ */
