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

class ClickScrollingTest : public SeleniumTestCase
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

protected:
  long getScrollTop() {
    ScriptResult res = webDriver().executeScript("return document.body.scrollTop;");
    return (res.isBool())
        ? res.asBool()
        : 0L;
  }
};







TEST_F(ClickScrollingTest, testClickingOnAnchorScrollsPage) {
  std::stringstream scrollScript;
  scrollScript << "var pageY;";
  scrollScript << "if (typeof(window.pageYOffset) == 'number') {";
  scrollScript << "  pageY = window.pageYOffset;";
  scrollScript << "} else {";
  scrollScript << "  pageY = document.documentElement.scrollTop;";
  scrollScript << "}";
  scrollScript << "return pageY;";

  webDriver().get(pages().macbethPage);

  webDriver().findElement(By::partialLinkText("last speech")).click();

  ScriptResult res = webDriver()
      .executeScript(scrollScript.str());

  long yOffset = res.asLargestInt();
  // Focusing on to click, but not actually following,
  // the link will scroll it in to view, which is a few pixels further than 0
  EXPECT_GT(yOffset, 300L) << "Did not scroll";
}


TEST_F(ClickScrollingTest, testShouldScrollToClickOnAnElementHiddenByOverflow) {
  std::string url = whereIs("click_out_of_bounds_overflow.html");
  webDriver().get(url);

  WebElement link = webDriver().findElement(By::id("link"));
  try {
    link.click();
  } catch (MoveTargetOutOfBoundsException& e) {
    FAIL() << "Should not be out of bounds: " <<  e.what();
  }
}



TEST_F(ClickScrollingTest, testShouldBeAbleToClickOnAnElementHiddenByOverflow) {
  webDriver().get(whereIs("scroll.html"));

  WebElement link = webDriver().findElement(By::id("line8"));
  // This used to throw a MoveTargetOutOfBoundsException - we don't expect it to
  link.click();
  EXPECT_STREQ("line8", webDriver().findElement(By::id("clicked")).text().data());
}


//@JavascriptEnabled
//@Ignore(value = {CHROME, IPHONE},
//        reason = "Chrome: failed, iPhone: untested, Firefox: failed with native events")
//@Test
/*
TEST_F(ClickScrollingTest, testShouldBeAbleToClickOnAnElementHiddenByDoubleOverflow) {
  webDriver().get(whereIs("scrolling_tests/page_with_double_overflow_auto.html"));

  try {
    webDriver().findElement(By::id("link")).click();
  }
  catch (WebDriverException& e)
  {
    LOG("got exception: " << e.what());
  }
  wait().until(TitleIs("Clicked Successfully!"));
}
*/



TEST_F(ClickScrollingTest, testShouldBeAbleToClickOnAnElementHiddenByYOverflow) {
  webDriver().get(whereIs("scrolling_tests/page_with_y_overflow_auto.html"));

  webDriver().findElement(By::id("link")).click();
  wait().until(TitleIs("Clicked Successfully!"));
}




TEST_F(ClickScrollingTest, testShouldNotScrollOverflowElementsWhichAreVisible) {
  webDriver().get(whereIs("scroll2.html"));
  WebElement list = webDriver().findElement(By::tagName("ul"));
  WebElement item = list.findElement(By::id("desired"));
  item.click();
  ScriptResult res = webDriver().executeScript("return arguments[0].scrollTop;", {list});
  long yOffset = res.asLargestInt();
  EXPECT_EQ(0, yOffset) << "Should not have scrolled";
}



TEST_F(ClickScrollingTest, testShouldNotScrollIfAlreadyScrolledAndElementIsInView) {
  webDriver().get(whereIs("scroll3.html"));
  webDriver().findElement(By::id("button2")).click();
  long scrollTop = getScrollTop();
  webDriver().findElement(By::id("button1")).click();
  EXPECT_EQ(scrollTop, getScrollTop());
}



TEST_F(ClickScrollingTest, testShouldBeAbleToClickRadioButtonScrolledIntoView) {
  webDriver().get(whereIs("scroll4.html"));
  webDriver().findElement(By::id("radio")).click();
  // If we don't throw, we're good
}



