/*
 * correct_event_firing_test.cpp
 *
 *  Created on: Sep 20, 2014
 *      Author: speedpat
 */

#include <list>

#include "selenium/selenium.hpp"
#include "support/selenium_testcase.hpp"
#include "support/expected_test_conditions.hpp"


using namespace selenium;

class CorrectEventFiringTest : public SeleniumTestCase
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


  void clickOnElementWhichRecordsEvents() {
    webDriver().findElement(By::id("plainButton")).click();
  }

  void assertEventFired(const std::string& eventName) {
    WebElement result = webDriver().findElement(By::id("result"));

    std::string text = wait().until(ElementTextToContain(result, eventName));
    bool conditionMet = (text.find(eventName) != std::string::npos);

    ASSERT_TRUE(conditionMet) << "No " << eventName << " fired: " << text;
  }

  void assertEventNotFired(const std::string& eventName) {
    WebElement result = webDriver().findElement(By::id("result"));
    std::string text = result.text();
    ASSERT_FALSE(text.find(eventName) != std::string::npos) << eventName << " fired: " << text;
  }

/*  bool browserNeedsFocusOnThisOs(WebDriver driver) {
    // No browser yet demands focus on windows
    if (TestUtilities.getEffectivePlatform().is(Platform.WINDOWS))
      return false;

    if (Boolean.getBoolean("webwebDriver().focus.override")) {
      return false;
    }

    std::string browserName = getBrowserName(driver);
    return browserName.toLowerCase().contains("firefox");
  }*/

  std::string getBrowserName(WebDriver driver) {
/*    if (driver instanceof HasCapabilities) {
      return ((HasCapabilities) driver).getCapabilities().getBrowserName();
    }

    return webDriver().getClass().getName();*/
    return "chrome";
  }

  std::string getTextFromElementOnceAvailable(std::string elementId) {
    return wait().until(VisibilityOfElementLocated(By::id(elementId))).text();
  }

};




//@Ignore(value = {CHROME, ANDROID}, reason = "Webkit bug 22261")
//@JavascriptEnabled

TEST_F(CorrectEventFiringTest, testShouldFireFocusEventWhenClicking) {
  webDriver().get(pages().javascriptPage);

  clickOnElementWhichRecordsEvents();

  assertEventFired("focus");
}

//@Ignore(ANDROID)
//@JavascriptEnabled

TEST_F(CorrectEventFiringTest, testShouldFireClickEventWhenClicking) {
  webDriver().get(pages().javascriptPage);

  clickOnElementWhichRecordsEvents();

  assertEventFired("click");
}

//@JavascriptEnabled
//@Ignore({ANDROID})

TEST_F(CorrectEventFiringTest, testShouldFireMouseDownEventWhenClicking) {
  webDriver().get(pages().javascriptPage);

  clickOnElementWhichRecordsEvents();

  assertEventFired("mousedown");
}

//@JavascriptEnabled
//@Ignore({ANDROID})

TEST_F(CorrectEventFiringTest, testShouldFireMouseUpEventWhenClicking) {
  webDriver().get(pages().javascriptPage);

  clickOnElementWhichRecordsEvents();

  assertEventFired("mouseup");
}

//@JavascriptEnabled

TEST_F(CorrectEventFiringTest, testShouldFireMouseOverEventWhenClicking) {
  webDriver().get(pages().javascriptPage);

  clickOnElementWhichRecordsEvents();

  assertEventFired("mouseover");
}

// TODO: this is a bad test: mousemove should not fire in a perfect click (e.g. mouse did not move
// while doing down, up, click
//@JavascriptEnabled

//@Ignore(MARIONETTE)
TEST_F(CorrectEventFiringTest, testShouldFireMouseMoveEventWhenClicking) {
  webDriver().get(pages().javascriptPage);

  clickOnElementWhichRecordsEvents();

  assertEventFired("mousemove");
}

//@JavascriptEnabled

