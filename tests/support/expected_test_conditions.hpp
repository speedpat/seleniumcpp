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
  NewWindowIsOpenedPredicate(const std::vector<std::string>& originalHandles)
   : m_originalHandles(originalHandles)
  {
  }

  ::boost::optional<std::string> apply(WebDriver& driver)
  {
    std::vector<std::string> currentHandles = driver.windowHandles();
    if (currentHandles.size() > m_originalHandles.size())
    {
      for (std::string handle: m_originalHandles)
      {
        std::remove(currentHandles.begin(), currentHandles.end(), handle);
      }
      return ::boost::optional<std::string>(currentHandles[0]);
    }
    return ::boost::optional<std::string>(::boost::none);

  }

  std::vector<std::string> m_originalHandles;


};


typedef conditions::ExpectedCondition<std::string, PageSourceToContainPredicate, std::string> PageSourceToContain;
typedef conditions::ExpectedCondition<std::string, NewWindowIsOpenedPredicate, std::vector<std::string> > NewWindowIsOpened;


} /* namespace tests */

typedef tests::PageSourceToContain PageSourceToContain;
typedef tests::NewWindowIsOpened NewWindowIsOpened;

} /* namespace selenkum */

#endif /* EXPECTED_TEST_CONDITIONS_HPP_ */
