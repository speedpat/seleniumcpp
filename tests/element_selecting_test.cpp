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

class ElementSelectingTest : public SeleniumTestCase
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

  void assertNotSelected(WebElement element) {
    assertSelected(element, UNSELECTED);
  }

  void assertSelected(WebElement element) {
    assertSelected(element, SELECTED);
  }

  void assertSelected(WebElement element, bool isSelected) {
    wait().until(ElementSelectionState(element, isSelected));
    ASSERT_EQ(element.isSelected(), isSelected) << "Expected element " << describe(element) << " to be " << selectedToString(isSelected) << " but was " << selectedToString(!isSelected);
  }

  void assertCannotSelect(WebElement element) {
    bool previous = element.isSelected();
    element.click();
    ASSERT_EQ(previous, element.isSelected());
  }

  void assertCanSelect(WebElement element) {
    assertNotSelected(element);

    element.click();
    assertSelected(element);
  }

  void assertClickingPreservesCurrentlySelectedStatus(WebElement element) {
    bool currentSelectedStatus = element.isSelected();
    element.click();
    assertSelected(element, currentSelectedStatus);
  }

  static const std::string selectedToString(bool isSelected) {
    return isSelected ? "[selected]" : "[not selected]";
  }

  static const std::string describe(WebElement element) {
    return element.getAttribute("id").asString();
  }

  void assertCanToggle(WebElement element) {
    bool originalState = element.isSelected();

    assertSelected(element, originalState);

    assertTogglingSwapsSelectedStateFrom(element, originalState);
    assertTogglingSwapsSelectedStateFrom(element, !originalState);
  }

  void assertTogglingSwapsSelectedStateFrom(WebElement element, bool originalState) {
    element.click();
    bool isNowSelected = element.isSelected();
    ASSERT_EQ(isNowSelected, !originalState) << "Expected element " << describe(element) << " to have been toggled to " << selectedToString(!originalState) << " but was " << selectedToString(originalState);
    assertSelected(element, !originalState);
  }

  // TODO: Test disabled multi-selects
  // TODO: Test selecting options


  WebElement enabledUnselectedCheckbox() {
    return webDriver().findElement(By::id("checky"));
  }

  WebElement enabledSelectedCheckbox() {
    return webDriver().findElement(By::id("checkedchecky"));
  }

  WebElement disabledUnselectedCheckbox() {
    return webDriver().findElement(By::id("disabledchecky"));
  }

  WebElement randomlyDisabledSelectedCheckbox() {
    return webDriver().findElement(By::id("randomly_disabled_checky"));
  }

  WebElement enabledUnselectedRadioButton() {
    return webDriver().findElement(By::id("peas"));
  }

  WebElement enabledSelectedRadioButton() {
    return webDriver().findElement(By::id("cheese_and_peas"));
  }

  WebElement disabledSelectedRadioButton() {
    return webDriver().findElement(By::id("lone_disabled_selected_radio"));
  }

  WebElement disabledUnselectedRadioButton() {
    return webDriver().findElement(By::id("nothing"));
  }

  WebElement randomlyDisabledUnselectedRadioButton() {
    return webDriver().findElement(By::id("randomly_disabled_nothing"));
  }

  WebElement selectedMultipleSelectOption() {
    WebElement select = webDriver().findElement(By::name("multi"));
    return select.findElements(By::tagName("option"))[0];
  }

  static const bool UNSELECTED = false;
  static const bool SELECTED = true;
};


//@Test
TEST_F(ElementSelectingTest, testShouldBeAbleToSelectAnEnabledUnselectedCheckbox) {
  webDriver().get(pages().formPage);
  assertCanSelect(enabledUnselectedCheckbox());
}

//@Test
TEST_F(ElementSelectingTest, testShouldBeAbleToSelectAnEnabledUnselectedRadioButton) {
  webDriver().get(pages().formPage);
  assertCanSelect(enabledUnselectedRadioButton());
}

//@Test
//@Ignore(MARIONETTE)
TEST_F(ElementSelectingTest, testShouldNotBeAbleToSelectADisabledCheckbox) {
  webDriver().get(pages().formPage);
  assertCannotSelect(disabledUnselectedCheckbox());
}

//@Test
//@Ignore(MARIONETTE)
TEST_F(ElementSelectingTest, testShouldNotBeAbleToSelectADisabledCheckboxDisabledWithRandomString) {
  webDriver().get(pages().formPage);
  assertCannotSelect(randomlyDisabledSelectedCheckbox());
}

