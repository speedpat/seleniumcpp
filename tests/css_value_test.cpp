/*
 * css_value_test.cpp
 *
 *  Created on: Sep 20, 2014
 *      Author: speedpat
 */

#include <list>

#include "selenium/selenium.hpp"
#include "support/selenium_testcase.hpp"
#include "support/expected_test_conditions.hpp"


using namespace selenium;

class CssValueTest : public SeleniumTestCase
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

};



//@JavascriptEnabled
//@Ignore({ANDROID, HTMLUNIT, OPERA, MARIONETTE})
//@Test
TEST_F(CssValueTest, testShouldPickUpStyleOfAnElement) {
  webDriver().get(pages().javascriptPage);

  WebElement element = webDriver().findElement(By::id("green-parent"));
  std::string backgroundColour = element.valueOfCssProperty("background-color");

  ASSERT_STREQ("rgba(0, 128, 0, 1)", backgroundColour.data());

  element = webDriver().findElement(By::id("red-item"));
  backgroundColour = element.valueOfCssProperty("background-color");

  ASSERT_STREQ("rgba(255, 0, 0, 1)", backgroundColour.data());
}

//@JavascriptEnabled
//@Ignore({ANDROID, HTMLUNIT, OPERA, MARIONETTE})
//@Test
TEST_F(CssValueTest, testGetCssValueShouldReturnStandardizedColour) {
  webDriver().get(pages().colorPage);

  WebElement element = webDriver().findElement(By::id("namedColor"));
  std::string backgroundColour = element.valueOfCssProperty("background-color");
  ASSERT_STREQ("rgba(0, 128, 0, 1)", backgroundColour.data());

  element = webDriver().findElement(By::id("rgb"));
  backgroundColour = element.valueOfCssProperty("background-color");
  ASSERT_STREQ("rgba(0, 128, 0, 1)", backgroundColour.data());

}

//@JavascriptEnabled
//@Ignore({ANDROID, IPHONE, OPERA, HTMLUNIT, MARIONETTE})
//@Test
/*TEST_F(CssValueTest, testShouldAllowInheritedStylesToBeUsed) {
  webDriver().get(pages().javascriptPage);

  WebElement element = webDriver().findElement(By::id("green-item"));
  std::string backgroundColour = element.valueOfCssProperty("background-color");

  // TODO: How should this be standardized? Should it be standardized?
  assertThat(backgroundColour, anyOf(
      equalTo("transparent"),
      equalTo("rgba(0, 0, 0, 0)")));
}*/

