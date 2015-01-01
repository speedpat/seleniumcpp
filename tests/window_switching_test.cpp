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

#include <gmock/gmock.h>


using namespace selenium;
using namespace testing;

class WindowSwitchingTest : public Test
{
public:
  WindowSwitchingTest()
   : m_driver(nullptr), m_wait(nullptr)\
     {

     }

  virtual void SetUp()
  {
    Test::SetUp();

    m_driver = new WebDriver(testEnvironment().driverUrl(), DesiredCapabilities::FIREFOX);

    m_wait = new Wait(*m_driver, 5);

  }

  virtual void TearDown()
  {
    Test::TearDown();

    delete m_wait;
    m_wait = nullptr;


    if (m_driver)
    {
      m_driver->quit();
      delete m_driver;
      m_driver = nullptr;
    }

  }

  static TestEnvironment& testEnvironment()
  {
    return *selenium::TestEnvironment::s_testEnvironment;
  }

  static Pages& pages()
  {
    return testEnvironment().pages();
  }

  static std::string whereIs(const std::string& relativePath)
  {
    return testEnvironment().whereIs(relativePath);
  }

  WebDriver& webDriver()
  {
    if (m_driver == nullptr)
    {
      throw WebDriverException("illegal state, not properly intialized");
    }
    return *m_driver;
  }

  Wait& wait()
  {
    return *m_wait;
  }


  WebDriver* m_driver;
  Wait* m_wait;

};

class SwitchToAfterTest
{
public:
  SwitchToAfterTest(const std::string& windowName, WebDriver& driver)
   : m_windowName(windowName), m_driver(driver)
  {

  }
  ~SwitchToAfterTest()
  {
    m_driver.switchTo().window(m_windowName);
  }

private:
  std::string m_windowName;
  WebDriver& m_driver;

};




//@Ignore({OPERA_MOBILE, MARIONETTE})
//@Test
TEST_F(WindowSwitchingTest, testShouldSwitchFocusToANewWindowWhenItIsOpenedAndNotStopFutureOperations) {
//  assumeFalse(Browser.detect() == Browser.opera &&
//              TestUtilities.getEffectivePlatform().is(Platform.WINDOWS));

  webDriver().get(pages().xhtmlTestPage);
  std::string current = webDriver().currentWindowHandle();
  WindowHandles currentWindowHandles = webDriver().windowHandles();

  webDriver().findElement(By::linkText("Open new window")).click();

  wait().until(NewWindowIsOpened(currentWindowHandles));

  ASSERT_THAT(webDriver().title(), Eq("XHTML Test Page"));

  webDriver().switchTo().window("result");
  ASSERT_THAT(webDriver().title(), Eq("We Arrive Here"));

  webDriver().get(pages().iframePage);
  std::string handle = webDriver().currentWindowHandle();
  webDriver().findElement(By::id("iframe_page_heading"));
  webDriver().switchTo().frame("iframe1");
  ASSERT_THAT(webDriver().currentWindowHandle(), Eq(handle));

  webDriver().close();
  webDriver().switchTo().window(current);
}

//@Test
TEST_F(WindowSwitchingTest, testShouldThrowNoSuchWindowException) {
  webDriver().get(pages().xhtmlTestPage);
  std::string current = webDriver().currentWindowHandle();

  {
    SwitchToAfterTest(current, webDriver());
    ASSERT_THROW(webDriver().switchTo().window("invalid name"), NoSuchWindowException);
  }
}
/*
//@Ignore({OPERA, OPERA_MOBILE, MARIONETTE})
//@Test
TEST_F(WindowSwitchingTest, testShouldThrowNoSuchWindowExceptionOnAnAttemptToGetItsHandle) {
  webDriver().get(pages().xhtmlTestPage);
  std::string current = webDriver().currentWindowHandle();
  WindowHandles currentWindowHandles = webDriver().windowHandles();

  webDriver().findElement(By::linkText("Open new window")).click();

  wait().until(NewWindowIsOpened(currentWindowHandles));

  webDriver().switchTo().window("result");
  webDriver().close();

  {
    SwitchToAfterTest(current, webDriver());
    ASSERT_THROW(webDriver().currentWindowHandle(), NoSuchWindowException) << "NoSuchWindowException expected";
  }
}*/

