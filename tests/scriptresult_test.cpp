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

#include <list>

#include "selenium/selenium.hpp"
#include "support/selenium_testcase.hpp"
#include "support/expected_test_conditions.hpp"


using namespace selenium;

class ScriptResultTest : public SeleniumTestCase
{
public:

  virtual void SetUp()
  {
    SeleniumTestCase::SetUp();
    webDriver().get(pages().javascriptPage);

  }

  virtual void TearDown()
  {
    SeleniumTestCase::TearDown();
  }

};


TEST_F(ScriptResultTest, testConversionOperators) {

  ScriptResult res = webDriver().executeScript("return arguments[0];", {41});
  EXPECT_EQ(41, (int)(res));
  EXPECT_EQ(41.0f, (float)(res));
  EXPECT_EQ(41l, (long)(res));
  EXPECT_TRUE((bool)(res));


  res = webDriver().executeScript("return arguments[0];", {0});
  EXPECT_FALSE((bool)(res));

  WebElement element = webDriver().findElementByID("resultContainer");
  res = webDriver().executeScript("return arguments[0];", {element});
  EXPECT_EQ(element, (WebElement)(res));

  WebElements elements = webDriver().findElementsByTagName("p");
  res = webDriver().executeScript("return arguments[0];", elements);
  WebElements ret =  res;
  EXPECT_EQ(elements, ret);



  res = webDriver().executeScript("return arguments[0];", {-42});
  EXPECT_EQ(-42, (int)(res));

  res = webDriver().executeScript("return arguments[0];", {3.14f});
  EXPECT_EQ(3.14f, (float)(res));
  EXPECT_EQ(3, (int)(res));
  EXPECT_EQ(3l, (long)(res));

/*  res = webDriver().executeScript("return arguments[0];", {3.2f});
  EXPECT_EQ(3.2f, (double)(res));*/

  res = webDriver().executeScript("return arguments[0];", {8.0f});
  EXPECT_TRUE((bool)(res));
  res = webDriver().executeScript("return arguments[0];", {0.0f});
  EXPECT_FALSE((bool)(res));

  res = webDriver().executeScript("return arguments[0];", {-3.14f});
  EXPECT_EQ(-3.14f, (float)(res));


  res = webDriver().executeScript("return arguments[0];", {3.141592654});
  EXPECT_EQ(3.141592654, (double)(res));
  EXPECT_EQ(3, ((int)res));
  EXPECT_EQ(3.141592654f, (float)(res));
  EXPECT_EQ(3l, (long)(res));

  res = webDriver().executeScript("return arguments[0];", {8.0});
  EXPECT_TRUE((bool)(res));

  res = webDriver().executeScript("return arguments[0];", {0.0});
  EXPECT_FALSE((bool)(res));

  res = webDriver().executeScript("return arguments[0];", {1099511627776});
  EXPECT_EQ(1099511627776, (long)(res));
  EXPECT_EQ(1099511627776, (long long)(res));


  res = webDriver().executeScript("return arguments[0];", {true});
  EXPECT_TRUE((bool)(res));

  res = webDriver().executeScript("return arguments[0];", {false});
  EXPECT_FALSE((bool)(res));

  res = webDriver().executeScript("return arguments[0];", {"42"});
  EXPECT_EQ(std::string("42"), (std::string)(res));
  EXPECT_STREQ("42", (const char*)(res));

  std::string hello("hello");
  res = webDriver().executeScript("return arguments[0];", {hello});
  EXPECT_EQ(hello, (std::string)(res));



}

