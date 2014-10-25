/*
 * element_finding_test.cpp
 *
 *  Created on: Sep 20, 2014
 *      Author: speedpat
 */

#include <list>

#include "selenium/selenium.hpp"
#include "support/selenium_testcase.hpp"
#include "support/expected_test_conditions.hpp"


using namespace selenium;

class ElementFindingShortcutTest : public SeleniumTestCase
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



// By::id positive

//@Test
TEST_F(ElementFindingShortcutTest, testShouldBeAbleToFindASingleElementById) {
  webDriver().get(pages().xhtmlTestPage);
  WebElement element = webDriver().findElementByID("linkId");
  ASSERT_TRUE(equals(element.getAttribute("id"), "linkId"));
}

//@Ignore(value = ANDROID, reason = "Bug in Android's XPath library.")
//@Test
TEST_F(ElementFindingShortcutTest, testShouldBeAbleToFindMultipleElementsById) {
  webDriver().get(pages().nestedPage);
  WebElements elements = webDriver().findElementsByID("2");
  ASSERT_EQ(elements.size(), 8);
}

// By::id negative

//@Test(expected = NoSuchElementException.class)
TEST_F(ElementFindingShortcutTest, testShouldNotBeAbleToLocateByIdASingleElementThatDoesNotExist) {
  webDriver().get(pages().formPage);
  ASSERT_THROW(webDriver().findElementByID("nonExistentButton"), NoSuchElementException);
}

//@Test
TEST_F(ElementFindingShortcutTest, testShouldNotBeAbleToLocateByIdMultipleElementsThatDoNotExist) {
  webDriver().get(pages().formPage);
  WebElements elements = webDriver().findElementsByID("nonExistentButton");
  ASSERT_EQ(elements.size(), 0);
}

//@Test(expected = NoSuchElementException.class)
TEST_F(ElementFindingShortcutTest, testFindingASingleElementByEmptyIdShouldThrow) {
  webDriver().get(pages().formPage);
  ASSERT_THROW(webDriver().findElementByID(""), NoSuchElementException);
}

//@Test
TEST_F(ElementFindingShortcutTest, testFindingMultipleElementsByEmptyIdShouldThrow) {
  webDriver().get(pages().formPage);
  WebElements elements = webDriver().findElementsByID("");
  ASSERT_EQ(elements.size(), 0);
}

//@Test(expected = NoSuchElementException.class)
TEST_F(ElementFindingShortcutTest, testFindingASingleElementByIdWithSpaceShouldThrow) {
  webDriver().get(pages().formPage);
  ASSERT_THROW(webDriver().findElementByID("nonexistent button"), NoSuchElementException);
}

//@Test
TEST_F(ElementFindingShortcutTest, testFindingMultipleElementsByIdWithSpaceShouldThrow) {
  webDriver().get(pages().formPage);
  WebElements elements = webDriver().findElementsByID("nonexistent button");
  ASSERT_EQ(elements.size(), 0);
}

// By::name positive

//@Test
TEST_F(ElementFindingShortcutTest, testShouldBeAbleToFindASingleElementByName) {
  webDriver().get(pages().formPage);
  WebElement element = webDriver().findElementByName("checky");
  ASSERT_TRUE(equals(element.getAttribute("value"), "furrfu"));
}

//@Test
TEST_F(ElementFindingShortcutTest, testShouldBeAbleToFindMultipleElementsByName) {
  webDriver().get(pages().nestedPage);
  WebElements elements = webDriver().findElementsByName("checky");
  ASSERT_GT(elements.size(), 1);
}

//@Test
TEST_F(ElementFindingShortcutTest, testShouldBeAbleToFindAnElementThatDoesNotSupportTheNameProperty) {
  webDriver().get(pages().nestedPage);
  WebElement element = webDriver().findElementByName("div1");
  ASSERT_TRUE(equals(element.getAttribute("name"), "div1"));
}

// By::name negative

//@Test(expected = NoSuchElementException.class)
TEST_F(ElementFindingShortcutTest, testShouldNotBeAbleToLocateByNameASingleElementThatDoesNotExist) {
  webDriver().get(pages().formPage);
  ASSERT_THROW(webDriver().findElementByName("nonExistentButton"), NoSuchElementException);
}

//@Test
TEST_F(ElementFindingShortcutTest, testShouldNotBeAbleToLocateByNameMultipleElementsThatDoNotExist) {
  webDriver().get(pages().formPage);
  WebElements elements = webDriver().findElementsByName("nonExistentButton");
  ASSERT_EQ(elements.size(), 0);
}

