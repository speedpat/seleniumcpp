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

class ChildrenFindingTest : public SeleniumTestCase
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



TEST_F(ChildrenFindingTest, testFindElementByXPath) {
  webDriver().get(testEnvironment().pages().nestedPage);
  WebElement element = webDriver().findElement(By::name("form2"));
  WebElement child = element.findElement(By::xpath("select"));
  assertThat(equals(child.getAttribute("id"), "2"));
}


TEST_F(ChildrenFindingTest, testFindingElementsOnElementByXPathShouldFindTopLevelElements) {
  webDriver().get(testEnvironment().pages().simpleTestPage);
  WebElements allPs = webDriver().findElements(By::xpath("//p"));
  WebElement parent = webDriver().findElement(By::id("multiline"));
  WebElements children = parent.findElements(By::xpath("//p"));
  EXPECT_EQ(allPs.size(), children.size());
}


TEST_F(ChildrenFindingTest, testFindingDotSlashElementsOnElementByXPathShouldFindNotTopLevelElements) {
  webDriver().get(testEnvironment().pages().simpleTestPage);
  WebElement parent = webDriver().findElement(By::id("multiline"));
  WebElements children = parent.findElements(By::xpath("./p"));
  EXPECT_EQ(1, children.size());
  const std::string text = children[0].text();
  assertThat(equals("A div containing", children[0].text()));
}


TEST_F(ChildrenFindingTest, testFindElementByXPathWhenNoMatch) {
  webDriver().get(testEnvironment().pages().nestedPage);

  WebElement element = webDriver().findElement(By::name("form2"));
  try {
    element.findElement(By::xpath(".//select/x"));
    FAIL() << "Did not expect to find element";
  } catch (NoSuchElementException& ignored) {
    // this is expected
  }
}


TEST_F(ChildrenFindingTest, testFindElementsByXPath) {
  webDriver().get(testEnvironment().pages().nestedPage);
  WebElement element = webDriver().findElement(By::name("form2"));
  WebElements children = element.findElements(By::xpath("select/option"));
  EXPECT_EQ(children.size(), 8);
  assertThat(equals(children[0].text(), "One"));
  assertThat(equals(children[1].text(), "Two"));
}


TEST_F(ChildrenFindingTest, testFindElementsByXPathWhenNoMatch) {
  webDriver().get(testEnvironment().pages().nestedPage);
  WebElement element = webDriver().findElement(By::name("form2"));
  WebElements children = element.findElements(By::xpath(".//select/x"));
  EXPECT_EQ(0, children.size());
}


TEST_F(ChildrenFindingTest, testFindElementByName) {
  webDriver().get(testEnvironment().pages().nestedPage);
  WebElement element = webDriver().findElement(By::name("form2"));
  WebElement child = element.findElement(By::name("selectomatic"));
  assertThat(equals(child.getAttribute("id"), "2"));
}


TEST_F(ChildrenFindingTest, testFindElementsByName) {
  webDriver().get(testEnvironment().pages().nestedPage);
  WebElement element = webDriver().findElement(By::name("form2"));
  WebElements children = element.findElements(By::name("selectomatic"));
  EXPECT_EQ(children.size(), 2);
}


TEST_F(ChildrenFindingTest, testFindElementById) {
  webDriver().get(testEnvironment().pages().nestedPage);
  WebElement element = webDriver().findElement(By::name("form2"));
  WebElement child = element.findElement(By::id("2"));
  assertThat(equals(child.getAttribute("name"), "selectomatic"));
}


TEST_F(ChildrenFindingTest, testFindElementByIdWhenMultipleMatchesExist) {
  webDriver().get(testEnvironment().pages().nestedPage);
  WebElement element = webDriver().findElement(By::id("test_id_div"));
  WebElement child = element.findElement(By::id("test_id"));
  assertThat(equals(child.text().data(), "inside"));
}


TEST_F(ChildrenFindingTest, testFindElementByIdWhenNoMatchInContext) {
  webDriver().get(testEnvironment().pages().nestedPage);
  WebElement element = webDriver().findElement(By::id("test_id_div"));
  ASSERT_THROW(element.findElement(By::id("test_id_out")), NoSuchElementException);
}


TEST_F(ChildrenFindingTest, testFindElementsById) {
  webDriver().get(testEnvironment().pages().nestedPage);
  WebElement element = webDriver().findElement(By::name("form2"));
  WebElements children = element.findElements(By::id("2"));
  EXPECT_EQ(children.size(), 2);
}


TEST_F(ChildrenFindingTest, testFindElementByLinkText) {
  webDriver().get(testEnvironment().pages().nestedPage);
  WebElement element = webDriver().findElement(By::name("div1"));
  WebElement child = element.findElement(By::linkText("hello world"));
  assertThat(equals(child.getAttribute("name"), "link1"));
}


TEST_F(ChildrenFindingTest, testFindElementsByLinkTest) {
  webDriver().get(testEnvironment().pages().nestedPage);
  WebElement element = webDriver().findElement(By::name("div1"));
  WebElements elements = element.findElements(By::linkText("hello world"));

  EXPECT_EQ(2, elements.size());
  assertThat(equals(elements[0].getAttribute("name"), "link1"));
  assertThat(equals(elements[1].getAttribute("name"), "link2"));
}


TEST_F(ChildrenFindingTest, testShouldFindChildElementsByClassName) {
  webDriver().get(testEnvironment().pages().nestedPage);
  WebElement parent = webDriver().findElement(By::name("classes"));

  WebElement element = parent.findElement(By::className("one"));

  assertThat(equals("Find me", element.text()));
}


