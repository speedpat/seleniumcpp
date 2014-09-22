/*
 * alerts_test.cpp
 *
 *  Created on: Sep 20, 2014
 *      Author: speedpat
 */


#include "selenium/selenium.hpp"
#include "support/selenium_testcase.hpp"


using namespace selenium;

class AlertsTest : public SeleniumTestCase
{
public:

  virtual void SetUp()
  {
    SeleniumTestCase::SetUp();
    webDriver().get(testEnvironment().pages().alertsPage);

  }

  virtual void TearDown()
  {
    SeleniumTestCase::TearDown();
  }
};

struct AlertAcceptor
{
  AlertAcceptor(Alert alert) : m_alert(alert) {}
  ~AlertAcceptor()
  {
    try
    {
      m_alert.accept();
    }
    catch (NoAlertPresentException &e)
    {

    }
  }


  Alert m_alert;
};


TEST_F(AlertsTest, testShouldBeAbleToOverrideTheWindowAlertMethod)
{
    webDriver().executeScript(
        "window.alert = function(msg) { document.getElementById('text').innerHTML = msg; }");
    webDriver().findElement(By::id("alert")).click();
}

TEST_F(AlertsTest, testShouldAllowUsersToAcceptAnAlertManually)
{
    webDriver().findElement(By::id("alert")).click();

    Alert alert = wait().until(AlertIsPresent());
    alert.accept();

    // If we can perform any action, we're good to go
    EXPECT_EQ("Testing Alerts", webDriver().title());
}

TEST_F(AlertsTest, testShouldAllowUsersToAcceptAnAlertWithNoTextManually)
{
    webDriver().findElement(By::id("empty-alert")).click();

    Alert alert = wait().until(AlertIsPresent());
    alert.accept();

    // If we can perform any action, we're good to go
    EXPECT_EQ("Testing Alerts", webDriver().title());
  }

TEST_F(AlertsTest, testShouldGetTextOfAlertOpenedInSetTimeout)
{
    webDriver().findElement(By::id("slow-alert")).click();

    // DO NOT WAIT OR SLEEP HERE.
    // This is a regression test for a bug where only the first switchTo call would throw,
    // and only if it happens before the alert actually loads.
    try
    {
      Alert alert = webDriver().switchTo().alert();
      AlertAcceptor acceptor(alert);
      EXPECT_EQ("Slow", alert.text());
    }
    catch (NoAlertPresentException& e)
    {

    }
  }

TEST_F(AlertsTest, testShouldAllowUsersToDismissAnAlertManually)
{
    wait().until(ExpectedConditions::PresenceOfElementLocated(By::id("alert"))).click();

    Alert alert =  wait().until(AlertIsPresent());
    alert.dismiss();

    // If we can perform any action, we're good to go
    EXPECT_EQ("Testing Alerts", webDriver().title());
  }

TEST_F(AlertsTest, testShouldAllowAUserToAcceptAPrompt) {
    webDriver().findElement(By::id("prompt")).click();

    Alert alert = wait().until(AlertIsPresent());
    alert.accept();

    // If we can perform any action, we're good to go
    EXPECT_EQ("Testing Alerts", webDriver().title());
}

TEST_F(AlertsTest, testShouldAllowAUserToDismissAPrompt) {
    webDriver().findElement(By::id("prompt")).click();

    Alert alert = wait().until(AlertIsPresent());
    alert.dismiss();

    // If we can perform any action, we're good to go
    EXPECT_EQ("Testing Alerts", webDriver().title());
  }

TEST_F(AlertsTest, testShouldAllowAUserToSetTheValueOfAPrompt) {
    webDriver().findElement(By::id("prompt")).click();

    Alert alert = wait().until(AlertIsPresent());
    alert.sendKeys("cheese");
    alert.accept();

    wait().until(ExpectedConditions::TextToBePresentInElement(By::id("text"), "cheese"));
  }

