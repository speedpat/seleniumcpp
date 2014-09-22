/*
 * selenium_testcase.hpp
 *
 *  Created on: Sep 18, 2014
 *      Author: speedpat
 */

#ifndef SELENIUM_TESTCASE_HPP_
#define SELENIUM_TESTCASE_HPP_

#include <gtest/gtest.h>
#include "in_process_web_server.hpp"
#include "test_environment.hpp"
#include "pages.hpp"
#include "log.hpp"

namespace selenium
{

class SeleniumTestCase : public ::testing::Test
{
public:
  SeleniumTestCase();
  virtual ~SeleniumTestCase();

  static void SetUpTestCase();

  static void TearDownTestCase();

  virtual void SetUp();

  virtual void TearDown();


protected:
  static TestEnvironment& testEnvironment();
  static WebDriver& webDriver();
  static Pages& pages();
  static std::string whereIs(const std::string& relativePath);
  Wait& wait();

private:
  static WebDriver* s_driver;
  Wait* m_wait;
};

} /* namespace selenium */

#endif /* SELENIUM_TESTCASE_HPP_ */
