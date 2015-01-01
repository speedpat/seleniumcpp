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

class ChildrenFindingShortcutTest : public SeleniumTestCase
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



TEST_F(ChildrenFindingShortcutTest, testFindElementByXPath) {
  webDriver().get(testEnvironment().pages().nestedPage);
  WebElement element = webDriver().findElementByName("form2");
  WebElement child = element.findElementByXPath("select");
  assertThat(equals(child.getAttribute("id"), "2"));
}


TEST_F(ChildrenFindingShortcutTest, testFindingElementsOnElementByXPathShouldFindTopLevelElements) {
  webDriver().get(testEnvironment().pages().simpleTestPage);
  WebElements allPs = webDriver().findElementsByXPath("//p");
  WebElement parent = webDriver().findElementByID("multiline");
  WebElements children = parent.findElementsByXPath("//p");
  EXPECT_EQ(allPs.size(), children.size());
}


TEST_F(ChildrenFindingShortcutTest, testFindingDotSlashElementsOnElementByXPathShouldFindNotTopLevelElements) {
  webDriver().get(testEnvironment().pages().simpleTestPage);
  WebElement parent = webDriver().findElementByID("multiline");
  WebElements children = parent.findElementsByXPath("./p");
  EXPECT_EQ(1, children.size());
  const std::string text = children[0].text();
  assertThat(equals("A div containing", children[0].text()));
}


TEST_F(ChildrenFindingShortcutTest, testFindElementByXPathWhenNoMatch) {
  webDriver().get(testEnvironment().pages().nestedPage);

  WebElement element = webDriver().findElementByName("form2");
  try {
    element.findElementByXPath(".//select/x");
    FAIL() << "Did not expect to find element";
  } catch (NoSuchElementException& ignored) {
    // this is expected
  }
}


TEST_F(ChildrenFindingShortcutTest, testFindElementsByXPath) {
  webDriver().get(testEnvironment().pages().nestedPage);
  WebElement element = webDriver().findElementByName("form2");
  WebElements children = element.findElementsByXPath("select/option");
  EXPECT_EQ(children.size(), 8);
  assertThat(equals(children[0].text(), "One"));
  assertThat(equals(children[1].text(), "Two"));
}


TEST_F(ChildrenFindingShortcutTest, testFindElementsByXPathWhenNoMatch) {
  webDriver().get(testEnvironment().pages().nestedPage);
  WebElement element = webDriver().findElementByName("form2");
  WebElements children = element.findElementsByXPath(".//select/x");
  EXPECT_EQ(0, children.size());
}


TEST_F(ChildrenFindingShortcutTest, testFindElementByName) {
  webDriver().get(testEnvironment().pages().nestedPage);
  WebElement element = webDriver().findElementByName("form2");
  WebElement child = element.findElementByName("selectomatic");
  assertThat(equals(child.getAttribute("id"), "2"));
}


TEST_F(ChildrenFindingShortcutTest, testFindElementsByName) {
  webDriver().get(testEnvironment().pages().nestedPage);
  WebElement element = webDriver().findElementByName("form2");
  WebElements children = element.findElementsByName("selectomatic");
  EXPECT_EQ(children.size(), 2);
}


TEST_F(ChildrenFindingShortcutTest, testFindElementById) {
  webDriver().get(testEnvironment().pages().nestedPage);
  WebElement element = webDriver().findElementByName("form2");
  WebElement child = element.findElementByID("2");
  assertThat(equals(child.getAttribute("name"), "selectomatic"));
}


TEST_F(ChildrenFindingShortcutTest, testFindElementByIdWhenMultipleMatchesExist) {
  webDriver().get(testEnvironment().pages().nestedPage);
  WebElement element = webDriver().findElementByID("test_id_div");
  WebElement child = element.findElementByID("test_id");
  assertThat(equals(child.text().data(), "inside"));
}


TEST_F(ChildrenFindingShortcutTest, testFindElementByIdWhenNoMatchInContext) {
  webDriver().get(testEnvironment().pages().nestedPage);
  WebElement element = webDriver().findElementByID("test_id_div");
  ASSERT_THROW(element.findElementByID("test_id_out"), NoSuchElementException);
}


TEST_F(ChildrenFindingShortcutTest, testFindElementsById) {
  webDriver().get(testEnvironment().pages().nestedPage);
  WebElement element = webDriver().findElementByName("form2");
  WebElements children = element.findElementsByID("2");
  EXPECT_EQ(children.size(), 2);
}


TEST_F(ChildrenFindingShortcutTest, testFindElementByLinkText) {
  webDriver().get(testEnvironment().pages().nestedPage);
  WebElement element = webDriver().findElementByName("div1");
  WebElement child = element.findElementByLinkText("hello world");
  assertThat(equals(child.getAttribute("name"), "link1"));
}


TEST_F(ChildrenFindingShortcutTest, testFindElementsByLinkTest) {
  webDriver().get(testEnvironment().pages().nestedPage);
  WebElement element = webDriver().findElementByName("div1");
  WebElements elements = element.findElementsByLinkText("hello world");

  EXPECT_EQ(2, elements.size());
  assertThat(equals(elements[0].getAttribute("name"), "link1"));
  assertThat(equals(elements[1].getAttribute("name"), "link2"));
}


TEST_F(ChildrenFindingShortcutTest, testShouldFindChildElementsByClassName) {
  webDriver().get(testEnvironment().pages().nestedPage);
  WebElement parent = webDriver().findElementByName("classes");

  WebElement element = parent.findElementByClassName("one");

  assertThat(equals("Find me", element.text()));
}


