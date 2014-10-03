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

class ElementFindingTest : public SeleniumTestCase
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
TEST_F(ElementFindingTest, testShouldBeAbleToFindASingleElementById) {
  webDriver().get(pages().xhtmlTestPage);
  WebElement element = webDriver().findElement(By::id("linkId"));
  ASSERT_STREQ(element.getAttribute("id").data(), "linkId");
}

//@Ignore(value = ANDROID, reason = "Bug in Android's XPath library.")
//@Test
TEST_F(ElementFindingTest, testShouldBeAbleToFindMultipleElementsById) {
  webDriver().get(pages().nestedPage);
  WebElements elements = webDriver().findElements(By::id("2"));
  ASSERT_EQ(elements.size(), 8);
}

// By::id negative

//@Test(expected = NoSuchElementException.class)
TEST_F(ElementFindingTest, testShouldNotBeAbleToLocateByIdASingleElementThatDoesNotExist) {
  webDriver().get(pages().formPage);
  ASSERT_THROW(webDriver().findElement(By::id("nonExistentButton")), NoSuchElementException);
}

//@Test
TEST_F(ElementFindingTest, testShouldNotBeAbleToLocateByIdMultipleElementsThatDoNotExist) {
  webDriver().get(pages().formPage);
  WebElements elements = webDriver().findElements(By::id("nonExistentButton"));
  ASSERT_EQ(elements.size(), 0);
}

//@Test(expected = NoSuchElementException.class)
TEST_F(ElementFindingTest, testFindingASingleElementByEmptyIdShouldThrow) {
  webDriver().get(pages().formPage);
  ASSERT_THROW(webDriver().findElement(By::id("")), NoSuchElementException);
}

//@Test
TEST_F(ElementFindingTest, testFindingMultipleElementsByEmptyIdShouldThrow) {
  webDriver().get(pages().formPage);
  WebElements elements = webDriver().findElements(By::id(""));
  ASSERT_EQ(elements.size(), 0);
}

//@Test(expected = NoSuchElementException.class)
TEST_F(ElementFindingTest, testFindingASingleElementByIdWithSpaceShouldThrow) {
  webDriver().get(pages().formPage);
  ASSERT_THROW(webDriver().findElement(By::id("nonexistent button")), NoSuchElementException);
}

//@Test
TEST_F(ElementFindingTest, testFindingMultipleElementsByIdWithSpaceShouldThrow) {
  webDriver().get(pages().formPage);
  WebElements elements = webDriver().findElements(By::id("nonexistent button"));
  ASSERT_EQ(elements.size(), 0);
}

// By::name positive

//@Test
TEST_F(ElementFindingTest, testShouldBeAbleToFindASingleElementByName) {
  webDriver().get(pages().formPage);
  WebElement element = webDriver().findElement(By::name("checky"));
  ASSERT_STREQ(element.getAttribute("value").data(), "furrfu");
}

//@Test
TEST_F(ElementFindingTest, testShouldBeAbleToFindMultipleElementsByName) {
  webDriver().get(pages().nestedPage);
  WebElements elements = webDriver().findElements(By::name("checky"));
  ASSERT_GT(elements.size(), 1);
}

//@Test
TEST_F(ElementFindingTest, testShouldBeAbleToFindAnElementThatDoesNotSupportTheNameProperty) {
  webDriver().get(pages().nestedPage);
  WebElement element = webDriver().findElement(By::name("div1"));
  ASSERT_STREQ(element.getAttribute("name").data(), "div1");
}

// By::name negative

//@Test(expected = NoSuchElementException.class)
TEST_F(ElementFindingTest, testShouldNotBeAbleToLocateByNameASingleElementThatDoesNotExist) {
  webDriver().get(pages().formPage);
  ASSERT_THROW(webDriver().findElement(By::name("nonExistentButton")), NoSuchElementException);
}

//@Test
TEST_F(ElementFindingTest, testShouldNotBeAbleToLocateByNameMultipleElementsThatDoNotExist) {
  webDriver().get(pages().formPage);
  WebElements elements = webDriver().findElements(By::name("nonExistentButton"));
  ASSERT_EQ(elements.size(), 0);
}

//@Test(expected = NoSuchElementException.class)
TEST_F(ElementFindingTest, testFindingASingleElementByEmptyNameShouldThrow) {
  webDriver().get(pages().formPage);
  ASSERT_THROW(webDriver().findElement(By::name("")), NoSuchElementException);
}

