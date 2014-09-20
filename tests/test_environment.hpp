/*
 * test_environment.hpp
 *
 *  Created on: Sep 18, 2014
 *      Author: speedpat
 */

#ifndef TEST_ENVIRONMENT_HPP_
#define TEST_ENVIRONMENT_HPP_

#include <gtest/gtest.h>
#include "boost/process.hpp"

namespace selenium
{
class InProcessWebServer;
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

  static TestEnvironment* s_testEnvironment;

private:
  InProcessWebServer* m_webserver;
  boost::process::process m_driver;
  Pages* m_pages;
  std::string m_driverUrl;
};


} /* namespace selenium */

#endif /* TEST_ENVIRONMENT_HPP_ */