/*
//@Ignore({OPERA, OPERA_MOBILE, MARIONETTE})
//@Test
TEST_F(WindowSwitchingTest, testShouldThrowNoSuchWindowExceptionOnAnyOperationIfAWindowIsClosed) {
  webDriver().get(pages().xhtmlTestPage);
  std::string current = webDriver().currentWindowHandle();
  WindowHandles currentWindowHandles = webDriver().windowHandles();

  webDriver().findElement(By::linkText("Open new window")).click();

  wait().until(NewWindowIsOpened(currentWindowHandles));

  webDriver().switchTo().window("result");
  webDriver().close();

  {
    SwitchToAfterTest(current, webDriver());
    EXPECT_THROW(webDriver().title(), NoSuchWindowException) << "NoSuchWindowException expected";

    EXPECT_THROW(webDriver().findElement(By::tagName("body")), NoSuchWindowException) << "NoSuchWindowException expected";
  }
}
*/
//@Ignore({OPERA, OPERA_MOBILE, MARIONETTE})
//@Test
TEST_F(WindowSwitchingTest, testShouldThrowNoSuchWindowExceptionOnAnyElementOperationIfAWindowIsClosed) {
  webDriver().get(pages().xhtmlTestPage);
  std::string current = webDriver().currentWindowHandle();
  WindowHandles currentWindowHandles = webDriver().windowHandles();

  webDriver().findElement(By::linkText("Open new window")).click();

  wait().until(NewWindowIsOpened(currentWindowHandles));

  webDriver().switchTo().window("result");
  WebElement body = webDriver().findElement(By::tagName("body"));
  webDriver().close();

  {
    SwitchToAfterTest(current, webDriver());
    EXPECT_THROW(body.text(), StaleElementReferenceException) << "StaleElementReferenceException expected";
  }
}

//@NeedsFreshDriver
//@NoDriverAfterTest
//@Ignore({IE, REMOTE})
//@Test
TEST_F(WindowSwitchingTest, testShouldBeAbleToIterateOverAllOpenWindows) {
  webDriver().get(pages().xhtmlTestPage);
  webDriver().findElement(By::name("windowOne")).click();
  webDriver().findElement(By::name("windowTwo")).click();

  wait().until(WindowHandleCountToBeGreaterThan(2));

  WindowHandles allWindowHandles = webDriver().windowHandles();

  // There should be three windows. We should also see each of the window titles at least once.
  WindowHandles seenHandles;
  for (std::string handle : allWindowHandles) {
    ASSERT_FALSE(std::find(seenHandles.begin(), seenHandles.end(), handle) != seenHandles.end());
    webDriver().switchTo().window(handle);
    seenHandles.push_back(handle);
  }

  ASSERT_THAT(allWindowHandles.size(), Eq(3));
}

/*//@JavascriptEnabled
//@Test
//@Ignore(MARIONETTE)
TEST_F(WindowSwitchingTest, testClickingOnAButtonThatClosesAnOpenWindowDoesNotCauseTheBrowserToHang) {
//  assumeFalse(Browser.detect() == Browser.opera &&
//              TestUtilities.getEffectivePlatform().is(Platform.WINDOWS));

  webDriver().get(pages().xhtmlTestPage);
  Boolean isIEDriver = TestUtilities.isInternetExplorer(driver);
  Boolean isIE6 = TestUtilities.isIe6(driver);
  std::string currentHandle = webDriver().currentWindowHandle();
  WindowHandles currentWindowHandles = webDriver().windowHandles();

  webDriver().findElement(By::name("windowThree")).click();

  wait().until(newWindowIsOpened(currentWindowHandles));

  webDriver().switchTo().window("result");

  try {
    wait().until(ExpectedConditions.presenceOfElementLocated(By::id("close")));
    webDriver().findElement(By::id("close")).click();

    if (isIEDriver && !isIE6) {
      Alert alert = wait().until(alertIsPresent());
      alert.accept();
    }

    // If we make it this far, we're all good.
  } finally {
    webDriver().switchTo().window(currentHandle);
    webDriver().findElement(By::id("linkId"));
  }
}

//@JavascriptEnabled
//@Test
//@Ignore(MARIONETTE)
TEST_F(WindowSwitchingTest, testCanCallGetWindowHandlesAfterClosingAWindow) {
  assumeFalse(Browser.detect() == Browser.opera &&
              TestUtilities.getEffectivePlatform().is(Platform.WINDOWS));

  webDriver().get(pages().xhtmlTestPage);

  Boolean isIEDriver = TestUtilities.isInternetExplorer(driver);
  Boolean isIE6 = TestUtilities.isIe6(driver);
  std::string currentHandle = webDriver().currentWindowHandle();
  WindowHandles currentWindowHandles = webDriver().windowHandles();

  webDriver().findElement(By::name("windowThree")).click();

  wait().until(newWindowIsOpened(currentWindowHandles));

  webDriver().switchTo().window("result");
  int allWindowHandles = webDriver().windowHandles().size();

  try {
    wait().until(ExpectedConditions.presenceOfElementLocated(By::id("close"))).click();

    if (isIEDriver && !isIE6) {
      Alert alert = wait().until(alertIsPresent());
      alert.accept();
    }

    WindowHandles allHandles = wait().until(windowHandleCountToBe(allWindowHandles - 1));

    assertEquals(currentWindowHandles.size(), allHandles.size());
  } finally {
    webDriver().switchTo().window(currentHandle);
  }
}*/

