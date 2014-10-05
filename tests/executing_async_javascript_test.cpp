/*
 * executing_async_javascript_test.cpp
 *
 *  Created on: Sep 20, 2014
 *      Author: speedpat
 */

#include <list>

#include "selenium/selenium.hpp"
#include "support/selenium_testcase.hpp"
#include "support/expected_test_conditions.hpp"

using namespace selenium;

class ExecutingAsyncJavaScript : public SeleniumTestCase
{
public:

  virtual void SetUp()
  {
    SeleniumTestCase::SetUp();
    //webDriver().setScriptTimeout(1);
  }

  virtual void TearDown()
  {
    SeleniumTestCase::TearDown();
  }

  ::testing::AssertionResult notNull(const ScriptResult& result)
  {
    if (result.isNull())
    {
      return ::testing::AssertionFailure();
    }
    return ::testing::AssertionSuccess();
  }

  ::testing::AssertionResult null(const ScriptResult& result)
  {
    if (!result.isNull())
    {
      return ::testing::AssertionFailure();
    }
    return ::testing::AssertionSuccess();
  }
};






//@JavascriptEnabled
//@Test
TEST_F(ExecutingAsyncJavaScript, shouldNotTimeoutIfCallbackInvokedImmediately) {
  webDriver().get(pages().ajaxyPage);
  int result = webDriver().executeAsyncScript("arguments[arguments.length - 1](123);");
  ASSERT_EQ(123, result);
}

//@JavascriptEnabled
//@Test
TEST_F(ExecutingAsyncJavaScript, shouldBeAbleToReturnJavascriptPrimitivesFromAsyncScripts_NeitherNullNorUndefined) {
  webDriver().get(pages().ajaxyPage);
  ASSERT_EQ(webDriver().executeAsyncScript(
      "arguments[arguments.length - 1](123);"), 123);
  ASSERT_EQ(webDriver().executeAsyncScript("arguments[arguments.length - 1]('abc');"), "abc");
  ASSERT_EQ("abc", webDriver().executeAsyncScript("arguments[arguments.length - 1]('abc');"));
  ASSERT_FALSE((bool)webDriver().executeAsyncScript("arguments[arguments.length - 1](false);"));
  ASSERT_TRUE((bool) webDriver().executeAsyncScript("arguments[arguments.length - 1](true);"));
}

//@JavascriptEnabled
//@Test
TEST_F(ExecutingAsyncJavaScript, shouldBeAbleToReturnJavascriptPrimitivesFromAsyncScripts_NullAndUndefined) {
  webDriver().get(pages().ajaxyPage);
  ASSERT_TRUE(null(webDriver().executeAsyncScript("arguments[arguments.length - 1](null)")));
  ASSERT_TRUE(null(webDriver().executeAsyncScript("arguments[arguments.length - 1]()")));
}


//@JavascriptEnabled
//@Test
TEST_F(ExecutingAsyncJavaScript, shouldBeAbleToReturnAnArrayLiteralFromAnAsyncScript) {
  webDriver().get(pages().ajaxyPage);

  ScriptResult result = webDriver().executeAsyncScript("arguments[arguments.length - 1]([]);");
  //assertThat(result, instanceOf(List.class));
  //assertTrue(((List<?>) result).isEmpty());
  ASSERT_TRUE(result.begin() == result.end());
}


//@JavascriptEnabled
//@Test
TEST_F(ExecutingAsyncJavaScript, shouldBeAbleToReturnAnArrayScriptResultFromAnAsyncScript) {
  webDriver().get(pages().ajaxyPage);

  ScriptResult result = webDriver().executeAsyncScript("arguments[arguments.length - 1](new Array());");
  ASSERT_TRUE(notNull(result)) << "Expected not to be null!";

/*  assertThat(result, instanceOf(List.class));
  assertTrue(((List<?>) result).isEmpty());*/
  ASSERT_TRUE(result.begin() == result.end());
}


//@JavascriptEnabled
//@Test
//@Ignore(value = {ANDROID},
//       reason = "Android does not properly handle arrays")
TEST_F(ExecutingAsyncJavaScript, shouldBeAbleToReturnArraysOfPrimitivesFromAsyncScripts) {
  webDriver().get(pages().ajaxyPage);

  ScriptResult result = webDriver().executeAsyncScript(
      "arguments[arguments.length - 1]([null, 123, 'abc', true, false]);");

  ASSERT_TRUE(notNull(result));
  ASSERT_TRUE(result.isArray());

  ScriptResult::iterator results = result.begin();
  ASSERT_TRUE(null(*results++));
  ASSERT_EQ(123, (long)(*results++));
  ASSERT_STREQ("abc", ((std::string)(*results++)).data());
  ASSERT_TRUE((bool)(*results++));
  ASSERT_FALSE((bool)(*results++));
  ASSERT_TRUE(results == result.end());
}


