/*
 * alerts_test.cpp
 *
 *  Created on: Sep 20, 2014
 *      Author: speedpat
 */

#include <list>

#include "selenium/selenium.hpp"
#include "support/selenium_testcase.hpp"
#include "support/expected_test_conditions.hpp"


using namespace selenium;

class ClickTest : public SeleniumTestCase
{
public:

  virtual void SetUp()
  {
    SeleniumTestCase::SetUp();
    webDriver().get(pages().clicksPage);

  }

  virtual void TearDown()
  {
    SeleniumTestCase::TearDown();
    webDriver().switchTo().defaultContent();
  }

};








TEST_F(ClickTest, testCanClickOnALinkAndFollowIt) {
  webDriver().findElement(By::id("normal")).click();

  wait().until(TitleIs("XHTML Test Page"));
}



TEST_F(ClickTest, testCanClickOnALinkThatOverflowsAndFollowIt) {
  webDriver().findElement(By::id("overflowLink")).click();

  wait().until(TitleIs("XHTML Test Page"));
}




TEST_F(ClickTest, testCanClickOnAnAnchorAndNotReloadThePage) {
  webDriver().executeScript("document.latch = true");

  webDriver().findElement(By::id("anchor")).click();

  ScriptResult res = webDriver().executeScript("return document.latch");

  bool samePage = res.asBool();
  EXPECT_EQ(true, samePage) << "Latch was reset";
}



TEST_F(ClickTest, testCanClickOnALinkThatUpdatesAnotherFrame) {
  webDriver().switchTo().frame("source");

  webDriver().findElement(By::id("otherframe")).click();
  webDriver().switchTo().defaultContent();
  webDriver().switchTo().frame("target");

  wait().until(PageSourceToContain("Hello WebDriver"));
}




TEST_F(ClickTest, testElementsFoundByJsCanLoadUpdatesInAnotherFrame) {
  webDriver().switchTo().frame("source");

  WebElement toClick = webDriver().executeScript(
      "return document.getElementById('otherframe');"
  );
  toClick.click();
  webDriver().switchTo().defaultContent();
  webDriver().switchTo().frame("target");

  wait().until(PageSourceToContain("Hello WebDriver"));
}



TEST_F(ClickTest, testJsLocatedElementsCanUpdateFramesIfFoundSomehowElse) {
  webDriver().switchTo().frame("source");

  // Prime the cache of elements
  webDriver().findElement(By::id("otherframe"));

  // This _should_ return the same element
  WebElement toClick = webDriver().executeScript(
      "return document.getElementById('otherframe');"
  );
  toClick.click();
  webDriver().switchTo().defaultContent();
  webDriver().switchTo().frame("target");

  wait().until(PageSourceToContain("Hello WebDriver"));
}



TEST_F(ClickTest, testCanClickOnAnElementWithTopSetToANegativeNumber) {
  std::string page = whereIs("styledPage.html");
  webDriver().get(page);
  WebElement searchBox = webDriver().findElement(By::name("searchBox"));
//  searchBox.sendKeys("Cheese");
  webDriver().findElement(By::name("btn")).click();

  const std::string log = webDriver().findElement(By::id("log")).text();
  EXPECT_STREQ("click", log.data());
}



/*TEST_F(ClickTest, testShouldClickOnFirstBoundingClientRectWithNonZeroSize) {
  webDriver().findElement(By::id("twoClientRects")).click();
  wait().until(TitleIs("XHTML Test Page"));
}*/




/*TEST_F(ClickTest, testShouldSetRelatedTargetForMouseOver) {
  webDriver().get(pages().javascriptPage);

  webDriver().findElement(By::id("movable")).click();

  const std::string log = webDriver().findElement(By::id("result")).text();

  // Note: It is not guaranteed that the relatedTarget property of the mouseover
  // event will be the parent, when using native events. Only check that the mouse
  // has moved to this element, not that the parent element was the related target.
//  if (isNativeEventsEnabled(webDriver())) {
//    EXPECT_TRUE(log.startsWith("parent matches?"));
//  } else {
    EXPECT_STREQ("parent matches? true", log.data());
//  }
}*/






/*
TEST_F(ClickTest, testShouldOnlyFollowHrefOnce) {
  webDriver().get(pages().clicksPage);
  std::string current = webDriver().currentWindowHandle();
  std::vector<std::string> currentWindowHandles = webDriver().windowHandles();

//  try {
    webDriver().findElement(By::id("new-window")).click();
    std::string newWindowHandle = wait().until(NewWindowIsOpened(currentWindowHandles));
    webDriver().switchTo().window(newWindowHandle);
    webDriver().close();
//  } finally {
//    webDriver().switchTo().window(current);
//  }
}
*/




TEST_F(ClickTest, testClickingLabelShouldSetCheckbox) {
  webDriver().get(pages().formPage);

  webDriver().findElement(By::id("label-for-checkbox-with-label")).click();

  EXPECT_TRUE(
      webDriver().findElement(By::id("checkbox-with-label")).isSelected())
      << "Should be selected";
}