//@Test
TEST_F(WindowSwitchingTest, testCanObtainAWindowHandle) {
  webDriver().get(pages().xhtmlTestPage);

  std::string currentHandle = webDriver().currentWindowHandle();

  EXPECT_THAT(currentHandle, ::testing::Not(Eq("")));
}

//@Test
TEST_F(WindowSwitchingTest, testFailingToSwitchToAWindowLeavesTheCurrentWindowAsIs) {
  webDriver().get(pages().xhtmlTestPage);
  std::string current = webDriver().currentWindowHandle();

  EXPECT_THROW(webDriver().switchTo().window("i will never exist"), NoSuchWindowException) << "Should not be ablt to change to a non-existant window";

  std::string newHandle = webDriver().currentWindowHandle();

  ASSERT_THAT(current, Eq(newHandle));
}

//@NeedsFreshDriver
//@NoDriverAfterTest
//@Ignore(value = {OPERA_MOBILE})
//@Test
TEST_F(WindowSwitchingTest, testCanCloseWindowWhenMultipleWindowsAreOpen) {
  webDriver().get(pages().xhtmlTestPage);
  WindowHandles currentWindowHandles = webDriver().windowHandles();

  webDriver().findElement(By::name("windowOne")).click();

  wait().until(NewWindowIsOpened(currentWindowHandles));

  WindowHandles allWindowHandles = webDriver().windowHandles();

  // There should be two windows. We should also see each of the window titles at least once.
  ASSERT_THAT(allWindowHandles.size(), Eq(2));
  std::string handle1 = *(++allWindowHandles.begin());
  webDriver().switchTo().window(handle1);
  webDriver().close();
  allWindowHandles = webDriver().windowHandles();
  ASSERT_THAT(allWindowHandles.size(), Eq(1));
}

//@NeedsFreshDriver
//@NoDriverAfterTest
//@Ignore(value = {OPERA_MOBILE})
//@Test
TEST_F(WindowSwitchingTest, testCanCloseWindowAndSwitchBackToMainWindow) {
  webDriver().get(pages().xhtmlTestPage);
  WindowHandles currentWindowHandles = webDriver().windowHandles();

  webDriver().findElement(By::name("windowOne")).click();

  wait().until(NewWindowIsOpened(currentWindowHandles));

  WindowHandles allWindowHandles = webDriver().windowHandles();

  // There should be two windows. We should also see each of the window titles at least once.
  ASSERT_THAT(allWindowHandles.size(), Eq(2));
  WindowHandles::iterator pos = allWindowHandles.begin();
  std::string mainHandle = *pos++;
  std::string handle1 = *pos;
  webDriver().switchTo().window(handle1);
  webDriver().close();
  webDriver().switchTo().window(mainHandle);

  std::string newHandle = webDriver().currentWindowHandle();
  ASSERT_THAT(mainHandle, Eq(newHandle));
}

//@NeedsFreshDriver
//@NoDriverAfterTest
//@Test
TEST_F(WindowSwitchingTest, testClosingOnlyWindowShouldNotCauseTheBrowserToHang) {
  webDriver().get(pages().xhtmlTestPage);
  webDriver().close();
}

//@NeedsFreshDriver
//@NoDriverAfterTest
//@Test
//@Ignore(MARIONETTE)
TEST_F(WindowSwitchingTest, testShouldFocusOnTheTopMostFrameAfterSwitchingToAWindow) {
  webDriver().get(whereIs("window_switching_tests/page_with_frame.html"));

  WindowHandles currentWindowHandles = webDriver().windowHandles();
  std::string mainWindow = webDriver().currentWindowHandle();

  webDriver().findElement(By::id("a-link-that-opens-a-new-window")).click();
  wait().until(NewWindowIsOpened(currentWindowHandles));

  webDriver().switchTo().frame("myframe");

  webDriver().switchTo().window("newWindow");
  webDriver().close();
  webDriver().switchTo().window(mainWindow);

  webDriver().findElement(By::name("myframe"));
}





