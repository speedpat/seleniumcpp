/*
 * element_attribute_test.cpp
 *
 *  Created on: Sep 20, 2014
 *      Author: speedpat
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
  std::string attribute = head.getAttribute("cheese");
  ASSERT_STREQ(attribute.data(), "null"); // TODO handle null values
}

//@Test
TEST_F(ElementAttributeTest, testShouldReturnNullWhenGettingSrcAttributeOfInvalidImgTag) {
  webDriver().get(pages().simpleTestPage);
  WebElement img = webDriver().findElement(By::id("invalidImgTag"));
  std::string attribute = img.getAttribute("src");
  ASSERT_STREQ(attribute.data(), "null"); // TODO handle null values
}

//@Test
TEST_F(ElementAttributeTest, testShouldReturnAnAbsoluteUrlWhenGettingSrcAttributeOfAValidImgTag) {
  webDriver().get(pages().simpleTestPage);
  WebElement img = webDriver().findElement(By::id("validImgTag"));
  std::string attribute = img.getAttribute("src");
  ASSERT_STREQ(attribute.data(), whereIs("icon.gif").data());
}

//@Test
TEST_F(ElementAttributeTest, testShouldReturnAnAbsoluteUrlWhenGettingHrefAttributeOfAValidAnchorTag) {
  webDriver().get(pages().simpleTestPage);
  WebElement img = webDriver().findElement(By::id("validAnchorTag"));
  std::string attribute = img.getAttribute("href");
  ASSERT_STREQ(attribute.data(), whereIs("icon.gif").data());
}

//@Test
TEST_F(ElementAttributeTest, testShouldReturnEmptyAttributeValuesWhenPresentAndTheValueIsActuallyEmpty) {
  webDriver().get(pages().simpleTestPage);
  WebElement body = webDriver().findElement(By::xpath("//body"));
  ASSERT_STREQ(body.getAttribute("style").data(), "");
}

//@Ignore({OPERA, IPHONE, ANDROID, MARIONETTE})
//@Test
TEST_F(ElementAttributeTest, testShouldReturnTheValueOfTheDisabledAttributeAsNullIfNotSet) {
  webDriver().get(pages().formPage);
  WebElement inputElement = webDriver().findElement(By::xpath("//input[@id='working']"));
  ASSERT_STREQ(inputElement.getAttribute("disabled").data(), "null"); // TODO handle null values
  ASSERT_TRUE(inputElement.isEnabled());

  WebElement pElement = webDriver().findElement(By::id("peas"));
  ASSERT_STREQ(pElement.getAttribute("disabled").data(), "null"); // TODO handle null values
  ASSERT_TRUE(pElement.isEnabled());
}

//@Test
TEST_F(ElementAttributeTest, testShouldReturnTheValueOfTheIndexAttrbuteEvenIfItIsMissing) {
  webDriver().get(pages().formPage);

  WebElement multiSelect = webDriver().findElement(By::id("multi"));
  WebElements options = multiSelect.findElements(By::tagName("option"));
  ASSERT_STREQ(options[1].getAttribute("index").data(), "1");
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
  ASSERT_STREQ(disabledTextElement1.text().data(), "");

  WebElement disabledTextElement2 = webDriver().findElement(By::id("disabledTextElement2"));
  try {
    actions().sendKeys(disabledTextElement2, "bar").perform();
    FAIL() << "Should have thrown exception";
  } catch (InvalidElementStateException& e) {
    // Expected
  }
  ASSERT_STREQ(disabledTextElement2.text().data(), "");
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
  ASSERT_STREQ(checkbox.getAttribute("checked").data(), "null"); // TODO handle null value
  checkbox.click();
  ASSERT_STREQ(checkbox.getAttribute("checked").data(), "true");
}

//@Test
TEST_F(ElementAttributeTest, testShouldOnlyReturnTheValueOfSelectedForRadioButtonsIfItIsSet) {
  webDriver().get(pages().formPage);
  WebElement neverSelected = webDriver().findElement(By::id("cheese"));
  WebElement initiallyNotSelected = webDriver().findElement(By::id("peas"));
  WebElement initiallySelected = webDriver().findElement(By::id("cheese_and_peas"));

  ASSERT_STREQ(neverSelected.getAttribute("selected").data(), "null"); // TODO handle null value
  ASSERT_STREQ(initiallyNotSelected.getAttribute("selected").data(), "null"); // TODO handle null value
  ASSERT_STREQ(initiallySelected.getAttribute("selected").data(), "true");

  initiallyNotSelected.click();
  ASSERT_STREQ(neverSelected.getAttribute("selected").data(), "null"); // TODO handle null value
  ASSERT_STREQ(initiallyNotSelected.getAttribute("selected").data(), "true");
  ASSERT_STREQ(initiallySelected.getAttribute("selected").data(), "null"); // TODO handle null value
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
  ASSERT_STREQ(one.getAttribute("selected").data(), "true");
  ASSERT_STREQ(two.getAttribute("selected").data(), "null"); // TODO handle null value
}

//@Test
TEST_F(ElementAttributeTest, testShouldReturnValueOfClassAttributeOfAnElement) {
  webDriver().get(pages().xhtmlTestPage);

  WebElement heading = webDriver().findElement(By::xpath("//h1"));
  std::string className = heading.getAttribute("class");

  ASSERT_STREQ(className.data(), "header");
}

//@Test
TEST_F(ElementAttributeTest, testShouldReturnTheContentsOfATextAreaAsItsValue) {
  webDriver().get(pages().formPage);

  std::string value = webDriver().findElement(By::id("withText")).getAttribute("value");

  ASSERT_STREQ(value.data(), "Example text");
}

//@Test
TEST_F(ElementAttributeTest, testShouldTreatReadonlyAsAValue) {
  webDriver().get(pages().formPage);

  WebElement element = webDriver().findElement(By::name("readonly"));
  std::string readonly = element.getAttribute("readonly");

  ASSERT_STRNE(readonly.data(), "null"); // TODO handle null value (!null check)

  WebElement textInput = webDriver().findElement(By::name("x"));
  std::string notReadonly = textInput.getAttribute("readonly");

  ASSERT_FALSE(readonly == notReadonly);
}

//@Test
TEST_F(ElementAttributeTest, testShouldGetNumericAtribute) {
  webDriver().get(pages().formPage);
  WebElement element = webDriver().findElement(By::id("withText"));
  ASSERT_STREQ(element.getAttribute("rows").data(), "5");
}

//@Test
TEST_F(ElementAttributeTest, testCanReturnATextApproximationOfTheStyleAttribute) {
  webDriver().get(pages().javascriptPage);

  std::string style = webDriver().findElement(By::id("red-item")).getAttribute("style");

  std::transform(style.begin(), style.end(), style.begin(), ::tolower);
  ASSERT_TRUE(style.find("background-color") != std::string::npos);
}

//@Test
TEST_F(ElementAttributeTest, testShouldCorrectlyReportValueOfColspan) {
  webDriver().get(pages().tables);

  std::this_thread::sleep_for(std::chrono::seconds(1));

  WebElement th1 = webDriver().findElement(By::id("th1"));
  WebElement td2 = webDriver().findElement(By::id("td2"));

  ASSERT_STREQ("th1", th1.getAttribute("id").data()) << "th1 id";
  ASSERT_STREQ("3", th1.getAttribute("colspan").data()) << "th1 colspan should be 3";

  ASSERT_STREQ("td2", td2.getAttribute("id").data()) << "td2 id";
  ASSERT_STREQ("2", td2.getAttribute("colspan").data()) << "td2 colspan should be 2";
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
  ASSERT_STREQ("", mousedownDiv.getAttribute("onclick").data()); // TODO handle null values
}*/

