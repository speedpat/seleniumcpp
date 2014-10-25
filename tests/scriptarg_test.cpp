/*
 * alerts_test.cpp
 *
 *  Created on: Sep 20, 2014
 *      Author: speedpat
 */

#include <list>

#include <gtest/gtest.h>

#include "selenium/selenium.hpp"


using namespace selenium;







TEST(ScriptArgTest, testConversionOperators) {
  EXPECT_EQ(41, (int)(ScriptArg(41)));
  EXPECT_EQ(41.0f, (float)(ScriptArg(41)));
  EXPECT_EQ(42l, (long)(ScriptArg(42)));
  EXPECT_EQ(true, (bool)(ScriptArg(8)));
  EXPECT_EQ(false, (bool)(ScriptArg(0)));

  EXPECT_EQ(-42, (int)(ScriptArg(-42)));

  EXPECT_EQ(3.14f, (float)(ScriptArg(3.14f)));
  EXPECT_EQ(-3.14f, (float)(ScriptArg(-3.14f)));
  EXPECT_EQ(3, (int)(ScriptArg(3.14f)));
  EXPECT_EQ(3l, (long)(ScriptArg(3.14f)));
  EXPECT_EQ(3.2f, (double)(ScriptArg(3.2f)));
  EXPECT_EQ(true, (bool)(ScriptArg(8.0f)));
  EXPECT_EQ(false, (bool)(ScriptArg(0.0f)));

  EXPECT_EQ(3.141592654, (double)(ScriptArg(3.141592654)));
  EXPECT_EQ(3, ((int)ScriptArg(3.141592654)));
  EXPECT_EQ(3.141592654f, (float)(ScriptArg(3.141592654)));
  EXPECT_EQ(3l, (long)(ScriptArg(3.141592654)));
  EXPECT_EQ(true, (bool)(ScriptArg(8.0)));
  EXPECT_EQ(false, (bool)(ScriptArg(0.0)));

  EXPECT_EQ(1099511627776, (long)(ScriptArg(1099511627776)));

  EXPECT_EQ(true, (bool)(ScriptArg(true)));
  EXPECT_EQ(false, (bool)(ScriptArg(false)));

  EXPECT_EQ(std::string("42"), (std::string)(ScriptArg("42")));
  std::string hello("hello");
  EXPECT_EQ(hello, (std::string)(ScriptArg(hello)));


}


