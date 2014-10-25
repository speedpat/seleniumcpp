/*
 * alerts_test.cpp
 *
 *  Created on: Sep 20, 2014
 *      Author: speedpat
 */

#include <list>

#include "selenium/selenium.hpp"
#include "support/selenium_testcase.hpp"


using namespace selenium;

class ClearTest : public SeleniumTestCase
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






TEST_F(ClearTest, testWritableTextInputShouldClear) {
  webDriver().get(pages().readOnlyPage);
  WebElement element = webDriver().findElement(By::id("writableTextInput"));
  element.clear();
  EXPECT_STREQ("", element.getAttribute("value").asString().data());
}


TEST_F(ClearTest, testTextInputShouldNotClearWhenDisabled) {
  webDriver().get(pages().readOnlyPage);
  try {
    WebElement element = webDriver().findElement(By::id("textInputnotenabled"));
    EXPECT_EQ(false, element.isEnabled());
    element.clear();
    FAIL() << ("Should not have succeeded");
  } catch (InvalidElementStateException& e) {
    // This is expected
  }
}



TEST_F(ClearTest, testTextInputShouldNotClearWhenReadOnly) {
  try {
    webDriver().get(pages().readOnlyPage);
    WebElement element = webDriver().findElement(By::id("readOnlyTextInput"));
    element.clear();
    FAIL() << ("Should not have succeeded");
  } catch (InvalidElementStateException& e) {
    // This is expected
  }
}


TEST_F(ClearTest, testWritableTextAreaShouldClear) {
  webDriver().get(pages().readOnlyPage);
  WebElement element = webDriver().findElement(By::id("writableTextArea"));
  element.clear();
  EXPECT_STREQ("", element.getAttribute("value").asString().data());
}


TEST_F(ClearTest, testTextAreaShouldNotClearWhenDisabled) {
  try {
    webDriver().get(pages().readOnlyPage);
    WebElement element = webDriver().findElement(By::id("textAreaNotenabled"));
    element.clear();
    FAIL() << ("Should not have succeeded");
  } catch (InvalidElementStateException& e) {
    // This is expected
  }
}



TEST_F(ClearTest, testTextAreaShouldNotClearWhenReadOnly) {
  try {
    webDriver().get(pages().readOnlyPage);
    WebElement element = webDriver().findElement(By::id("textAreaReadOnly"));
    element.clear();
    FAIL() << ("Should not have succeeded");
  } catch (InvalidElementStateException& e) {
    // This is expected
  }
}



TEST_F(ClearTest, testContentEditableAreaShouldClear) {
  webDriver().get(pages().readOnlyPage);
  WebElement element = webDriver().findElement(By::id("content-editable"));
  element.clear();
  EXPECT_STREQ("", element.text().data());
}

