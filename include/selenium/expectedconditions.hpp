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
  typedef conditions::ExpectedCondition<WebElement, conditions::PresenceOfElementLocatedPredicate, const By&, std::string> PresenceOfElementLocated;
  typedef conditions::ExpectedCondition<bool, conditions::VisibilityOfElementLocatedPredicate, const By&, std::string> VisibilityOfElementLocated;
  typedef conditions::ExpectedCondition<WebElement, conditions::VisibilityOfElementPredicate, WebElement> VisibilityOfElement;
  typedef conditions::ExpectedCondition<WebElements, conditions::PresenceOfAllElementsLocatedPredicate, const By&, std::string> PresenceOfAllElementsLocated;
  typedef conditions::ExpectedCondition<std::string, conditions::TextToBePresentInElementPredicate, const By&, std::string, std::string> TextToBePresentInElement;
  typedef conditions::ExpectedCondition<std::string, conditions::TextToBePresentInElementValuePredicate, const By&, std::string, std::string> TextToBePresentInElementValue;
  typedef conditions::ExpectedCondition<bool, conditions::InvisibilityOfElementLocatedPredicate, const By&, std::string> InvisibilityOfElementLocated;
  typedef conditions::ExpectedCondition<WebElement, conditions::ElementToBeClickablePredicate, const By&, std::string> ElementToBeClickable;
  typedef conditions::ExpectedCondition<bool, conditions::StalenessOfPredicate, WebElement> StalenessOf;
  typedef conditions::ExpectedCondition<bool, conditions::ElementIsSelectedPredicate, WebElement> ElementIsSelected;
  typedef conditions::ExpectedCondition<bool, conditions::ElementSelectionStatePredicate, WebElement, bool> ElementSelectionState;
  typedef conditions::ExpectedCondition<bool, conditions::ElementLocatedIsSelectedPredicate, const By&, std::string> ElementLocatedIsSelected;
  typedef conditions::ExpectedCondition<bool, conditions::ElementLocatedSelectionStateToBePredicate, const By&, std::string, bool> ElementLocatedSelectionStateToBe;
  typedef conditions::ExpectedCondition<Alert, conditions::AlertIsPresentPredicate> AlertIsPresent;

private:
  ExpectedConditions() = delete;
  ~ExpectedConditions() = default;
};

} /* namespace selenium */

#endif /* EXPECTEDCONDITIONS_HPP_ */