//@Test
TEST_F(ElementFindingTest, testFindingMultipleElementsByEmptyNameShouldThrow) {
  webDriver().get(pages().formPage);
  WebElements elements = webDriver().findElements(By::name(""));
  ASSERT_EQ(elements.size(), 0);
}

//@Test(expected = NoSuchElementException.class)
TEST_F(ElementFindingTest, testFindingASingleElementByNameWithSpaceShouldThrow) {
  webDriver().get(pages().formPage);
  ASSERT_THROW(webDriver().findElement(By::name("nonexistent button")), NoSuchElementException);
}

//@Test
TEST_F(ElementFindingTest, testFindingMultipleElementsByNameWithSpaceShouldThrow) {
  webDriver().get(pages().formPage);
  WebElements elements = webDriver().findElements(By::name("nonexistent button"));
  ASSERT_EQ(elements.size(), 0);
}

// By::tagName positive

//@Test
TEST_F(ElementFindingTest, testShouldBeAbleToFindASingleElementByTagName) {
  webDriver().get(pages().formPage);
  WebElement element = webDriver().findElement(By::tagName("input"));
  ASSERT_STRCASEEQ(element.tagName().data(), "input");
}

//@Test
TEST_F(ElementFindingTest, testShouldBeAbleToFindMultipleElementsByTagName) {
  webDriver().get(pages().formPage);
  WebElements elements = webDriver().findElements(By::tagName("input"));
  ASSERT_GT(elements.size(), 1);
}

// By::tagName negative

//@Test(expected = NoSuchElementException.class)
TEST_F(ElementFindingTest, testShouldNotBeAbleToLocateByTagNameASingleElementThatDoesNotExist) {
  webDriver().get(pages().formPage);
  ASSERT_THROW(webDriver().findElement(By::tagName("nonExistentButton")), NoSuchElementException);
}

//@Test
TEST_F(ElementFindingTest, testShouldNotBeAbleToLocateByTagNameMultipleElementsThatDoNotExist) {
  webDriver().get(pages().formPage);
  WebElements elements = webDriver().findElements(By::tagName("nonExistentButton"));
  ASSERT_EQ(elements.size(), 0);
}

//@Test(expected = NoSuchElementException.class)
TEST_F(ElementFindingTest, testFindingASingleElementByEmptyTagNameShouldThrow) {
  webDriver().get(pages().formPage);
  ASSERT_THROW(webDriver().findElement(By::tagName("")), NoSuchElementException);
}

//@Test
TEST_F(ElementFindingTest, testFindingMultipleElementsByEmptyTagNameShouldThrow) {
  webDriver().get(pages().formPage);
  WebElements elements = webDriver().findElements(By::tagName(""));
  ASSERT_EQ(elements.size(), 0);
}

//@Test(expected = NoSuchElementException.class)
TEST_F(ElementFindingTest, testFindingASingleElementByTagNameWithSpaceShouldThrow) {
  webDriver().get(pages().formPage);
  ASSERT_THROW(webDriver().findElement(By::tagName("nonexistent button")), NoSuchElementException);
}

//@Test
TEST_F(ElementFindingTest, testFindingMultipleElementsByTagNameWithSpaceShouldThrow) {
  webDriver().get(pages().formPage);
  WebElements elements = webDriver().findElements(By::tagName("nonexistent button"));
  ASSERT_EQ(elements.size(), 0);
}

// By::className positive

//@Test
/*TEST_F(ElementFindingTest, testShouldBeAbleToFindASingleElementByClass) {
  webDriver().get(pages().xhtmlTestPage);
  WebElement element = webDriver().findElement(By::className("extraDiv"));
  ASSERT_EQ(element.text().data(), startsWith("Another div starts here."));
}*/

//@Test
TEST_F(ElementFindingTest, testShouldBeAbleToFindMultipleElementsByClassName) {
  webDriver().get(pages().xhtmlTestPage);
  WebElements elements = webDriver().findElements(By::className("nameC"));
  ASSERT_GT(elements.size(), 1);
}

//@Test
TEST_F(ElementFindingTest, testShouldFindElementByClassWhenItIsTheFirstNameAmongMany) {
  webDriver().get(pages().xhtmlTestPage);
  WebElement element = webDriver().findElement(By::className("nameA"));
  ASSERT_STREQ(element.text().data(), "An H2 title");
}