//@Test(expected = NoSuchElementException.class)
TEST_F(ElementFindingShortcutTest, testFindingASingleElementByEmptyNameShouldThrow) {
  webDriver().get(pages().formPage);
  ASSERT_THROW(webDriver().findElementByName(""), NoSuchElementException);
}

//@Test
TEST_F(ElementFindingShortcutTest, testFindingMultipleElementsByEmptyNameShouldThrow) {
  webDriver().get(pages().formPage);
  WebElements elements = webDriver().findElementsByName("");
  ASSERT_EQ(elements.size(), 0);
}

//@Test(expected = NoSuchElementException.class)
TEST_F(ElementFindingShortcutTest, testFindingASingleElementByNameWithSpaceShouldThrow) {
  webDriver().get(pages().formPage);
  ASSERT_THROW(webDriver().findElementByName("nonexistent button"), NoSuchElementException);
}

//@Test
TEST_F(ElementFindingShortcutTest, testFindingMultipleElementsByNameWithSpaceShouldThrow) {
  webDriver().get(pages().formPage);
  WebElements elements = webDriver().findElementsByName("nonexistent button");
  ASSERT_EQ(elements.size(), 0);
}

// By::tagName positive

//@Test
TEST_F(ElementFindingShortcutTest, testShouldBeAbleToFindASingleElementByTagName) {
  webDriver().get(pages().formPage);
  WebElement element = webDriver().findElementByTagName("input");
  ASSERT_TRUE(equalsIgnoreCase(element.tagName(), "input"));
}

//@Test
TEST_F(ElementFindingShortcutTest, testShouldBeAbleToFindMultipleElementsByTagName) {
  webDriver().get(pages().formPage);
  WebElements elements = webDriver().findElementsByTagName("input");
  ASSERT_GT(elements.size(), 1);
}

// By::tagName negative

//@Test(expected = NoSuchElementException.class)
TEST_F(ElementFindingShortcutTest, testShouldNotBeAbleToLocateByTagNameASingleElementThatDoesNotExist) {
  webDriver().get(pages().formPage);
  ASSERT_THROW(webDriver().findElementByTagName("nonExistentButton"), NoSuchElementException);
}

//@Test
TEST_F(ElementFindingShortcutTest, testShouldNotBeAbleToLocateByTagNameMultipleElementsThatDoNotExist) {
  webDriver().get(pages().formPage);
  WebElements elements = webDriver().findElementsByTagName("nonExistentButton");
  ASSERT_EQ(elements.size(), 0);
}

//@Test(expected = NoSuchElementException.class)
TEST_F(ElementFindingShortcutTest, testFindingASingleElementByEmptyTagNameShouldThrow) {
  webDriver().get(pages().formPage);
  ASSERT_THROW(webDriver().findElementByTagName(""), NoSuchElementException);
}

//@Test
TEST_F(ElementFindingShortcutTest, testFindingMultipleElementsByEmptyTagNameShouldThrow) {
  webDriver().get(pages().formPage);
  WebElements elements = webDriver().findElementsByTagName("");
  ASSERT_EQ(elements.size(), 0);
}

//@Test(expected = NoSuchElementException.class)
TEST_F(ElementFindingShortcutTest, testFindingASingleElementByTagNameWithSpaceShouldThrow) {
  webDriver().get(pages().formPage);
  ASSERT_THROW(webDriver().findElementByTagName("nonexistent button"), NoSuchElementException);
}

//@Test
TEST_F(ElementFindingShortcutTest, testFindingMultipleElementsByTagNameWithSpaceShouldThrow) {
  webDriver().get(pages().formPage);
  WebElements elements = webDriver().findElementsByTagName("nonexistent button");
  ASSERT_EQ(elements.size(), 0);
}

// By::className positive

//@Test
/*TEST_F(ElementFindingShortcutTest, testShouldBeAbleToFindASingleElementByClass) {
  webDriver().get(pages().xhtmlTestPage);
  WebElement element = webDriver().findElementByClassName("extraDiv");
  ASSERT_EQ(element.text(), startsWith("Another div starts here."));
}*/

//@Test
TEST_F(ElementFindingShortcutTest, testShouldBeAbleToFindMultipleElementsByClassName) {
  webDriver().get(pages().xhtmlTestPage);
  WebElements elements = webDriver().findElementsByClassName("nameC");
  ASSERT_GT(elements.size(), 1);
}

