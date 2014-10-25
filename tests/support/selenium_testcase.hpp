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

  void assertThat(::testing::AssertionResult result);
   ::testing::AssertionResult equals(Attribute attribute, const char* value);
   ::testing::AssertionResult equals(Attribute attribute, const std::string& value);
   ::testing::AssertionResult equals(const char* value, Attribute attribute);
   ::testing::AssertionResult equals(const char* val1, const char* val2);
   ::testing::AssertionResult equals(const char* val1, const std::string val2);
   ::testing::AssertionResult equals(const std::string val1, const std::string val2);
   ::testing::AssertionResult equals(const std::string val1, const char* val2);
   ::testing::AssertionResult equals(const Attribute& attribute, bool value);
   ::testing::AssertionResult equals(const Attribute& attribute, int value);

   ::testing::AssertionResult equals(Response& resp, selenium::ScriptResult result);
   ::testing::AssertionResult equals(Response& resp, Response& result);

   ::testing::AssertionResult equalsIgnoreCase(Attribute attribute, const char* value);
   ::testing::AssertionResult equalsIgnoreCase(const char* value, const std::string& value2);

   ::testing::AssertionResult null(Attribute attribute);

   ::testing::AssertionResult contains(const Attribute& attribute, const char* value);
   ::testing::AssertionResult contains(const Attribute& attribute, const std::string& value);

private:
  static WebDriver* s_driver;
  Wait* m_wait;
};

} /* namespace selenium */

#endif /* SELENIUM_TESTCASE_HPP_ */
