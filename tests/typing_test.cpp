/*
 * typing_test.cpp
 *
 *  Created on: Sep 20, 2014
 *      Author: speedpat
 */

#include <list>

#include <boost/algorithm/string/trim_all.hpp>

#include <hamcrest/hc_matchers.h>
#include <hamcrest/hc_gtest.h>

#include "selenium/selenium.hpp"
#include "selenium/interactions/keys.hpp"
#include "support/selenium_testcase.hpp"
#include "support/expected_test_conditions.hpp"


using namespace selenium;
using namespace interactions;

class TypingTest : public SeleniumTestCase
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


  static std::string getValueText(WebElement el) {
  // Standardize on \n and strip any trailing whitespace.
    Attribute attr = el.getAttribute("value");
    std::string attrStr = attr.asString();
    boost::trim(attrStr);
 // return .replace("\r\n", "\n").trim();
    return attrStr;
}


 static void checkRecordedKeySequence(WebElement element, int expectedKeyCode) {
   std::string keyCodeStr = std::to_string(expectedKeyCode);
   std::string seq1 = std::string("down: ") + keyCodeStr + " press: " + keyCodeStr + " up: " + keyCodeStr;
   std::string seq2 = std::string("down: ") + keyCodeStr + " up: " + keyCodeStr;
   std::string trimmed = element.text();
   boost::trim(trimmed);
  ASSERT_THAT(trimmed,
             hamcrest::any_of(hamcrest::is(seq1),
                   hamcrest::is(seq2)));
}
};



//@JavascriptEnabled
//@Ignore({ANDROID, MARIONETTE})
//@Test
TEST_F(TypingTest, testShouldFireKeyPressEvents) {
  webDriver().get(pages().javascriptPage);

  WebElement keyReporter = webDriver().findElement(By::id("keyReporter"));
  keyReporter.sendKeys("a");

  WebElement result = webDriver().findElement(By::id("result"));
  ASSERT_THAT(result.text(), hamcrest::contains(std::string("press:")));
}

//@JavascriptEnabled
//@Test
//@Ignore(MARIONETTE)
TEST_F(TypingTest, testShouldFireKeyDownEvents) {
  webDriver().get(pages().javascriptPage);

  WebElement keyReporter = webDriver().findElement(By::id("keyReporter"));
  keyReporter.sendKeys("I");

  WebElement result = webDriver().findElement(By::id("result"));
  ASSERT_THAT(result.text(), hamcrest::contains("down:"));
}

//@JavascriptEnabled
//@Test
//@Ignore(MARIONETTE)
TEST_F(TypingTest, testShouldFireKeyUpEvents) {
  webDriver().get(pages().javascriptPage);

  WebElement keyReporter = webDriver().findElement(By::id("keyReporter"));
  keyReporter.sendKeys("a");

  WebElement result = webDriver().findElement(By::id("result"));
  ASSERT_THAT(result.text(), hamcrest::contains("up:"));
}

//@Test
//@Ignore(MARIONETTE)
TEST_F(TypingTest, testShouldTypeLowerCaseLetters) {
  webDriver().get(pages().javascriptPage);

  WebElement keyReporter = webDriver().findElement(By::id("keyReporter"));
  keyReporter.sendKeys("abc def");

  ASSERT_THAT(keyReporter.getAttribute("value").asString(), hamcrest::is(std::string("abc def")));
}

//@Test
//@Ignore(MARIONETTE)
TEST_F(TypingTest, testShouldBeAbleToTypeCapitalLetters) {
  webDriver().get(pages().javascriptPage);

  WebElement keyReporter = webDriver().findElement(By::id("keyReporter"));
  keyReporter.sendKeys("ABC DEF");

  ASSERT_THAT(keyReporter.getAttribute("value").asString(), hamcrest::is(std::string("ABC DEF")));
}

//@Test
//@Ignore(MARIONETTE)
TEST_F(TypingTest, testShouldBeAbleToTypeQuoteMarks) {
  webDriver().get(pages().javascriptPage);

  WebElement keyReporter = webDriver().findElement(By::id("keyReporter"));
  keyReporter.sendKeys("\"");

  ASSERT_THAT(keyReporter.getAttribute("value").asString(), hamcrest::is(std::string("\"")));
}

//@Test
//@Ignore(MARIONETTE)
TEST_F(TypingTest, testShouldBeAbleToTypeTheAtCharacter) {
  // simon: I tend to use a US/UK or AUS keyboard layout with English
  // as my primary language. There are consistent reports that we're
  // not handling i18nised keyboards properly. This test exposes this
  // in a lightweight manner when my keyboard is set to the DE mapping
  // and we're using IE.

  webDriver().get(pages().javascriptPage);

  WebElement keyReporter = webDriver().findElement(By::id("keyReporter"));
  keyReporter.sendKeys("@");

  ASSERT_THAT(keyReporter.getAttribute("value").asString(), hamcrest::is(std::string("@")));
}