//@Test
TEST_F(ElementFindingShortcutTest, testShouldFindElementByClassWhenItIsTheFirstNameAmongMany) {
  webDriver().get(pages().xhtmlTestPage);
  WebElement element = webDriver().findElementByClassName("nameA");
  ASSERT_TRUE(equals(element.text(), "An H2 title"));
}

//@Test
TEST_F(ElementFindingShortcutTest, testShouldFindElementByClassWhenItIsTheLastNameAmongMany) {
  webDriver().get(pages().xhtmlTestPage);
  WebElement element = webDriver().findElementByClassName("nameC");
  ASSERT_TRUE(equals(element.text(), "An H2 title"));
}

//@Test
TEST_F(ElementFindingShortcutTest, testShouldFindElementByClassWhenItIsInTheMiddleAmongMany) {
  webDriver().get(pages().xhtmlTestPage);
  WebElement element = webDriver().findElementByClassName("nameBnoise");
  ASSERT_TRUE(equals(element.text(), "An H2 title"));
}

//@Test
TEST_F(ElementFindingShortcutTest, testShouldFindElementByClassWhenItsNameIsSurroundedByWhitespace) {
  webDriver().get(pages().xhtmlTestPage);
  WebElement element = webDriver().findElementByClassName("spaceAround");
  ASSERT_TRUE(equals(element.text(), "Spaced out"));
}

//@Test
TEST_F(ElementFindingShortcutTest, testShouldFindElementsByClassWhenItsNameIsSurroundedByWhitespace) {
  webDriver().get(pages().xhtmlTestPage);
  WebElements elements = webDriver().findElementsByClassName("spaceAround");
  ASSERT_EQ(elements.size(), 1);
  ASSERT_TRUE(equals(elements[0].text(), "Spaced out"));
}

// By::className negative

//@Test(expected = NoSuchElementException.class)
TEST_F(ElementFindingShortcutTest, testShouldNotFindElementByClassWhenTheNameQueriedIsShorterThanCandidateName) {
  webDriver().get(pages().xhtmlTestPage);
  ASSERT_THROW(webDriver().findElementByClassName("nameB"), NoSuchElementException);
}

//@Ignore(value = {CHROME}, reason = "Throws WebDriverException")
//@Test(expected = NoSuchElementException.class)
/*TEST_F(ElementFindingShortcutTest, testFindingASingleElementByEmptyClassNameShouldThrow) {
  webDriver().get(pages().xhtmlTestPage);
  ASSERT_THROW(webDriver().findElementByClassName(""), NoSuchElementException);
}*/

//@Ignore(value = {CHROME, OPERA, OPERA_MOBILE}, reason = "Throws WebDriverException")
//@Test(expected = NoSuchElementException.class)
/*TEST_F(ElementFindingShortcutTest, testFindingMultipleElementsByEmptyClassNameShouldThrow) {
  webDriver().get(pages().xhtmlTestPage);
  ASSERT_THROW(webDriver().findElementsByClassName(""), NoSuchElementException);
}*/

//@Ignore(value = {CHROME, OPERA, OPERA_MOBILE}, reason = "Throws WebDriverException")
//@Test(expected = NoSuchElementException.class)
/*TEST_F(ElementFindingShortcutTest, testFindingASingleElementByCompoundClassNameShouldThrow) {
  webDriver().get(pages().xhtmlTestPage);
  ASSERT_THROW(webDriver().findElementByClassName("a b"), NoSuchElementException);
}*/

//@Ignore(value = {CHROME, OPERA, OPERA_MOBILE},
//        reason = "Chrome: throws WebDriverException")
//@Test(expected = NoSuchElementException.class)
/*TEST_F(ElementFindingShortcutTest, testFindingMultipleElementsByCompoundClassNameShouldThrow) {
  webDriver().get(pages().xhtmlTestPage);
  ASSERT_THROW(webDriver().findElementsByClassName("a b"), NoSuchElementException);
}*/

//@Ignore(value = {CHROME}, reason = "Throws InvalidElementStateException")
//@Test(expected = NoSuchElementException.class)
/*TEST_F(ElementFindingShortcutTest, testFindingASingleElementByInvalidClassNameShouldThrow) {
  webDriver().get(pages().xhtmlTestPage);
  ASSERT_THROW(webDriver().findElementByClassName("!@#$%^&*"), NoSuchElementException);
}*/