TEST_F(ScriptResultTest, testComparisionOperators) {

  ScriptResult res = webDriver().executeScript("return arguments[0];", {41});
  EXPECT_EQ(41, res);
  EXPECT_EQ(41.0f, res);
  EXPECT_EQ(41l, res);
  EXPECT_TRUE(res);

  WebElement element = webDriver().findElementByID("resultContainer");
  res = webDriver().executeScript("return arguments[0];", {element});
  EXPECT_EQ(element, res);

  res = webDriver().executeScript("return arguments[0];", {-42});
  EXPECT_EQ(-42, res);

  res = webDriver().executeScript("return arguments[0];", {3.14f});
  EXPECT_EQ(3.14f, res);
  EXPECT_EQ(3, res);
  EXPECT_EQ(3l, res);

  res = webDriver().executeScript("return arguments[0];", {3.2f});
  EXPECT_EQ(3.2f, res);

  res = webDriver().executeScript("return arguments[0];", {8.0f});
  EXPECT_TRUE(res);
  res = webDriver().executeScript("return arguments[0];", {0.0f});
  EXPECT_FALSE(res == true);

  res = webDriver().executeScript("return arguments[0];", {-3.14f});
  EXPECT_EQ(-3.14f, res);


  res = webDriver().executeScript("return arguments[0];", {3.141592654});
  EXPECT_EQ(3.141592654, res);
  EXPECT_EQ(3, res);
  EXPECT_EQ(3.141592654f, res);
  EXPECT_EQ(3l, res);
  EXPECT_EQ(3ll, res);

  res = webDriver().executeScript("return arguments[0];", {8.0});
  EXPECT_TRUE(res);

  res = webDriver().executeScript("return arguments[0];", {0.0});
  EXPECT_FALSE(res == true);

  res = webDriver().executeScript("return arguments[0];", {1099511627776});
  EXPECT_EQ(1099511627776l, res);
  EXPECT_EQ(1099511627776ll, res);


  res = webDriver().executeScript("return arguments[0];", {true});
  EXPECT_TRUE(res == true);

  res = webDriver().executeScript("return arguments[0];", {false});
  EXPECT_FALSE(res == true);

  res = webDriver().executeScript("return arguments[0];", {"42"});
  EXPECT_EQ(std::string("42"), res);
  std::string hello("hello");

  res = webDriver().executeScript("return arguments[0];", {hello});
  EXPECT_EQ(hello, res);

  res = webDriver().executeScript("return arguments[0];", {"world"});
  EXPECT_STREQ("world", res.operator const char *());

}

TEST_F(ScriptResultTest, testIterators)
{

  WebElement element = webDriver().findElementByID("resultContainer");
  ScriptResult res = webDriver().executeScript("return arguments[0];", {element});
  EXPECT_EQ(element, res);

  std::string hello("hello");
  res = webDriver().executeScript("return arguments;", {41, -42, 3.14f, 3.2f, 8.0f, 0.0f, -3.14f, 3.141592654, 8.0, 0.0, 1099511627776, true, false, "42", hello, "world"});
  ScriptResult::iterator pos = res.begin();
  EXPECT_EQ(41, *pos);
  EXPECT_EQ(41.0f, *pos);
  EXPECT_EQ(41l, *pos);
  EXPECT_TRUE(*pos);

  ++pos;
  EXPECT_EQ(-42, *pos);

  ++pos;
  EXPECT_EQ(3.14f, *pos);
  EXPECT_EQ(3, *pos);
  EXPECT_EQ(3l, *pos);

  ++pos;
  EXPECT_EQ(3.2f, *pos);

  ++pos;
  EXPECT_TRUE(*pos);
  ++pos;
  EXPECT_FALSE(*pos == true);

  ++pos;
  EXPECT_EQ(-3.14f, *pos);

  ++pos;
  EXPECT_EQ(3.141592654, *pos);
  EXPECT_EQ(3, *pos);
  EXPECT_EQ(3.141592654f, *pos);
  EXPECT_EQ(3l, *pos);
  EXPECT_EQ(3ll, *pos);

  ++pos;
  EXPECT_TRUE(*pos);

  ++pos;
  EXPECT_FALSE(*pos == true);

  ++pos;
  EXPECT_EQ(1099511627776l, *pos);
  EXPECT_EQ(1099511627776ll, *pos);


  ++pos;
  EXPECT_TRUE(*pos);

  ++pos;
  EXPECT_FALSE(*pos == true);

  ++pos;
  EXPECT_EQ(std::string("42"), *pos);

  ++pos;
  EXPECT_EQ(hello, *pos);

  ++pos;
  EXPECT_STREQ("world", (*pos).operator const char *());

  EXPECT_EQ("world", *pos);

  ++pos;
  EXPECT_EQ(pos, res.end());
}

