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

class FrameSwitchingTest : public SeleniumTestCase
{
public:

  virtual void SetUp()
  {
    SeleniumTestCase::SetUp();

  }

  virtual void TearDown()
  {
    SeleniumTestCase::TearDown();
    webDriver().switchTo().defaultContent();
  }


  std::string getTextOfGreetingElement() {
    return wait().until(PresenceOfElementLocated(By::id("greeting"))).text();
  }

  void assertFrameNotPresent(std::string locator) {
    webDriver().switchTo().defaultContent();
    wait().until(Not<FrameToBeAvailableAndSwitchToIt>(FrameToBeAvailableAndSwitchToIt(locator)));
    webDriver().switchTo().defaultContent();
  }
};


// ----------------------------------------------------------------------------------------------
//
// Tests that WebDriver doesn't do anything fishy when it navigates to a page with frames.
//
// ----------------------------------------------------------------------------------------------
//@Test
//@Ignore(MARIONETTE)
TEST_F(FrameSwitchingTest, testShouldAlwaysFocusOnTheTopMostFrameAfterANavigationEvent) {
  webDriver().get(pages().framesetPage);
  webDriver().findElement(By::tagName("frameset")); // Test passes if this does not throw.
}

//@Test
TEST_F(FrameSwitchingTest, testShouldNotAutomaticallySwitchFocusToAnIFrameWhenAPageContainingThemIsLoaded) {
  webDriver().get(pages().iframePage);
  webDriver().findElement(By::id("iframe_page_heading"));
}

//@Test(timeout = 10000)
//@NeedsLocalEnvironment(reason = "it hangs at IE9 and event Test.timeout doesn't help")
TEST_F(FrameSwitchingTest, testShouldOpenPageWithBrokenFrameset) {
  webDriver().get(whereIs("framesetPage3.html"));

  WebElement frame1 = webDriver().findElement(By::id("first"));
  webDriver().switchTo().frame(frame1);

  webDriver().switchTo().defaultContent();

  WebElement frame2 = webDriver().findElement(By::id("second"));

  try {
    webDriver().switchTo().frame(frame2);
  } catch (WebDriverException& e) {
    // IE9 can not switch to this broken frame - it has no window.
  }
}

// ----------------------------------------------------------------------------------------------
//
// Tests that WebDriver can switch to frames as expected.
//
// ----------------------------------------------------------------------------------------------
//@Test
//@Ignore(MARIONETTE)
TEST_F(FrameSwitchingTest, testShouldBeAbleToSwitchToAFrameByItsIndex) {
  webDriver().get(pages().framesetPage);
  webDriver().switchTo().frame(1);

  assertThat(equals(webDriver().findElement(By::id("pageNumber")).text(), "2"));
}

//@Test
TEST_F(FrameSwitchingTest, testShouldBeAbleToSwitchToAnIframeByItsIndex) {
  webDriver().get(pages().iframePage);
  webDriver().switchTo().frame(0);

  assertThat(equals(webDriver().findElement(By::name("id-name1")).getAttribute("value"), "name"));
}

//@Test
//@Ignore(MARIONETTE)
TEST_F(FrameSwitchingTest, testShouldBeAbleToSwitchToAFrameByItsName) {
  webDriver().get(pages().framesetPage);
  webDriver().switchTo().frame("fourth");

  assertThat(equals(webDriver().findElement(By::tagName("frame")).getAttribute("name"), "child1"));
}

//@Test
//@Ignore(MARIONETTE)
TEST_F(FrameSwitchingTest, testShouldBeAbleToSwitchToAnIframeByItsName) {
  webDriver().get(pages().iframePage);
  webDriver().switchTo().frame("iframe1-name");

  assertThat(equals(webDriver().findElement(By::name("id-name1")).getAttribute("value"), "name"));
}

