/*
 * executing_javascript_test.cpp
 *
 *  Created on: Sep 20, 2014
 *      Author: speedpat
 */

#include <list>

#include <boost/algorithm/string.hpp>

#include "selenium/selenium.hpp"
#include "support/selenium_testcase.hpp"
#include "support/expected_test_conditions.hpp"

using namespace selenium;

class ExecutingJavaScript : public SeleniumTestCase
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


  ::testing::AssertionResult null(ScriptResult& attribute)
  {
    return (attribute.isNull()) ? ::testing::AssertionSuccess() : ::testing::AssertionFailure();
  }

  template <class First, class Second>
  ::testing::AssertionResult compareLists(First& first, Second& second) {
  if (first.size() != second.size()) {
    return ::testing::AssertionSuccess();
  }
  typename First::iterator fit = first.begin();
  typename Second::iterator sit = second.begin();
  for (; fit != first.end(); ++fit) {
    if ((*fit).isArray()) {
      First f = *fit;
      Second s = *sit;
      return compareLists(f, s);
    } else {
      if (!equals(*fit, *sit++)) {
        return ::testing::AssertionFailure();
      }
    }
  }
  return ::testing::AssertionSuccess();
}

};


//@JavascriptEnabled
//@Test
TEST_F(ExecutingJavaScript, testShouldBeAbleToExecuteSimpleJavascriptAndReturnAString) {
  webDriver().get(pages().xhtmlTestPage);

  ScriptResult result = webDriver().executeScript("return document.title;");

  ASSERT_TRUE(result.isString());
  ASSERT_TRUE(equals("XHTML Test Page", (std::string)result));
}

//@JavascriptEnabled
//@Test
TEST_F(ExecutingJavaScript, testShouldBeAbleToExecuteSimpleJavascriptAndReturnALong) {
  webDriver().get(pages().nestedPage);

  ScriptResult result = webDriver().executeScript("return document.getElementsByName('checky').length;");

  ASSERT_TRUE(result.isInt());
  ASSERT_TRUE(((long) result) > 1);
}

//@JavascriptEnabled
//@Test
TEST_F(ExecutingJavaScript, testShouldBeAbleToExecuteSimpleJavascriptAndReturnAWebElement) {
  webDriver().get(pages().xhtmlTestPage);

  ScriptResult result = webDriver().executeScript("return document.getElementById('id1');");

  ASSERT_FALSE(null(result));
  ASSERT_TRUE(equalsIgnoreCase("a", ((WebElement) result).tagName()));
}


//@JavascriptEnabled
//@Test
TEST_F(ExecutingJavaScript, testShouldBeAbleToExecuteSimpleJavascriptAndReturnABoolean) {
  webDriver().get(pages().xhtmlTestPage);

  ScriptResult result = webDriver().executeScript("return true;");

  ASSERT_FALSE(null(result));
  ASSERT_TRUE(result.isBool());
  ASSERT_TRUE((bool)result);
}


//@SuppressWarnings("unchecked")
//@JavascriptEnabled
//@Test
TEST_F(ExecutingJavaScript, testShouldBeAbleToExecuteSimpleJavascriptAndReturnAStringsArray) {
  webDriver().get(pages().javascriptPage);
  Response expectedResult;
  expectedResult.append("zero");
  expectedResult.append("one");
  expectedResult.append("two");
  ScriptResult result = webDriver().executeScript(
      "return ['zero', 'one', 'two'];");

  ASSERT_TRUE(compareLists(expectedResult, result));
}

//@SuppressWarnings("unchecked")
//@JavascriptEnabled
//@Test
TEST_F(ExecutingJavaScript, testShouldBeAbleToExecuteSimpleJavascriptAndReturnAnArray) {
  webDriver().get(pages().javascriptPage);
  Response expectedResult(Json::arrayValue);
  expectedResult.append("zero");
  Response subList(Json::arrayValue);
  subList.append(true);
  subList.append(false);
  expectedResult.append(subList);
  ScriptResult result = webDriver().executeScript("return ['zero', [true, false]];");
  ASSERT_FALSE(null(result));
  ASSERT_TRUE(result.isArray()) << "result was not an array " << (std::string)result;
  ASSERT_TRUE(compareLists(expectedResult, result));
}