//@Test
TEST_F(ElementFindingTest, testShouldFindElementByClassWhenItIsTheLastNameAmongMany) {
  webDriver().get(pages().xhtmlTestPage);
  WebElement element = webDriver().findElement(By::className("nameC"));
  ASSERT_STREQ(element.text().data(), "An H2 title");
}

//@Test
TEST_F(ElementFindingTest, testShouldFindElementByClassWhenItIsInTheMiddleAmongMany) {
  webDriver().get(pages().xhtmlTestPage);
  WebElement element = webDriver().findElement(By::className("nameBnoise"));
  ASSERT_STREQ(element.text().data(), "An H2 title");
}

//@Test
TEST_F(ElementFindingTest, testShouldFindElementByClassWhenItsNameIsSurroundedByWhitespace) {
  webDriver().get(pages().xhtmlTestPage);
  WebElement element = webDriver().findElement(By::className("spaceAround"));
  ASSERT_STREQ(element.text().data(), "Spaced out");
}

//@Test
TEST_F(ElementFindingTest, testShouldFindElementsByClassWhenItsNameIsSurroundedByWhitespace) {
  webDriver().get(pages().xhtmlTestPage);
  WebElements elements = webDriver().findElements(By::className("spaceAround"));
  ASSERT_EQ(elements.size(), 1);
  ASSERT_STREQ(elements[0].text().data(), "Spaced out");
}

// By::className negative

//@Test(expected = NoSuchElementException.class)
TEST_F(ElementFindingTest, testShouldNotFindElementByClassWhenTheNameQueriedIsShorterThanCandidateName) {
  webDriver().get(pages().xhtmlTestPage);
  ASSERT_THROW(webDriver().findElement(By::className("nameB")), NoSuchElementException);
}

//@Ignore(value = {CHROME}, reason = "Throws WebDriverException")
//@Test(expected = NoSuchElementException.class)
/*TEST_F(ElementFindingTest, testFindingASingleElementByEmptyClassNameShouldThrow) {
  webDriver().get(pages().xhtmlTestPage);
  ASSERT_THROW(webDriver().findElement(By::className("")), NoSuchElementException);
}*/

//@Ignore(value = {CHROME, OPERA, OPERA_MOBILE}, reason = "Throws WebDriverException")
//@Test(expected = NoSuchElementException.class)
/*TEST_F(ElementFindingTest, testFindingMultipleElementsByEmptyClassNameShouldThrow) {
  webDriver().get(pages().xhtmlTestPage);
  ASSERT_THROW(webDriver().findElements(By::className("")), NoSuchElementException);
}*/

//@Ignore(value = {CHROME, OPERA, OPERA_MOBILE}, reason = "Throws WebDriverException")
//@Test(expected = NoSuchElementException.class)
/*TEST_F(ElementFindingTest, testFindingASingleElementByCompoundClassNameShouldThrow) {
  webDriver().get(pages().xhtmlTestPage);
  ASSERT_THROW(webDriver().findElement(By::className("a b")), NoSuchElementException);
}*/

//@Ignore(value = {CHROME, OPERA, OPERA_MOBILE},
//        reason = "Chrome: throws WebDriverException")
//@Test(expected = NoSuchElementException.class)
/*TEST_F(ElementFindingTest, testFindingMultipleElementsByCompoundClassNameShouldThrow) {
  webDriver().get(pages().xhtmlTestPage);
  ASSERT_THROW(webDriver().findElements(By::className("a b")), NoSuchElementException);
}*/

//@Ignore(value = {CHROME}, reason = "Throws InvalidElementStateException")
//@Test(expected = NoSuchElementException.class)
/*TEST_F(ElementFindingTest, testFindingASingleElementByInvalidClassNameShouldThrow) {
  webDriver().get(pages().xhtmlTestPage);
  ASSERT_THROW(webDriver().findElement(By::className("!@#$%^&*")), NoSuchElementException);
}*/

//@Ignore(value = {CHROME, OPERA, OPERA_MOBILE},
//        reason = "Chrome: throws InvalidElementStateException")
//@Test(expected = NoSuchElementException.class)
/*
TEST_F(ElementFindingTest, testFindingMultipleElementsByInvalidClassNameShouldThrow) {
  webDriver().get(pages().xhtmlTestPage);
  ASSERT_THROW(webDriver().findElements(By::className("!@#$%^&*")), NoSuchElementException);
}
*/

