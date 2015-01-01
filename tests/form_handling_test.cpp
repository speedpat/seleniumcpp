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

class FormHandlingTest : public SeleniumTestCase
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

  void checkSubmitButton(std::string buttonId) {
    webDriver().get(whereIs("click_tests/html5_submit_buttons.html"));
    std::string name = "Gromit";

    webDriver().findElement(By::id("name")).sendKeys(name);
    webDriver().findElement(By::id(buttonId)).click();

    wait().until(TitleIs("Submitted Successfully!"));

    assertThat(contains(webDriver().currentUrl(), "name="+name));
  }

};





//@Test
TEST_F(FormHandlingTest, testShouldClickOnSubmitInputElements) {
  webDriver().get(pages().formPage);
  webDriver().findElement(By::id("submitButton")).click();
  wait().until(TitleIs("We Arrive Here"));
  assertThat(equals(webDriver().title(), "We Arrive Here"));
}

//@Test
TEST_F(FormHandlingTest, testClickingOnUnclickableElementsDoesNothing) {
  webDriver().get(pages().formPage);
  ASSERT_NO_THROW(webDriver().findElement(By::xpath("//body")).click()) << "Clicking on the unclickable should be a no-op";
}

//@Ignore(value = ANDROID, reason = "The page is zoomed in because of the previous state"
//                                  + "which causes the click to fail.")
//@Test
TEST_F(FormHandlingTest, testShouldBeAbleToClickImageButtons) {
  webDriver().get(pages().formPage);
  webDriver().findElement(By::id("imageButton")).click();
  wait().until(TitleIs("We Arrive Here"));
  assertThat(equals(webDriver().title(), "We Arrive Here"));
}

//@Test
//@Ignore(MARIONETTE)
TEST_F(FormHandlingTest, testShouldBeAbleToSubmitForms) {
  webDriver().get(pages().formPage);
  webDriver().findElement(By::name("login")).submit();
  wait().until(TitleIs("We Arrive Here"));
}

//@Test
//@Ignore(MARIONETTE)
TEST_F(FormHandlingTest, testShouldSubmitAFormWhenAnyInputElementWithinThatFormIsSubmitted) {
  webDriver().get(pages().formPage);
  webDriver().findElement(By::id("checky")).submit();
  wait().until(TitleIs("We Arrive Here"));
}

//@Test
//@Ignore(MARIONETTE)
TEST_F(FormHandlingTest, testShouldSubmitAFormWhenAnyElementWithinThatFormIsSubmitted) {
  webDriver().get(pages().formPage);
  webDriver().findElement(By::xpath("//form/p")).submit();
  wait().until(TitleIs("We Arrive Here"));
}

//@Test(expected = NoSuchElementException.class)
//@Ignore(value = {ANDROID, IPHONE, OPERA, PHANTOMJS, SAFARI, OPERA_MOBILE, MARIONETTE})
TEST_F(FormHandlingTest, testShouldNotBeAbleToSubmitAFormThatDoesNotExist) {
  webDriver().get(pages().formPage);
  ASSERT_THROW(webDriver().findElement(By::name("SearchableText")).submit(), NoSuchElementException);
}

//@Test
//@Ignore(OPERA_MOBILE)
TEST_F(FormHandlingTest, testShouldBeAbleToEnterTextIntoATextAreaBySettingItsValue) {
  webDriver().get(pages().javascriptPage);
  WebElement textarea = webDriver().findElement(By::id("keyUpArea"));
  std::string cheesy = "brie and cheddar";
  textarea.sendKeys(cheesy);
  assertThat(equals(textarea.getAttribute("value"), cheesy));
}

//@Ignore(value = {ANDROID, OPERA_MOBILE},
//        reason = "Android: capitalization bug in ICS keeps caps on after a capital letter is sent")
//@Test
TEST_F(FormHandlingTest, testSendKeysKeepsCapitalization) {
  webDriver().get(pages().javascriptPage);
  WebElement textarea = webDriver().findElement(By::id("keyUpArea"));
  std::string cheesey = "BrIe And CheDdar";
  textarea.sendKeys(cheesey);
  assertThat(equals(textarea.getAttribute("value"), cheesey));
}

