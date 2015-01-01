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

#ifndef TEST_ENVIRONMENT_HPP_
#define TEST_ENVIRONMENT_HPP_

#include <gtest/gtest.h>
#include "boost/process.hpp"

namespace selenium
{
class Pages;


class TestEnvironment : public testing::Environment
{
public:
  TestEnvironment();
  virtual ~TestEnvironment();

  virtual void SetUp() override;

  virtual void TearDown() override;

  Pages& pages();
  std::string& driverUrl();

  std::string whereIs(const std::string& page);

  static TestEnvironment* s_testEnvironment;

private:
  boost::process::process m_driver;
  Pages* m_pages;
  std::string m_driverUrl;
};


} /* namespace selenium */

#endif /* TEST_ENVIRONMENT_HPP_ */