//@JavascriptEnabled
//@Test
TEST_F(ExecutingAsyncJavaScript, shouldBeAbleToReturnWebElementsFromAsyncScripts) {
  webDriver().get(pages().ajaxyPage);

  ScriptResult result = webDriver().executeAsyncScript("arguments[arguments.length - 1](document.body);");
  ASSERT_STRCASEEQ("body", ((WebElement) result).tagName().data());
}

//@JavascriptEnabled
//@Test
//@Ignore(value = {ANDROID},
//        reason = "Android does not properly handle arrays")
TEST_F(ExecutingAsyncJavaScript, shouldBeAbleToReturnArraysOfWebElementsFromAsyncScripts) {
  webDriver().get(pages().ajaxyPage);

  ScriptResult result = webDriver().executeAsyncScript(
      "arguments[arguments.length - 1]([document.body, document.body]);");
  ASSERT_TRUE(notNull(result));

  ASSERT_EQ(2, result.size());
  ScriptResult::iterator results = result.begin();
  WebElement element1 = *results++;
  WebElement element2 = *results;
  ASSERT_STRCASEEQ("body", element1.tagName().data());
  ASSERT_STRCASEEQ("body", element2.tagName().data());
  ASSERT_EQ(element1, element2);
}


//@JavascriptEnabled
//@Test
TEST_F(ExecutingAsyncJavaScript, shouldTimeoutIfScriptDoesNotInvokeCallback) {
  webDriver().get(pages().ajaxyPage);
  // Script is expected to be async and explicitly callback, so this should timeout.
  ASSERT_THROW(webDriver().executeAsyncScript("return 1 + 2;"), TimeoutException);
}


//@JavascriptEnabled
//@Test
TEST_F(ExecutingAsyncJavaScript, shouldTimeoutIfScriptDoesNotInvokeCallbackWithAZeroTimeout) {
  webDriver().get(pages().ajaxyPage);
  ASSERT_THROW(webDriver().executeAsyncScript("window.setTimeout(function() {}, 0);"), TimeoutException);
}

//@JavascriptEnabled
//@Test
TEST_F(ExecutingAsyncJavaScript, shouldNotTimeoutIfScriptCallsbackInsideAZeroTimeout) {
  webDriver().get(pages().ajaxyPage);
  webDriver().executeAsyncScript(
      "var callback = arguments[arguments.length - 1];"
      "window.setTimeout(function() { callback(123); }, 0)");
}

