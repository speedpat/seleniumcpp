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

SeleniumTestCase::SeleniumTestCase()
 : m_driver(nullptr), m_wait(nullptr)
{

}

SeleniumTestCase::~SeleniumTestCase()
{
}

void SeleniumTestCase::SetUpTestCase()
{

}

void SeleniumTestCase::TearDownTestCase()
{

}

void SeleniumTestCase::SetUp()
{
  m_driver = new WebDriver(testEnvironment().driverUrl(), DesiredCapabilities::CHROME);
  m_wait = new Wait(*m_driver, 5);
}

void SeleniumTestCase::TearDown()
{
  m_driver->quit();
  delete m_driver;
  m_driver = nullptr;
  delete m_wait;
  m_wait = nullptr;
}

TestEnvironment& SeleniumTestCase::testEnvironment()
{
  return *selenium::TestEnvironment::s_testEnvironment;
}

WebDriver& SeleniumTestCase::webDriver()
{
  return *m_driver;
}

Wait& SeleniumTestCase::wait()
{
  return *m_wait;
}

} /* namespace selenium */
