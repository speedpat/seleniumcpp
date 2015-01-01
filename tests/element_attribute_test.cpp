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
using namespace interactions;

class ElementAttributeTest : public SeleniumTestCase
{
public:
  ElementAttributeTest()
   : m_actions(nullptr)
  {

  }
  virtual ~ElementAttributeTest()
  {
    delete m_actions;
    m_actions = nullptr;
  }

  virtual void SetUp()
  {
    SeleniumTestCase::SetUp();
    m_actions = new Actions(webDriver());
  }

  virtual void TearDown()
  {
    SeleniumTestCase::TearDown();
    delete m_actions;
    m_actions = nullptr;
  }

  Actions& actions()
  {
    return *m_actions;
  }


  Actions* m_actions;
};



//@Test
TEST_F(ElementAttributeTest, testShouldReturnNullWhenGettingTheValueOfAnAttributeThatIsNotListed) {
  webDriver().get(pages().simpleTestPage);
  WebElement head = webDriver().findElement(By::xpath("/html"));
  Response attribute = head.getAttribute("cheese");
  ASSERT_TRUE(null(attribute));
}

//@Test
TEST_F(ElementAttributeTest, testShouldReturnNullWhenGettingSrcAttributeOfInvalidImgTag) {
  webDriver().get(pages().simpleTestPage);
  WebElement img = webDriver().findElement(By::id("invalidImgTag"));
  Response attribute= img.getAttribute("src");
  ASSERT_TRUE(null(attribute));
}

//@Test
TEST_F(ElementAttributeTest, testShouldReturnAnAbsoluteUrlWhenGettingSrcAttributeOfAValidImgTag) {
  webDriver().get(pages().simpleTestPage);
  WebElement img = webDriver().findElement(By::id("validImgTag"));
  Response attribute= img.getAttribute("src");
  ASSERT_TRUE(equals(attribute, whereIs("icon.gif")));
}

//@Test
TEST_F(ElementAttributeTest, testShouldReturnAnAbsoluteUrlWhenGettingHrefAttributeOfAValidAnchorTag) {
  webDriver().get(pages().simpleTestPage);
  WebElement img = webDriver().findElement(By::id("validAnchorTag"));
  Response attribute= img.getAttribute("href");
  ASSERT_TRUE(equals(attribute, whereIs("icon.gif")));
}

//@Test
TEST_F(ElementAttributeTest, testShouldReturnEmptyAttributeValuesWhenPresentAndTheValueIsActuallyEmpty) {
  webDriver().get(pages().simpleTestPage);
  WebElement body = webDriver().findElement(By::xpath("//body"));
  ASSERT_TRUE(equals(body.getAttribute("style"), ""));
}

//@Ignore({OPERA, IPHONE, ANDROID, MARIONETTE})
//@Test
TEST_F(ElementAttributeTest, testShouldReturnTheValueOfTheDisabledAttributeAsNullIfNotSet) {
  webDriver().get(pages().formPage);
  WebElement inputElement = webDriver().findElement(By::xpath("//input[@id='working']"));
  ASSERT_TRUE(inputElement.getAttribute("disabled").isNull());
  ASSERT_TRUE(inputElement.isEnabled());

  WebElement pElement = webDriver().findElement(By::id("peas"));
  ASSERT_TRUE(null(pElement.getAttribute("disabled")));
  ASSERT_TRUE(pElement.isEnabled());
}

//@Test
TEST_F(ElementAttributeTest, testShouldReturnTheValueOfTheIndexAttrbuteEvenIfItIsMissing) {
  webDriver().get(pages().formPage);

  WebElement multiSelect = webDriver().findElement(By::id("multi"));
  WebElements options = multiSelect.findElements(By::tagName("option"));
  ASSERT_TRUE(equals(options[1].getAttribute("index"), "1"));
}

//@Test
TEST_F(ElementAttributeTest, testShouldIndicateTheElementsThatAreDisabledAreNotEnabled) {
  webDriver().get(pages().formPage);
  WebElement inputElement = webDriver().findElement(By::xpath("//input[@id='notWorking']"));
  ASSERT_FALSE(inputElement.isEnabled());

  inputElement = webDriver().findElement(By::xpath("//input[@id='working']"));
  ASSERT_TRUE(inputElement.isEnabled());
}