//@Ignore(value = {CHROME, OPERA, OPERA_MOBILE},
//        reason = "Chrome: throws InvalidElementStateException")
//@Test(expected = NoSuchElementException.class)
/*
TEST_F(ElementFindingShortcutTest, testFindingMultipleElementsByInvalidClassNameShouldThrow) {
  webDriver().get(pages().xhtmlTestPage);
  ASSERT_THROW(webDriver().findElementsByClassName("!@#$%^&*"), NoSuchElementException);
}
*/

// By::xpath positive

//@Test
TEST_F(ElementFindingShortcutTest, testShouldBeAbleToFindASingleElementByXPath) {
  webDriver().get(pages().xhtmlTestPage);
  WebElement element = webDriver().findElementByXPath("//h1");
  ASSERT_TRUE(equals(element.text(), "XHTML Might Be The Future"));
}

//@Test
TEST_F(ElementFindingShortcutTest, testShouldBeAbleToFindMultipleElementsByXPath) {
  webDriver().get(pages().xhtmlTestPage);
  WebElements elements = webDriver().findElementsByXPath("//div");
  ASSERT_EQ(elements.size(), 13);
}

//@Test
TEST_F(ElementFindingShortcutTest, testShouldBeAbleToFindManyElementsRepeatedlyByXPath) {
  webDriver().get(pages().xhtmlTestPage);
  std::string xpathString = "//node()[contains(@id,'id')]";
  ASSERT_EQ(webDriver().findElementsByXPath(xpathString).size(), 3);

  xpathString = "//node()[contains(@id,'nope')]";
  ASSERT_EQ(webDriver().findElementsByXPath(xpathString).size(), 0);
}

//@Test
TEST_F(ElementFindingShortcutTest, testShouldBeAbleToIdentifyElementsByClass) {
  webDriver().get(pages().xhtmlTestPage);
  WebElement header = webDriver().findElementByXPath("//h1[@class='header']");
  ASSERT_TRUE(equals(header.text(), "XHTML Might Be The Future"));
}

//@Test
TEST_F(ElementFindingShortcutTest, testShouldBeAbleToFindAnElementByXPathWithMultipleAttributes) {
  webDriver().get(pages().formPage);
  WebElement element = webDriver().findElementByXPath("//form[@name='optional']/input[@type='submit' and @value='Click!']");
  std::string tagName = element.tagName();
  std::transform(tagName.begin(), tagName.end(), tagName.begin(), ::tolower);
  ASSERT_TRUE(equals(tagName, "input"));
  ASSERT_TRUE(equals(element.getAttribute("value"), "Click!"));
}

//@Test
TEST_F(ElementFindingShortcutTest, testFindingALinkByXpathShouldLocateAnElementWithTheGivenText) {
  webDriver().get(pages().xhtmlTestPage);
  WebElement element = webDriver().findElementByXPath("//a[text()='click me']");
  ASSERT_TRUE(equals(element.text(), "click me"));
}

//@Test
TEST_F(ElementFindingShortcutTest, testFindingALinkByXpathUsingContainsKeywordShouldWork) {
  webDriver().get(pages().nestedPage);
  WebElement element = webDriver().findElementByXPath("//a[contains(.,'hello world')]");
  ASSERT_TRUE(element.text().find("hello world") != std::string::npos);
}

// By::xpath negative

//@Test(expected = NoSuchElementException.class)
TEST_F(ElementFindingShortcutTest, testShouldThrowAnExceptionWhenThereIsNoLinkToClick) {
  webDriver().get(pages().xhtmlTestPage);
ASSERT_THROW(webDriver().findElementByXPath("//a[@id='Not here']"), NoSuchElementException);
}

//@Ignore({ANDROID, IPHONE, OPERA, OPERA_MOBILE, MARIONETTE})
//@Test(expected = InvalidSelectorException.class)
TEST_F(ElementFindingShortcutTest, testShouldThrowInvalidSelectorExceptionWhenXPathIsSyntacticallyInvalidInDriverFindElement) {
  webDriver().get(pages().formPage);
  ASSERT_THROW(webDriver().findElementByXPath("this][isnot][valid"), InvalidSelectorException);
}

//@Ignore({ANDROID, IPHONE, OPERA, OPERA_MOBILE, MARIONETTE})
//@Test(expected = InvalidSelectorException.class)
TEST_F(ElementFindingShortcutTest, testShouldThrowInvalidSelectorExceptionWhenXPathIsSyntacticallyInvalidInDriverFindElements) {
 // assumeFalse("Ignoring xpath error test in IE6", TestUtilities.isIe6(driver));

  webDriver().get(pages().formPage);
  ASSERT_THROW(webDriver().findElementsByXPath("this][isnot][valid"), InvalidSelectorException);
}