// By::xpath positive

//@Test
TEST_F(ElementFindingTest, testShouldBeAbleToFindASingleElementByXPath) {
  webDriver().get(pages().xhtmlTestPage);
  WebElement element = webDriver().findElement(By::xpath("//h1"));
  ASSERT_STREQ(element.text().data(), "XHTML Might Be The Future");
}

//@Test
TEST_F(ElementFindingTest, testShouldBeAbleToFindMultipleElementsByXPath) {
  webDriver().get(pages().xhtmlTestPage);
  WebElements elements = webDriver().findElements(By::xpath("//div"));
  ASSERT_EQ(elements.size(), 13);
}

//@Test
TEST_F(ElementFindingTest, testShouldBeAbleToFindManyElementsRepeatedlyByXPath) {
  webDriver().get(pages().xhtmlTestPage);
  std::string xpathString = "//node()[contains(@id,'id')]";
  ASSERT_EQ(webDriver().findElements(By::xpath(xpathString)).size(), 3);

  xpathString = "//node()[contains(@id,'nope')]";
  ASSERT_EQ(webDriver().findElements(By::xpath(xpathString)).size(), 0);
}

//@Test
TEST_F(ElementFindingTest, testShouldBeAbleToIdentifyElementsByClass) {
  webDriver().get(pages().xhtmlTestPage);
  WebElement header = webDriver().findElement(By::xpath("//h1[@class='header']"));
  ASSERT_STREQ(header.text().data(), "XHTML Might Be The Future");
}

//@Test
TEST_F(ElementFindingTest, testShouldBeAbleToFindAnElementByXPathWithMultipleAttributes) {
  webDriver().get(pages().formPage);
  WebElement element = webDriver().findElement(
      By::xpath("//form[@name='optional']/input[@type='submit' and @value='Click!']"));
  std::string tagName = element.tagName();
  std::transform(tagName.begin(), tagName.end(), tagName.begin(), ::tolower);
  ASSERT_STREQ(tagName.data(), "input");
  ASSERT_STREQ(element.getAttribute("value").data(), "Click!");
}

//@Test
TEST_F(ElementFindingTest, testFindingALinkByXpathShouldLocateAnElementWithTheGivenText) {
  webDriver().get(pages().xhtmlTestPage);
  WebElement element = webDriver().findElement(By::xpath("//a[text()='click me']"));
  ASSERT_STREQ(element.text().data(), "click me");
}

//@Test
TEST_F(ElementFindingTest, testFindingALinkByXpathUsingContainsKeywordShouldWork) {
  webDriver().get(pages().nestedPage);
  WebElement element = webDriver().findElement(By::xpath("//a[contains(.,'hello world')]"));
  ASSERT_TRUE(element.text().find("hello world") != std::string::npos);
}

// By::xpath negative

//@Test(expected = NoSuchElementException.class)
TEST_F(ElementFindingTest, testShouldThrowAnExceptionWhenThereIsNoLinkToClick) {
  webDriver().get(pages().xhtmlTestPage);
ASSERT_THROW(webDriver().findElement(By::xpath("//a[@id='Not here']")), NoSuchElementException);
}

//@Ignore({ANDROID, IPHONE, OPERA, OPERA_MOBILE, MARIONETTE})
//@Test(expected = InvalidSelectorException.class)
TEST_F(ElementFindingTest, testShouldThrowInvalidSelectorExceptionWhenXPathIsSyntacticallyInvalidInDriverFindElement) {
  webDriver().get(pages().formPage);
  ASSERT_THROW(webDriver().findElement(By::xpath("this][isnot][valid")), InvalidSelectorException);
}

//@Ignore({ANDROID, IPHONE, OPERA, OPERA_MOBILE, MARIONETTE})
//@Test(expected = InvalidSelectorException.class)
TEST_F(ElementFindingTest, testShouldThrowInvalidSelectorExceptionWhenXPathIsSyntacticallyInvalidInDriverFindElements) {
 // assumeFalse("Ignoring xpath error test in IE6", TestUtilities.isIe6(driver));

  webDriver().get(pages().formPage);
  ASSERT_THROW(webDriver().findElements(By::xpath("this][isnot][valid")), InvalidSelectorException);
}