//@Ignore(MARIONETTE)
TEST_F(CorrectEventFiringTest, testShouldNotThrowIfEventHandlerThrows) {
  webDriver().get(pages().javascriptPage);

  try {
    webDriver().findElement(By::id("throwing-mouseover")).click();
  } catch (WebDriverException& e) {
    FAIL() << "Error in event handler should not have propagated: " <<  e.what();
  }
}

//@Ignore(value = {CHROME, ANDROID}, reason = "Webkit bug 22261")
//@JavascriptEnabled

TEST_F(CorrectEventFiringTest, testShouldFireEventsInTheRightOrder) {
  webDriver().get(pages().javascriptPage);

  clickOnElementWhichRecordsEvents();

  std::string text = webDriver().findElement(By::id("result")).text();

  int lastIndex = -1;
  std::vector<std::string> events = {"mousedown", "focus", "mouseup", "click"};
  for (std::string event : events) {
    int index = text.find(event);

    ASSERT_TRUE(index != std::string::npos) << event << " did not fire at all";
    ASSERT_TRUE(index > lastIndex) << event << " did not fire in the correct order";
    lastIndex = index;
  }
}

//@JavascriptEnabled
//@Ignore({ANDROID})

TEST_F(CorrectEventFiringTest, testsShouldIssueMouseDownEvents) {
  webDriver().get(pages().javascriptPage);
  webDriver().findElement(By::id("mousedown")).click();

  assertEventFired("mouse down");
  const std::string result = webDriver().findElement(By::id("result")).text();
  ASSERT_STREQ("mouse down", result.data());
}

//@JavascriptEnabled

TEST_F(CorrectEventFiringTest, testShouldIssueClickEvents) {
  webDriver().get(pages().javascriptPage);
  webDriver().findElement(By::id("mouseclick")).click();

  WebElement result = webDriver().findElement(By::id("result"));
  wait().until(ElementTextToBeEqual(result, "mouse click"));
  ASSERT_STREQ(result.text().data(), "mouse click");
}

//@JavascriptEnabled
//@Ignore(value = {ANDROID}, reason = "Android: triggers mouse click instead.")

TEST_F(CorrectEventFiringTest, testShouldIssueMouseUpEvents) {
  webDriver().get(pages().javascriptPage);
  webDriver().findElement(By::id("mouseup")).click();

  WebElement result = webDriver().findElement(By::id("result"));
  wait().until(ElementTextToBeEqual(result, "mouse up"));
  ASSERT_STREQ(result.text().data(), "mouse up");
}

//@JavascriptEnabled
//@Ignore(value = {IPHONE})

TEST_F(CorrectEventFiringTest, testMouseEventsShouldBubbleUpToContainingElements) {
  webDriver().get(pages().javascriptPage);
  webDriver().findElement(By::id("child")).click();

  WebElement result = webDriver().findElement(By::id("result"));
  wait().until(ElementTextToBeEqual(result, "mouse down"));
  ASSERT_STREQ(result.text().data(), "mouse down");
}

//@JavascriptEnabled
//@Ignore(value = {IPHONE, ANDROID, MARIONETTE})

TEST_F(CorrectEventFiringTest, testShouldEmitOnChangeEventsWhenSelectingElements) {
  webDriver().get(pages().javascriptPage);
  // Intentionally not looking up the select tag. See selenium r7937 for details.
  WebElements allOptions = webDriver().findElements(By::xpath("//select[@id='selector']//option"));

  std::string initialTextValue = webDriver().findElement(By::id("result")).text();

  WebElement foo = allOptions[0];
  WebElement bar = allOptions[1];

  foo.click();
  ASSERT_STREQ(webDriver().findElement(By::id("result")).text().data(),
      initialTextValue.data());
  bar.click();
  ASSERT_STREQ(webDriver().findElement(By::id("result")).text().data(),
      "bar");
}

//@JavascriptEnabled
//@Ignore(value = {IPHONE, ANDROID, HTMLUNIT, MARIONETTE})