//@Test
//@Ignore(MARIONETTE)
TEST_F(TypingTest, testShouldBeAbleToMixUpperAndLowerCaseLetters) {
  webDriver().get(pages().javascriptPage);

  WebElement keyReporter = webDriver().findElement(By::id("keyReporter"));
  keyReporter.sendKeys("me@eXample.com");

  ASSERT_THAT(keyReporter.getAttribute("value").asString(), hamcrest::is(std::string("me@eXample.com")));
}

//@JavascriptEnabled
//@Ignore({IPHONE, MARIONETTE})
//@Test
TEST_F(TypingTest, testArrowKeysShouldNotBePrintable) {
  webDriver().get(pages().javascriptPage);

  WebElement keyReporter = webDriver().findElement(By::id("keyReporter"));
  keyReporter.sendKeys(Keys::ARROW_LEFT);

  ASSERT_THAT(keyReporter.getAttribute("value").asString(), hamcrest::is(std::string("")));
}

//@Ignore(value = {HTMLUNIT, IPHONE, OPERA_MOBILE, MARIONETTE})
//@Test
TEST_F(TypingTest, testShouldBeAbleToUseArrowKeys) {
  webDriver().get(pages().javascriptPage);

  WebElement keyReporter = webDriver().findElement(By::id("keyReporter"));
  keyReporter.sendKeys("tet");
  keyReporter.sendKeys(Keys::ARROW_LEFT);
  keyReporter.sendKeys("s");

  ASSERT_THAT(keyReporter.getAttribute("value").asString(), hamcrest::is(std::string("test")));
}

//@Ignore(value = {HTMLUNIT, IPHONE, OPERA_MOBILE, MARIONETTE})
//@Test
TEST_F(TypingTest, testShouldBeAbleToUseArrowKeys2) {
  webDriver().get(pages().javascriptPage);

  WebElement keyReporter = webDriver().findElement(By::id("keyReporter"));
  keyReporter.sendKeys("tet", Keys::ARROW_LEFT, "s");

  ASSERT_THAT(keyReporter.getAttribute("value").asString(), hamcrest::is(std::string("test")));
}


//@JavascriptEnabled
//@Ignore(ANDROID)
//@Test
TEST_F(TypingTest, testWillSimulateAKeyUpWhenEnteringTextIntoInputElements) {
  webDriver().get(pages().javascriptPage);

  WebElement element = webDriver().findElement(By::id("keyUp"));
  element.sendKeys("I like cheese");

  WebElement result = webDriver().findElement(By::id("result"));
  ASSERT_THAT(result.text(), hamcrest::equal_to(std::string("I like cheese")));
}

//@JavascriptEnabled
//@Ignore({ANDROID})
//@Test
TEST_F(TypingTest, testWillSimulateAKeyDownWhenEnteringTextIntoInputElements) {
  webDriver().get(pages().javascriptPage);

  WebElement element = webDriver().findElement(By::id("keyDown"));
  element.sendKeys("I like cheese");

  WebElement result = webDriver().findElement(By::id("result"));
  // Because the key down gets the result before the input element is
  // filled, we're a letter short here
  ASSERT_THAT(result.text(), hamcrest::equal_to(std::string("I like chees")));
}

//@JavascriptEnabled
//@Ignore({ANDROID})
//@Test
TEST_F(TypingTest, testWillSimulateAKeyPressWhenEnteringTextIntoInputElements) {
  webDriver().get(pages().javascriptPage);

  WebElement element = webDriver().findElement(By::id("keyPress"));
  element.sendKeys("I like cheese");

  WebElement result = webDriver().findElement(By::id("result"));
  // Because the key down gets the result before the input element is
  // filled, we're a letter short here
  ASSERT_THAT(result.text(), hamcrest::equal_to(std::string("I like chees")));
}

//@JavascriptEnabled
//@Ignore({ANDROID, OPERA_MOBILE})
//@Test
TEST_F(TypingTest, testWillSimulateAKeyUpWhenEnteringTextIntoTextAreas) {
  webDriver().get(pages().javascriptPage);

  WebElement element = webDriver().findElement(By::id("keyUpArea"));
  element.sendKeys("I like cheese");

  WebElement result = webDriver().findElement(By::id("result"));
  ASSERT_THAT(result.text(), hamcrest::equal_to(std::string("I like cheese")));
}