TEST_F(ChildrenFindingShortcutTest, testShouldFindChildrenByClassName) {
  webDriver().get(testEnvironment().pages().nestedPage);
  WebElement parent = webDriver().findElementByName("classes");

  WebElements elements = parent.findElementsByClassName("one");

  EXPECT_EQ(2, elements.size());
}


TEST_F(ChildrenFindingShortcutTest, testShouldFindChildElementsByTagName) {
  webDriver().get(testEnvironment().pages().nestedPage);
  WebElement parent = webDriver().findElementByName("div1");

  WebElement element = parent.findElementByTagName("a");

  assertThat(equals("link1", element.getAttribute("name")));
}


TEST_F(ChildrenFindingShortcutTest, testShouldFindChildrenByTagName) {
  webDriver().get(testEnvironment().pages().nestedPage);
  WebElement parent = webDriver().findElementByName("div1");

  WebElements elements = parent.findElementsByTagName("a");

  EXPECT_EQ(2, elements.size());
}

TEST_F(ChildrenFindingShortcutTest, testShouldBeAbleToFindAnElementByCssSelector) {
  webDriver().get(testEnvironment().pages().nestedPage);
  WebElement parent = webDriver().findElementByName("form2");

  WebElement element = parent.findElementByCssSelector("*[name=\"selectomatic\"]");

  assertThat(equals("2", element.getAttribute("id")));
}

TEST_F(ChildrenFindingShortcutTest, testShouldBeAbleToFindAnElementByCss3Selector) {
  webDriver().get(testEnvironment().pages().nestedPage);
  WebElement parent = webDriver().findElementByName("form2");

  WebElement element = parent.findElementByCssSelector("*[name^=\"selecto\"]");

  assertThat(equals("2", element.getAttribute("id")));
}

TEST_F(ChildrenFindingShortcutTest, testShouldBeAbleToFindElementsByCssSelector) {
  webDriver().get(testEnvironment().pages().nestedPage);
  WebElement parent = webDriver().findElementByName("form2");

  WebElements elements = parent.findElementsByCssSelector("*[name=\"selectomatic\"]");

  EXPECT_EQ(2, elements.size());
}


TEST_F(ChildrenFindingShortcutTest, testShouldBeAbleToFindChildrenOfANode) {
  webDriver().get(testEnvironment().pages().selectableItemsPage);
  WebElements elements = webDriver().findElementsByXPath("/html/head");
  WebElement head = elements[0];
  WebElements importedScripts = head.findElementsByTagName("script");
  EXPECT_EQ(importedScripts.size(), 3);
}


TEST_F(ChildrenFindingShortcutTest, testReturnAnEmptyListWhenThereAreNoChildrenOfANode) {
  webDriver().get(testEnvironment().pages().xhtmlTestPage);
  WebElement table = webDriver().findElementByID("table");
  WebElements rows = table.findElementsByTagName("tr");

  EXPECT_EQ(rows.size(), 0);
}


TEST_F(ChildrenFindingShortcutTest, testShouldFindGrandChildren) {
  webDriver().get(testEnvironment().pages().formPage);
  WebElement form = webDriver().findElementByID("nested_form");
  form.findElementByName("x");
}


TEST_F(ChildrenFindingShortcutTest, testShouldNotFindElementOutSideTree) {
  webDriver().get(testEnvironment().pages().formPage);
  WebElement element = webDriver().findElementByName("login");
  try {
    element.findElementByName("x");
  } catch (NoSuchElementException& e) {
    // this is expected
  }
}


TEST_F(ChildrenFindingShortcutTest, testFindingByTagNameShouldNotIncludeParentElementIfSameTagType) {
  webDriver().get(testEnvironment().pages().xhtmlTestPage);
  WebElement parent = webDriver().findElementByID("my_span");

  EXPECT_EQ(2, parent.findElementsByTagName("div").size());
  EXPECT_EQ(2, parent.findElementsByTagName("span").size());
}


TEST_F(ChildrenFindingShortcutTest, testFindingByCssShouldNotIncludeParentElementIfSameTagType) {
  webDriver().get(testEnvironment().pages().xhtmlTestPage);
  WebElement parent = webDriver().findElementByCssSelector("div#parent");
  WebElement child = parent.findElementByCssSelector("div");

  assertThat(equals("child", child.getAttribute("id")));
}

TEST_F(ChildrenFindingShortcutTest, testFindMultipleElements) {
  webDriver().get(testEnvironment().pages().simpleTestPage);
  WebElement elem = webDriver().findElementByID("links");

  WebElements elements =
      elem.findElementsByPartialLinkText("link");
  EXPECT_EQ(6, elements.size());
}



TEST_F(ChildrenFindingShortcutTest, testLinkWithLeadingSpaces) {
  webDriver().get(testEnvironment().pages().simpleTestPage);
  WebElement elem = webDriver().findElementByID("links");

  WebElement res = elem.findElementByPartialLinkText("link with leading space");
  assertThat(equals("link with leading space", res.text()));
}



TEST_F(ChildrenFindingShortcutTest, testLinkWithTrailingSpace) {
  webDriver().get(testEnvironment().pages().simpleTestPage);
  WebElement elem = webDriver().findElementByID("links");

  WebElement res = elem.findElementByPartialLinkText("link with trailing space");
  assertThat(equals("link with trailing space", res.text()));
}


TEST_F(ChildrenFindingShortcutTest, testElementCanGetLinkByLinkTestIgnoringTrailingWhitespace) {
  webDriver().get(testEnvironment().pages().simpleTestPage);
  WebElement elem = webDriver().findElementByID("links");

  try {
    WebElement link = elem.findElementByLinkText("link with trailing space");
    assertThat(equals("linkWithTrailingSpace", link.getAttribute("id")));
  } catch (NoSuchElementException& e) {
    FAIL() << "Should have found link";
  }
}