TEST_F(ClickTest, testCanClickOnALinkWithEnclosedImage) {
  webDriver().findElement(By::id("link-with-enclosed-image")).click();

  wait().until(TitleIs("XHTML Test Page"));
}


TEST_F(ClickTest, testCanClickOnAnImageEnclosedInALink) {
  webDriver().findElement(By::id("link-with-enclosed-image")).findElement(By::tagName("img")).click();

  wait().until(TitleIs("XHTML Test Page"));
}


TEST_F(ClickTest, testCanClickOnALinkThatContainsTextWrappedInASpan) {
  webDriver().findElement(By::id("link-with-enclosed-span")).click();

  wait().until(TitleIs("XHTML Test Page"));
}


TEST_F(ClickTest, testCanClickOnALinkThatContainsEmbeddedBlockElements) {
  webDriver().findElement(By::id("embeddedBlock")).click();
  wait().until(TitleIs("XHTML Test Page"));
}


TEST_F(ClickTest, testCanClickOnAnElementEnclosedInALink) {
  webDriver().findElement(By::id("link-with-enclosed-span")).findElement(By::tagName("span")).click();

  wait().until(TitleIs("XHTML Test Page"));
}

// See http://code.google.com/p/selenium/issues/attachmentText?id=2700

TEST_F(ClickTest, testShouldBeAbleToClickOnAnElementInTheViewport) {
 std::string url = whereIs("click_out_of_bounds.html");

  webDriver().get(url);
  WebElement button = webDriver().findElement(By::id("button"));

  try {
    button.click();
  } catch (MoveTargetOutOfBoundsException& e) {
    FAIL() << "Should not be out of bounds: " << e.what();
  }
}


TEST_F(ClickTest, testClicksASurroundingStrongTag) {
  webDriver().get(whereIs("ClickTest_testClicksASurroundingStrongTag.html"));
  webDriver().findElement(By::tagName("a")).click();
  wait().until(TitleIs("XHTML Test Page"));
}



TEST_F(ClickTest, testCanClickAnImageMapArea) {
  webDriver().get(whereIs("click_tests/google_map.html"));
  webDriver().findElement(By::id("rectG")).click();
  wait().until(TitleIs("Target Page 1"));

  webDriver().get(whereIs("click_tests/google_map.html"));
  webDriver().findElement(By::id("circleO")).click();
  wait().until(TitleIs("Target Page 2"));

  webDriver().get(whereIs("click_tests/google_map.html"));
  webDriver().findElement(By::id("polyLE")).click();
  wait().until(TitleIs("Target Page 3"));
}



TEST_F(ClickTest, testShouldBeAbleToClickOnAnElementGreaterThanTwoViewports) {
  std::string url = whereIs("click_too_big.html");
  webDriver().get(url);

  WebElement element = webDriver().findElement(By::id("click"));

  element.click();

  wait().until(TitleIs("clicks"));
}




TEST_F(ClickTest, testShouldBeAbleToClickOnRTLLanguageLink) {
  std::string url = whereIs("click_rtl.html");
  webDriver().get(url);

  WebElement element = webDriver().findElement(By::id("ar_link"));
  element.click();

  wait().until(TitleIs("clicks"));
}



TEST_F(ClickTest, testShouldBeAbleToClickOnLinkInAbsolutelyPositionedFooter) {
  std::string url = whereIs("fixedFooterNoScroll.html");
  webDriver().get(url);

  WebElement element = webDriver().findElement(By::id("link"));
  element.click();

  wait().until(TitleIs("XHTML Test Page"));
}



TEST_F(ClickTest, testShouldBeAbleToClickOnLinkInAbsolutelyPositionedFooterInQuirksMode) {
  std::string url = whereIs("fixedFooterNoScrollQuirksMode.html");
  webDriver().get(url);

  WebElement element = webDriver().findElement(By::id("link"));
  element.click();

  wait().until(TitleIs("XHTML Test Page"));
}



TEST_F(ClickTest, testShouldBeAbleToClickOnLinksWithNoHrefAttribute) {
  webDriver().get(pages().javascriptPage);

  WebElement element = webDriver().findElement(By::linkText("No href"));
  element.click();

  wait().until(TitleIs("Changed"));
}





TEST_F(ClickTest, testShouldBeAbleToClickOnALinkThatWrapsToTheNextLine) {
  webDriver().get(whereIs("click_tests/link_that_wraps.html"));

  webDriver().findElement(By::id("link")).click();

  wait().until(TitleIs("Submitted Successfully!"));
}





TEST_F(ClickTest, testShouldBeAbleToClickOnASpanThatWrapsToTheNextLine) {
  webDriver().get(whereIs("click_tests/span_that_wraps.html"));

  webDriver().findElement(By::id("span")).click();

  wait().until(TitleIs("Submitted Successfully!"));
}