//@Test
TEST_F(ElementAttributeTest, testElementsShouldBeDisabledIfTheyAreDisabledUsingRandomDisabledStrings) {
  webDriver().get(pages().formPage);
  WebElement disabledTextElement1 = webDriver().findElement(By::id("disabledTextElement1"));
  ASSERT_FALSE(disabledTextElement1.isEnabled());

  WebElement disabledTextElement2 = webDriver().findElement(By::id("disabledTextElement2"));
  ASSERT_FALSE(disabledTextElement2.isEnabled());

  WebElement disabledSubmitElement = webDriver().findElement(By::id("disabledSubmitElement"));
  ASSERT_FALSE(disabledSubmitElement.isEnabled());
}

//@Ignore(value = {IPHONE, MARIONETTE},
//        reason = "sendKeys does not determine whether the element is disabled")
//@Test
TEST_F(ElementAttributeTest, testShouldThrowExceptionIfSendingKeysToElementDisabledUsingRandomDisabledStrings) {
  webDriver().get(pages().formPage);
  WebElement disabledTextElement1 = webDriver().findElement(By::id("disabledTextElement1"));
  try {
    actions().sendKeys(disabledTextElement1, "foo").perform();
    FAIL() << "Should have thrown exception";
  } catch (InvalidElementStateException& e) {
    // Expected
  }
  ASSERT_TRUE(equals(disabledTextElement1.text(), ""));

  WebElement disabledTextElement2 = webDriver().findElement(By::id("disabledTextElement2"));
  try {
    actions().sendKeys(disabledTextElement2, "bar").perform();
    FAIL() << "Should have thrown exception";
  } catch (InvalidElementStateException& e) {
    // Expected
  }
  ASSERT_TRUE(equals(disabledTextElement2.text(), ""));
}

//@Test
TEST_F(ElementAttributeTest, testShouldIndicateWhenATextAreaIsDisabled) {
  webDriver().get(pages().formPage);
  WebElement textArea = webDriver().findElement(By::xpath("//textarea[@id='notWorkingArea']"));
  ASSERT_FALSE(textArea.isEnabled());
}

//@Test
TEST_F(ElementAttributeTest, testShouldIndicateWhenASelectIsDisabled) {
  webDriver().get(pages().formPage);

  WebElement enabled = webDriver().findElement(By::name("selectomatic"));
  WebElement disabled = webDriver().findElement(By::name("no-select"));

  ASSERT_TRUE(enabled.isEnabled());
  ASSERT_FALSE(disabled.isEnabled());
}

//@Test
TEST_F(ElementAttributeTest, testShouldReturnTheValueOfCheckedForACheckboxOnlyIfItIsChecked) {
  webDriver().get(pages().formPage);
  WebElement checkbox = webDriver().findElement(By::xpath("//input[@id='checky']"));
  ASSERT_TRUE(null(checkbox.getAttribute("checked")));
  checkbox.click();
  ASSERT_TRUE(equals(checkbox.getAttribute("checked"), "true"));
}

//@Test
TEST_F(ElementAttributeTest, testShouldOnlyReturnTheValueOfSelectedForRadioButtonsIfItIsSet) {
  webDriver().get(pages().formPage);
  WebElement neverSelected = webDriver().findElement(By::id("cheese"));
  WebElement initiallyNotSelected = webDriver().findElement(By::id("peas"));
  WebElement initiallySelected = webDriver().findElement(By::id("cheese_and_peas"));

  ASSERT_TRUE(null(neverSelected.getAttribute("selected")));
  ASSERT_TRUE(null(initiallyNotSelected.getAttribute("selected")));
  ASSERT_TRUE(equals(initiallySelected.getAttribute("selected"), "true"));

  initiallyNotSelected.click();
  ASSERT_TRUE(null(neverSelected.getAttribute("selected")));
  ASSERT_TRUE(equals(initiallyNotSelected.getAttribute("selected"), "true"));
  ASSERT_TRUE(null(initiallySelected.getAttribute("selected")));
}

//@Test
TEST_F(ElementAttributeTest, testShouldReturnTheValueOfSelectedForOptionsOnlyIfTheyAreSelected) {
  webDriver().get(pages().formPage);
  WebElement selectBox = webDriver().findElement(By::xpath("//select[@name='selectomatic']"));
  WebElements options = selectBox.findElements(By::tagName("option"));
  WebElement one = options[0];
  WebElement two = options[1];
  ASSERT_TRUE(one.isSelected());
  ASSERT_FALSE(two.isSelected());
  ASSERT_TRUE(equals(one.getAttribute("selected"), "true"));
  ASSERT_TRUE(null(two.getAttribute("selected")));
}

//@Test
TEST_F(ElementAttributeTest, testShouldReturnValueOfClassAttributeOfAnElement) {
  webDriver().get(pages().xhtmlTestPage);

  WebElement heading = webDriver().findElement(By::xpath("//h1"));
  Attribute className = heading.getAttribute("class");

  ASSERT_TRUE(equals(className, "header"));
}