//@Ignore({ANDROID, IPHONE, OPERA, OPERA_MOBILE, MARIONETTE})
//@Test(expected = InvalidSelectorException.class)
TEST_F(ElementFindingShortcutTest, testShouldThrowInvalidSelectorExceptionWhenXPathIsSyntacticallyInvalidInElementFindElement) {
  webDriver().get(pages().formPage);
  WebElement body = webDriver().findElementByTagName("body");
  ASSERT_THROW(body.findElementByXPath("this][isnot][valid"), InvalidSelectorException);
}

//@Ignore({ANDROID, IPHONE, OPERA, OPERA_MOBILE, MARIONETTE})
//@Test(expected = InvalidSelectorException.class)
TEST_F(ElementFindingShortcutTest, testShouldThrowInvalidSelectorExceptionWhenXPathIsSyntacticallyInvalidInElementFindElements) {
 // assumeFalse("Ignoring xpath error test in IE6", TestUtilities.isIe6(driver));

  webDriver().get(pages().formPage);
  WebElement body = webDriver().findElementByTagName("body");
  ASSERT_THROW(body.findElementsByXPath("this][isnot][valid"), InvalidSelectorException);
}

//@Ignore({ANDROID, IPHONE, OPERA, OPERA_MOBILE, MARIONETTE})
//@Test(expected = InvalidSelectorException.class)
TEST_F(ElementFindingShortcutTest, testShouldThrowInvalidSelectorExceptionWhenXPathReturnsWrongTypeInDriverFindElement) {
  webDriver().get(pages().formPage);
  ASSERT_THROW(webDriver().findElementByXPath("count(//input)"), InvalidSelectorException);
}

//@Ignore({ANDROID, IPHONE, OPERA, OPERA_MOBILE, MARIONETTE})
//@Test(expected = InvalidSelectorException.class)
TEST_F(ElementFindingShortcutTest, testShouldThrowInvalidSelectorExceptionWhenXPathReturnsWrongTypeInDriverFindElements) {
 // assumeFalse("Ignoring xpath error test in IE6", TestUtilities.isIe6(driver));

  webDriver().get(pages().formPage);
  ASSERT_THROW(webDriver().findElementsByXPath("count(//input)"), InvalidSelectorException);
}

//@Ignore({ANDROID, IPHONE, OPERA, OPERA_MOBILE, MARIONETTE})
//@Test(expected = InvalidSelectorException.class)
TEST_F(ElementFindingShortcutTest, testShouldThrowInvalidSelectorExceptionWhenXPathReturnsWrongTypeInElementFindElement) {
  webDriver().get(pages().formPage);

  WebElement body = webDriver().findElementByTagName("body");
  ASSERT_THROW(body.findElementByXPath("count(//input)"), InvalidSelectorException);
}

//@Ignore({ANDROID, IPHONE, OPERA, OPERA_MOBILE, MARIONETTE})
//@Test(expected = InvalidSelectorException.class)
TEST_F(ElementFindingShortcutTest, testShouldThrowInvalidSelectorExceptionWhenXPathReturnsWrongTypeInElementFindElements) {
 // assumeFalse("Ignoring xpath error test in IE6", TestUtilities.isIe6(driver));

  webDriver().get(pages().formPage);
  WebElement body = webDriver().findElementByTagName("body");
  ASSERT_THROW(body.findElementsByXPath("count(//input)"), InvalidSelectorException);
}

// By::cssSelector positive

//@Test
TEST_F(ElementFindingShortcutTest, testShouldBeAbleToFindASingleElementByCssSelector) {
  webDriver().get(pages().xhtmlTestPage);
  WebElement element = webDriver().findElementByCssSelector("div.content");
  std::string tagName = element.tagName();
  std::transform(tagName.begin(), tagName.end(), tagName.begin(), ::tolower);
  ASSERT_TRUE(equals(tagName, "div"));
  ASSERT_TRUE(equals(element.getAttribute("class"), "content"));
}

//@Test
TEST_F(ElementFindingShortcutTest, testShouldBeAbleToFindMultipleElementsByCssSelector) {
  webDriver().get(pages().xhtmlTestPage);
  WebElements elements = webDriver().findElementsByCssSelector("p");
  ASSERT_GT(elements.size(), 1);
}

