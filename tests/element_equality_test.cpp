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

class ElementEqualityTest : public SeleniumTestCase
{
public:

  virtual void SetUp()
  {
    SeleniumTestCase::SetUp();

  }

  virtual void TearDown()
  {
    SeleniumTestCase::TearDown();
  }

  void checkIdEqualityIfRemote(WebElement first, WebElement second) {
    std::string firstId = first.id();
    std::string secondId = second.id();

    ASSERT_STREQ(firstId.data(), secondId.data());
  }

};

//@Test
TEST_F(ElementEqualityTest, testSameElementLookedUpDifferentWaysShouldBeEqual) {
  webDriver().get(pages().simpleTestPage);

  WebElement body = webDriver().findElement(By::tagName("body"));
  WebElement xbody = webDriver().findElements(By::xpath("//body"))[0];

  ASSERT_EQ(body, xbody);
}

//@Test
TEST_F(ElementEqualityTest, testDifferentElementsShouldNotBeEqual) {
  webDriver().get(pages().simpleTestPage);

  WebElements ps = webDriver().findElements(By::tagName("p"));

  ASSERT_FALSE(ps[0] == ps[1]);
}


//@JavascriptEnabled
//@Ignore(value = {ANDROID, IPHONE, OPERA, OPERA_MOBILE, MARIONETTE},
//        reason = "Opera: Needs investigation")
//@Test
TEST_F(ElementEqualityTest, testAnElementFoundInADifferentFrameViaJsShouldHaveSameId) {
  webDriver().get(pages().missedJsReferencePage);

  webDriver().switchTo().frame("inner");
  WebElement first = webDriver().findElement(By::id("oneline"));

  webDriver().switchTo().defaultContent();
  WebElement element = webDriver().executeScript(
      "return frames[0].document.getElementById('oneline');");

  webDriver().switchTo().frame("inner");

  WebElement second = webDriver().findElement(By::id("oneline"));

  checkIdEqualityIfRemote(first, element);
  checkIdEqualityIfRemote(second, element);
}