//@Test
TEST_F(ElementAttributeTest, testShouldReturnTheContentsOfATextAreaAsItsValue) {
  webDriver().get(pages().formPage);

  Attribute value = webDriver().findElement(By::id("withText")).getAttribute("value");

  ASSERT_TRUE(equals(value, "Example text"));
}

//@Test
TEST_F(ElementAttributeTest, testShouldTreatReadonlyAsAValue) {
  webDriver().get(pages().formPage);

  WebElement element = webDriver().findElement(By::name("readonly"));
  Attribute readonly = element.getAttribute("readonly");

  ASSERT_FALSE(null(readonly));

  WebElement textInput = webDriver().findElement(By::name("x"));
  Attribute notReadonly = textInput.getAttribute("readonly");

  ASSERT_FALSE(readonly == notReadonly);
}

//@Test
TEST_F(ElementAttributeTest, testShouldGetNumericAtribute) {
  webDriver().get(pages().formPage);
  WebElement element = webDriver().findElement(By::id("withText"));
  ASSERT_TRUE(equals(element.getAttribute("rows"), "5"));
}

//@Test
TEST_F(ElementAttributeTest, testCanReturnATextApproximationOfTheStyleAttribute) {
  webDriver().get(pages().javascriptPage);

  Attribute style = webDriver().findElement(By::id("red-item")).getAttribute("style");

  ASSERT_TRUE(contains(style, "background-color"));
}

//@Test
TEST_F(ElementAttributeTest, testShouldCorrectlyReportValueOfColspan) {
  webDriver().get(pages().tables);

  std::this_thread::sleep_for(std::chrono::seconds(1));

  WebElement th1 = webDriver().findElement(By::id("th1"));
  WebElement td2 = webDriver().findElement(By::id("td2"));

  ASSERT_TRUE(equals(th1.getAttribute("id"), "th1")) << "th1 id";
  ASSERT_TRUE(equals(th1.getAttribute("colspan"), "3")) << "th1 colspan should be 3";

  ASSERT_TRUE(equals(td2.getAttribute("id"), "td2")) << "td2 id";
  ASSERT_TRUE(equals(td2.getAttribute("colspan"), "2")) << "td2 colspan should be 2";
}

// This is a test-case re-creating issue 900.
//@Test
/*TEST_F(ElementAttributeTest, testShouldReturnValueOfOnClickAttribute) {
  webDriver().get(pages().javascriptPage);

  WebElement mouseclickDiv = webDriver().findElement(By::id("mouseclick"));

  std::string onClickValue = mouseclickDiv.getAttribute("onclick");
  std::string expectedOnClickValue = "displayMessage('mouse click');";
  assertThat("Javascript code expected", onClickValue, anyOf(
      equalTo("javascript:" + expectedOnClickValue), // Non-IE
      equalTo("function anonymous()\n{\n" + expectedOnClickValue + "\n}"), // IE
      equalTo("function onclick()\n{\n" + expectedOnClickValue + "\n}"))); // IE

  WebElement mousedownDiv = webDriver().findElement(By::id("mousedown"));
  ASSERT_TRUE(equals(("", mousedownDiv.getAttribute("onclick").data()); // TODO handle null values
}*/

//@Ignore(value = {IE, IPHONE, ANDROID}, reason = "IE7 Does not support SVG; " +
 //                                               "SVG elements crash the iWebDriver app (issue 1134)",
 //       issues = {1134})
//@Test
TEST_F(ElementAttributeTest, testGetAttributeDoesNotReturnAnObjectForSvgProperties) {
  webDriver().get(pages().svgPage);
  WebElement svgElement = webDriver().findElement(By::id("rotate"));
  ASSERT_TRUE(equals(svgElement.getAttribute("transform"), "rotate(30)"));
}

//@Test
TEST_F(ElementAttributeTest, testCanRetrieveTheCurrentValueOfATextFormField_textInput) {
  webDriver().get(pages().formPage);
  WebElement element = webDriver().findElement(By::id("working"));
  ASSERT_TRUE(equals(element.getAttribute("value"), ""));
  actions().sendKeys(element, "hello world").perform();
  ASSERT_TRUE(equals(element.getAttribute("value"), "hello world"));
}

