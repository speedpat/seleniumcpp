/*
 * WebElement.cpp
 *
 *  Created on: Sep 7, 2014
 *      Author: speedpat
 */


#include <boost/property_tree/json_parser.hpp>


#include "selenium/by.hpp"
#include "selenium/webelement.hpp"
#include "selenium/webdriver.hpp"
#include "command.hpp"
#include "webelement_private.hpp"

namespace selenium {

WebElement::WebElement(WebDriver::Private& driver, const std::string& elementId)
 : m_private(new Private(driver, elementId))
{
}

WebElement::WebElement(const WebElement& other)
 : m_private(new Private(*other.m_private))
{

}

WebElement::~WebElement()
{
	delete m_private;
}

std::string WebElement::tagName()
{
	return m_private->execute<std::string>(Command::GET_ELEMENT_TAG_NAME);
}


std::string WebElement::text()
{
	return m_private->execute<std::string>(Command::GET_ELEMENT_TEXT);
}

void WebElement::submit()
{
	m_private->execute(Command::SUBMIT_ELEMENT);
}

void WebElement::click()
{
	m_private->execute(Command::CLICK_ELEMENT);
}

void WebElement::clear()
{
	m_private->execute(Command::CLEAR_ELEMENT);
}

std::string WebElement::getAttribute(const std::string& name)
{
	CommandParameters params;
	params.add("name", name);

	return m_private->execute<std::string>(Command::GET_ELEMENT_ATTRIBUTE, params);
}

bool WebElement::isSelected()
{
	return m_private->execute<bool>(Command::IS_ELEMENT_SELECTED);
}

bool WebElement::isEnabled()
{
	return m_private->execute<bool>(Command::IS_ELEMENT_ENABLED);
}

WebElement WebElement::findElementByID(const std::string& id)
{
	return findElement(By::ID, id);
}

WebElement WebElement::findElementByName(const std::string& name)
{
	return findElement(By::NAME, name);
}

WebElement WebElement::findElementByLinkText(const std::string& linkText)
{
	return findElement(By::LINK_TEXT, linkText);
}

WebElement WebElement::findElementByPartialLinkText(const std::string& linkText)
{
	return findElement(By::PARTIAL_LINK_TEXT, linkText);
}

WebElement WebElement::findElementByTagName(const std::string& name)
{
	return findElement(By::TAG_NAME, name);
}

WebElement WebElement::findElementByXPath(const std::string& xpath)
{
	return findElement(By::XPATH, xpath);
}

WebElement WebElement::findElementByClassName(const std::string& className)
{
	return findElement(By::CLASS_NAME, className);
}

WebElement WebElement::findElementByCssSelector(const std::string& css_selector)
{
	return findElement(By::CSS_SELECTOR, css_selector);
}

WebElement WebElement::findElement(const By& by, const std::string& value)
{
	CommandParameters params;
	params.add("using", by);
	params.add("value", value);

	return m_private->execute<WebElement>(Command::FIND_CHILD_ELEMENT, params);
}

WebElements WebElement::findElementsByID(const std::string& id)
{
	return findElements(By::ID, id);
}

WebElements WebElement::findElementsByName(const std::string& name)
{
	return findElements(By::NAME, name);
}

WebElements WebElement::findElementsByLinkText(const std::string& linkText)
{
	return findElements(By::LINK_TEXT, linkText);
}

WebElements WebElement::findElementsByPartialLinkText(const std::string& linkText)
{
	return findElements(By::PARTIAL_LINK_TEXT, linkText);
}

WebElements WebElement::findElementsByTagName(const std::string& name)
{
	return findElements(By::TAG_NAME, name);
}

WebElements WebElement::findElementsByXPath(const std::string& xpath)
{
	return findElements(By::XPATH, xpath);
}

WebElements WebElement::findElementsByClassName(const std::string& className)
{
	return findElements(By::CLASS_NAME, className);
}

WebElements WebElement::findElementsByCssSelector(const std::string& css_selector)
{
	return findElements(By::CSS_SELECTOR, css_selector);
}

WebElements WebElement::findElements(const By& by, const std::string& value)
{
	CommandParameters params;
	params.add("using", by);
	params.add("value", value);

	return m_private->execute<WebElements>(Command::FIND_CHILD_ELEMENTS, params);
}

void WebElement::sendKeys()
{

}

bool WebElement::isDisplayed()
{
	return m_private->execute<bool>(Command::IS_ELEMENT_DISPLAYED);
}

Dimension WebElement::size()
{
	return m_private->execute<Dimension>(Command::GET_ELEMENT_SIZE);
}

std::string WebElement::valueOfCssProperty(const std::string& propertyName)
{
	CommandParameters params;
	params.put("propertyName", propertyName);
	return m_private->execute(Command::GET_ELEMENT_VALUE_OF_CSS_PROPERTY);
}
std::string WebElement::location()
{
	return m_private->execute(Command::GET_ELEMENT_LOCATION);
}

std::string WebElement::id() const
{
	return m_private->m_elementId;
}

} /* namespace selenium */