//@Ignore({ANDROID, IPHONE, OPERA, OPERA_MOBILE, MARIONETTE})
//@Test(expected = InvalidSelectorException.class)
TEST_F(ElementFindingTest, testShouldThrowInvalidSelectorExceptionWhenXPathIsSyntacticallyInvalidInElementFindElement) {
  webDriver().get(pages().formPage);
  WebElement body = webDriver().findElement(By::tagName("body"));
  ASSERT_THROW(body.findElement(By::xpath("this][isnot][valid")), InvalidSelectorException);
}

//@Ignore({ANDROID, IPHONE, OPERA, OPERA_MOBILE, MARIONETTE})
//@Test(expected = InvalidSelectorException.class)
TEST_F(ElementFindingTest, testShouldThrowInvalidSelectorExceptionWhenXPathIsSyntacticallyInvalidInElementFindElements) {
 // assumeFalse("Ignoring xpath error test in IE6", TestUtilities.isIe6(driver));

  webDriver().get(pages().formPage);
  WebElement body = webDriver().findElement(By::tagName("body"));
  ASSERT_THROW(body.findElements(By::xpath("this][isnot][valid")), InvalidSelectorException);
}

//@Ignore({ANDROID, IPHONE, OPERA, OPERA_MOBILE, MARIONETTE})
//@Test(expected = InvalidSelectorException.class)
TEST_F(ElementFindingTest, testShouldThrowInvalidSelectorExceptionWhenXPathReturnsWrongTypeInDriverFindElement) {
  webDriver().get(pages().formPage);
  ASSERT_THROW(webDriver().findElement(By::xpath("count(//input)")), InvalidSelectorException);
}

//@Ignore({ANDROID, IPHONE, OPERA, OPERA_MOBILE, MARIONETTE})
//@Test(expected = InvalidSelectorException.class)
TEST_F(ElementFindingTest, testShouldThrowInvalidSelectorExceptionWhenXPathReturnsWrongTypeInDriverFindElements) {
 // assumeFalse("Ignoring xpath error test in IE6", TestUtilities.isIe6(driver));

  webDriver().get(pages().formPage);
  ASSERT_THROW(webDriver().findElements(By::xpath("count(//input)")), InvalidSelectorException);
}

//@Ignore({ANDROID, IPHONE, OPERA, OPERA_MOBILE, MARIONETTE})
//@Test(expected = InvalidSelectorException.class)
TEST_F(ElementFindingTest, testShouldThrowInvalidSelectorExceptionWhenXPathReturnsWrongTypeInElementFindElement) {
  webDriver().get(pages().formPage);

  WebElement body = webDriver().findElement(By::tagName("body"));
  ASSERT_THROW(body.findElement(By::xpath("count(//input)")), InvalidSelectorException);
}

//@Ignore({ANDROID, IPHONE, OPERA, OPERA_MOBILE, MARIONETTE})
//@Test(expected = InvalidSelectorException.class)
TEST_F(ElementFindingTest, testShouldThrowInvalidSelectorExceptionWhenXPathReturnsWrongTypeInElementFindElements) {
 // assumeFalse("Ignoring xpath error test in IE6", TestUtilities.isIe6(driver));

  webDriver().get(pages().formPage);
  WebElement body = webDriver().findElement(By::tagName("body"));
  ASSERT_THROW(body.findElements(By::xpath("count(//input)")), InvalidSelectorException);
}

// By::cssSelector positive

//@Test
TEST_F(ElementFindingTest, testShouldBeAbleToFindASingleElementByCssSelector) {
  webDriver().get(pages().xhtmlTestPage);
  WebElement element = webDriver().findElement(By::cssSelector("div.content"));
  std::string tagName = element.tagName();
  std::transform(tagName.begin(), tagName.end(), tagName.begin(), ::tolower);
  ASSERT_STREQ(tagName.data(), "div");
  ASSERT_STREQ(element.getAttribute("class").data(), "content");
}

//@Test
TEST_F(ElementFindingTest, testShouldBeAbleToFindMultipleElementsByCssSelector) {
  webDriver().get(pages().xhtmlTestPage);
  WebElements elements = webDriver().findElements(By::cssSelector("p"));
  ASSERT_GT(elements.size(), 1);
}

