/*
 * dummy_test.cpp
 *
 *  Created on: Sep 19, 2014
 *      Author: speedpat
 */


#include "selenium/selenium.hpp"
#include "selenium_testcase.hpp"

using namespace selenium;

TEST_F(SeleniumTestCase, dummy)
{
  webDriver().get(testEnvironment().pages().errorsPage);
}