//@SuppressWarnings("unchecked")
//@JavascriptEnabled
//@Test
TEST_F(ExecutingJavaScript, testShouldBeAbleToExecuteJavascriptAndReturnABasicObjectLiteral) {
  webDriver().get(pages().javascriptPage);

  ScriptResult result = webDriver().executeScript("return {abc: '123', tired: false};");
  ASSERT_TRUE(result.isObject()) << "result was not an object";

  Response expected(Json::objectValue);
  expected["abc"] = "123";
  expected["tired"] = false;

  // Cannot do an exact match; Firefox 4 inserts a few extra keys in our object; this is OK, as
  // long as the expected keys are there.
  ASSERT_GE(result.size(), expected.size()) << "Expected:<" << expected.size() << ">, but was:<" << result.size() + ">";

  Response::iterator expIterator = expected.begin();
  for (; expIterator != expected.end(); ++expIterator)
  {
    Response& exp = *expIterator;
    std::string key = expIterator.key().asString();
    Response& act = result[key];
    ASSERT_TRUE(equals(exp, act)) << "Difference at key:<" << expIterator.key() << ">";
  }
}

//@SuppressWarnings("unchecked")
//@JavascriptEnabled
//@Test
TEST_F(ExecutingJavaScript, testShouldBeAbleToExecuteSimpleJavascriptAndReturnAnObjectLiteral) {
  webDriver().get(pages().javascriptPage);

  Response expectedResult(Json::objectValue);
  expectedResult["foo"] = "bar";
  Response arrayResult(Json::arrayValue);
  arrayResult.append("a");
  arrayResult.append("b");
  arrayResult.append("c");
  expectedResult["baz"] = arrayResult;
  Response objectResult(Json::objectValue);
  objectResult["first"] = "John";
  objectResult["last"] = "Doe";
  expectedResult["person"] = objectResult;

  ScriptResult result = webDriver().executeScript(
      "return {foo:'bar', baz: ['a', 'b', 'c'], "
      "person: {first: 'John',last: 'Doe'}};");
  ASSERT_TRUE(result.isObject()) << "result was not an object";

  ASSERT_GE(result.size(), expectedResult.size()) << "Expected:<" << expectedResult.size() << ">, but was:<" << result.size() << ">";
  ASSERT_TRUE(equals("bar", result["foo"]));
  ASSERT_TRUE(compareLists(expectedResult["baz"],
                          result["baz"]));

  Response person = result["person"];
  ASSERT_GE(person.size(), 2) << "Expected:<{first:John, last:Doe}>, but was:<" << person << ">";
  ASSERT_TRUE(equals("John", person["first"]));
  ASSERT_TRUE(equals("Doe", person["last"]));
}

//@SuppressWarnings("unchecked")
//@JavascriptEnabled
//@Ignore({IE, OPERA, OPERA_MOBILE})
//@Test
TEST_F(ExecutingJavaScript, testShouldBeAbleToExecuteSimpleJavascriptAndReturnAComplexObject) {
  webDriver().get(pages().javascriptPage);

  ScriptResult result = webDriver().executeScript("return window.location;");

  ASSERT_TRUE(result.isObject());
  ASSERT_TRUE(equals("http:", result["protocol"]));
  ASSERT_TRUE(equals(result["href"], pages().javascriptPage));
}

//@JavascriptEnabled
//@Test
TEST_F(ExecutingJavaScript, testPassingAndReturningALongShouldReturnAWholeNumber) {
  webDriver().get(pages().javascriptPage);
  long expectedResult = 1L;
  ScriptResult result = webDriver().executeScript("return arguments[0];", {expectedResult});
  ASSERT_TRUE(result.isConvertibleTo(Json::intValue)) << "Expected result to be an Integer or Long";
  ASSERT_EQ(expectedResult, result.asInt64());
}