//@Test
TEST_F(ElementFindingTest, testShouldBeAbleToFindASingleElementByCompoundCssSelector) {
  webDriver().get(pages().xhtmlTestPage);
  WebElement element = webDriver().findElement(By::cssSelector("div.extraDiv, div.content"));
  std::string tagName = element.tagName();
  std::transform(tagName.begin(), tagName.end(), tagName.begin(), ::tolower);
  ASSERT_STREQ(tagName.data(), "div");
  ASSERT_STREQ(element.getAttribute("class").data(), "content");
}

//@Test
TEST_F(ElementFindingTest, testShouldBeAbleToFindMultipleElementsByCompoundCssSelector) {
  webDriver().get(pages().xhtmlTestPage);
  WebElements elements = webDriver().findElements(By::cssSelector("div.extraDiv, div.content"));
  ASSERT_GT(elements.size(), 1);
  ASSERT_STREQ(elements[0].getAttribute("class").data(), "content");
  ASSERT_STREQ(elements[1].getAttribute("class").data(), "extraDiv");
}

//@Test
//@Ignore(value = {IE}, reason = "IE supports only short version option[selected]")
TEST_F(ElementFindingTest, testShouldBeAbleToFindAnElementByBooleanAttributeUsingCssSelector) {
  webDriver().get(whereIs("locators_tests/boolean_attribute_selected.html"));
  WebElement element = webDriver().findElement(By::cssSelector("option[selected='selected']"));
  ASSERT_STREQ(element.getAttribute("value").data(), "two");
}

//@Test
TEST_F(ElementFindingTest, testShouldBeAbleToFindAnElementByBooleanAttributeUsingShortCssSelector) {
  webDriver().get(whereIs("locators_tests/boolean_attribute_selected.html"));
  WebElement element = webDriver().findElement(By::cssSelector("option[selected]"));
  ASSERT_STREQ(element.getAttribute("value").data(), "two");
}

//@Test
TEST_F(ElementFindingTest, testShouldBeAbleToFindAnElementByBooleanAttributeUsingShortCssSelectorOnHtml4Page) {
  webDriver().get(whereIs("locators_tests/boolean_attribute_selected_html4.html"));
  WebElement element = webDriver().findElement(By::cssSelector("option[selected]"));
  ASSERT_STREQ(element.getAttribute("value").data(), "two");
}

// By::cssSelector negative

//@Test(expected = NoSuchElementException.class)
TEST_F(ElementFindingTest, testShouldNotFindElementByCssSelectorWhenThereIsNoSuchElement) {
  webDriver().get(pages().xhtmlTestPage);
  ASSERT_THROW(webDriver().findElement(By::cssSelector(".there-is-no-such-class")), NoSuchElementException);
}

TEST_F(ElementFindingTest, testShouldNotFindElementsByCssSelectorWhenThereIsNoSuchElement) {
  webDriver().get(pages().xhtmlTestPage);
  WebElements elements = webDriver().findElements(By::cssSelector(".there-is-no-such-class"));
  ASSERT_EQ(elements.size(), 0);
}

//@Ignore(value = {CHROME}, reason = "Throws WebDriverException")
//@Test(expected = NoSuchElementException.class)
/*TEST_F(ElementFindingTest, testFindingASingleElementByEmptyCssSelectorShouldThrow) {
  webDriver().get(pages().xhtmlTestPage);
  ASSERT_THROW(webDriver().findElement(By::cssSelector("")), NoSuchElementException);
}*/

//@Ignore(value = {CHROME, OPERA, OPERA_MOBILE},
//        reason = "Chrome: throws WebDriverException")
//@Test(expected = NoSuchElementException.class)
/*TEST_F(ElementFindingTest, testFindingMultipleElementsByEmptyCssSelectorShouldThrow) {
  webDriver().get(pages().xhtmlTestPage);
  ASSERT_THROW(webDriver().findElements(By::cssSelector("")), NoSuchElementException);
}*/

//@Ignore(value = {CHROME}, reason = "Throws InvalidElementStateException")
//@Test(expected = NoSuchElementException.class)
/*
TEST_F(ElementFindingTest, testFindingASingleElementByInvalidCssSelectorShouldThrow) {
  webDriver().get(pages().xhtmlTestPage);
  ASSERT_THROW(webDriver().findElement(By::cssSelector("//a/b/c[@id='1']")), NoSuchElementException);
}
*/