/*
 @Ignore(CHROME)
TEST_F(AlertsTest, testSettingTheValueOfAnAlertThrows) {
    webDriver().findElement(By::id("alert")).click();

    {
    Alert alert = wait().until(AlertIsPresent());
    AlertAcceptor acceptor(alert);
    try {
      alert.sendKeys("cheese");
      FAIL() << "Expected exception";
    } catch (ElementNotVisibleException& expected) {
    }
  }
}
*/

TEST_F(AlertsTest, testShouldAllowTheUserToGetTheTextOfAnAlert) {
    webDriver().findElement(By::id("alert")).click();

    Alert alert = wait().until(AlertIsPresent());
    std::string value = alert.text();
    alert.accept();

    EXPECT_EQ("cheese", value);
}

TEST_F(AlertsTest, testShouldAllowTheUserToGetTheTextOfAPrompt)
  {
    webDriver().findElement(By::id("prompt")).click();

    Alert alert = wait().until(AlertIsPresent());
    std::string value = alert.text();
    alert.accept();

    EXPECT_EQ("Enter something", value);
  }

TEST_F(AlertsTest, testAlertShouldNotAllowAdditionalCommandsIfDismissed)
{
    webDriver().findElement(By::id("alert")).click();

    Alert alert = wait().until(AlertIsPresent());
    alert.accept();

    try {
      alert.text();
    } catch (NoAlertPresentException& expected) {
      return;
    }
    FAIL() << "Expected NoAlertPresentException";
}

TEST_F(AlertsTest, testShouldAllowUsersToAcceptAnAlertInAFrame) {
    webDriver().switchTo().frame("iframeWithAlert");

    webDriver().findElement(By::id("alertInFrame")).click();

    Alert alert = wait().until(AlertIsPresent());
    alert.accept();

    // If we can perform any action, we're good to go
    EXPECT_EQ("Testing Alerts", webDriver().title());
  }

/*
TEST_F(AlertsTest, testShouldAllowUsersToAcceptAnAlertInANestedFrame) {
    webDriver().switchTo().frame("iframeWithIframe").switchTo().frame("iframeWithAlert");

    webDriver().findElement(By::id("alertInFrame")).click();

    Alert alert = wait().until(AlertIsPresent());
    alert.accept();

    // If we can perform any action, we're good to go
    EXPECT_EQ("Testing Alerts", webDriver().title());
  }
*/

TEST_F(AlertsTest, testSwitchingToMissingAlertThrows) {
    try {
      webDriver().switchTo().alert().text();
      FAIL() << "Expected exception";
    } catch (NoAlertPresentException& expected) {
      // Expected
    }
  }

/*
TEST_F(AlertsTest, testSwitchingToMissingAlertInAClosedWindowThrows) {
    assumeFalse("This test does not fail on itself, but it causes the subsequent tests to fail",
                isFirefox(webDriver()) &&
                isNativeEventsEnabled(webDriver()) &&
                getEffectivePlatform().is(Platform.LINUX));

    String mainWindow = webDriver().getWindowHandle();
    try {
      webDriver().findElement(By::id("open-new-window")).click();
      wait().until(windowCountIs(2));
      wait().until(ableToSwitchToWindow("newwindow"));
      webDriver().close();

      try {
        webDriver().switchTo().alert();
        fail("Expected exception");
      } catch (NoSuchWindowException expected) {
        // Expected
      }

    } finally {
      webDriver().switchTo().window(mainWindow);
      wait().until(textInElementLocated(By::id("open-new-window"), "open new window"));
    }
  }
*/

TEST_F(AlertsTest, testPromptShouldUseDefaultValueIfNoKeysSent) {
    webDriver().findElement(By::id("prompt-with-default")).click();

    Alert alert = wait().until(AlertIsPresent());
    alert.accept();

    wait().until(ExpectedConditions::TextToBePresentInElement(By::id("text"), "This is a default value"));
  }