//@Test
//@Ignore(MARIONETTE)
TEST_F(FrameSwitchingTest, testShouldBeAbleToSwitchToAFrameByItsID) {
  webDriver().get(pages().framesetPage);
  webDriver().switchTo().frame("fifth");
  assertThat(equals(webDriver().findElement(By::name("windowOne")).text(), "Open new window"));
}

//@Test
TEST_F(FrameSwitchingTest, testShouldBeAbleToSwitchToAnIframeByItsID) {
  webDriver().get(pages().iframePage);
  webDriver().switchTo().frame("iframe1");

  assertThat(equals(webDriver().findElement(By::name("id-name1")).getAttribute("value"), "name"));
}

//@Test
//@Ignore({OPERA, OPERA_MOBILE, MARIONETTE})
TEST_F(FrameSwitchingTest, testShouldBeAbleToSwitchToFrameWithNameContainingDot) {
  webDriver().get(pages().framesetPage);
  webDriver().switchTo().frame("sixth.iframe1");
  assertThat(contains(webDriver().findElement(By::tagName("body")).text(), "Page number 3"));
}

//@Test
TEST_F(FrameSwitchingTest, testShouldBeAbleToSwitchToAFrameUsingAPreviouslyLocatedWebElement) {
  webDriver().get(pages().framesetPage);
  WebElement frame = webDriver().findElement(By::tagName("frame"));
  webDriver().switchTo().frame(frame);

  assertThat(equals(webDriver().findElement(By::id("pageNumber")).text(), "1"));
}

//@Test
TEST_F(FrameSwitchingTest, testShouldBeAbleToSwitchToAnIFrameUsingAPreviouslyLocatedWebElement) {
  webDriver().get(pages().iframePage);
  WebElement frame = webDriver().findElement(By::tagName("iframe"));
  webDriver().switchTo().frame(frame);

  WebElement element = webDriver().findElement(By::name("id-name1"));
  assertThat(equals(element.getAttribute("value"), "name"));
}

//@Test
TEST_F(FrameSwitchingTest, testShouldEnsureElementIsAFrameBeforeSwitching) {
  webDriver().get(pages().framesetPage);
  WebElement frame = webDriver().findElement(By::tagName("frameset"));

  ASSERT_THROW(webDriver().switchTo().frame(frame), NoSuchFrameException);
}

//@Ignore({ANDROID, MARIONETTE})
//@Test
TEST_F(FrameSwitchingTest, testFrameSearchesShouldBeRelativeToTheCurrentlySelectedFrame) {
  webDriver().get(pages().framesetPage);

  webDriver().switchTo().frame("second");
  assertThat(equals(webDriver().findElement(By::id("pageNumber")).text(), "2"));

  ASSERT_THROW(webDriver().switchTo().frame("third"), NoSuchFrameException);

  webDriver().switchTo().defaultContent();
  webDriver().switchTo().frame("third");

  ASSERT_THROW(webDriver().switchTo().frame("second"), NoSuchFrameException);

  webDriver().switchTo().defaultContent();
  webDriver().switchTo().frame("second");
  assertThat(equals(webDriver().findElement(By::id("pageNumber")).text(), "2"));
}

//@Ignore({ANDROID, OPERA, OPERA_MOBILE, MARIONETTE})
//@Test
TEST_F(FrameSwitchingTest, testShouldSelectChildFramesByChainedCalls) {
  webDriver().get(pages().framesetPage);

  webDriver().switchTo().frame("fourth").frame("child2");
  assertThat(equals(webDriver().findElement(By::id("pageNumber")).text(), "11"));
}

//@Ignore({ANDROID, MARIONETTE})
//@Test
TEST_F(FrameSwitchingTest, testShouldThrowFrameNotFoundExceptionLookingUpSubFramesWithSuperFrameNames) {
  webDriver().get(pages().framesetPage);
  webDriver().switchTo().frame("fourth");

  ASSERT_THROW(webDriver().switchTo().frame("second"), NoSuchFrameException);
}