//@JavascriptEnabled
//@Test
TEST_F(ExecutingJavaScript, testPassingAndReturningADoubleShouldReturnADecimal) {
  webDriver().get(pages().javascriptPage);
  double expectedResult = 1.2;
  ScriptResult result = webDriver().executeScript("return arguments[0];", {expectedResult});
  ASSERT_TRUE(result.isConvertibleTo(Json::realValue)) << "Expected result to be a Double or Float";;
  ASSERT_EQ(expectedResult, result.asDouble());
}

//@JavascriptEnabled
//@Test
TEST_F(ExecutingJavaScript, testShouldThrowAnExceptionWhenTheJavascriptIsBad) {
  webDriver().get(pages().xhtmlTestPage);

   ASSERT_THROW(webDriver().executeScript("return squiggle();"), WebDriverException);
}

//@JavascriptEnabled
//@Test
//@Ignore(value = {ANDROID, CHROME, HTMLUNIT, IE, IPHONE, OPERA, OPERA_MOBILE, PHANTOMJS, SAFARI, MARIONETTE})
TEST_F(ExecutingJavaScript, testShouldThrowAnExceptionWithMessageAndStacktraceWhenTheJavascriptIsBad) {
  webDriver().get(pages().xhtmlTestPage);

  std::string js = "function functionB() { throw Error('errormessage'); };"
              "function functionA() { functionB(); };"
              "functionA();";
  try {
   webDriver().executeScript(js);
    FAIL() << "Expected an exception";
  } catch (WebDriverException& e) {
    ASSERT_TRUE(contains(e.what(), "errormessage"));

  }
}

//@JavascriptEnabled
//@Test
//@Ignore(MARIONETTE)
TEST_F(ExecutingJavaScript, testShouldBeAbleToCallFunctionsDefinedOnThePage) {
  webDriver().get(pages().javascriptPage);
 webDriver().executeScript("displayMessage('I like cheese');");
  std::string text = webDriver().findElement(By::id("result")).text();

  ::boost::algorithm::trim(text);

  ASSERT_TRUE(equals("I like cheese", text));
}

//@JavascriptEnabled
//@Test
TEST_F(ExecutingJavaScript, testShouldBeAbleToPassAStringAnAsArgument) {
  webDriver().get(pages().javascriptPage);
  std::string value =
      (std::string)webDriver().executeScript("return arguments[0] == 'fish' ? 'fish' : 'not fish';", {"fish"});

  ASSERT_TRUE(equals("fish", value));
}

//@JavascriptEnabled
//@Test
TEST_F(ExecutingJavaScript, testShouldBeAbleToPassABooleanAsArgument) {
  webDriver().get(pages().javascriptPage);
  bool value = (bool)webDriver().executeScript("return arguments[0] == true;", {true});

  ASSERT_TRUE(value);
}

//@JavascriptEnabled
//@Test
TEST_F(ExecutingJavaScript, testShouldBeAbleToPassANumberAnAsArgument) {
  webDriver().get(pages().javascriptPage);
  bool value = (bool)webDriver().executeScript("return arguments[0] == 1 ? true : false;", {1});

  ASSERT_TRUE(value);
}

//@JavascriptEnabled
//@Test
TEST_F(ExecutingJavaScript, testShouldBeAbleToPassAWebElementAsArgument) {
  webDriver().get(pages().javascriptPage);
  WebElement button = webDriver().findElement(By::id("plainButton"));
  std::string value =
      (std::string)webDriver().executeScript(
          "arguments[0]['flibble'] = arguments[0].getAttribute('id'); return arguments[0]['flibble'];",
          {button});

  ASSERT_TRUE(equals("plainButton", value));
}

/*
//@JavascriptEnabled
//@Test
TEST_F(ExecutingJavaScript, testPassingArrayAsOnlyArgumentFlattensArray) {
  webDriver().get(pages().javascriptPage);
  Response array(Json::arrayValue);
  array.append("zero");
  array.append(1);
  array.append(true);
  array.append(3.14159);
  array.append(false);
  std::string value = (std::string)webDriver().executeScript("return arguments[0]", {array});
  ASSERT_TRUE(equals(array[0], value));
}
*/