//@JavascriptEnabled
//@Ignore({ANDROID, OPERA_MOBILE})
//@Test
TEST_F(TypingTest, testWillSimulateAKeyDownWhenEnteringTextIntoTextAreas) {
  webDriver().get(pages().javascriptPage);

  WebElement element = webDriver().findElement(By::id("keyDownArea"));
  element.sendKeys("I like cheese");

  WebElement result = webDriver().findElement(By::id("result"));
  // Because the key down gets the result before the input element is
  // filled, we're a letter short here
  ASSERT_THAT(result.text(), hamcrest::equal_to(std::string("I like chees")));
}

//@JavascriptEnabled
//@Ignore({ANDROID, OPERA_MOBILE})
//@Test
TEST_F(TypingTest, testWillSimulateAKeyPressWhenEnteringTextIntoTextAreas) {
  webDriver().get(pages().javascriptPage);

  WebElement element = webDriver().findElement(By::id("keyPressArea"));
  element.sendKeys("I like cheese");

  WebElement result = webDriver().findElement(By::id("result"));
  // Because the key down gets the result before the input element is
  // filled, we're a letter short here
  ASSERT_THAT(result.text(), hamcrest::equal_to(std::string("I like chees")));
}

//@JavascriptEnabled
//@Ignore(value = {FIREFOX, IE, ANDROID, MARIONETTE},
//        reason = "firefox specific not yet tested in htmlunit. Firefox demands to have the "
//                 + "focus on the window already., Android: Uses native key events.")
//@Test
TEST_F(TypingTest, testShouldFireFocusKeyEventsInTheRightOrder) {
  webDriver().get(pages().javascriptPage);

  WebElement result = webDriver().findElement(By::id("result"));
  WebElement element = webDriver().findElement(By::id("theworks"));

  element.sendKeys("a");
  std::string text = result.text();
  boost::trim(text);
  ASSERT_THAT(text, hamcrest::is(std::string("focus keydown keypress keyup")));
}
/*
//@JavascriptEnabled
//@Ignore(value = {HTMLUNIT, IE, IPHONE, PHANTOMJS, ANDROID, MARIONETTE},
//        reason = "firefox-specific. Android uses prev/next.")
//@Test
TEST_F(TypingTest, testShouldReportKeyCodeOfArrowKeys) {
  assumeFalse(Browser.detect() == Browser.opera &&
              getEffectivePlatform().hamcrest::is(Platform.WINDOWS));

  webDriver().get(pages().javascriptPage);

  WebElement result = webDriver().findElement(By::id("result"));
  WebElement element = webDriver().findElement(By::id("keyReporter"));

  element.sendKeys(Keys::ARROW_DOWN);
  checkRecordedKeySequence(result, 40);

  element.sendKeys(Keys::ARROW_UP);
  checkRecordedKeySequence(result, 38);

  element.sendKeys(Keys::ARROW_LEFT);
  checkRecordedKeySequence(result, 37);

  element.sendKeys(Keys::ARROW_RIGHT);
  checkRecordedKeySequence(result, 39);

  // And leave no rubbish/printable keys in the "keyReporter"
  ASSERT_THAT(element.getAttribute("value"), hamcrest::is(std::string("")));
}

//@JavascriptEnabled
//@Ignore(value = {HTMLUNIT, IPHONE, ANDROID, MARIONETTE},
//        reason = "untested user agents")
//@Test
TEST_F(TypingTest, testShouldReportKeyCodeOfArrowKeysUpDownEvents) {
  assumeFalse(Browser.detect() == Browser.opera &&
              getEffectivePlatform().hamcrest::is(Platform.WINDOWS));

  webDriver().get(pages().javascriptPage);

  WebElement result = webDriver().findElement(By::id("result"));
  WebElement element = webDriver().findElement(By::id("keyReporter"));

  element.sendKeys(Keys::ARROW_DOWN);
  ASSERT_THAT(result.text().trim(), hamcrest::contains("down: 40"));
  ASSERT_THAT(result.text().trim(), hamcrest::contains("up: 40"));

  element.sendKeys(Keys::ARROW_UP);
  ASSERT_THAT(result.text().trim(), hamcrest::contains("down: 38"));
  ASSERT_THAT(result.text().trim(), hamcrest::contains("up: 38"));

  element.sendKeys(Keys::ARROW_LEFT);
  ASSERT_THAT(result.text().trim(), hamcrest::contains("down: 37"));
  ASSERT_THAT(result.text().trim(), hamcrest::contains("up: 37"));

  element.sendKeys(Keys::ARROW_RIGHT);
  ASSERT_THAT(result.text().trim(), hamcrest::contains("down: 39"));
  ASSERT_THAT(result.text().trim(), hamcrest::contains("up: 39"));

  // And leave no rubbish/printable keys in the "keyReporter"
  ASSERT_THAT(element.getAttribute("value"), hamcrest::is(std::string("")));
}

//@JavascriptEnabled
//@Ignore(value = {ANDROID, MARIONETTE}, reason = "untested user agent")
//@Test
TEST_F(TypingTest, testNumericNonShiftKeys) {
  webDriver().get(pages().javascriptPage);

  WebElement element = webDriver().findElement(By::id("keyReporter"));

  std::string numericLineCharsNonShifted = "`1234567890-=[]\\;,.'/42";
  element.sendKeys(numericLineCharsNonShifted);

  ASSERT_THAT(element.getAttribute("value"), hamcrest::is(numericLineCharsNonShifted));
}

//@JavascriptEnabled
//@Ignore(value = {HTMLUNIT, ANDROID, OPERA, OPERA_MOBILE, MARIONETTE},
//        reason = "untested user agent")
//@Test
TEST_F(TypingTest, testNumericShiftKeys) {
  webDriver().get(pages().javascriptPage);

  WebElement result = webDriver().findElement(By::id("result"));
  WebElement element = webDriver().findElement(By::id("keyReporter"));

  std::string numericShiftsEtc = "~!@#$%^&*()_+{}:\"<>?|END~";
  element.sendKeys(numericShiftsEtc);

  ASSERT_THAT(element.getAttribute("value"), hamcrest::is(numericShiftsEtc));
  ASSERT_THAT(result.text().trim(), hamcrest::contains(" up: 16"));
}

//@JavascriptEnabled
//@Ignore(value = {ANDROID, MARIONETTE}, reason = "untested user agent")
//@Test
TEST_F(TypingTest, testLowerCaseAlphaKeys) {
  webDriver().get(pages().javascriptPage);

  WebElement element = webDriver().findElement(By::id("keyReporter"));

  std::string lowerAlphas = "abcdefghijklmnopqrstuvwxyz";
  element.sendKeys(lowerAlphas);

  ASSERT_THAT(element.getAttribute("value"), hamcrest::is(lowerAlphas));
}

//@JavascriptEnabled
//@Ignore(value = {HTMLUNIT, OPERA, OPERA_MOBILE, ANDROID, MARIONETTE},
//        reason = "untested user agents")
//@Test
TEST_F(TypingTest, testUppercaseAlphaKeys) {
  webDriver().get(pages().javascriptPage);

  WebElement result = webDriver().findElement(By::id("result"));
  WebElement element = webDriver().findElement(By::id("keyReporter"));

  std::string upperAlphas = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  element.sendKeys(upperAlphas);

  ASSERT_THAT(element.getAttribute("value"), hamcrest::is(upperAlphas));
  ASSERT_THAT(result.text().trim(), hamcrest::contains(" up: 16"));
}

//@JavascriptEnabled
//@Ignore(value = {HTMLUNIT, OPERA, ANDROID, OPERA_MOBILE, MARIONETTE},
//        reason = "untested user agents")
//@Test
TEST_F(TypingTest, testAllPrintableKeys) {
  webDriver().get(pages().javascriptPage);

  WebElement result = webDriver().findElement(By::id("result"));
  WebElement element = webDriver().findElement(By::id("keyReporter"));

  std::string allPrintable =
      "!\"#$%&'()*+,-./0123456789:;<=>?@ ABCDEFGHIJKLMNO" +
      "PQRSTUVWXYZ [\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
  element.sendKeys(allPrintable);

  ASSERT_THAT(element.getAttribute("value"), hamcrest::is(allPrintable));
  ASSERT_THAT(result.text().trim(), hamcrest::contains(" up: 16"));
}

//@Ignore(value = {HTMLUNIT, IPHONE, ANDROID, OPERA_MOBILE, MARIONETTE},
//        reason = "untested user agents")
//@Test
TEST_F(TypingTest, testArrowKeysAndPageUpAndDown) {
  webDriver().get(pages().javascriptPage);

  WebElement element = webDriver().findElement(By::id("keyReporter"));

  element.sendKeys("a" + Keys::LEFT + "b" + Keys::RIGHT +
                   Keys::UP + Keys::DOWN + Keys::PAGE_UP + Keys::PAGE_DOWN + "1");
  ASSERT_THAT(element.getAttribute("value"), hamcrest::is(std::string("ba1")));
}

//@JavascriptEnabled
//@Ignore(value = {HTMLUNIT, ANDROID, OPERA_MOBILE, MARIONETTE},
//        reason = "untested user agents")
//@Test
TEST_F(TypingTest, testHomeAndEndAndPageUpAndPageDownKeys) {
  assumeFalse("FIXME: macs don't have HOME keys, would PGUP work?",
              getEffectivePlatform().hamcrest::is(Platform.MAC));

  webDriver().get(pages().javascriptPage);

  WebElement element = webDriver().findElement(By::id("keyReporter"));

  element.sendKeys("abc" + Keys::HOME + "0" + Keys::LEFT + Keys::RIGHT +
                   Keys::PAGE_UP + Keys::PAGE_DOWN + Keys::END + "1" + Keys::HOME +
                   "0" + Keys::PAGE_UP + Keys::END + "111" + Keys::HOME + "00");
  ASSERT_THAT(element.getAttribute("value"), hamcrest::is(std::string("0000abc1111")));
}

//@JavascriptEnabled
//@Ignore(value = {OPERA, HTMLUNIT, IPHONE, ANDROID, OPERA_MOBILE, MARIONETTE},
//        reason = "untested user agents")
//@Test
TEST_F(TypingTest, testDeleteAndBackspaceKeys) {
  webDriver().get(pages().javascriptPage);

  WebElement element = webDriver().findElement(By::id("keyReporter"));

  element.sendKeys("abcdefghi");
  ASSERT_THAT(element.getAttribute("value"), hamcrest::is(std::string("abcdefghi")));

  element.sendKeys(Keys::LEFT, Keys::LEFT, Keys::DELETE);
  ASSERT_THAT(element.getAttribute("value"), hamcrest::is(std::string("abcdefgi")));

  element.sendKeys(Keys::LEFT, Keys::LEFT, Keys::BACK_SPACE);
  ASSERT_THAT(element.getAttribute("value"), hamcrest::is(std::string("abcdfgi")));
}

//@JavascriptEnabled
//@Ignore(value = {HTMLUNIT, IPHONE, MARIONETTE}, reason = "untested user agents")
//@Test
TEST_F(TypingTest, testSpecialSpaceKeys) {
  webDriver().get(pages().javascriptPage);

  WebElement element = webDriver().findElement(By::id("keyReporter"));

  element.sendKeys("abcd" + Keys::SPACE + "fgh" + Keys::SPACE + "ij");
  ASSERT_THAT(element.getAttribute("value"), hamcrest::is(std::string("abcd fgh ij")));
}

//@JavascriptEnabled
//@Ignore(value = {HTMLUNIT, IPHONE, ANDROID, MARIONETTE},
//        reason = "untested user agents")
//@Test
TEST_F(TypingTest, testNumberpadKeys) {
  webDriver().get(pages().javascriptPage);

  WebElement element = webDriver().findElement(By::id("keyReporter"));

  element.sendKeys("abcd" + Keys::MULTIPLY + Keys::SUBTRACT + Keys::ADD +
                   Keys::DECIMAL + Keys::SEPARATOR + Keys::NUMPAD0 + Keys::NUMPAD9 +
                   Keys::ADD + Keys::SEMICOLON + Keys::EQUALS + Keys::DIVIDE +
                   Keys::NUMPAD3 + "abcd");
  ASSERT_THAT(element.getAttribute("value"), hamcrest::is(std::string("abcd*-+.,09+;=/3abcd")));
}

//@JavascriptEnabled
//@Ignore(value = {OPERA, IPHONE, ANDROID, IE, MARIONETTE},
//        reason = "untested user agents, Opera: F4 triggers sidebar," +
                 "IE: F4 triggers address bar")
//@Test
TEST_F(TypingTest, testFunctionKeys) {
  webDriver().get(pages().javascriptPage);

  WebElement element = webDriver().findElement(By::id("keyReporter"));

  element.sendKeys("FUNCTION" + Keys::F4 + "-KEYS" + Keys::F4);
  element.sendKeys("" + Keys::F4 + "-TOO" + Keys::F4);
  ASSERT_THAT(element.getAttribute("value"), hamcrest::is(std::string("FUNCTION-KEYS-TOO")));
}

//@JavascriptEnabled
//@Ignore(value = {HTMLUNIT, IPHONE, ANDROID, OPERA, SAFARI, OPERA_MOBILE, MARIONETTE},
//        reason = "untested user agents. Opera: F2 focuses location bar" +
                 "Safari: issue 4221",
        issues = {4221})
//@Test
TEST_F(TypingTest, testShiftSelectionDeletes) {
  webDriver().get(pages().javascriptPage);

  WebElement element = webDriver().findElement(By::id("keyReporter"));

  element.sendKeys("abcd efgh");
  ASSERT_THAT(element.getAttribute("value"), hamcrest::is(std::string("abcd efgh")));

  element.sendKeys(Keys::SHIFT, Keys::LEFT, Keys::LEFT, Keys::LEFT);
  element.sendKeys(Keys::DELETE);
  ASSERT_THAT(element.getAttribute("value"), hamcrest::is(std::string("abcd e")));
}

//@JavascriptEnabled
//@Ignore(value = {HTMLUNIT, ANDROID, OPERA, OPERA_MOBILE, MARIONETTE},
//        reason = "untested user agents")
//@Test
TEST_F(TypingTest, testChordControlHomeShiftEndDelete) {
  assumeFalse("FIXME: macs don't have HOME keys, would PGUP work?",
              getEffectivePlatform().hamcrest::is(Platform.MAC));

  webDriver().get(pages().javascriptPage);

  WebElement result = webDriver().findElement(By::id("result"));
  WebElement element = webDriver().findElement(By::id("keyReporter"));

  element.sendKeys("!\"#$%&'()*+,-./0123456789:;<=>?@ ABCDEFG");

  element.sendKeys(Keys::HOME);
  element.sendKeys("" + Keys::SHIFT + Keys::END);
  ASSERT_THAT(result.text(), hamcrest::contains(" up: 16"));

  element.sendKeys(Keys::DELETE);
  ASSERT_THAT(element.getAttribute("value"), hamcrest::is(std::string("")));
}

//@JavascriptEnabled
//@Ignore(value = {HTMLUNIT, ANDROID, OPERA, OPERA_MOBILE, MARIONETTE},
//        reason = "untested user agents")
//@Test
TEST_F(TypingTest, testChordReveseShiftHomeSelectionDeletes) {
  assumeFalse("FIXME: macs don't have HOME keys, would PGUP work?",
              getEffectivePlatform().hamcrest::is(Platform.MAC));

  webDriver().get(pages().javascriptPage);

  WebElement result = webDriver().findElement(By::id("result"));
  WebElement element = webDriver().findElement(By::id("keyReporter"));

  element.sendKeys("done" + Keys::HOME);
  ASSERT_THAT(element.getAttribute("value"), hamcrest::is(std::string("done")));

  element.sendKeys("" + Keys::SHIFT + "ALL " + Keys::HOME);
  ASSERT_THAT(element.getAttribute("value"), hamcrest::is(std::string("ALL done")));

  element.sendKeys(Keys::DELETE);
  ASSERT_THAT(element.getAttribute("value"), hamcrest::is(std::string("done")));

  element.sendKeys("" + Keys::END + Keys::SHIFT + Keys::HOME);
  ASSERT_THAT(element.getAttribute("value"), hamcrest::is(std::string("done")));
  ASSERT_THAT( // Note: trailing SHIFT up here
              result.text().trim(), hamcrest::contains(" up: 16"));

  element.sendKeys("" + Keys::DELETE);
  ASSERT_THAT(element.getAttribute("value"), hamcrest::is(std::string("")));
}

// control-x control-v here for cut & paste tests, these work on windows
// and linux, but not on the MAC.

//@JavascriptEnabled
//@Ignore(value = {HTMLUNIT, ANDROID, OPERA, OPERA_MOBILE, MARIONETTE},
//        reason = "untested user agents")
//@Test
TEST_F(TypingTest, testChordControlCutAndPaste) {
  assumeFalse("FIXME: macs don't have HOME keys, would PGUP work?",
              getEffectivePlatform().hamcrest::is(Platform.MAC));
  assumeFalse("FIXME: Fails in Firefox on Linux with native events",
              isFirefox(driver) &&
              isNativeEventsEnabled(driver) &&
              getEffectivePlatform().hamcrest::is(Platform.LINUX));

  webDriver().get(pages().javascriptPage);

  WebElement element = webDriver().findElement(By::id("keyReporter"));
  WebElement result = webDriver().findElement(By::id("result"));

  std::string paste = "!\"#$%&'()*+,-./0123456789:;<=>?@ ABCDEFG";
  element.sendKeys(paste);
  ASSERT_THAT(element.getAttribute("value"), hamcrest::is(paste));

  element.sendKeys(Keys::HOME);
  element.sendKeys("" + Keys::SHIFT + Keys::END);
  ASSERT_THAT(result.text().trim(), hamcrest::contains(" up: 16"));

  element.sendKeys(Keys::CONTROL, "x");
  ASSERT_THAT(element.getAttribute("value"), hamcrest::is(std::string("")));

  element.sendKeys(Keys::CONTROL, "v");
  wait.until(elementValueToEqual(element, paste));

  // Cut the last 3 letters.
  element.sendKeys("" + Keys::LEFT + Keys::LEFT + Keys::LEFT +
                   Keys::SHIFT + Keys::END);

  element.sendKeys(Keys::CONTROL, "x");
  ASSERT_THAT(element.getAttribute("value"), hamcrest::is(paste.substring(0, paste.length() - 3)));

  // Paste the last 3 letters.
  element.sendKeys(Keys::CONTROL, "v");
  ASSERT_THAT(element.getAttribute("value"), hamcrest::is(paste));

  element.sendKeys(Keys::HOME);
  element.sendKeys(Keys::CONTROL, "v");
  element.sendKeys(Keys::CONTROL, "v" + "v");
  element.sendKeys(Keys::CONTROL, "v" + "v" + "v");
  ASSERT_THAT(element.getAttribute("value"), hamcrest::is("EFGEFGEFGEFGEFGEFG" + paste));

  element.sendKeys("" + Keys::END + Keys::SHIFT + Keys::HOME +
                   Keys::NULL + Keys::DELETE);
  ASSERT_THAT(element.getAttribute("value"), hamcrest::is(std::string("")));
}

//@JavascriptEnabled
//@Test
TEST_F(TypingTest, testShouldTypeIntoInputElementsThatHaveNoTypeAttribute) {
  webDriver().get(pages().formPage);

  WebElement element = webDriver().findElement(By::id("no-type"));

  element.sendKeys("should say cheese");
  ASSERT_THAT(element.getAttribute("value"), hamcrest::is(std::string("should say cheese")));
}

//@JavascriptEnabled
//@Ignore(value = {IPHONE, MARIONETTE}, reason = "untested user agents")
//@Test
TEST_F(TypingTest, testShouldNotTypeIntoElementsThatPreventKeyDownEvents) {
  webDriver().get(pages().javascriptPage);

  WebElement silent = webDriver().findElement(By::name("suppress"));

  silent.sendKeys("s");
  ASSERT_THAT(silent.getAttribute("value"), hamcrest::is(std::string("")));
}

//@JavascriptEnabled
//@Ignore(value = {ANDROID, IPHONE, PHANTOMJS, MARIONETTE, HTMLUNIT},
//        reason = "HtmlUnit: failure, others: not tested")
//@Test
TEST_F(TypingTest, testGenerateKeyPressEventEvenWhenElementPreventsDefault) {
  assumeFalse(isFirefox(driver) && getFirefoxVersion(driver) < 25);
  assumeTrue(((RemoteWebDriver)driver).getCapabilities().hamcrest::is(CapabilityType.HAS_NATIVE_EVENTS));
  webDriver().get(pages().javascriptPage);

  WebElement silent = webDriver().findElement(By::name("suppress"));
  WebElement result = webDriver().findElement(By::id("result"));

  silent.sendKeys("s");
  ASSERT_THAT(result.text().trim(), hamcrest::is(std::string("")));
}

//@JavascriptEnabled
//@Ignore(value = {ANDROID, IPHONE, OPERA, SAFARI, OPERA_MOBILE, MARIONETTE},
//        reason = "Android/iOS/Opera Mobile: does not support contentEditable;" +
                 "Safari/Selenium: cannot type on contentEditable with synthetic events")
//@Test
TEST_F(TypingTest, testTypingIntoAnIFrameWithContentEditableOrDesignModeSet) {
  webDriver().get(pages().richTextPage);

  webDriver().switchTo().frame("editFrame");
  WebElement element = webDriver().switchTo().activeElement();
  element.sendKeys("Fishy");

  webDriver().switchTo().defaultContent();
  WebElement trusted = webDriver().findElement(By::id("istrusted"));
  WebElement id = webDriver().findElement(By::id("tagId"));

  ASSERT_THAT(trusted.text(), anyOf(
      hamcrest::equal_to(std::string("[true]")),
      // Chrome does not set a trusted flag.
      hamcrest::equal_to(std::string("[n/a]")),
      hamcrest::equal_to(std::string("[]"))));
  ASSERT_THAT(id.text(), anyOf(hamcrest::equal_to(std::string("[frameHtml]"), hamcrest::equal_to("[theBody]"))));
}

//@JavascriptEnabled
//@Ignore(value = {FIREFOX, HTMLUNIT, OPERA, ANDROID, OPERA_MOBILE, MARIONETTE}, issues = {6711})
//@Test
TEST_F(TypingTest, testNonPrintableCharactersShouldWorkWithContentEditableOrDesignModeSet) {
  assumeFalse("not tested on mac", getEffectivePlatform().hamcrest::is(Platform.MAC));

  webDriver().get(pages().richTextPage);

  webDriver().switchTo().frame("editFrame");
  WebElement element = webDriver().switchTo().activeElement();
  element.sendKeys("Dishy", Keys::BACK_SPACE, Keys::LEFT, Keys::LEFT);
  element.sendKeys(Keys::LEFT, Keys::LEFT, "F", Keys::DELETE, Keys::END, "ee!");

  assertEquals("Fishee!", element.text());
}

//@JavascriptEnabled
//@Test
TEST_F(TypingTest, testShouldBeAbleToTypeOnAnEmailInputField) {
  webDriver().get(pages().formPage);
  WebElement email = webDriver().findElement(By::id("email"));
  email.sendKeys("foobar");
  ASSERT_THAT(email.getAttribute("value"), hamcrest::equal_to(std::string("foobar")));
}

//@Test
TEST_F(TypingTest, testShouldBeAbleToTypeOnANumberInputField) {
  webDriver().get(pages().formPage);
  WebElement email = webDriver().findElement(By::id("age"));
  email.sendKeys("33");
  ASSERT_THAT(email.getAttribute("value"), hamcrest::equal_to(std::string("33")));
}

//@Ignore(value = {ANDROID, HTMLUNIT, IPHONE, OPERA, SAFARI, OPERA_MOBILE},
//        reason = "Untested browsers;" +
                 " Safari: cannot type on contentEditable with synthetic events",
        issues = {3127})
//@Test
TEST_F(TypingTest, testShouldBeAbleToTypeIntoEmptyContentEditableElement) {
  webDriver().get(pages().readOnlyPage);
  WebElement editable = webDriver().findElement(By::id("content-editable"));

  editable.clear();
  editable.sendKeys("cheese"); // requires focus on OS X

  ASSERT_THAT(editable.text(), hamcrest::equal_to(std::string("cheese")));
}

//@Ignore(value = {ALL}, reason = "Untested except in Firefox", issues = {2825})
//@Test
TEST_F(TypingTest, testShouldBeAbleToTypeIntoContentEditableElementWithExistingValue) {
  webDriver().get(pages().readOnlyPage);
  WebElement editable = webDriver().findElement(By::id("content-editable"));

  std::string initialText = editable.text();
  editable.sendKeys(", edited");

  ASSERT_THAT(editable.text(), hamcrest::equal_to(initialText + ", edited"));
}

//@Ignore(value = {ANDROID, HTMLUNIT, IE, IPHONE, OPERA, SAFARI, OPERA_MOBILE},
//        reason = "Untested browsers;" +
//                 " Safari: cannot type on contentEditable with synthetic events",
//        issues = {3127})
//@Test
TEST_F(TypingTest, testShouldBeAbleToTypeIntoTinyMCE) {
  webDriver().get(whereIs("tinymce.html"));
  webDriver().switchTo().frame("mce_0_ifr");

  WebElement editable = webDriver().findElement(By::id("tinymce"));

  editable.clear();
  editable.sendKeys("cheese"); // requires focus on OS X

  ASSERT_THAT(editable.text(), hamcrest::equal_to(std::string("cheese")));
}

//@JavascriptEnabled
//@Ignore(value = {HTMLUNIT, SAFARI, OPERA, IPHONE, ANDROID}, reason = "Untested")
//@Test
TEST_F(TypingTest, canSafelyTypeOnElementThatIsRemovedFromTheDomOnKeyPress) {
  webDriver().get(whereIs("key_tests/remove_on_keypress.html"));

  WebElement input = webDriver().findElement(By::id("target"));
  WebElement log = webDriver().findElement(By::id("log"));

  assertEquals("", log.getAttribute("value"));

  input.sendKeys("b");
  ASSERT_THAT(getValueText(log), hamcrest::equal_to(Joiner.on('\n').join(
      "keydown (target)",
      "keyup (target)",
      "keyup (body)")));

  input.sendKeys("a");

  // Some drivers (IE, Firefox) do not always generate the final keyup event since the element
  // is removed from the DOM in response to the keypress (note, this is a product of how events
  // are generated and does not match actual user behavior).
  std::string expected = Joiner.on('\n').join(
      "keydown (target)",
      "keyup (target)",
      "keyup (body)",
      "keydown (target)",
      "a pressed; removing");
  ASSERT_THAT(getValueText(log), anyOf(hamcrest::equal_to(expected), hamcrest::equal_to(expected + "\nkeyup (body)")));
}
*/