TEST_F(AlertsTest, testPromptShouldHaveNullValueIfDismissed) {
    webDriver().findElement(By::id("prompt-with-default")).click();

    Alert alert = wait().until(AlertIsPresent());
    alert.dismiss();

    wait().until(ExpectedConditions::TextToBePresentInElement(By::id("text"), "null"));
  }



  TEST_F(AlertsTest, testHandlesTwoAlertsFromOneInteraction) {
    wait().until(ExpectedConditions::PresenceOfElementLocated(By::id("double-prompt"))).click();

    Alert alert1 = wait().until(AlertIsPresent());
    alert1.sendKeys("brie");
    alert1.accept();

    Alert alert2 = wait().until(AlertIsPresent());
    alert2.sendKeys("cheddar");
    alert2.accept();

    wait().until(ExpectedConditions::TextToBePresentInElement(By::id("text1"), "brie"));
    wait().until(ExpectedConditions::TextToBePresentInElement(By::id("text2"), "cheddar"));
  }



TEST_F(AlertsTest, testShouldHandleAlertOnPageLoad) {
    webDriver().findElement(By::id("open-page-with-onload-alert")).click();

    Alert alert = wait().until(AlertIsPresent());
    std::string value = alert.text();
    alert.accept();

    EXPECT_EQ("onload", value);
    wait().until(ExpectedConditions::TextToBePresentInElement(By::tagName("p"), "Page with onload event handler"));
  }


/*
TEST_F(AlertsTest, testShouldHandleAlertOnPageLoadUsingGet) {
    webDriver().get(testEnvironment().pages().pageWithOnLoad);

    Alert alert = wait().until(AlertIsPresent());
    std::string value = alert.text();
    alert.accept();

    EXPECT_EQ("onload", value);
    wait().until(TextToBePresentInElement(By::tagName("p"), "Page with onload event handler"));
  }
*/

/*
TEST_F(AlertsTest, testShouldNotHandleAlertInAnotherWindow) {
    std::string mainWindow = webDriver().currentWindowHandle();
    std::vector<std::string> currentWindowHandles = webDriver().windowHandles();
    std::string onloadWindow = "";
//    try {
      webDriver().findElement(By::id("open-window-with-onload-alert")).click();
      onloadWindow = wait().until(newWindowIsOpened(currentWindowHandles));

      bool gotException = false;
      try {
        wait().until(AlertIsPresent());
      } catch (AssertionError expected) {
        // Expected
        gotException = true;
      }
      EXPECT_TRUE(gotException);

    } finally {
      webDriver().switchTo().window(onloadWindow);
      wait().until(AlertIsPresent()).dismiss();
      webDriver().close();
      webDriver().switchTo().window(mainWindow);
      wait().until(textInElementLocated(By::id("open-window-with-onload-alert"), "open new window"));
//    }
  }
*/

/*
TEST_F(AlertsTest, testShouldHandleAlertOnPageUnload) {
    assumeFalse("Firefox 27 does not trigger alerts on unload",
        isFirefox(webDriver()) && getFirefoxVersion(webDriver()) >= 27);
    webDriver().findElement(By::id("open-page-with-onunload-alert")).click();
    webDriver().navigate().back();

    Alert alert = wait().until(AlertIsPresent());
    String value = alert.getText();
    alert.accept();

    EXPECT_EQ("onunload", value);
    wait().until(textInElementLocated(By::id("open-page-with-onunload-alert"), "open new page"));
  }
*/