//@JavascriptEnabled
//@Ignore({OPERA, OPERA_MOBILE})
//@Test
TEST_F(ExecutingJavaScript, testShouldBeAbleToPassAnArrayAsAdditionalArgument) {
  webDriver().get(pages().javascriptPage);
  Response array(Json::arrayValue);
  array.append("zero");
  array.append(1);
  array.append(true);
  array.append(3.14159);
  array.append(false);

  long length = (long)webDriver().executeScript("return arguments[1].length",{ "string", array});
  ASSERT_EQ(array.size(), length);
}



/*
//@JavascriptEnabled
//@Test
TEST_F(ExecutingJavaScript, testShouldThrowAnExceptionIfAnArgumentIsNotValid) {
  webDriver().get(pages().javascriptPage);
  try {
   webDriver().executeScript("return arguments[0];", webDriver());
    fail("Exception should have been thrown");
  } catch (IllegalArgumentException e) {
    // this is expected
  }
}
*/
//@JavascriptEnabled
//@Test
TEST_F(ExecutingJavaScript, testShouldBeAbleToPassInMoreThanOneArgument) {
  webDriver().get(pages().javascriptPage);
  std::string result = (std::string)webDriver().executeScript("return arguments[0] + arguments[1];", ScriptArgs({"one", "two"}));

  ASSERT_TRUE(equals("onetwo", result));
}

//@JavascriptEnabled
//@Test
//@Ignore({MARIONETTE, OPERA, OPERA_MOBILE})
TEST_F(ExecutingJavaScript, testShouldBeAbleToGrabTheBodyOfFrameOnceSwitchedTo) {
  webDriver().get(pages().richTextPage);

  webDriver().switchTo().frame("editFrame");
  WebElement body = (WebElement)webDriver().executeScript("return document.body");
  std::string text = body.text();
  webDriver().switchTo().defaultContent();

  ASSERT_TRUE(equals("", text));
}

//@SuppressWarnings("unchecked")
//@JavascriptEnabled
//@Test
//@Ignore(MARIONETTE)
TEST_F(ExecutingJavaScript, testShouldBeAbleToReturnAnArrayOf) {
  webDriver().get(pages().formPage);

  WebElements items = webDriver().executeScript(
      "return document.getElementsByName('snack');");

  ASSERT_FALSE(items.empty());
}

//@JavascriptEnabled
//@Test
TEST_F(ExecutingJavaScript, testJavascriptStringHandlingShouldWorkAsExpected) {
  webDriver().get(pages().javascriptPage);

  std::string value = webDriver().executeScript("return '';");
  ASSERT_TRUE(equals("", value));

  ScriptResult res = webDriver().executeScript("return undefined;");
  ASSERT_TRUE(null(res));

  value = (std::string)webDriver().executeScript("return ' '");
  ASSERT_TRUE(equals(" ", value));
}

/*
//@JavascriptEnabled
//@Ignore(OPERA)
//@Test
TEST_F(ExecutingJavaScript, testShouldBeAbleToExecuteABigChunkOfJavascriptCode) {
  webDriver().get(pages().javascriptPage);

  File jqueryFile = InProject.locate("common/src/web/jquery-1.3.2.js");
  std::string jquery = Files.toString(jqueryFile, Charset.forName("US-ASCII"));
  ASSERT_TRUE("The javascript code should be at least 50 KB.", jquery.length() > 50000);
  // This should not throw an exception ...
 webDriver().executeScript(jquery);
}
*/
//@SuppressWarnings("unchecked")
//@JavascriptEnabled
//@Test
//@Ignore(MARIONETTE)
TEST_F(ExecutingJavaScript, testShouldBeAbleToExecuteScriptAndReturnElementsList) {
  webDriver().get(pages().formPage);
  std::string scriptToExec = "return document.getElementsByName('snack');";

  WebElements resultsList = webDriver().executeScript(scriptToExec);

  ASSERT_FALSE(resultsList.empty());
}

/*
//@JavascriptEnabled
//@NeedsFreshDriver
//@NoDriverAfterTest
//@Ignore(reason = "Failure indicates hang condition, which would break the" +
//    " test suite. Really needs a timeout set.")
//@Test
TEST_F(ExecutingJavaScript, testShouldThrowExceptionIfExecutingOnNoPage) {
  try {
   webDriver().executeScript("return 1;");
  } catch (WebDriverException& e) {
    // Expected
    return;
  }
  FAIL() << "Expected exception to be thrown";
}
*/