//@Ignore(value = {IE, IPHONE, ANDROID}, reason = "IE7 Does not support SVG; " +
 //                                               "SVG elements crash the iWebDriver app (issue 1134)",
 //       issues = {1134})
//@Test
TEST_F(ElementAttributeTest, testGetAttributeDoesNotReturnAnObjectForSvgProperties) {
  webDriver().get(pages().svgPage);
  WebElement svgElement = webDriver().findElement(By::id("rotate"));
  ASSERT_STREQ("rotate(30)", svgElement.getAttribute("transform").data());
}

//@Test
TEST_F(ElementAttributeTest, testCanRetrieveTheCurrentValueOfATextFormField_textInput) {
  webDriver().get(pages().formPage);
  WebElement element = webDriver().findElement(By::id("working"));
  ASSERT_STREQ("", element.getAttribute("value").data());
  actions().sendKeys(element, "hello world").perform();
  ASSERT_STREQ("hello world", element.getAttribute("value").data());
}

//@Test
TEST_F(ElementAttributeTest, testCanRetrieveTheCurrentValueOfATextFormField_emailInput) {
  webDriver().get(pages().formPage);
  WebElement element = webDriver().findElement(By::id("email"));
  ASSERT_STREQ("", element.getAttribute("value").data());
  actions().sendKeys(element, "hello@example.com").perform();
  ASSERT_STREQ("hello@example.com", element.getAttribute("value").data());
}