//@Ignore(value = {CHROME, OPERA, OPERA_MOBILE},
//        reason = "Chrome: throws InvalidElementStateException")
//@Test(expected = NoSuchElementException.class)
/*
TEST_F(ElementFindingTest, testFindingMultipleElementsByInvalidCssSelectorShouldThrow) {
//  assumeFalse("Ignoring test for lack of error in CSS in IE6", TestUtilities.isIe6(driver));
  webDriver().get(pages().xhtmlTestPage);
  ASSERT_THROW(webDriver().findElements(By::cssSelector("//a/b/c[@id='1']")), NoSuchElementException);
}
*/

// By::linkText positive

//@Test
TEST_F(ElementFindingTest, testShouldBeAbleToFindALinkByText) {
  webDriver().get(pages().xhtmlTestPage);
  WebElement link = webDriver().findElement(By::linkText("click me"));
  ASSERT_STREQ(link.text().data(), "click me");
}

//@Test
TEST_F(ElementFindingTest, testShouldBeAbleToFindMultipleLinksByText) {
  webDriver().get(pages().xhtmlTestPage);
  WebElements elements = webDriver().findElements(By::linkText("click me"));
  ASSERT_EQ(elements.size(), 2);
}

//@Test
TEST_F(ElementFindingTest, testShouldFindElementByLinkTextContainingEqualsSign) {
  webDriver().get(pages().xhtmlTestPage);
  WebElement element = webDriver().findElement(By::linkText("Link=equalssign"));
  ASSERT_STREQ(element.getAttribute("id").data(), "linkWithEqualsSign");
}

//@Test
TEST_F(ElementFindingTest, testShouldFindMultipleElementsByLinkTextContainingEqualsSign) {
  webDriver().get(pages().xhtmlTestPage);
  WebElements elements = webDriver().findElements(By::linkText("Link=equalssign"));
  ASSERT_EQ(1, elements.size());
  ASSERT_STREQ(elements[0].getAttribute("id").data(), "linkWithEqualsSign");
}

//@Test
//@Ignore({OPERA, MARIONETTE})
TEST_F(ElementFindingTest, findsByLinkTextOnXhtmlPage) {
//  assumeFalse("Old IE doesn't render XHTML pages(). don't try loading XHTML pages().in it",
//              isOldIe(driver));

  webDriver().get(whereIs("actualXhtmlPage.xhtml"));
  const std::string linkText = "Foo";
  WebElement element = webDriver().findElement(By::linkText(linkText));
  ASSERT_EQ(element.text(), linkText);
}

//@Ignore({REMOTE})
//@Test
TEST_F(ElementFindingTest, testLinkWithFormattingTags) {
  webDriver().get(pages().simpleTestPage);
  WebElement elem = webDriver().findElement(By::id("links"));

  WebElement res = elem.findElement(By::partialLinkText("link with formatting tags"));
  ASSERT_STREQ(res.text().data(), "link with formatting tags");
}

//@Test
//@Ignore(MARIONETTE)
TEST_F(ElementFindingTest, testDriverCanGetLinkByLinkTestIgnoringTrailingWhitespace) {
  webDriver().get(pages().simpleTestPage);
  WebElement link = webDriver().findElement(By::linkText("link with trailing space"));
  ASSERT_STREQ(link.getAttribute("id").data(), "linkWithTrailingSpace");
  ASSERT_STREQ(link.text().data(), "link with trailing space");
}

// By::linkText negative

//@Test(expected = NoSuchElementException.class)
TEST_F(ElementFindingTest, testShouldNotBeAbleToLocateByLinkTextASingleElementThatDoesNotExist) {
  webDriver().get(pages().xhtmlTestPage);
  ASSERT_THROW(webDriver().findElement(By::linkText("Not here either")), NoSuchElementException);
}

//@Test
TEST_F(ElementFindingTest, testShouldNotBeAbleToLocateByLinkTextMultipleElementsThatDoNotExist) {
  webDriver().get(pages().xhtmlTestPage);
  WebElements elements = webDriver().findElements(By::linkText("Not here either"));
  ASSERT_EQ(elements.size(), 0);
}

// By::partialLinkText positive

//@Test
TEST_F(ElementFindingTest, testShouldBeAbleToFindMultipleElementsByPartialLinkText) {
  webDriver().get(pages().xhtmlTestPage);
  WebElements elements = webDriver().findElements(By::partialLinkText("ick me"));
  ASSERT_EQ(elements.size(), 2);
}

