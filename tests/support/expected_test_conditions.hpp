/*
 * expected_test_conditions.hpp
 *
 *  Created on: Sep 22, 2014
 *      Author: speedpat
 */

#ifndef EXPECTED_TEST_CONDITIONS_HPP_
#define EXPECTED_TEST_CONDITIONS_HPP_

#include <selenium/conditions/expected_condition.hpp>

namespace selenium
{
namespace tests
{

struct PageSourceToContainPredicate
{
  PageSourceToContainPredicate(const std::string& expectedText)
   : m_expected(expectedText)
  {
  }

  ::boost::optional<std::string> apply(WebDriver& driver)
  {
    std::string source = driver.pageSource();
    if (source.find(m_expected) != std::string::npos)
    {
      return ::boost::optional<std::string>(source);
    }
    return ::boost::optional<std::string>(::boost::none);

  }

  std::string m_expected;
};

struct NewWindowIsOpenedPredicate
{
  NewWindowIsOpenedPredicate(const WindowHandles& originalHandles)
   : m_originalHandles(originalHandles)
  {
  }

  ::boost::optional<WindowHandle> apply(WebDriver& driver)
  {
    WindowHandles currentHandles = driver.windowHandles();
    if (currentHandles.size() > m_originalHandles.size())
    {
      for (WindowHandle handle: m_originalHandles)
      {
        std::remove(currentHandles.begin(), currentHandles.end(), handle);
      }
      return ::boost::optional<WindowHandle>(currentHandles[0]);
    }
    return ::boost::optional<WindowHandle>(::boost::none);

  }

  WindowHandles m_originalHandles;


};

struct FrameToBeAvailableAndSwitchToItPredicate
{
  FrameToBeAvailableAndSwitchToItPredicate(const std::string& frameLocator)
   : m_frameLocator(frameLocator)
  {
  }
  ::boost::optional<std::string> apply(WebDriver& driver)
    {
      try {
        driver.switchTo().frame(m_frameLocator);
        return ::boost::optional<std::string>(m_frameLocator);
      } catch (NoSuchFrameException& e) {
        std::cout << "FOOOOOOOOOOOOOOOOOOOOOOOOOOOOO"<< std::endl;
        return ::boost::optional<std::string>(::boost::none);
      }
    }
private:
  std::string m_frameLocator;
};

struct WindowHandleCountToBeGreaterThanPredicate
{
  WindowHandleCountToBeGreaterThanPredicate(const int count)
   : m_count(count)
  {

  }

  ::boost::optional<int> apply(WebDriver& driver)
  {
    WindowHandles windowHandles = driver.windowHandles();
    if (windowHandles.size() > m_count)
    {
      return ::boost::optional<int>(windowHandles.size());
    }
    return ::boost::optional<int>(::boost::none);
  }

private:
  int m_count;
};


typedef conditions::ExpectedCondition<std::string, PageSourceToContainPredicate, std::string> PageSourceToContain;
typedef conditions::ExpectedCondition<WindowHandle, NewWindowIsOpenedPredicate, WindowHandles> NewWindowIsOpened;
typedef conditions::ExpectedCondition<std::string, FrameToBeAvailableAndSwitchToItPredicate, std::string> FrameToBeAvailableAndSwitchToIt;
typedef conditions::ExpectedCondition<int, WindowHandleCountToBeGreaterThanPredicate, int> WindowHandleCountToBeGreaterThan;


} /* namespace tests */

typedef tests::PageSourceToContain PageSourceToContain;
typedef tests::NewWindowIsOpened NewWindowIsOpened;
typedef tests::FrameToBeAvailableAndSwitchToIt FrameToBeAvailableAndSwitchToIt;
typedef tests::WindowHandleCountToBeGreaterThan WindowHandleCountToBeGreaterThan;

template <typename Condition, typename T = typename Condition::return_type>
class Not
{
public:
  typedef bool return_type;
  typedef Condition condition_type;
  typedef T condition_return_type;
  Not(Condition condition)
  : m_condition(condition)
  {

  }

  virtual ~Not() = default;

  virtual bool apply(WebDriver& driver, ::boost::optional<return_type>& retval)
  {
    ::boost::optional<condition_return_type> ret;

    bool res = m_condition.apply(driver, ret);
    if (res)
    {
      return false;
    }

    retval = true;
    return true;
  }
private:
  Condition m_condition;
};

} /* namespace selenkum */

#endif /* EXPECTED_TEST_CONDITIONS_HPP_ */