//@JavascriptEnabled
//@Ignore({OPERA, MARIONETTE})
//@Test
TEST_F(ExecutingJavaScript, testShouldBeAbleToCreateAPersistentValue) {
  webDriver().get(pages().formPage);

 webDriver().executeScript("document.alerts = []");
 webDriver().executeScript("document.alerts.push('hello world');");
  std::string text = webDriver().executeScript("return document.alerts.shift()");

  ASSERT_TRUE(equals("hello world", text));
}

//@JavascriptEnabled
//@Ignore(OPERA)
//@Test
TEST_F(ExecutingJavaScript, testCanHandleAnArrayOfElementsAsAnObjectArray) {
  webDriver().get(pages().formPage);

  WebElements forms = webDriver().findElements(By::tagName("form"));

  for (auto elem: forms)
  {
    LOG(elem.tagName());
  }

  std::string name = (std::string) webDriver().executeScript(
      "return arguments[0][0].tagName", forms);

  ASSERT_TRUE(equalsIgnoreCase("form", name));
}

//@JavascriptEnabled
//@Ignore(value = {ANDROID, OPERA, OPERA_MOBILE, MARIONETTE},
//        reason = "Opera obeys the method contract. Android not tested")
//@Test
TEST_F(ExecutingJavaScript, testCanPassAMapAsAParameter) {
  webDriver().get(pages().simpleTestPage);

  ScriptArg arg(Json::arrayValue);
  arg.append(1);
  arg.append(2);

  std::map<std::string, ScriptArg> args = { { "bar", "test" } , { "foo", arg }};

  ScriptResult res = webDriver().executeScript("return arguments[0]['foo'][1]", args);

  ASSERT_TRUE(equals(2, res.asInt()));
}

//@JavascriptEnabled
//@Test
//@Ignore(value = {OPERA, OPERA_MOBILE}, reason = "Opera: failed")
TEST_F(ExecutingJavaScript, testShouldThrowAnExceptionWhenArgumentsWithStaleElementPassed) {
  webDriver().get(pages().simpleTestPage);

  WebElement el = webDriver().findElement(By::id("oneline"));

  webDriver().get(pages().simpleTestPage);

  ScriptArg array(Json::arrayValue);
  array.append("zero");
  array.append(1);
  array.append(true);
  array.append(3.14159);
  array.append(false);
  array.append(ScriptArg(el));

  ScriptArg array2(Json::arrayValue);
  array2.append("a");
  array2.append(array);
  array2.append("c");

  std::map<std::string, ScriptArg> args = { {"key", array2 }};

 ASSERT_THROW(webDriver().executeScript("return undefined;", args), StaleElementReferenceException);
}
/*
//@JavascriptEnabled
//@Test
//@Ignore(value = {ANDROID, CHROME, HTMLUNIT, IE, IPHONE, OPERA, OPERA_MOBILE, PHANTOMJS, SAFARI, MARIONETTE})
TEST_F(ExecutingJavaScript, testShouldBeAbleToReturnADateObject) {
  webDriver().get(pages().simpleTestPage);

  std::string date = (std::string)webDriver().executeScript("return new Date();");

  try {
    new SimpleDateFormat("yyyy-MM-dd'T'HH:mm:ss.SSS'Z'").parse(date);
  } catch (ParseException e) {
    fail();
  }
}

//@JavascriptEnabled
//@Test(timeout = 10000)
//@Ignore(value = {ANDROID, CHROME, IE, IPHONE, OPERA, OPERA_MOBILE, PHANTOMJS, SAFARI, MARIONETTE})
TEST_F(ExecutingJavaScript, shouldReturnDocumentElementIfDocumentIsReturned) {
  webDriver().get(pages().simpleTestPage);

  WebElement result = webDriver().executeScript("return document");

  ASSERT_TRUE(result.text().find("A single line of text") != std::string::npos);
}
*/
