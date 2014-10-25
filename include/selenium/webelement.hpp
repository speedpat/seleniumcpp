/*
 * WebElement.h
 *
 *  Created on: Sep 7, 2014
 *      Author: speedpat
 */

#ifndef WEBELEMENT_H_
#define WEBELEMENT_H_

#include <selenium/types.hpp>

namespace selenium {
namespace interactions {
class Keys;
}

class CommandExecutor;

class WebElement {
public:
	WebElement(CommandExecutor& driver, const std::string& elementId);
	WebElement(const WebElement& other);
	~WebElement();

	const std::string tagName();
	const std::string text();
	void submit();
	void click();
	void clear();
	Attribute getAttribute(const std::string& name);
	bool isSelected();
	bool isEnabled();
	WebElement findElementByID(const std::string& id);
	WebElement findElementByName(const std::string& name);
	WebElement findElementByLinkText(const std::string& linkText);
	WebElement findElementByPartialLinkText(const std::string& linkText);
	WebElement findElementByTagName(const std::string& name);
	WebElement findElementByXPath(const std::string& xpath);
	WebElement findElementByClassName(const std::string& className);
	WebElement findElementByCssSelector(const std::string& css_selector);

	WebElement findElement(const By& by, const std::string& value);
	WebElement findElement(const Locator& locator);

	WebElements findElementsByID(const std::string& id);
	WebElements findElementsByName(const std::string& name);
	WebElements findElementsByLinkText(const std::string& linkText);
	WebElements findElementsByPartialLinkText(const std::string& linkText);
	WebElements findElementsByTagName(const std::string& name);
	WebElements findElementsByXPath(const std::string& xpath);
	WebElements findElementsByClassName(const std::string& className);
	WebElements findElementsByCssSelector(const std::string& css_selector);

	WebElements findElements(const By& by, const std::string& value);
  WebElements findElements(const Locator& locator);

	void sendKeys(const std::string& keys);
	void sendKeys(const selenium::interactions::Keys& key);

	bool isDisplayed();

	Dimension size();

	std::string valueOfCssProperty(const std::string& propertyName);
	std::string location();

	std::string id() const;

  friend std::ostream& operator<<(std::ostream& os, const WebElement& element);

  WebElement& operator=(WebElement other);

  bool operator==(const WebElement& other) const;

private:
	struct Private;
	Private* m_private;
};

std::ostream& operator<< (std::ostream& stream, const WebElement& element);

} /* namespace selenium */

#endif /* WEBELEMENT_H_ */