//@Test
TEST_F(ElementFindingTest, testShouldBeAbleToFindASingleElementByPartialLinkText) {
  webDriver().get(pages().xhtmlTestPage);
  WebElement element = webDriver().findElement(By::partialLinkText("anon"));
  ASSERT_TRUE(element.text().find("anon") != std::string::npos);
}

//@Test
TEST_F(ElementFindingTest, testShouldFindElementByPartialLinkTextContainingEqualsSign) {
  webDriver().get(pages().xhtmlTestPage);
  WebElement element = webDriver().findElement(By::partialLinkText("Link="));
  ASSERT_STREQ(element.getAttribute("id").data(), "linkWithEqualsSign");
}

//@Test
TEST_F(ElementFindingTest, testShouldFindMultipleElementsByPartialLinkTextContainingEqualsSign) {
  webDriver().get(pages().xhtmlTestPage);
  WebElements elements = webDriver().findElements(By::partialLinkText("Link="));
  ASSERT_EQ(elements.size(), 1);
  ASSERT_STREQ(elements[0].getAttribute("id").data(), "linkWithEqualsSign");
}

// Misc tests

//@Test
TEST_F(ElementFindingTest, testDriverShouldBeAbleToFindElementsAfterLoadingMoreThanOnePageAtATime) {
  webDriver().get(pages().formPage);
  webDriver().get(pages().xhtmlTestPage);
  WebElement link = webDriver().findElement(By::linkText("click me"));
  ASSERT_STREQ(link.text().data(), "click me");
}

// You don't want to ask why this is here
//@Test
TEST_F(ElementFindingTest, testWhenFindingByNameShouldNotReturnById) {
  webDriver().get(pages().formPage);

  WebElement element = webDriver().findElement(By::name("id-name1"));
  ASSERT_STREQ(element.getAttribute("value").data(), "name");

  element = webDriver().findElement(By::id("id-name1"));
  ASSERT_STREQ(element.getAttribute("value").data(), "id");

  element = webDriver().findElement(By::name("id-name2"));
  ASSERT_STREQ(element.getAttribute("value").data(), "name");

  element = webDriver().findElement(By::id("id-name2"));
  ASSERT_STREQ(element.getAttribute("value").data(), "id");
}

//@Test
TEST_F(ElementFindingTest, testShouldBeAbleToFindAHiddenElementsByName) {
  webDriver().get(pages().formPage);
  WebElement element = webDriver().findElement(By::name("hidden"));
  ASSERT_STREQ(element.getAttribute("name").data(), "hidden");
}

//@Test(expected = NoSuchElementException.class)
TEST_F(ElementFindingTest, testShouldNotBeAbleToFindAnElementOnABlankPage) {
  webDriver().get("about:blank");
  ASSERT_THROW(webDriver().findElement(By::tagName("a")), NoSuchElementException);
}

//@Ignore({IPHONE})
//@NeedsFreshDriver
//@Test(expected = NoSuchElementException.class)
TEST_F(ElementFindingTest, testShouldNotBeAbleToLocateASingleElementOnABlankPage) {
  // Note we're on the default start page for the browser at this point.
  ASSERT_THROW(webDriver().findElement(By::id("nonExistantButton")), NoSuchElementException);
}

//@Ignore(value = {ANDROID, OPERA, OPERA_MOBILE, MARIONETTE}, reason = "Just not working")
//@Test
TEST_F(ElementFindingTest, testAnElementFoundInADifferentFrameIsStale) {
  webDriver().get(pages().missedJsReferencePage);
  webDriver().switchTo().frame("inner");
  WebElement element = webDriver().findElement(By::id("oneline"));
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
TEST_F(ElementFindingTest, testAnElementFoundInADifferentFrameViaJsCanBeUsed) {
  webDriver().get(pages().missedJsReferencePage);

  try {
    webDriver().switchTo().frame("inner");
    WebElement first = webDriver().findElement(By::id("oneline"));

    webDriver().switchTo().defaultContent();
    WebElement element = webDriver().executeScript(
        "return frames[0].document.getElementById('oneline');");


    webDriver().switchTo().frame("inner");

    WebElement second = webDriver().findElement(By::id("oneline"));

    ASSERT_EQ(first, element);
    ASSERT_EQ(second, element);
  } catch (...) {
    webDriver().switchTo().defaultContent();
    throw;
  }
  webDriver().switchTo().defaultContent();

}