//@Ignore(value = {IPHONE, ANDROID, OPERA_MOBILE})
//@Test
TEST_F(FormHandlingTest, testShouldSubmitAFormUsingTheNewlineLiteral) {
  webDriver().get(pages().formPage);
  WebElement nestedForm = webDriver().findElement(By::id("nested_form"));
  WebElement input = nestedForm.findElement(By::name("x"));
  input.sendKeys("\n");
  wait().until(TitleIs("We Arrive Here"));
  std::string url = webDriver().currentUrl();
  ASSERT_TRUE(url.find("?x=name") == (url.length() - 7));
}

//@Ignore({IPHONE, ANDROID, OPERA_MOBILE, MARIONETTE})
//@Test
TEST_F(FormHandlingTest, testShouldSubmitAFormUsingTheEnterKey) {
  webDriver().get(pages().formPage);
  WebElement nestedForm = webDriver().findElement(By::id("nested_form"));
  WebElement input = nestedForm.findElement(By::name("x"));
  input.sendKeys(interactions::Keys::ENTER);
  wait().until(TitleIs("We Arrive Here"));
  std::string url = webDriver().currentUrl();
  ASSERT_TRUE(url.find("?x=name") == (url.length() - 7));
}

//@Test
TEST_F(FormHandlingTest, testShouldEnterDataIntoFormFields) {
  webDriver().get(pages().xhtmlTestPage);
  WebElement element = webDriver().findElement(By::xpath("//form[@name='someForm']/input[@id='username']"));
  Attribute originalValue = element.getAttribute("value");
  assertThat(equals(originalValue, "change"));

  element.clear();
  element.sendKeys("some text");

  element = webDriver().findElement(By::xpath("//form[@name='someForm']/input[@id='username']"));
  Attribute newFormValue = element.getAttribute("value");
  assertThat(equals(newFormValue, "some text"));
}

/*
//@Ignore(value = {IPHONE, ANDROID, SAFARI, OPERA, OPERA_MOBILE, MARIONETTE},
//        reason = "Does not yet support file uploads", issues = {4220})
//@Test
TEST_F(FormHandlingTest, testShouldBeAbleToAlterTheContentsOfAFileUploadInputElement) {
  webDriver().get(pages().formPage);
  WebElement uploadElement = webDriver().findElement(By::id("upload"));
  assertThat(equals(uploadElement.getAttribute("value"), ""));

  File file = File.createTempFile("test", "txt");
  file.deleteOnExit();

  uploadElement.sendKeys(file.getAbsolutePath());

  std::string uploadPath = uploadElement.getAttribute("value");
  assertTrue(uploadPath.endsWith(file.getName()));
}

//@Ignore(value = {ANDROID, IPHONE, OPERA, SAFARI, OPERA_MOBILE, MARIONETTE},
//        reason = "Does not yet support file uploads", issues = {4220})
//@Test
public void testShouldBeAbleToSendKeysToAFileUploadInputElementInAnXhtmlDocument()
    throws IOException {
  assumeFalse("IE before 9 doesn't handle pages served with an XHTML content type,"
              + " and just prompts for to download it",
              TestUtilities.isOldIe(driver));

  webDriver().get(pages().xhtmlFormPage);
  WebElement uploadElement = webDriver().findElement(By::id("file"));
  assertThat(uploadElement.getAttribute("value"), equalTo(""));

  File file = File.createTempFile("test", "txt");
  file.deleteOnExit();

  uploadElement.sendKeys(file.getAbsolutePath());

  std::string uploadPath = uploadElement.getAttribute("value");
  assertTrue(uploadPath.endsWith(file.getName()));
}

//@Ignore(value = {IPHONE, ANDROID, OPERA, SAFARI, MARIONETTE},
//        reason = "Does not yet support file uploads", issues = {4220})
//@Test
public void testShouldBeAbleToUploadTheSameFileTwice() throws IOException {
  File file = File.createTempFile("test", "txt");
  file.deleteOnExit();

  webDriver().get(pages().formPage);
  WebElement uploadElement = webDriver().findElement(By::id("upload"));
  assertThat(uploadElement.getAttribute("value"), equalTo(""));

  uploadElement.sendKeys(file.getAbsolutePath());
  uploadElement.submit();

  webDriver().get(pages().formPage);
  uploadElement = webDriver().findElement(By::id("upload"));
  assertThat(uploadElement.getAttribute("value"), equalTo(""));

  uploadElement.sendKeys(file.getAbsolutePath());
  uploadElement.submit();

  // If we get this far, then we're all good.
}
*/
//@Ignore(value = {IPHONE, OPERA}, reason = "iPhone: sendKeys implemented incorrectly.")
//@Test
TEST_F(FormHandlingTest, testSendingKeyboardEventsShouldAppendTextInInputs) {
  webDriver().get(pages().formPage);
  WebElement element = webDriver().findElement(By::id("working"));
  element.sendKeys("some");
  Attribute value = element.getAttribute("value");
  assertThat(equals(value, "some"));

  element.sendKeys(" text");
  value = element.getAttribute("value");
  assertThat(equals(value, "some text"));
}