//@JavascriptEnabled
//@Test
TEST_F(ExecutingAsyncJavaScript, shouldTimeoutIfScriptDoesNotInvokeCallbackWithLongTimeout) {
  webDriver().setScriptTimeout(std::chrono::milliseconds(500));
  webDriver().get(pages().ajaxyPage);
  ASSERT_THROW(webDriver().executeAsyncScript(
        "var callback = arguments[arguments.length - 1];"
        "window.setTimeout(callback, 1500);"), TimeoutException);
}
/*
//@JavascriptEnabled
//@Test
//@Ignore(IE)
TEST_F(ExecutingAsyncJavaScript, shouldDetectPageLoadsWhileWaitingOnAnAsyncScriptAndReturnAnError) {
  webDriver().get(pages().ajaxyPage);
  webDriver().manage().timeouts().setScriptTimeout(100, TimeUnit.MILLISECONDS);
  try {
    webDriver().executeAsyncScript("window.location = '" + pages().dynamicPage + "';");
    fail();
  } catch (WebDriverException expected) {
  }
}

//@JavascriptEnabled
//@Test
TEST_F(ExecutingAsyncJavaScript, shouldCatchErrorsWhenExecutingInitialScript) {
  webDriver().get(pages().ajaxyPage);
  try {
    webDriver().executeAsyncScript("throw Error('you should catch this!');");
    fail();
  } catch (WebDriverException expected) {
  }
}

//@JavascriptEnabled
//@Test
TEST_F(ExecutingAsyncJavaScript, shouldNotTimeoutWithMultipleCallsTheFirstOneBeingSynchronous) {
  webDriver().get(pages().ajaxyPage);
  webDriver().manage().timeouts().setScriptTimeout(10, TimeUnit.MILLISECONDS);
  assertTrue((Boolean) webDriver().executeAsyncScript("arguments[arguments.length - 1](true);"));
  assertTrue((Boolean) webDriver().executeAsyncScript(
      "var cb = arguments[arguments.length - 1]; window.setTimeout(function(){cb(true);}, 9);"));
}

//@JavascriptEnabled
//@Test
//@Ignore(value = {ANDROID, CHROME, HTMLUNIT, IE, IPHONE, OPERA, OPERA_MOBILE, PHANTOMJS, SAFARI})
TEST_F(ExecutingAsyncJavaScript, shouldCatchErrorsWithMessageAndStacktraceWhenExecutingInitialScript) {
  webDriver().get(pages().ajaxyPage);
  String js = "function functionB() { throw Error('errormessage'); };"
              + "function functionA() { functionB(); };"
              + "functionA();";
  try {
    webDriver().executeAsyncScript(js);
    fail("Expected an exception");
  } catch (WebDriverException e) {
    assertThat(e.getMessage(), containsString("errormessage"));

    Throwable rootCause = Throwables.getRootCause(e);
    assertThat(rootCause.getMessage(), containsString("errormessage"));

    StackTraceElement [] st = rootCause.getStackTrace();
    boolean seen = false;
    for (StackTraceElement s: st) {
      if (s.getMethodName().equals("functionB")) {
        seen = true;
      }
    }
    assertTrue("Stacktrace has not js method info", seen);
  }
}

//@Ignore(value = {ANDROID},
        reason = "Android: Emulator is too slow and latency causes test to fall out of sync with app;")
//@JavascriptEnabled
//@Test
TEST_F(ExecutingAsyncJavaScript, shouldBeAbleToExecuteAsynchronousScripts) {
  webDriver().get(pages().ajaxyPage);

  WebElement typer = webDriver().findElement(By.name("typer"));
  typer.sendKeys("bob");
  ASSERT_EQ("bob", typer.getAttribute("value"));

  webDriver().findElement(By.id("red")).click();
  webDriver().findElement(By.name("submit")).click();

  ASSERT_EQ("There should only be 1 DIV at this point, which is used for the butter message",
               1, getNumDivElements());

  webDriver().manage().timeouts().setScriptTimeout(15, TimeUnit.SECONDS);
  String text = (String) webDriver().executeAsyncScript(
      "var callback = arguments[arguments.length - 1];"
      + "window.registerListener(arguments[arguments.length - 1]);");
  ASSERT_EQ("bob", text);
  ASSERT_EQ("", typer.getAttribute("value"));

  ASSERT_EQ("There should be 1 DIV (for the butter message) + 1 DIV (for the new label)",
               2, getNumDivElements());
}

//@JavascriptEnabled
//@Test
TEST_F(ExecutingAsyncJavaScript, shouldBeAbleToPassMultipleArgumentsToAsyncScripts) {
  webDriver().get(pages().ajaxyPage);
  Number result = (Number) ((JavascriptExecutor) webDriver().
      .executeAsyncScript("arguments[arguments.length - 1](arguments[0] + arguments[1]);", 1, 2);
  ASSERT_EQ(3, result.intValue());
}

//@JavascriptEnabled
//@Test
//@NeedsLocalEnvironment(reason = "Relies on timing")
TEST_F(ExecutingAsyncJavaScript, shouldBeAbleToMakeXMLHttpRequestsAndWaitForTheResponse) {
  String script =
      "var url = arguments[0];" +
      "var callback = arguments[arguments.length - 1];" +
      // Adapted from http://www.quirksmode.org/js/xmlhttp.html
      "var XMLHttpFactories = [" +
      "  function () {return new XMLHttpRequest()}," +
      "  function () {return new ActiveXScriptResult('Msxml2.XMLHTTP')}," +
      "  function () {return new ActiveXScriptResult('Msxml3.XMLHTTP')}," +
      "  function () {return new ActiveXScriptResult('Microsoft.XMLHTTP')}" +
      "];" +
      "var xhr = false;" +
      "while (!xhr && XMLHttpFactories.length) {" +
      "  try {" +
      "    xhr = XMLHttpFactories.shift().call();" +
      "  } catch (e) {}" +
      "}" +
      "if (!xhr) throw Error('unable to create XHR ScriptResult');" +
      "xhr.open('GET', url, true);" +
      "xhr.onreadystatechange = function() {" +
      "  if (xhr.readyState == 4) callback(xhr.responseText);" +
      "};" +
      "xhr.send('');"; // empty string to stop firefox 3 from choking

  webDriver().get(pages().ajaxyPage);
  webDriver().manage().timeouts().setScriptTimeout(3, TimeUnit.SECONDS);
  String response = (String) ((JavascriptExecutor) webDriver().
      .executeAsyncScript(script, pages().sleepingPage + "?time=2");
  assertThat(response.trim(),
             equalTo("<html><head><title>Done</title></head><body>Slept for 2s</body></html>"));
}

//@JavascriptEnabled
//@Test
//@Ignore(value = {ANDROID, CHROME, HTMLUNIT, IE, IPHONE, OPERA})
//@NeedsLocalEnvironment(reason = "Relies on timing")
TEST_F(ExecutingAsyncJavaScript, throwsIfScriptTriggersAlert) {
  webDriver().get(pages().simpleTestPage);
  webDriver().manage().timeouts().setScriptTimeout(5000, TimeUnit.MILLISECONDS);
  try {
    ((JavascriptExecutor) webDriver()..executeAsyncScript(
        "setTimeout(arguments[0], 200) ; setTimeout(function() { window.alert('Look! An alert!'); }, 50);");
    fail("Expected UnhandledAlertException");
  } catch (UnhandledAlertException expected) {
    // Expected exception
  }
  // Shouldn't throw
  webDriver().getTitle();
}

//@JavascriptEnabled
//@Test
//@Ignore(value = {ANDROID, CHROME, HTMLUNIT, IE, IPHONE, OPERA})
//@NeedsLocalEnvironment(reason = "Relies on timing")
TEST_F(ExecutingAsyncJavaScript, throwsIfAlertHappensDuringScript) {
  webDriver().get(pages().slowLoadingAlertPage);
  webDriver().manage().timeouts().setScriptTimeout(5000, TimeUnit.MILLISECONDS);
  try {
    ((JavascriptExecutor) webDriver()..executeAsyncScript("setTimeout(arguments[0], 1000);");
    fail("Expected UnhandledAlertException");
  } catch (UnhandledAlertException expected) {
    //Expected exception
  }
  // Shouldn't throw
  webDriver().getTitle();
}

//@Test
//@Ignore(value = {ANDROID, CHROME, HTMLUNIT, IE, IPHONE, OPERA})
//@NeedsLocalEnvironment(reason = "Relies on timing")
TEST_F(ExecutingAsyncJavaScript, throwsIfScriptTriggersAlertWhichTimesOut) {
  webDriver().get(pages().simpleTestPage);
  webDriver().manage().timeouts().setScriptTimeout(5000, TimeUnit.MILLISECONDS);
  try {
    ((JavascriptExecutor) webDriver().
        .executeAsyncScript("setTimeout(function() { window.alert('Look! An alert!'); }, 50);");
    fail("Expected UnhandledAlertException");
  } catch (UnhandledAlertException expected) {
    // Expected exception
  }
  // Shouldn't throw
  webDriver().getTitle();
}

//@JavascriptEnabled
//@Test
//@Ignore(value = {ANDROID, CHROME, HTMLUNIT, IE, IPHONE, OPERA})
//@NeedsLocalEnvironment(reason = "Relies on timing")
TEST_F(ExecutingAsyncJavaScript, throwsIfAlertHappensDuringScriptWhichTimesOut) {
  webDriver().get(pages().slowLoadingAlertPage);
  webDriver().manage().timeouts().setScriptTimeout(5000, TimeUnit.MILLISECONDS);
  try {
    ((JavascriptExecutor) webDriver()..executeAsyncScript("");
    fail("Expected UnhandledAlertException");
  } catch (UnhandledAlertException expected) {
    //Expected exception
  }
  // Shouldn't throw
  webDriver().getTitle();
}

//@JavascriptEnabled
//@Test
//@Ignore(value = {ANDROID, CHROME, HTMLUNIT, IE, IPHONE, OPERA})
//@NeedsLocalEnvironment(reason = "Relies on timing")
TEST_F(ExecutingAsyncJavaScript, includesAlertTextInUnhandledAlertException) {
  webDriver().manage().timeouts().setScriptTimeout(5000, TimeUnit.MILLISECONDS);
  String alertText = "Look! An alert!";
  try {
    ((JavascriptExecutor) webDriver()..executeAsyncScript(
        "setTimeout(arguments[0], 200) ; setTimeout(function() { window.alert('" + alertText
        + "'); }, 50);");
    fail("Expected UnhandledAlertException");
  } catch (UnhandledAlertException e) {
    ASSERT_EQ(alertText, e.getAlertText());
  }
}

private long getNumDivElements() {
  // Selenium does not support "findElements" yet, so we have to do this through a script.
  return (Long) ((JavascriptExecutor) webDriver()..executeScript(
      "return document.getElementsByTagName('div').length;");
}
*/
