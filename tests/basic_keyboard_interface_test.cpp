/*
 * basic_keybvoard_interface_test.cpp
 *
 *  Created on: Sep 20, 2014
 *      Author: speedpat
 */

#include <list>

#include <boost/algorithm/string/trim.hpp>
#include <boost/regex.hpp>

#include <gmock/gmock.h>

#include "selenium/selenium.hpp"
#include "selenium/support/colors.hpp"
#include "support/selenium_testcase.hpp"
#include "support/expected_test_conditions.hpp"



using namespace selenium;
using namespace interactions;
using namespace support;
using namespace testing;

class BasicKeyBoardInterfaceTest : public SeleniumTestCase
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

  Actions getBuilder(WebDriver& driver) {
  return Actions(driver);
  }



  void assertBackgroundColor(WebElement el, Color expected) {
    Color actual = Color::fromString(el.valueOfCssProperty("background-color"));
    ASSERT_THAT(actual, Eq(expected));
  }


  void assertThatFormEventsFiredAreExactly(std::string message, std::string expected) {
    ::boost::trim(expected);
    ASSERT_THAT(getFormEvents(), Eq(expected)) << message;
  }

  std::string getFormEvents() {
    std::string events = webDriver().findElement(By::id("result")).text();
    ::boost::trim(events);
    return events;
  }

  void assertThatFormEventsFiredAreExactly(std::string expected) {
    assertThatFormEventsFiredAreExactly("", expected);
  }

  void assertThatBodyEventsFiredAreExactly(std::string expected) {
    std::string events = webDriver().findElement(By::id("body_result")).text();
    ::boost::trim(events);
    std::string exp = ::boost::trim_copy(expected);
    EXPECT_THAT(events, Eq(exp));
  }

};





//@JavascriptEnabled
//@Ignore({ANDROID, IPHONE})
//@Test
TEST_F(BasicKeyBoardInterfaceTest, testBasicKeyboardInput) {
  webDriver().get(pages().javascriptPage);

  WebElement keyReporter = webDriver().findElement(By::id("keyReporter"));

  interactions::Action sendLowercase = getBuilder(webDriver()).sendKeys(keyReporter, "abc def").build();

  sendLowercase.perform();

  ASSERT_THAT(keyReporter.getAttribute("value"), Eq("abc def"));
}

//@JavascriptEnabled
//@Ignore({ANDROID, IPHONE, IE, OPERA, OPERA_MOBILE})
//@Test
TEST_F(BasicKeyBoardInterfaceTest, testSendingKeyDownOnly) {
  webDriver().get(pages().javascriptPage);

  WebElement keysEventInput = webDriver().findElement(By::id("theworks"));

  interactions::Action pressShift = getBuilder(webDriver()).keyDown(keysEventInput, Keys::SHIFT).build();

  pressShift.perform();

  WebElement keyLoggingElement = webDriver().findElement(By::id("result"));
  std::string logText = keyLoggingElement.text();

  interactions::Action releaseShift = getBuilder(webDriver()).keyUp(keysEventInput, Keys::SHIFT).build();
  releaseShift.perform();

  ASSERT_THAT(logText, EndsWith("keydown")) << "Key down event not isolated, got: " + logText;
}

//@JavascriptEnabled
//@Ignore({ANDROID, IPHONE, IE, OPERA, OPERA_MOBILE})
//@Test
TEST_F(BasicKeyBoardInterfaceTest, testSendingKeyUp) {
  webDriver().get(pages().javascriptPage);
  WebElement keysEventInput = webDriver().findElement(By::id("theworks"));

  interactions::Action pressShift = getBuilder(webDriver()).keyDown(keysEventInput, Keys::SHIFT).build();
  pressShift.perform();

  WebElement keyLoggingElement = webDriver().findElement(By::id("result"));

  std::string eventsText = keyLoggingElement.text();
  ASSERT_THAT(eventsText, EndsWith("keydown")) << ("Key down should be isolated for this test to be meaningful. Got events: " + eventsText);

  interactions::Action releaseShift = getBuilder(webDriver()).keyUp(keysEventInput, Keys::SHIFT).build();

  releaseShift.perform();

  eventsText = keyLoggingElement.text();
  ASSERT_THAT(eventsText, EndsWith("keyup")) << "Key up event not isolated. Got events: " + eventsText;
}