TEST_F(CorrectEventFiringTest, testShouldEmitOnClickEventsWhenSelectingElements) {
  webDriver().get(pages().javascriptPage);
  // Intentionally not looking up the select tag. See selenium r7937 for details.
  WebElements allOptions = webDriver().findElements(By::xpath("//select[@id='selector2']//option"));

  WebElement foo = allOptions[0];
  WebElement bar = allOptions[1];

  foo.click();
  ASSERT_STREQ(webDriver().findElement(By::id("result")).text().data(),
      "foo");
  bar.click();
  ASSERT_STREQ(webDriver().findElement(By::id("result")).text().data(),
      "bar");
}

//@JavascriptEnabled
//@Ignore(value = {IE, HTMLUNIT},
//    reason = "IE: Only fires the onchange event when the checkbox loses the focus, "
//           + "HtmlUnit: default mode is IE8 now")

TEST_F(CorrectEventFiringTest, testShouldEmitOnChangeEventsWhenChangingTheStateOfACheckbox) {
  webDriver().get(pages().javascriptPage);
  WebElement checkbox = webDriver().findElement(By::id("checkbox"));

  checkbox.click();
  WebElement result = webDriver().findElement(By::id("result"));
  wait().until(ElementTextToBeEqual(result, "checkbox thing"));
}

//@JavascriptEnabled

TEST_F(CorrectEventFiringTest, testShouldEmitClickEventWhenClickingOnATextInputElement) {
  webDriver().get(pages().javascriptPage);

  WebElement clicker = webDriver().findElement(By::id("clickField"));
  clicker.click();

  wait().until(ElementValueToBeEqual(clicker, "Clicked"));
  ASSERT_STREQ(clicker.getAttribute("value").asString().data(), "Clicked");
}


//@Ignore({ANDROID})
//@JavascriptEnabled

TEST_F(CorrectEventFiringTest, testShouldFireTwoClickEventsWhenClickingOnALabel) {
  webDriver().get(pages().javascriptPage);

  webDriver().findElement(By::id("labelForCheckbox")).click();

  WebElement result = webDriver().findElement(By::id("result"));
  std::string val = wait().until(ElementTextToContain(result, "labelclick chboxclick"));
  //ASSERT_STREQ("labelclick chboxclick", val.data());
}

//@Ignore(ANDROID)
//@JavascriptEnabled

TEST_F(CorrectEventFiringTest, testClearingAnElementShouldCauseTheOnChangeHandlerToFire) {
  webDriver().get(pages().javascriptPage);

  WebElement element = webDriver().findElement(By::id("clearMe"));
  element.clear();

  WebElement result = webDriver().findElement(By::id("result"));
  ASSERT_STREQ("Cleared", result.text().data());
}

//@JavascriptEnabled
//@Ignore(value = {IPHONE, ANDROID, MARIONETTE}, reason = "iPhone: sendKeys implementation is incorrect")

/*TEST_F(CorrectEventFiringTest, testSendingKeysToAnotherElementShouldCauseTheBlurEventToFire) {
  //assumeFalse(browserNeedsFocusOnThisOs(driver));

  webDriver().get(pages().javascriptPage);
  WebElement element = webDriver().findElement(By::id("theworks"));
  element.sendKeys("foo");
  WebElement element2 = webDriver().findElement(By::id("changeable"));
  element2.sendKeys("bar");
  assertEventFired("blur");
}*/

//@JavascriptEnabled
//@Ignore(value = {IPHONE, ANDROID, MARIONETTE}, reason = "iPhone: sendKeys implementation is incorrect")
/*
TEST_F(CorrectEventFiringTest, testSendingKeysToAnElementShouldCauseTheFocusEventToFire) {
  assumeFalse(browserNeedsFocusOnThisOs(driver));

  webDriver().get(pages().javascriptPage);
  WebElement element = webDriver().findElement(By::id("theworks"));
  element.sendKeys("foo");
  assertEventFired("focus");
}*/

//@JavascriptEnabled
//@Ignore(value = {IPHONE, ANDROID},
//    reason = "iPhone: input elements are blurred when the keyboard is closed")