TEST_F(ScriptResultTest, testConstIterators)
{

  WebElement element = webDriver().findElementByID("resultContainer");
  ScriptResult res = webDriver().executeScript("return arguments[0];", {element});
  EXPECT_EQ(element, res);

  std::string hello("hello");
  const ScriptResult res2 = webDriver().executeScript("return arguments;", {41, -42, 3.14f, 3.2f, 8.0f, 0.0f, -3.14f, 3.141592654, 8.0, 0.0, 1099511627776, true, false, "42", hello, "world"});
  ScriptResult::const_iterator pos = res2.begin();
  EXPECT_EQ(41, *pos);
  EXPECT_EQ(41.0f, *pos);
  EXPECT_EQ(41l, *pos);
  EXPECT_TRUE(*pos);

  ++pos;
  EXPECT_EQ(-42, *pos);

  ++pos;
  EXPECT_EQ(3.14f, *pos);
  EXPECT_EQ(3, *pos);
  EXPECT_EQ(3l, *pos);

  ++pos;
  EXPECT_EQ(3.2f, *pos);

  ++pos;
  EXPECT_TRUE(*pos);
  ++pos;
  EXPECT_FALSE(*pos == true);

  ++pos;
  EXPECT_EQ(-3.14f, *pos);

  ++pos;
  EXPECT_EQ(3.141592654, *pos);
  EXPECT_EQ(3, *pos);
  EXPECT_EQ(3.141592654f, *pos);
  EXPECT_EQ(3l, *pos);
  EXPECT_EQ(3ll, *pos);

  ++pos;
  EXPECT_TRUE(*pos);

  ++pos;
  EXPECT_FALSE(*pos == true);

  ++pos;
  EXPECT_EQ(1099511627776l, *pos);
  EXPECT_EQ(1099511627776ll, *pos);


  ++pos;
  EXPECT_TRUE(*pos);

  ++pos;
  EXPECT_FALSE(*pos == true);

  ++pos;
  EXPECT_EQ(std::string("42"), *pos);

  ++pos;
  EXPECT_EQ(hello, *pos);

  ++pos;
  EXPECT_STREQ("world", (const char*)(*pos));

  EXPECT_EQ("world", *pos);

  ++pos;
  EXPECT_EQ(pos, res2.end());

}

TEST_F(ScriptResultTest, testConversionOperatorsFails) {
  ScriptResult res = webDriver().executeScript("return arguments[0];", {41});

  WebElements items =  res;
  EXPECT_TRUE(items.empty());

  EXPECT_THROW((WebElement)res, std::runtime_error);
  EXPECT_THROW((std::string)res, std::runtime_error);
//  EXPECT_ANY_THROW((const char*)res);

  res = webDriver().executeScript("return arguments[0];", {"hello"});

  EXPECT_THROW((int)res, std::runtime_error);
  EXPECT_THROW((float)res, std::runtime_error);
  EXPECT_THROW((double)res, std::runtime_error);
  EXPECT_THROW((long)res, std::runtime_error);
  EXPECT_THROW((long long)res, std::runtime_error);

  EXPECT_FALSE(42 == res);



}

TEST_F(ScriptResultTest, testConversionOperatorWebElements) {
  webDriver().get(pages().formPage);

  ScriptResult res = webDriver().executeScript(
      "return document.getElementsByName('snack');");

  WebElements items =  res;
  EXPECT_FALSE(items.empty());
}