//@Test
TEST_F(FrameSwitchingTest, testShouldThrowAnExceptionWhenAFrameCannotBeFound) {
  webDriver().get(pages().xhtmlTestPage);

  ASSERT_THROW(webDriver().switchTo().frame("Nothing here"), NoSuchFrameException) << "Should not have been able to switch";
}

//@Test
TEST_F(FrameSwitchingTest, testShouldThrowAnExceptionWhenAFrameCannotBeFoundByIndex) {
  webDriver().get(pages().xhtmlTestPage);

  ASSERT_THROW(webDriver().switchTo().frame("27"), NoSuchFrameException) << "Should not have been able to switch";
}

//@Ignore({ANDROID, CHROME, IE, OPERA, OPERA_MOBILE, PHANTOMJS, SAFARI, MARIONETTE})
//@Test
TEST_F(FrameSwitchingTest, testShouldBeAbleToSwitchToParentFrame) {
  webDriver().get(pages().framesetPage);

  webDriver().switchTo().frame("fourth").parentFrame().frame("first");
  assertThat(equals(webDriver().findElement(By::id("pageNumber")).text(), "1"));
}

//@Ignore({ANDROID, CHROME, IE, OPERA, OPERA_MOBILE, PHANTOMJS, SAFARI, MARIONETTE})
//@Test
TEST_F(FrameSwitchingTest, testShouldBeAbleToSwitchToParentFrameFromASecondLevelFrame) {
  webDriver().get(pages().framesetPage);

  webDriver().switchTo().frame("fourth").frame("child1")
      .parentFrame().frame("child2");
  assertThat(equals(webDriver().findElement(By::id("pageNumber")).text(), "11"));
}

//@Ignore({ANDROID, CHROME, IE, OPERA, OPERA_MOBILE, PHANTOMJS, SAFARI, MARIONETTE})
//@Test
TEST_F(FrameSwitchingTest, testSwitchingToParentFrameFromDefaultContextIsNoOp) {
  webDriver().get(pages().xhtmlTestPage);
  webDriver().switchTo().parentFrame();
  assertThat(equals(webDriver().title(), "XHTML Test Page"));
}

//@Ignore({ANDROID, CHROME, IE, OPERA, OPERA_MOBILE, PHANTOMJS, SAFARI, MARIONETTE})
//@Test
TEST_F(FrameSwitchingTest, testShouldBeAbleToSwitchToParentFromAnIframe) {
  webDriver().get(pages().iframePage);
  webDriver().switchTo().frame(0);

  webDriver().switchTo().parentFrame();
  webDriver().findElement(By::id("iframe_page_heading"));
}

// ----------------------------------------------------------------------------------------------
//
// General frame handling behavior tests
//
// ----------------------------------------------------------------------------------------------

//@Ignore({ANDROID, MARIONETTE})
//@Test
TEST_F(FrameSwitchingTest, testShouldContinueToReferToTheSameFrameOnceItHasBeenSelected) {
  webDriver().get(pages().framesetPage);

  webDriver().switchTo().frame(2);
  WebElement checkbox = webDriver().findElement(By::xpath("//input[@name='checky']"));
  checkbox.click();
  checkbox.submit();

  // TODO(simon): this should not be needed, and is only here because IE's submit returns too
  // soon.

  wait().until(ElementTextToBeEqualLocated(By::xpath("//p"), "Success!"));
}

//@Ignore(value = {ANDROID, OPERA, OPERA_MOBILE, MARIONETTE},
//        reason = "Android does not detect that the select frame has disappeared")
//@Test
TEST_F(FrameSwitchingTest, testShouldFocusOnTheReplacementWhenAFrameFollowsALinkToA_TopTargetedPage) {
  webDriver().get(pages().framesetPage);

  webDriver().switchTo().frame(0);
  webDriver().findElement(By::linkText("top")).click();

  std::string expectedTitle = "XHTML Test Page";

  wait().until(TitleIs(expectedTitle));
  wait().until(PresenceOfElementLocated(By::id("only-exists-on-xhtmltest")));
}