//@Test
//@Ignore({OPERA_MOBILE, MARIONETTE})
TEST_F(ElementSelectingTest, testShouldNotBeAbleToSelectADisabledRadioButton) {
  webDriver().get(pages().formPage);
  assertCannotSelect(disabledUnselectedRadioButton());
}

//@Test
//@Ignore(MARIONETTE)
TEST_F(ElementSelectingTest, testShouldNotBeAbleToSelectADisabledRadioButtonDisabledWithRandomString) {
  webDriver().get(pages().formPage);
  assertCannotSelect(randomlyDisabledUnselectedRadioButton());
}

//@Test
TEST_F(ElementSelectingTest, testSelectingRadioButtonShouldUnselectItsSibling) {
  webDriver().get(pages().formPage);

  WebElement originallySelected = enabledSelectedRadioButton();
  assertSelected(originallySelected);

  WebElement toSelect = enabledUnselectedRadioButton();
  assertNotSelected(toSelect);

  toSelect.click();
  assertNotSelected(originallySelected);
  assertSelected(toSelect);
}

//@Test
TEST_F(ElementSelectingTest, testShouldBeAbleToToggleAnEnabledUnselectedCheckbox) {
  webDriver().get(pages().formPage);
  assertCanToggle(enabledUnselectedCheckbox());
}

//@Test
TEST_F(ElementSelectingTest, testShouldBeAbleToToggleAnEnabledSelectedCheckbox) {
  webDriver().get(pages().formPage);
  assertCanToggle(enabledSelectedCheckbox());
}

//@Test
TEST_F(ElementSelectingTest, testClickingOnASelectedRadioButtonShouldLeaveItSelected) {
  webDriver().get(pages().formPage);

  WebElement button = enabledSelectedRadioButton();
  ASSERT_TRUE(button.isSelected());

  button.click();

  ASSERT_TRUE(button.isSelected());
}

//@Ignore(value = {ANDROID, MARIONETTE}, reason = "Android: opens a dialog.")
//@Test
TEST_F(ElementSelectingTest, testShouldBeAbleToToggleEnabledMultiSelectOption) {
  webDriver().get(pages().formPage);
  assertCanToggle(selectedMultipleSelectOption());
}

//@Test
TEST_F(ElementSelectingTest, testShouldBeAbleToToggleSelectableCheckboxByClickingOnIt) {
  webDriver().get(pages().formPage);

  WebElement checkbox = enabledUnselectedCheckbox();
  assertNotSelected(checkbox);

  checkbox.click();
  assertSelected(checkbox);

  checkbox.click();
  assertNotSelected(checkbox);
}

//@Test
TEST_F(ElementSelectingTest, testShouldBeAbleToSelectSelectableRadioButtonByClickingOnIt) {
  webDriver().get(pages().formPage);

  WebElement radioButton = enabledUnselectedRadioButton();
  assertNotSelected(radioButton);

  radioButton.click();
  assertSelected(radioButton);

  radioButton.click();
  assertSelected(radioButton);
}

//@Test
//@Ignore(MARIONETTE)
TEST_F(ElementSelectingTest, testClickingDisabledSelectedCheckboxShouldBeNoop) {
  webDriver().get(pages().formPage);
  assertClickingPreservesCurrentlySelectedStatus(randomlyDisabledSelectedCheckbox());
}

//@Test
//@Ignore(MARIONETTE)
TEST_F(ElementSelectingTest, testClickingDisabledUnselectedCheckboxShouldBeNoop) {
  webDriver().get(pages().formPage);
  assertClickingPreservesCurrentlySelectedStatus(disabledUnselectedCheckbox());
}

//@Test
//@Ignore(MARIONETTE)
TEST_F(ElementSelectingTest, testClickingDisabledSelectedRadioButtonShouldBeNoop) {
  webDriver().get(pages().formPage);
  assertClickingPreservesCurrentlySelectedStatus(disabledSelectedRadioButton());
}

//@Test
//@Ignore(MARIONETTE)
TEST_F(ElementSelectingTest, testClickingDisabledUnselectedRadioButtonShouldBeNoop) {
  webDriver().get(pages().formPage);
  assertClickingPreservesCurrentlySelectedStatus(disabledUnselectedRadioButton());
}