//@Ignore(value = {ANDROID, HTMLUNIT, IPHONE, OPERA, OPERA_MOBILE},
//        reason = "iPhone: sendKeys implemented incorrectly")
//@Test
TEST_F(FormHandlingTest, testSendingKeyboardEventsShouldAppendTextInInputsWithExistingValue) {
  webDriver().get(pages().formPage);
  WebElement element = webDriver().findElement(By::id("inputWithText"));
  element.sendKeys(". Some text");
  Attribute value = element.getAttribute("value");

  assertThat(equals(value, "Example text. Some text"));
}

//@Ignore(value = {IPHONE, ANDROID, OPERA_MOBILE},
//        reason = "Not implemented going to the end of the line first;\n" +
//                 "iPhone: sendKeys not implemented correctly")
//@Test
TEST_F(FormHandlingTest, testSendingKeyboardEventsShouldAppendTextInTextAreas) {
  webDriver().get(pages().formPage);
  WebElement element = webDriver().findElement(By::id("withText"));

  element.sendKeys(". Some text");
  Attribute value = element.getAttribute("value");

  assertThat(equals(value, "Example text. Some text"));
}

//@Test
TEST_F(FormHandlingTest, testEmptyTextBoxesShouldReturnAnEmptyStringNotNull) {
  webDriver().get(pages().formPage);
  WebElement emptyTextBox = webDriver().findElement(By::id("working"));
  assertThat(equals(emptyTextBox.getAttribute("value"), ""));
}

//@Test
//@Ignore(value = {ANDROID, HTMLUNIT, IPHONE, OPERA, PHANTOMJS, SAFARI, OPERA_MOBILE, MARIONETTE},
//        reason = "untested")
TEST_F(FormHandlingTest, handleFormWithJavascriptAction) {
  std::string url = whereIs("form_handling_js_submit.html");
  webDriver().get(url);
  WebElement element = webDriver().findElement(By::id("theForm"));
  element.submit();
  Alert alert = webDriver().switchTo().alert();
  std::string text = alert.text();
  alert.accept();

  assertThat(equals("Tasty cheese", text));
}

//@Ignore(value = {ANDROID, IPHONE, SAFARI, OPERA_MOBILE}, reason = "untested")
//@Test
TEST_F(FormHandlingTest, testCanClickOnASubmitButton) {
  checkSubmitButton("internal_explicit_submit");
}

//@Ignore(value = {ANDROID, HTMLUNIT, IPHONE, SAFARI, OPERA_MOBILE}, reason = "untested")
//@Test
TEST_F(FormHandlingTest, testCanClickOnAnImplicitSubmitButton) {
//  assumeFalse(isIe6(driver) || isIe7(driver) );
  checkSubmitButton("internal_implicit_submit");
}

//@Ignore(value = {ANDROID, HTMLUNIT, IE, IPHONE, SAFARI, OPERA_MOBILE},
//        reason = "IE, HtmlUnit: failed; Others: untested")
//@Test
TEST_F(FormHandlingTest, testCanClickOnAnExternalSubmitButton) {
  checkSubmitButton("external_explicit_submit");
}

//@Ignore(value = {ANDROID, HTMLUNIT, IE, IPHONE, SAFARI, OPERA_MOBILE},
//    reason = "IE, HtmlUnit: failed; Others: untested")
//@Test
TEST_F(FormHandlingTest, testCanClickOnAnExternalImplicitSubmitButton) {
  checkSubmitButton("external_implicit_submit");
}