/*
TEST_F(AlertsTest, testShouldHandleAlertOnPageBeforeUnload) {
    webDriver().get(appServer.whereIs("pageWithOnBeforeUnloadMessage.html"));

    WebElement element = webDriver().findElement(By::id("navigate"));
    element.click();

    Alert alert = wait().until(AlertIsPresent());
    alert.dismiss();
    assertThat(webDriver().getCurrentUrl(), containsString("pageWithOnBeforeUnloadMessage.html"));

    element.click();
    alert = wait().until(AlertIsPresent());
    alert.accept();
    wait().until(titleIs("Testing Alerts"));
  }

  @NoDriverAfterTest

TEST_F(AlertsTest, testShouldHandleAlertOnPageBeforeUnloadAtQuit() {
    webDriver().get(appServer.whereIs("pageWithOnBeforeUnloadMessage.html"));

    WebElement element = webDriver().findElement(By::id("navigate"));
    element.click();

    wait().until(AlertIsPresent());

    webDriver().quit();
  }


  @Ignore(value = {ANDROID, CHROME}, reason = "On Android, alerts do not pop up" +
      " when a window is closed.")

TEST_F(AlertsTest, testShouldHandleAlertOnWindowClose() {
    if (isFirefox(webDriver()) &&
        isNativeEventsEnabled(webDriver()) &&
        getEffectivePlatform().is(Platform.LINUX)) {
      System.err.println("x_ignore_nofocus can cause a firefox crash here. Ignoring test. See issue 2987.");
      assumeTrue(false);
    }
    assumeFalse("Firefox 27 does not trigger alerts on unload",
        isFirefox(webDriver()) && getFirefoxVersion(webDriver()) >= 27);
    String mainWindow = webDriver().getWindowHandle();
    try {
      webDriver().findElement(By::id("open-window-with-onclose-alert")).click();
      wait().until(windowCountIs(2));
      wait().until(ableToSwitchToWindow("onclose"));
      webDriver().close();

      Alert alert = wait().until(AlertIsPresent());
      String value = alert.getText();
      alert.accept();

      EXPECT_EQ("onunload", value);

    } finally {
      webDriver().switchTo().window(mainWindow);
      wait().until(textInElementLocated(By::id("open-window-with-onclose-alert"), "open new window"));
    }
  }


  @Ignore(value = {ANDROID, CHROME, HTMLUNIT, IPHONE, OPERA})

TEST_F(AlertsTest, testIncludesAlertTextInUnhandledAlertException() {
    webDriver().findElement(By::id("alert")).click();
    wait().until(AlertIsPresent());
    try {
      webDriver().title();
      fail("Expected UnhandledAlertException");
    } catch (UnhandledAlertException e) {
      EXPECT_EQ("cheese", e.getAlertText());
      assertThat(e.getMessage(), containsString("cheese"));
    }
  }

  @NoDriverAfterTest

TEST_F(AlertsTest, testCanQuitWhenAnAlertIsPresent() {
    webDriver().get(pages.alertsPage);
    webDriver().findElement(By::id("alert")).click();
    wait().until(AlertIsPresent());

    webDriver().quit();
  }

  private static ExpectedCondition<Boolean> textInElementLocated(
      final By locator, final String text) {
    return new ExpectedCondition<Boolean>() {
      @Override
      public Boolean apply(WebDriver webDriver()) {
        return text.equals(webDriver().findElement(locator).getText());
      }
    };
  }

  private static ExpectedCondition<Boolean> windowCountIs(final int count) {
    return new ExpectedCondition<Boolean>() {
      @Override
      public Boolean apply(WebDriver webDriver()) {
        return webDriver().getWindowHandles().size() == count;
      }
    };
  }

  private static ExpectedCondition<WebDriver> ableToSwitchToWindow(final String name) {
    return new ExpectedCondition<WebDriver>() {
      @Override
      public WebDriver apply(WebDriver webDriver()) {
        return webDriver().switchTo().window(name);
      }
    };
  }

  private static ExpectedCondition<String> newWindowIsOpened(final Set<String> originalHandles) {
    return new ExpectedCondition<String>() {
      @Override
      public String apply(WebDriver webDriver()) {
        Set<String> currentWindowHandles = webDriver().getWindowHandles();
        currentWindowHandles.removeAll(originalHandles);
        return currentWindowHandles.isEmpty() ? null : currentWindowHandles.iterator().next();
      }
    };
  }
*/