//@JavascriptEnabled
//@Ignore({ANDROID, HTMLUNIT, IPHONE, IE, OPERA, OPERA_MOBILE})
//@Test
TEST_F(BasicKeyBoardInterfaceTest, testSendingKeysWithShiftPressed) {
  webDriver().get(pages().javascriptPage);

  WebElement keysEventInput = webDriver().findElement(By::id("theworks"));

  keysEventInput.click();

  std::string existingResult = getFormEvents();

  interactions::Action pressShift = getBuilder(webDriver()).keyDown(keysEventInput, Keys::SHIFT).build();
  pressShift.perform();

  interactions::Action sendLowercase = getBuilder(webDriver()).sendKeys(keysEventInput, "ab").build();
  sendLowercase.perform();

  interactions::Action releaseShift = getBuilder(webDriver()).keyUp(Keys::SHIFT).build();
  releaseShift.perform();

  std::string expectedEvents = " keydown keydown keypress keyup keydown keypress keyup keyup";
  assertThatFormEventsFiredAreExactly("Shift key not held",
      existingResult + expectedEvents);

  ASSERT_THAT(keysEventInput.getAttribute("value"), Eq("AB"));
}

//@JavascriptEnabled
//@Ignore({ANDROID, IPHONE})
//@Test
TEST_F(BasicKeyBoardInterfaceTest, testSendingKeysToActiveElement) {
 /* assumeFalse("This test fails due to a bug in Firefox 9. For more details, see: " +
              "https://bugzilla.mozilla.org/show_bug.cgi?id=696020",
              TestUtilities.isFirefox9(driver));*/

  webDriver().get(pages().bodyTypingPage);

  interactions::Action someKeys = getBuilder(webDriver()).sendKeys("ab").build();
  someKeys.perform();

  assertThatBodyEventsFiredAreExactly("keypress keypress");
  assertThatFormEventsFiredAreExactly("");
}

//@Ignore({ANDROID, IPHONE})
//@Test
TEST_F(BasicKeyBoardInterfaceTest, testBasicKeyboardInputOnActiveElement) {
  webDriver().get(pages().javascriptPage);

  WebElement keyReporter = webDriver().findElement(By::id("keyReporter"));

  keyReporter.click();

  interactions::Action sendLowercase = getBuilder(webDriver()).sendKeys("abc def").build();

  sendLowercase.perform();

  ASSERT_THAT(keyReporter.getAttribute("value"), Eq("abc def"));
}

//@Ignore(value = {ANDROID, IPHONE, IE, OPERA, SAFARI, HTMLUNIT}, reason = "untested")
//@JavascriptEnabled
//@Test
TEST_F(BasicKeyBoardInterfaceTest, canGenerateKeyboardShortcuts) {
/*  assumeTrue(
      "Test fails with native events enabled, likely due to issue 4385",
      !TestUtilities.isFirefox(driver) || !TestUtilities.isNativeEventsEnabled(driver));*/

  webDriver().get(whereIs("keyboard_shortcut.html"));

  WebElement body = webDriver().findElement(By::xpath("//body"));
  assertBackgroundColor(body, Colors::WHITE);

  Actions(webDriver()).keyDown(Keys::SHIFT).sendKeys("1").keyUp(Keys::SHIFT).perform();
  assertBackgroundColor(body, Colors::GREEN);

  Actions(webDriver()).keyDown(Keys::ALT).sendKeys("1").keyUp(Keys::ALT).perform();
  assertBackgroundColor(body, Colors::LIGHTBLUE);

  Actions(webDriver())
      .keyDown(Keys::SHIFT).keyDown(Keys::ALT)
      .sendKeys("1")
      .keyUp(Keys::SHIFT).keyUp(Keys::ALT)
      .perform();
  assertBackgroundColor(body, Colors::SILVER);
}


