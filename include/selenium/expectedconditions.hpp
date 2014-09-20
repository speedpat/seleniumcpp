/*
 * expectedconditions.hpp
 *
 *  Created on: Sep 15, 2014
 *      Author: speedpat
 */

#ifndef EXPECTEDCONDITIONS_HPP_
#define EXPECTEDCONDITIONS_HPP_

#include <boost/optional.hpp>

#include <selenium/exceptions.hpp>
#include <selenium/webelement.hpp>
#include <selenium/webdriver.hpp>

#include <selenium/conditions/conditions.hpp>

namespace selenium
{

class ExpectedConditions
{
public:
  typedef conditions::ExpectedCondition<bool, conditions::TitleIsPredicate, std::string> TitleIs;
  typedef conditions::ExpectedCondition<bool, conditions::TitleContainsPredicate, std::string> TitleContains;
  typedef conditions::ExpectedCondition<WebElement, conditions::PresenceOfElementLocatedPredicate, const Locator&> PresenceOfElementLocated;
  typedef conditions::ExpectedCondition<bool, conditions::VisibilityOfElementLocatedPredicate, const Locator&> VisibilityOfElementLocated;
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

} /* namespace selenium */

#endif /* EXPECTEDCONDITIONS_HPP_ */
