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
    EXPECT_FALSE(element.isEnabled());
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