TEST_F(ChildrenFindingTest, testShouldFindChildrenByClassName) {
  webDriver().get(testEnvironment().pages().nestedPage);
  WebElement parent = webDriver().findElement(By::name("classes"));

  WebElements elements = parent.findElements(By::className("one"));

  EXPECT_EQ(2, elements.size());
}


TEST_F(ChildrenFindingTest, testShouldFindChildElementsByTagName) {
  webDriver().get(testEnvironment().pages().nestedPage);
  WebElement parent = webDriver().findElement(By::name("div1"));

  WebElement element = parent.findElement(By::tagName("a"));

  assertThat(equals("link1", element.getAttribute("name")));
}


TEST_F(ChildrenFindingTest, testShouldFindChildrenByTagName) {
  webDriver().get(testEnvironment().pages().nestedPage);
  WebElement parent = webDriver().findElement(By::name("div1"));

  WebElements elements = parent.findElements(By::tagName("a"));

  EXPECT_EQ(2, elements.size());
}

TEST_F(ChildrenFindingTest, testShouldBeAbleToFindAnElementByCssSelector) {
  webDriver().get(testEnvironment().pages().nestedPage);
  WebElement parent = webDriver().findElement(By::name("form2"));

  WebElement element = parent.findElement(By::cssSelector("*[name=\"selectomatic\"]"));

  assertThat(equals("2", element.getAttribute("id")));
}

TEST_F(ChildrenFindingTest, testShouldBeAbleToFindAnElementByCss3Selector) {
  webDriver().get(testEnvironment().pages().nestedPage);
  WebElement parent = webDriver().findElement(By::name("form2"));

  WebElement element = parent.findElement(By::cssSelector("*[name^=\"selecto\"]"));

  assertThat(equals("2", element.getAttribute("id")));
}

TEST_F(ChildrenFindingTest, testShouldBeAbleToFindElementsByCssSelector) {
  webDriver().get(testEnvironment().pages().nestedPage);
  WebElement parent = webDriver().findElement(By::name("form2"));

  WebElements elements = parent.findElements(By::cssSelector("*[name=\"selectomatic\"]"));

  EXPECT_EQ(2, elements.size());
}


TEST_F(ChildrenFindingTest, testShouldBeAbleToFindChildrenOfANode) {
  webDriver().get(testEnvironment().pages().selectableItemsPage);
  WebElements elements = webDriver().findElements(By::xpath("/html/head"));
  WebElement head = elements[0];
  WebElements importedScripts = head.findElements(By::tagName("script"));
  EXPECT_EQ(importedScripts.size(), 3);
}


TEST_F(ChildrenFindingTest, testReturnAnEmptyListWhenThereAreNoChildrenOfANode) {
  webDriver().get(testEnvironment().pages().xhtmlTestPage);
  WebElement table = webDriver().findElement(By::id("table"));
  WebElements rows = table.findElements(By::tagName("tr"));

  EXPECT_EQ(rows.size(), 0);
}


TEST_F(ChildrenFindingTest, testShouldFindGrandChildren) {
  webDriver().get(testEnvironment().pages().formPage);
  WebElement form = webDriver().findElement(By::id("nested_form"));
  form.findElement(By::name("x"));
}


TEST_F(ChildrenFindingTest, testShouldNotFindElementOutSideTree) {
  webDriver().get(testEnvironment().pages().formPage);
  WebElement element = webDriver().findElement(By::name("login"));
  try {
    element.findElement(By::name("x"));
  } catch (NoSuchElementException& e) {
    // this is expected
  }
}


TEST_F(ChildrenFindingTest, testFindingByTagNameShouldNotIncludeParentElementIfSameTagType) {
  webDriver().get(testEnvironment().pages().xhtmlTestPage);
  WebElement parent = webDriver().findElement(By::id("my_span"));

  EXPECT_EQ(2, parent.findElements(By::tagName("div")).size());
  EXPECT_EQ(2, parent.findElements(By::tagName("span")).size());
}


TEST_F(ChildrenFindingTest, testFindingByCssShouldNotIncludeParentElementIfSameTagType) {
  webDriver().get(testEnvironment().pages().xhtmlTestPage);
  WebElement parent = webDriver().findElement(By::cssSelector("div#parent"));
  WebElement child = parent.findElement(By::cssSelector("div"));

  assertThat(equals("child", child.getAttribute("id")));
}

TEST_F(ChildrenFindingTest, testFindMultipleElements) {
  webDriver().get(testEnvironment().pages().simpleTestPage);
  WebElement elem = webDriver().findElement(By::id("links"));

  WebElements elements =
      elem.findElements(By::partialLinkText("link"));
  EXPECT_EQ(6, elements.size());
}



TEST_F(ChildrenFindingTest, testLinkWithLeadingSpaces) {
  webDriver().get(testEnvironment().pages().simpleTestPage);
  WebElement elem = webDriver().findElement(By::id("links"));

  WebElement res = elem.findElement(By::partialLinkText("link with leading space"));
  assertThat(equals("link with leading space", res.text()));
}



TEST_F(ChildrenFindingTest, testLinkWithTrailingSpace) {
  webDriver().get(testEnvironment().pages().simpleTestPage);
  WebElement elem = webDriver().findElement(By::id("links"));

  WebElement res = elem.findElement(By::partialLinkText("link with trailing space"));
  assertThat(equals("link with trailing space", res.text()));
}


TEST_F(ChildrenFindingTest, testElementCanGetLinkByLinkTestIgnoringTrailingWhitespace) {
  webDriver().get(testEnvironment().pages().simpleTestPage);
  WebElement elem = webDriver().findElement(By::id("links"));

  try {
    WebElement link = elem.findElement(By::linkText("link with trailing space"));
    assertThat(equals("linkWithTrailingSpace", link.getAttribute("id")));
  } catch (NoSuchElementException& e) {
    FAIL() << "Should have found link";
  }
}