//@Ignore(ANDROID)
//@Test
TEST_F(FrameSwitchingTest, testShouldAllowAUserToSwitchFromAnIframeBackToTheMainContentOfThePage) {
  webDriver().get(pages().iframePage);
  webDriver().switchTo().frame(0);

  ASSERT_NO_THROW(
    webDriver().switchTo().defaultContent();
    webDriver().findElement(By::id("iframe_page_heading"))) << "Should have switched back to main content";
}

//@Ignore(ANDROID)
//@Test
TEST_F(FrameSwitchingTest, testShouldAllowTheUserToSwitchToAnIFrameAndRemainFocusedOnIt) {
  webDriver().get(pages().iframePage);
  webDriver().switchTo().frame(0);

  webDriver().findElement(By::id("submitButton")).click();

  assertThat(equals(getTextOfGreetingElement(), "Success!"));
}



//@Ignore({OPERA, ANDROID, OPERA_MOBILE, MARIONETTE})
//@Test
TEST_F(FrameSwitchingTest, testShouldBeAbleToClickInAFrame) {
  webDriver().get(pages().framesetPage);
  webDriver().switchTo().frame("third");

  // This should replace frame "third" ...
  webDriver().findElement(By::id("submitButton")).click();
  // driver should still be focused on frame "third" ...
  assertThat(equals(getTextOfGreetingElement(), "Success!"));
  // Make sure it was really frame "third" which was replaced ...
  webDriver().switchTo().defaultContent().frame("third");
  assertThat(equals(getTextOfGreetingElement(), "Success!"));
}

// See https://code.google.com/p/selenium/issues/detail?id=5237
//@Ignore({OPERA, ANDROID, OPERA_MOBILE})
//@JavascriptEnabled
//@Test
TEST_F(FrameSwitchingTest, testShouldBeAbleToClickInAFrameThatRewritesTopWindowLocation) {
  webDriver().get(whereIs("click_tests/issue5237.html"));
  webDriver().switchTo().frame("search");
  webDriver().findElement(By::id("submit")).click();
  webDriver().switchTo().defaultContent();
  wait().until(TitleIs("Target page for issue 5237"));
}

//@Ignore({OPERA, ANDROID, OPERA_MOBILE, MARIONETTE})
//@Test
TEST_F(FrameSwitchingTest, testShouldBeAbleToClickInASubFrame) {
  webDriver().get(pages().framesetPage);
  webDriver().switchTo().frame("sixth")
      .frame("iframe1");

  // This should replace frame "iframe1" inside frame "sixth" ...
  webDriver().findElement(By::id("submitButton")).click();
  // driver should still be focused on frame "iframe1" inside frame "sixth" ...
  assertThat(equals(getTextOfGreetingElement(), "Success!"));
  // Make sure it was really frame "iframe1" inside frame "sixth" which was replaced ...
  webDriver().switchTo().defaultContent()
      .frame("sixth")
      .frame("iframe1");
  assertThat(equals(webDriver().findElement(By::id("greeting")).text(), "Success!"));
}

//@Ignore(ANDROID)
//@Test
TEST_F(FrameSwitchingTest, testShouldBeAbleToFindElementsInIframesByXPath) {
  webDriver().get(pages().iframePage);

  webDriver().switchTo().frame("iframe1");

  WebElement element = webDriver().findElement(By::xpath("//*[@id = 'changeme']"));

 //assertNotNull(element); TODO speedpat check what can be null here
}

