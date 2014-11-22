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

#ifndef EXPECTEDCONDITIONS_HPP_
#define EXPECTEDCONDITIONS_HPP_

#include <boost/optional.hpp>

#include <selenium/exceptions.hpp>
#include <selenium/webelement.hpp>
#include <selenium/webdriver.hpp>

#include <selenium/conditions/conditions.hpp>
#include <selenium/conditions/expected_condition.hpp>

namespace selenium
{

class ExpectedConditions
{
public:
  typedef conditions::ExpectedCondition<bool, conditions::TitleIsPredicate, std::string> TitleIs;
  typedef conditions::ExpectedCondition<bool, conditions::TitleContainsPredicate, std::string> TitleContains;
  typedef conditions::ExpectedCondition<WebElement, conditions::PresenceOfElementLocatedPredicate, const Locator&> PresenceOfElementLocated;
  typedef conditions::ExpectedCondition<WebElement, conditions::VisibilityOfElementLocatedPredicate, const Locator&> VisibilityOfElementLocated;
  typedef conditions::ExpectedCondition<WebElement, conditions::VisibilityOfElementPredicate, WebElement> VisibilityOfElement;
  typedef conditions::ExpectedCondition<WebElements, conditions::PresenceOfAllElementsLocatedPredicate, const Locator&> PresenceOfAllElementsLocated;
  typedef conditions::ExpectedCondition<std::string, conditions::TextToBePresentInElementPredicate, const Locator&, std::string> TextToBePresentInElement;
  typedef conditions::ExpectedCondition<std::string, conditions::TextToBePresentInElementValuePredicate, const Locator&, std::string> TextToBePresentInElementValue;
  typedef conditions::ExpectedCondition<bool, conditions::InvisibilityOfElementLocatedPredicate, const Locator&> InvisibilityOfElementLocated;
  typedef conditions::ExpectedCondition<WebElement, conditions::ElementToBeClickablePredicate, const Locator&> ElementToBeClickable;
  typedef conditions::ExpectedCondition<bool, conditions::StalenessOfPredicate, WebElement> StalenessOf;
  typedef conditions::ExpectedCondition<bool, conditions::ElementIsSelectedPredicate, WebElement> ElementIsSelected;
  typedef conditions::ExpectedCondition<bool, conditions::ElementSelectionStatePredicate, WebElement, bool> ElementSelectionState;
  typedef conditions::ExpectedCondition<bool, conditions::ElementLocatedIsSelectedPredicate, const Locator&> ElementLocatedIsSelected;
  typedef conditions::ExpectedCondition<bool, conditions::ElementLocatedSelectionStateToBePredicate, const Locator&, bool> ElementLocatedSelectionStateToBe;
  typedef conditions::ExpectedCondition<Alert, conditions::AlertIsPresentPredicate> AlertIsPresent;
  typedef conditions::ExpectedCondition<std::string, conditions::ElementTextToBeEqualPredicate, WebElement, std::string> ElementTextToBeEqual;
  typedef conditions::ExpectedCondition<std::string, conditions::ElementTextToBeEqualLocatedPredicate, Locator, std::string> ElementTextToBeEqualLocated;
  typedef conditions::ExpectedCondition<std::string, conditions::ElementValueToBeEqualPredicate, WebElement, std::string> ElementValueToBeEqual;
  typedef conditions::ExpectedCondition<std::string, conditions::ElementTextToContainPredicate, WebElement, std::string> ElementTextToContain;

private:
  ExpectedConditions() = delete;
  ~ExpectedConditions() = default;
};

typedef ExpectedConditions::TitleIs TitleIs;
typedef ExpectedConditions::TitleContains TitleContains;
typedef ExpectedConditions::PresenceOfElementLocated PresenceOfElementLocated;;
typedef ExpectedConditions::VisibilityOfElementLocated VisibilityOfElementLocated;
typedef ExpectedConditions::VisibilityOfElement VisibilityOfElement;
typedef ExpectedConditions::PresenceOfAllElementsLocated PresenceOfAllElementsLocated;
typedef ExpectedConditions::TextToBePresentInElement TextToBePresentInElement;
typedef ExpectedConditions::TextToBePresentInElementValue TextToBePresentInElementValue;
typedef ExpectedConditions::InvisibilityOfElementLocated InvisibilityOfElementLocated;
typedef ExpectedConditions::ElementToBeClickable ElementToBeClickable;
typedef ExpectedConditions::StalenessOf StalenessOf;
typedef ExpectedConditions::ElementIsSelected ElementIsSelected;
typedef ExpectedConditions::ElementSelectionState ElementSelectionState;
typedef ExpectedConditions::ElementLocatedIsSelected ElementLocatedIsSelected;
typedef ExpectedConditions::ElementLocatedSelectionStateToBe ElementLocatedSelectionStateToBe;
typedef ExpectedConditions::AlertIsPresent AlertIsPresent;
typedef ExpectedConditions::ElementTextToBeEqual ElementTextToBeEqual;
typedef ExpectedConditions::ElementTextToBeEqualLocated ElementTextToBeEqualLocated;
typedef ExpectedConditions::ElementValueToBeEqual ElementValueToBeEqual;
typedef ExpectedConditions::ElementTextToContain ElementTextToContain;

} /* namespace selenium */

#endif /* EXPECTEDCONDITIONS_HPP_ */
