/*
 * selenium_testcase.cpp
 *
 *  Created on: Sep 18, 2014
 *      Author: speedpat
 */

#include "selenium/selenium.hpp"
#include "selenium_testcase.hpp"
#include "test_environment.hpp"

namespace selenium
{

WebDriver* SeleniumTestCase::s_driver = nullptr;

SeleniumTestCase::SeleniumTestCase()
 : m_wait(nullptr)
{

}

SeleniumTestCase::~SeleniumTestCase()
{
}

void SeleniumTestCase::SetUpTestCase()
{
  s_driver = new WebDriver(testEnvironment().driverUrl(), DesiredCapabilities::CHROME);
}

void SeleniumTestCase::TearDownTestCase()
{
  s_driver->quit();
  delete s_driver;
  s_driver = nullptr;
}

void SeleniumTestCase::SetUp()
{
  m_wait = new Wait(*s_driver, 5);
}

void SeleniumTestCase::TearDown()
{
  delete m_wait;
  m_wait = nullptr;
}

TestEnvironment& SeleniumTestCase::testEnvironment()
{
  return *selenium::TestEnvironment::s_testEnvironment;
}

Pages& SeleniumTestCase::pages()
{
  return testEnvironment().pages();
}

std::string SeleniumTestCase::whereIs(const std::string& relativePath)
{
  return testEnvironment().whereIs(relativePath);
}

WebDriver& SeleniumTestCase::webDriver()
{
  return *SeleniumTestCase::s_driver;
}

Wait& SeleniumTestCase::wait()
{
  return *m_wait;
}

} /* namespace selenium */