//@Test
TEST_F(ElementAttributeTest, testCanRetrieveTheCurrentValueOfATextFormField_emailInput) {
  webDriver().get(pages().formPage);
  WebElement element = webDriver().findElement(By::id("email"));
  ASSERT_TRUE(equals(element.getAttribute("value"), ""));
  actions().sendKeys(element, "hello@example.com").perform();
  ASSERT_TRUE(equals(element.getAttribute("value"), "hello@example.com"));
}

//@Ignore({ANDROID, OPERA_MOBILE})
//@Test
TEST_F(ElementAttributeTest, testCanRetrieveTheCurrentValueOfATextFormField_textArea) {
  webDriver().get(pages().formPage);
  WebElement element = webDriver().findElement(By::id("emptyTextArea"));
  ASSERT_TRUE(equals(element.getAttribute("value"), ""));
  actions().sendKeys(element, "hello world").perform();
  ASSERT_TRUE(equals(element.getAttribute("value"), "hello world"));
}

//@Ignore({OPERA, IPHONE, ANDROID, MARIONETTE})
//@Test
TEST_F(ElementAttributeTest, testShouldReturnNullForNonPresentBooleanAttributes) {
  webDriver().get(pages().booleanAttributes);
  WebElement element1 = webDriver().findElement(By::id("working"));
  ASSERT_TRUE(null(element1.getAttribute("required")));
  WebElement element2 = webDriver().findElement(By::id("wallace"));
  ASSERT_TRUE(null(element2.getAttribute("nowrap")));
}

//@Ignore({IPHONE, ANDROID})
//@Test
TEST_F(ElementAttributeTest, testShouldReturnTrueForPresentBooleanAttributes) {
  webDriver().get(pages().booleanAttributes);
  WebElement element1 = webDriver().findElement(By::id("emailRequired"));
  ASSERT_TRUE(equals(element1.getAttribute("required"), "true"));
  WebElement element2 = webDriver().findElement(By::id("emptyTextAreaRequired"));
  ASSERT_TRUE(equals(element2.getAttribute("required"), "true"));
  WebElement element3 = webDriver().findElement(By::id("inputRequired"));
  ASSERT_TRUE(equals(element3.getAttribute("required"), "true"));
  WebElement element4 = webDriver().findElement(By::id("textAreaRequired"));
  ASSERT_TRUE(equals(element4.getAttribute("required"), "true"));
  WebElement element5 = webDriver().findElement(By::id("unwrappable"));
  ASSERT_TRUE(equals(element5.getAttribute("nowrap"), "true"));
}

//@Ignore({OPERA, IPHONE, ANDROID, MARIONETTE})
//@Test
TEST_F(ElementAttributeTest, testMultipleAttributeShouldBeNullWhenNotSet) {
  webDriver().get(pages().selectPage);
  WebElement element = webDriver().findElement(By::id("selectWithoutMultiple"));
  ASSERT_TRUE(null(element.getAttribute("multiple")));
}

//@Test
TEST_F(ElementAttributeTest, testMultipleAttributeShouldBeTrueWhenSet) {
  webDriver().get(pages().selectPage);
  WebElement element = webDriver().findElement(By::id("selectWithMultipleEqualsMultiple"));
  ASSERT_TRUE(equals(element.getAttribute("multiple"), "true"));
}

//@Test
TEST_F(ElementAttributeTest, testMultipleAttributeShouldBeTrueWhenSelectHasMultipleWithValueAsBlank) {
  webDriver().get(pages().selectPage);
  WebElement element = webDriver().findElement(By::id("selectWithEmptyStringMultiple"));
  ASSERT_TRUE(equals(element.getAttribute("multiple"), "true"));
}

//@Test
TEST_F(ElementAttributeTest, testMultipleAttributeShouldBeTrueWhenSelectHasMultipleWithoutAValue) {
  webDriver().get(pages().selectPage);
  WebElement element = webDriver().findElement(By::id("selectWithMultipleWithoutValue"));
  ASSERT_TRUE(equals(element.getAttribute("multiple"), "true"));
}

//@Test
TEST_F(ElementAttributeTest, testMultipleAttributeShouldBeTrueWhenSelectHasMultipleWithValueAsSomethingElse) {
  webDriver().get(pages().selectPage);
  WebElement element = webDriver().findElement(By::id("selectWithRandomMultipleValue"));
  ASSERT_TRUE(equals(element.getAttribute("multiple"), "true"));
}

//@Ignore({HTMLUNIT})
//@Test
TEST_F(ElementAttributeTest, testGetAttributeOfUserDefinedProperty) {
  webDriver().get(pages().userDefinedProperty);
  WebElement element = webDriver().findElement(By::id("d"));
  ASSERT_TRUE(equals(element.getAttribute("dynamicProperty"), "sampleValue"));
}
