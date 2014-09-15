/*
 * WebElement.h
 *
 *  Created on: Sep 7, 2014
 *      Author: speedpat
 */

#ifndef WEBELEMENT_H_
#define WEBELEMENT_H_

#include <selenium/types.hpp>
#include <selenium/webdriver.hpp>

namespace selenium {


class WebElement {
public:
	WebElement(WebDriver::Private& driver, const std::string& elementId);
	WebElement(const WebElement& other);
	~WebElement();

	std::string tagName();
	std::string text();
	void submit();
	void click();
	void clear();
	std::string getAttribute(const std::string& name);
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

	WebElements findElementsByID(const std::string& id);
	WebElements findElementsByName(const std::string& name);
	WebElements findElementsByLinkText(const std::string& linkText);
	WebElements findElementsByPartialLinkText(const std::string& linkText);
	WebElements findElementsByTagName(const std::string& name);
	WebElements findElementsByXPath(const std::string& xpath);
	WebElements findElementsByClassName(const std::string& className);
	WebElements findElementsByCssSelector(const std::string& css_selector);

	WebElements findElements(const By& by, const std::string& value);

	void sendKeys();

	bool isDisplayed();

	Dimension size();

	std::string valueOfCssProperty(const std::string& propertyName);
	std::string location();

	std::string id() const;

private:
	struct Private;
	Private* m_private;
};

} /* namespace selenium */

#endif /* WEBELEMENT_H_ */