//@Test
TEST_F(ElementFindingShortcutTest, testShouldBeAbleToFindASingleElementByCompoundCssSelector) {
  webDriver().get(pages().xhtmlTestPage);
  WebElement element = webDriver().findElementByCssSelector("div.extraDiv, div.content");
  std::string tagName = element.tagName();
  std::transform(tagName.begin(), tagName.end(), tagName.begin(), ::tolower);
  ASSERT_TRUE(equals(tagName, "div"));
  ASSERT_TRUE(equals(element.getAttribute("class"), "content"));
}

//@Test
TEST_F(ElementFindingShortcutTest, testShouldBeAbleToFindMultipleElementsByCompoundCssSelector) {
  webDriver().get(pages().xhtmlTestPage);
  WebElements elements = webDriver().findElementsByCssSelector("div.extraDiv, div.content");
  ASSERT_GT(elements.size(), 1);
  ASSERT_TRUE(equals(elements[0].getAttribute("class"), "content"));
  ASSERT_TRUE(equals(elements[1].getAttribute("class"), "extraDiv"));
}

//@Test
//@Ignore(value = {IE}, reason = "IE supports only short version option[selected]")
TEST_F(ElementFindingShortcutTest, testShouldBeAbleToFindAnElementByBooleanAttributeUsingCssSelector) {
  webDriver().get(whereIs("locators_tests/boolean_attribute_selected.html"));
  WebElement element = webDriver().findElementByCssSelector("option[selected='selected']");
  ASSERT_TRUE(equals(element.getAttribute("value"), "two"));
}

//@Test
TEST_F(ElementFindingShortcutTest, testShouldBeAbleToFindAnElementByBooleanAttributeUsingShortCssSelector) {
  webDriver().get(whereIs("locators_tests/boolean_attribute_selected.html"));
  WebElement element = webDriver().findElementByCssSelector("option[selected]");
  ASSERT_TRUE(equals(element.getAttribute("value"), "two"));
}

//@Test
TEST_F(ElementFindingShortcutTest, testShouldBeAbleToFindAnElementByBooleanAttributeUsingShortCssSelectorOnHtml4Page) {
  webDriver().get(whereIs("locators_tests/boolean_attribute_selected_html4.html"));
  WebElement element = webDriver().findElementByCssSelector("option[selected]");
  ASSERT_TRUE(equals(element.getAttribute("value"), "two"));
}

// By::cssSelector negative

//@Test(expected = NoSuchElementException.class)
TEST_F(ElementFindingShortcutTest, testShouldNotFindElementByCssSelectorWhenThereIsNoSuchElement) {
  webDriver().get(pages().xhtmlTestPage);
  ASSERT_THROW(webDriver().findElementByCssSelector(".there-is-no-such-class"), NoSuchElementException);
}

TEST_F(ElementFindingShortcutTest, testShouldNotFindElementsByCssSelectorWhenThereIsNoSuchElement) {
  webDriver().get(pages().xhtmlTestPage);
  WebElements elements = webDriver().findElementsByCssSelector(".there-is-no-such-class");
  ASSERT_EQ(elements.size(), 0);
}

//@Ignore(value = {CHROME}, reason = "Throws WebDriverException")
//@Test(expected = NoSuchElementException.class)
/*TEST_F(ElementFindingShortcutTest, testFindingASingleElementByEmptyCssSelectorShouldThrow) {
  webDriver().get(pages().xhtmlTestPage);
  ASSERT_THROW(webDriver().findElementByCssSelector(""), NoSuchElementException);
}*/

//@Ignore(value = {CHROME, OPERA, OPERA_MOBILE},
//        reason = "Chrome: throws WebDriverException")
//@Test(expected = NoSuchElementException.class)
/*TEST_F(ElementFindingShortcutTest, testFindingMultipleElementsByEmptyCssSelectorShouldThrow) {
  webDriver().get(pages().xhtmlTestPage);
  ASSERT_THROW(webDriver().findElementsByCssSelector(""), NoSuchElementException);
}*/

//@Ignore(value = {CHROME}, reason = "Throws InvalidElementStateException")
//@Test(expected = NoSuchElementException.class)
/*
TEST_F(ElementFindingShortcutTest, testFindingASingleElementByInvalidCssSelectorShouldThrow) {
  webDriver().get(pages().xhtmlTestPage);
  ASSERT_THROW(webDriver().findElementByCssSelector("//a/b/c[@id='1']"), NoSuchElementException);
}
*/

//@Ignore(value = {CHROME, OPERA, OPERA_MOBILE},
//        reason = "Chrome: throws InvalidElementStateException")
//@Test(expected = NoSuchElementException.class)
/*
TEST_F(ElementFindingShortcutTest, testFindingMultipleElementsByInvalidCssSelectorShouldThrow) {
//  assumeFalse("Ignoring test for lack of error in CSS in IE6", TestUtilities.isIe6(driver));
  webDriver().get(pages().xhtmlTestPage);
  ASSERT_THROW(webDriver().findElementsByCssSelector("//a/b/c[@id='1']"), NoSuchElementException);
}
*/