//@Ignore({ANDROID, OPERA_MOBILE})
//@Test
TEST_F(ElementAttributeTest, testCanRetrieveTheCurrentValueOfATextFormField_textArea) {
  webDriver().get(pages().formPage);
  WebElement element = webDriver().findElement(By::id("emptyTextArea"));
  ASSERT_STREQ("", element.getAttribute("value").data());
  actions().sendKeys(element, "hello world").perform();
  ASSERT_STREQ("hello world", element.getAttribute("value").data());
}

//@Ignore({OPERA, IPHONE, ANDROID, MARIONETTE})
//@Test
TEST_F(ElementAttributeTest, testShouldReturnNullForNonPresentBooleanAttributes) {
  webDriver().get(pages().booleanAttributes);
  WebElement element1 = webDriver().findElement(By::id("working"));
  ASSERT_STREQ(element1.getAttribute("required").data(), "null"); // TODO handle null value
  WebElement element2 = webDriver().findElement(By::id("wallace"));
  ASSERT_STREQ(element2.getAttribute("nowrap").data(), "null"); // TODO handle null value
}

//@Ignore({IPHONE, ANDROID})
//@Test
TEST_F(ElementAttributeTest, testShouldReturnTrueForPresentBooleanAttributes) {
  webDriver().get(pages().booleanAttributes);
  WebElement element1 = webDriver().findElement(By::id("emailRequired"));
  ASSERT_STREQ("true", element1.getAttribute("required").data());
  WebElement element2 = webDriver().findElement(By::id("emptyTextAreaRequired"));
  ASSERT_STREQ("true", element2.getAttribute("required").data());
  WebElement element3 = webDriver().findElement(By::id("inputRequired"));
  ASSERT_STREQ("true", element3.getAttribute("required").data());
  WebElement element4 = webDriver().findElement(By::id("textAreaRequired"));
  ASSERT_STREQ("true", element4.getAttribute("required").data());
  WebElement element5 = webDriver().findElement(By::id("unwrappable"));
  ASSERT_STREQ("true", element5.getAttribute("nowrap").data());
}

//@Ignore({OPERA, IPHONE, ANDROID, MARIONETTE})
//@Test
TEST_F(ElementAttributeTest, testMultipleAttributeShouldBeNullWhenNotSet) {
  webDriver().get(pages().selectPage);
  WebElement element = webDriver().findElement(By::id("selectWithoutMultiple"));
  ASSERT_STREQ("null", element.getAttribute("multiple").data()); // TODO handle null value
}

//@Test
TEST_F(ElementAttributeTest, testMultipleAttributeShouldBeTrueWhenSet) {
  webDriver().get(pages().selectPage);
  WebElement element = webDriver().findElement(By::id("selectWithMultipleEqualsMultiple"));
  ASSERT_STREQ("true", element.getAttribute("multiple").data());
}

//@Test
TEST_F(ElementAttributeTest, testMultipleAttributeShouldBeTrueWhenSelectHasMultipleWithValueAsBlank) {
  webDriver().get(pages().selectPage);
  WebElement element = webDriver().findElement(By::id("selectWithEmptyStringMultiple"));
  ASSERT_STREQ("true", element.getAttribute("multiple").data());
}

//@Test
TEST_F(ElementAttributeTest, testMultipleAttributeShouldBeTrueWhenSelectHasMultipleWithoutAValue) {
  webDriver().get(pages().selectPage);
  WebElement element = webDriver().findElement(By::id("selectWithMultipleWithoutValue"));
  ASSERT_STREQ("true", element.getAttribute("multiple").data());
}

//@Test
TEST_F(ElementAttributeTest, testMultipleAttributeShouldBeTrueWhenSelectHasMultipleWithValueAsSomethingElse) {
  webDriver().get(pages().selectPage);
  WebElement element = webDriver().findElement(By::id("selectWithRandomMultipleValue"));
  ASSERT_STREQ("true", element.getAttribute("multiple").data());
}

//@Ignore({HTMLUNIT})
//@Test
TEST_F(ElementAttributeTest, testGetAttributeOfUserDefinedProperty) {
  webDriver().get(pages().userDefinedProperty);
  WebElement element = webDriver().findElement(By::id("d"));
  ASSERT_STREQ("sampleValue", element.getAttribute("dynamicProperty").data());
}