//@Ignore({ANDROID, MARIONETTE})
//@Test
TEST_F(FrameSwitchingTest, testGetCurrentUrl) {
  webDriver().get(pages().framesetPage);

  webDriver().switchTo().frame("second");

  std::string url = whereIs("page/2");
  assertThat(equals(webDriver().currentUrl(), url + "?title=Fish"));

  url = whereIs("iframes.html");
  webDriver().get(pages().iframePage);
  assertThat(equals(webDriver().currentUrl(), url));

  url = whereIs("formPage.html");
  webDriver().switchTo().frame("iframe1");
  assertThat(equals(webDriver().currentUrl(), url));
}

//@Ignore(value = {ANDROID, OPERA, OPERA_MOBILE, PHANTOMJS})
//@JavascriptEnabled
//@Test
TEST_F(FrameSwitchingTest, testShouldBeAbleToSwitchToTheTopIfTheFrameIsDeletedFromUnderUs) {
  webDriver().get(whereIs("frame_switching_tests/deletingFrame.html"));

  webDriver().switchTo().frame("iframe1");

  WebElement killIframe = webDriver().findElement(By::id("killIframe"));
  killIframe.click();
  webDriver().switchTo().defaultContent();

  assertFrameNotPresent("iframe1");

  WebElement addIFrame = webDriver().findElement(By::id("addBackFrame"));
  addIFrame.click();
  wait().until(PresenceOfElementLocated(By::id("iframe1")));

  webDriver().switchTo().frame("iframe1");

  try {
    wait().until(PresenceOfElementLocated(By::id("success")));
  } catch (WebDriverException& web) {
    FAIL() << "Could not find element after switching frame";
  }
}

/*
//@Ignore(ALL)
//@JavascriptEnabled
//@Test
TEST_F(FrameSwitchingTest, testShouldNotBeAbleToDoAnythingTheFrameIsDeletedFromUnderUs) {
  webDriver().get(whereIs("frame_switching_tests/deletingFrame.html"));

  webDriver().switchTo().frame("iframe1");

  WebElement killIframe = webDriver().findElement(By::id("killIframe"));
  killIframe.click();

  ASSERT_THROW(webDriver().findElement(By::id("killIframe")).click(), NoSuchFrameException) << "NoSuchFrameException should be thrown";
}
*/

//@Test
//@Ignore(MARIONETTE)
TEST_F(FrameSwitchingTest, testShouldReturnWindowTitleInAFrameset) {
  webDriver().get(pages().framesetPage);
  webDriver().switchTo().frame("third");
  assertThat(equals(webDriver().title(), "Unique title"));
}

//@JavascriptEnabled
//@Test
//@Ignore(MARIONETTE)
TEST_F(FrameSwitchingTest, testJavaScriptShouldExecuteInTheContextOfTheCurrentFrame) {

  webDriver().get(pages().framesetPage);
  ASSERT_TRUE((bool) webDriver().executeScript("return window == window.top"));
  webDriver().switchTo().frame("third");
  ASSERT_TRUE((bool) webDriver().executeScript("return window != window.top"));
}

/*
//@Test
TEST_F(FrameSwitchingTest, testShouldNotSwitchMagicallyToTheTopWindow) {
  std::string baseUrl = whereIs("frame_switching_tests/");
  webDriver().get(baseUrl + "bug4876.html");
  webDriver().switchTo().frame(0);
  wait().until(PresenceOfElementLocated(By::id("inputText")));

  for (int i = 0; i < 20; i++) {
//    try {
      WebElement input = wait().until(PresenceOfElementLocated(By::id("inputText")));
      WebElement submit = wait().until(PresenceOfElementLocated(By::id("submitButton")));
      input.clear();
      input.sendKeys("rand" + rand());
      submit.click();
//    } finally {
      std::string url = webDriver().currentUrl();
      // IE6 and Chrome add "?"-symbol to the end of the URL
      if (url.back() == "?") {
        url = url.substring(0, url.length()-1);
      }
      assertEquals(baseUrl + "bug4876_iframe.html", url);
//    }
  }
}
*/