/*TEST_F(CorrectEventFiringTest, testSendingKeysToAFocusedElementShouldNotBlurThatElement) {
//  assumeFalse(browserNeedsFocusOnThisOs(driver));

  webDriver().get(pages().javascriptPage);
  WebElement element = webDriver().findElement(By::id("theworks"));
  element.click();

  // Wait until focused
  bool focused = false;
  WebElement result = webDriver().findElement(By::id("result"));
  for (int i = 0; i < 5; ++i) {
    std::string fired = result.text();
    if (fired.find("focus") != std::string::npos) {
      focused = true;
      break;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
  }
  if (!focused) {
    FAIL() << "Clicking on element didn't focus it in time - can't proceed so failing";
  }

  element.sendKeys("a");
  assertEventNotFired("blur");
}*/

//@JavascriptEnabled

//@Ignore(MARIONETTE)
TEST_F(CorrectEventFiringTest, testSubmittingFormFromFormElementShouldFireOnSubmitForThatForm) {
  webDriver().get(pages().javascriptPage);
  WebElement formElement = webDriver().findElement(By::id("submitListeningForm"));
  formElement.submit();
  assertEventFired("form-onsubmit");
}

//@JavascriptEnabled
//@Ignore({ANDROID, MARIONETTE})

TEST_F(CorrectEventFiringTest, testSubmittingFormFromFormInputSubmitElementShouldFireOnSubmitForThatForm) {
  webDriver().get(pages().javascriptPage);
  WebElement submit = webDriver().findElement(By::id("submitListeningForm-submit"));
  submit.submit();
  assertEventFired("form-onsubmit");
}

//@JavascriptEnabled
//@Ignore({ANDROID, MARIONETTE})

TEST_F(CorrectEventFiringTest, testSubmittingFormFromFormInputTextElementShouldFireOnSubmitForThatFormAndNotClickOnThatInput) {
  webDriver().get(pages().javascriptPage);
  WebElement submit = webDriver().findElement(By::id("submitListeningForm-submit"));
  submit.submit();
  assertEventFired("form-onsubmit");
  assertEventNotFired("text-onclick");
}

//@JavascriptEnabled
//@Ignore(value = {IPHONE, ANDROID, OPERA, SAFARI, OPERA_MOBILE, MARIONETTE},
//    reason = "Does not yet support file uploads", issues = { 4220 })

/*TEST_F(CorrectEventFiringTest, testUploadingFileShouldFireOnChangeEvent) {
  webDriver().get(pages().formPage);
  WebElement uploadElement = webDriver().findElement(By::id("upload"));
  WebElement result = webDriver().findElement(By::id("fileResults"));
  ASSERT_STREQ("", result.text().data());

  File file = File.createTempFile("test", "txt");
  file.deleteOnExit();

  uploadElement.sendKeys(file.getAbsolutePath());
  // Shift focus to something else because send key doesn't make the focus leave
  webDriver().findElement(By::id("id-name1")).click();

  assertThat(result.text(), equalTo("changed"));
}*/


//@JavascriptEnabled
//@Ignore(value = {ANDROID}, reason = "Not implemented")

TEST_F(CorrectEventFiringTest, testShouldReportTheXAndYCoordinatesWhenClicking) {
/*  assumeFalse("Skipping test which fails in IE on Sauce",
              SauceDriver.shouldUseSauce() && TestUtilities.isInternetExplorer(driver));*/

  webDriver().get(pages().clickEventPage);

  WebElement element = webDriver().findElement(By::id("eventish"));
  element.click();

  std::string clientX = getTextFromElementOnceAvailable("clientX");
  std::string clientY = getTextFromElementOnceAvailable("clientY");

  ASSERT_STRNE("0", clientX.data());
  ASSERT_STRNE("0", clientY.data());
}

//@JavascriptEnabled
//@Ignore(value = {ANDROID, IPHONE, MARIONETTE}, reason = "Not tested")

TEST_F(CorrectEventFiringTest, testClickEventsShouldBubble) {
  webDriver().get(pages().clicksPage);
  webDriver().findElement(By::id("bubblesFrom")).click();
  ScriptResult eventBubbled = webDriver().executeScript("return !!window.bubbledClick;");

  ASSERT_TRUE(eventBubbled.isBool() && eventBubbled.asBool()) << "Event didn't bubble up";
}
