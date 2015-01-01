/*
 * Copyright (C) 2014 Patrick Heeb
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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