// By::linkText positive

//@Test
TEST_F(ElementFindingShortcutTest, testShouldBeAbleToFindALinkByText) {
  webDriver().get(pages().xhtmlTestPage);
  WebElement link = webDriver().findElementByLinkText("click me");
  ASSERT_TRUE(equals(link.text(), "click me"));
}

//@Test
TEST_F(ElementFindingShortcutTest, testShouldBeAbleToFindMultipleLinksByText) {
  webDriver().get(pages().xhtmlTestPage);
  WebElements elements = webDriver().findElementsByLinkText("click me");
  ASSERT_EQ(elements.size(), 2);
}

//@Test
TEST_F(ElementFindingShortcutTest, testShouldFindElementByLinkTextContainingEqualsSign) {
  webDriver().get(pages().xhtmlTestPage);
  WebElement element = webDriver().findElementByLinkText("Link=equalssign");
  ASSERT_TRUE(equals(element.getAttribute("id"), "linkWithEqualsSign"));
}

//@Test
TEST_F(ElementFindingShortcutTest, testShouldFindMultipleElementsByLinkTextContainingEqualsSign) {
  webDriver().get(pages().xhtmlTestPage);
  WebElements elements = webDriver().findElementsByLinkText("Link=equalssign");
  ASSERT_EQ(1, elements.size());
  ASSERT_TRUE(equals(elements[0].getAttribute("id"), "linkWithEqualsSign"));
}

//@Test
//@Ignore({OPERA, MARIONETTE})
TEST_F(ElementFindingShortcutTest, findsByLinkTextOnXhtmlPage) {
//  assumeFalse("Old IE doesn't render XHTML pages(). don't try loading XHTML pages().in it",
//              isOldIe(driver));

  webDriver().get(whereIs("actualXhtmlPage.xhtml"));
  const std::string linkText = "Foo";
  WebElement element = webDriver().findElementByLinkText(linkText);
  ASSERT_EQ(element.text(), linkText);
}

//@Ignore({REMOTE})
//@Test
TEST_F(ElementFindingShortcutTest, testLinkWithFormattingTags) {
  webDriver().get(pages().simpleTestPage);
  WebElement elem = webDriver().findElementByID("links");

  WebElement res = elem.findElementByPartialLinkText("link with formatting tags");
  ASSERT_TRUE(equals(res.text(), "link with formatting tags"));
}

//@Test
//@Ignore(MARIONETTE)
TEST_F(ElementFindingShortcutTest, testDriverCanGetLinkByLinkTestIgnoringTrailingWhitespace) {
  webDriver().get(pages().simpleTestPage);
  WebElement link = webDriver().findElementByLinkText("link with trailing space");
  ASSERT_TRUE(equals(link.getAttribute("id"), "linkWithTrailingSpace"));
  ASSERT_TRUE(equals(link.text(), "link with trailing space"));
}

// By::linkText negative

//@Test(expected = NoSuchElementException.class)
TEST_F(ElementFindingShortcutTest, testShouldNotBeAbleToLocateByLinkTextASingleElementThatDoesNotExist) {
  webDriver().get(pages().xhtmlTestPage);
  ASSERT_THROW(webDriver().findElementByLinkText("Not here either"), NoSuchElementException);
}

//@Test
TEST_F(ElementFindingShortcutTest, testShouldNotBeAbleToLocateByLinkTextMultipleElementsThatDoNotExist) {
  webDriver().get(pages().xhtmlTestPage);
  WebElements elements = webDriver().findElementsByLinkText("Not here either");
  ASSERT_EQ(elements.size(), 0);
}

// By::partialLinkText positive

//@Test
TEST_F(ElementFindingShortcutTest, testShouldBeAbleToFindMultipleElementsByPartialLinkText) {
  webDriver().get(pages().xhtmlTestPage);
  WebElements elements = webDriver().findElementsByPartialLinkText("ick me");
  ASSERT_EQ(elements.size(), 2);
}

//@Test
TEST_F(ElementFindingShortcutTest, testShouldBeAbleToFindASingleElementByPartialLinkText) {
  webDriver().get(pages().xhtmlTestPage);
  WebElement element = webDriver().findElementByPartialLinkText("anon");
  ASSERT_TRUE(element.text().find("anon") != std::string::npos);
}