TEST_F(ClickScrollingTest, testShouldScrollOverflowElementsIfClickPointIsOutOfViewButElementIsInView) {
  webDriver().get(whereIs("scroll5.html"));
  webDriver().findElement(By::id("inner")).click();
  EXPECT_STREQ("clicked", webDriver().findElement(By::id("clicked")).text().data());
}



TEST_F(ClickScrollingTest, testShouldBeAbleToClickElementInAFrameThatIsOutOfView) {
    webDriver().get(whereIs("scrolling_tests/page_with_frame_out_of_view.html"));
    webDriver().switchTo().frame("frame");
    WebElement element = webDriver().findElement(By::name("checkbox"));
    element.click();
    EXPECT_TRUE(element.isSelected());
}



TEST_F(ClickScrollingTest, testShouldBeAbleToClickElementThatIsOutOfViewInAFrame) {
    webDriver().get(whereIs("scrolling_tests/page_with_scrolling_frame.html"));
    webDriver().switchTo().frame("scrolling_frame");
    WebElement element = webDriver().findElement(By::name("scroll_checkbox"));
    element.click();
    EXPECT_TRUE(element.isSelected());
}



TEST_F(ClickScrollingTest, testShouldNotBeAbleToClickElementThatIsOutOfViewInANonScrollableFrame) {
//  try {
    webDriver().get(whereIs("scrolling_tests/page_with_non_scrolling_frame.html"));
    webDriver().switchTo().frame("scrolling_frame");
    WebElement element = webDriver().findElement(By::name("scroll_checkbox"));
    element.click();
//  } finally {
//    webDriver().switchTo().defaultContent();
//  }
}



TEST_F(ClickScrollingTest, testShouldBeAbleToClickElementThatIsOutOfViewInAFrameThatIsOutOfView) {
//  try {
    webDriver().get(whereIs("scrolling_tests/page_with_scrolling_frame_out_of_view.html"));
    webDriver().switchTo().frame("scrolling_frame");
    WebElement element = webDriver().findElement(By::name("scroll_checkbox"));
    element.click();
    EXPECT_TRUE(element.isSelected());
//  } finally {
//    webDriver().switchTo().defaultContent();
//  }
}



TEST_F(ClickScrollingTest, testShouldBeAbleToClickElementThatIsOutOfViewInANestedFrame) {
//  try {
    webDriver().get(whereIs("scrolling_tests/page_with_nested_scrolling_frames.html"));
    webDriver().switchTo().frame("scrolling_frame");
    webDriver().switchTo().frame("nested_scrolling_frame");
    WebElement element = webDriver().findElement(By::name("scroll_checkbox"));
    element.click();
    EXPECT_TRUE(element.isSelected());
//  } finally {
//    webDriver().switchTo().defaultContent();
//  }
}



TEST_F(ClickScrollingTest, testShouldBeAbleToClickElementThatIsOutOfViewInANestedFrameThatIsOutOfView) {
//  try {
    webDriver().get(whereIs("scrolling_tests/page_with_nested_scrolling_frames_out_of_view.html"));
    webDriver().switchTo().frame("scrolling_frame");
    webDriver().switchTo().frame("nested_scrolling_frame");
    WebElement element = webDriver().findElement(By::name("scroll_checkbox"));
    element.click();
    EXPECT_TRUE(element.isSelected());
//  } finally {
//    webDriver().switchTo().defaultContent();
//  }
}



TEST_F(ClickScrollingTest, testShouldNotScrollWhenGettingElementSize) {
  webDriver().get(whereIs("scroll3.html"));
  long scrollTop = getScrollTop();
  webDriver().findElement(By::id("button1")).size();
  EXPECT_EQ(scrollTop, getScrollTop());
}





TEST_F(ClickScrollingTest, testShouldBeAbleToClickElementInATallFrame) {
//  try {
    webDriver().get(whereIs("scrolling_tests/page_with_tall_frame.html"));
    webDriver().switchTo().frame("tall_frame");
    WebElement element = webDriver().findElement(By::name("checkbox"));
    element.click();
    EXPECT_TRUE(element.isSelected());
//  } finally {
//    webDriver().switchTo().defaultContent();
//  }
}