//@Test
TEST_F(ElementFindingShortcutTest, testShouldFindElementByPartialLinkTextContainingEqualsSign) {
  webDriver().get(pages().xhtmlTestPage);
  WebElement element = webDriver().findElementByPartialLinkText("Link=");
  ASSERT_TRUE(equals(element.getAttribute("id"), "linkWithEqualsSign"));
}

//@Test
TEST_F(ElementFindingShortcutTest, testShouldFindMultipleElementsByPartialLinkTextContainingEqualsSign) {
  webDriver().get(pages().xhtmlTestPage);
  WebElements elements = webDriver().findElementsByPartialLinkText("Link=");
  ASSERT_EQ(elements.size(), 1);
  ASSERT_TRUE(equals(elements[0].getAttribute("id"), "linkWithEqualsSign"));
}

// Misc tests

//@Test
TEST_F(ElementFindingShortcutTest, testDriverShouldBeAbleToFindElementsAfterLoadingMoreThanOnePageAtATime) {
  webDriver().get(pages().formPage);
  webDriver().get(pages().xhtmlTestPage);
  WebElement link = webDriver().findElementByLinkText("click me");
  ASSERT_TRUE(equals(link.text(), "click me"));
}

// You don't want to ask why this is here
//@Test
TEST_F(ElementFindingShortcutTest, testWhenFindingByNameShouldNotReturnById) {
  webDriver().get(pages().formPage);

  WebElement element = webDriver().findElementByName("id-name1");
  ASSERT_TRUE(equals(element.getAttribute("value"), "name"));

  element = webDriver().findElementByID("id-name1");
  ASSERT_TRUE(equals(element.getAttribute("value"), "id"));

  element = webDriver().findElementByName("id-name2");
  ASSERT_TRUE(equals(element.getAttribute("value"), "name"));

  element = webDriver().findElementByID("id-name2");
  ASSERT_TRUE(equals(element.getAttribute("value"), "id"));
}

//@Test
TEST_F(ElementFindingShortcutTest, testShouldBeAbleToFindAHiddenElementsByName) {
  webDriver().get(pages().formPage);
  WebElement element = webDriver().findElementByName("hidden");
  ASSERT_TRUE(equals(element.getAttribute("name"), "hidden"));
}

//@Test(expected = NoSuchElementException.class)
TEST_F(ElementFindingShortcutTest, testShouldNotBeAbleToFindAnElementOnABlankPage) {
  webDriver().get("about:blank");
  ASSERT_THROW(webDriver().findElementByTagName("a"), NoSuchElementException);
}

//@Ignore({IPHONE})
//@NeedsFreshDriver
//@Test(expected = NoSuchElementException.class)
TEST_F(ElementFindingShortcutTest, testShouldNotBeAbleToLocateASingleElementOnABlankPage) {
  // Note we're on the default start page for the browser at this point.
  ASSERT_THROW(webDriver().findElementByID("nonExistantButton"), NoSuchElementException);
}

//@Ignore(value = {ANDROID, OPERA, OPERA_MOBILE, MARIONETTE}, reason = "Just not working")
//@Test
TEST_F(ElementFindingShortcutTest, testAnElementFoundInADifferentFrameIsStale) {
  webDriver().get(pages().missedJsReferencePage);
  webDriver().switchTo().frame("inner");
  WebElement element = webDriver().findElementByID("oneline");
  webDriver().switchTo().defaultContent();
  try {
    element.text();
    FAIL() << "Expected exception";
  } catch (StaleElementReferenceException& expected) {
    // Expected
  }
}

//@JavascriptEnabled
//@Ignore({ANDROID, IPHONE, OPERA, OPERA_MOBILE, MARIONETTE})
//@Test
TEST_F(ElementFindingShortcutTest, testAnElementFoundInADifferentFrameViaJsCanBeUsed) {
  webDriver().get(pages().missedJsReferencePage);

  try {
    webDriver().switchTo().frame("inner");
    WebElement first = webDriver().findElementByID("oneline");

    webDriver().switchTo().defaultContent();
    WebElement element = webDriver().executeScript(
        "return frames[0].document.getElementById('oneline');");


    webDriver().switchTo().frame("inner");

    WebElement second = webDriver().findElementByID("oneline");

    ASSERT_EQ(first, element);
    ASSERT_EQ(second, element);
  } catch (...) {
    webDriver().switchTo().defaultContent();
    throw;
  }
  webDriver().switchTo().defaultContent();

}

