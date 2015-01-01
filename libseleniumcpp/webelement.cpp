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

#include <sstream>

#include "selenium/by.hpp"
#include "selenium/command_executor.hpp"
#include "selenium/webdriver.hpp"
#include "selenium/webelement.hpp"

#include <selenium/interactions/keys.hpp>


#include "command.hpp"
#include "log.hpp"

namespace selenium {

struct WebElement::Private {
  Private(CommandExecutor& driver, const std::string& elementId);
  Private(const Private& other);
  virtual ~Private();

  CommandExecutor& m_driver;
  std::string m_elementId;

  template <typename RES = std::string, typename value_handler = response_value_handler<RES> >
  RES execute(const Command& command, const CommandParameters& params)
  {
    CommandParameters _params = params;
    _params["id"] = m_elementId;
    return m_driver.execute<RES, value_handler>(command, _params);
  }


  template <typename RES = std::string, typename value_handler = response_value_handler<RES> >
  RES execute(const Command& command)
  {
    CommandParameters params;
    params["id"] = m_elementId;
    return execute<RES, value_handler>(command, params);
  }

};

} /* namespace selenium */

namespace selenium {

WebElement::WebElement(CommandExecutor& driver, const std::string& elementId)
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

const std::string WebElement::tagName()
{
	return m_private->execute<std::string>(Command::GET_ELEMENT_TAG_NAME);
}


const std::string WebElement::text()
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

Attribute WebElement::getAttribute(const std::string& name)
{
	CommandParameters params;
	params["name"] = name;

	return m_private->execute<Attribute>(Command::GET_ELEMENT_ATTRIBUTE, params);
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
	params["using"] = by;
	params["value"] = value;

	return m_private->execute<WebElement>(Command::FIND_CHILD_ELEMENT, params);
}

WebElement WebElement::findElement(const Locator& locator)
{
  return findElement(locator.getClause(), locator.getValue());
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
  params["using"] = by;
  params["value"] = value;

	return m_private->execute<WebElements>(Command::FIND_CHILD_ELEMENTS, params);
}

WebElements WebElement::findElements(const Locator& locator)
{
  return findElements(locator.getClause(), locator.getValue());
}

void WebElement::appendKeys(CommandParameters& result, const char* keys)
{
  std::string keysToSend(keys);
  appendKeys(result, keysToSend);
}

void WebElement::appendKeys(CommandParameters& result, const std::string& keysToSend)
{
  for (char key: keysToSend)
  {
    std::string keyString;
    keyString += key;
    result.append(keyString);

  }
}

void WebElement::appendKeys(CommandParameters& result, const selenium::interactions::Keys& key)
{
  result.append(key);
}

void WebElement::sendSequence(CommandParameters& result)
{
  CommandParameters params;
  params["value"] = result;
  params["id"] = m_private->m_elementId;
  m_private->execute(Command::SEND_KEYS_TO_ELEMENT, params);
}

void WebElement::sendKeys(const char* keys)
{
  std::string keysToSend = keys;
  sendKeys(keysToSend);
}

void WebElement::sendKeys(const std::string& keysToSend)
{
  CommandParameters params;
  CommandParameters keysParam;
  CommandParameters keyParam;
  for (char key: keysToSend)
  {
    std::string keyString;
    keyString += key;
    keysParam.append(keyString);

  }
  params["value"] = keysParam;
  params["id"] = m_private->m_elementId;
  m_private->execute(Command::SEND_KEYS_TO_ELEMENT, params);
}



void WebElement::sendKeys(const selenium::interactions::Keys& key)
{
  CommandParameters params;
  CommandParameters keysParam;

  keysParam.append(key);


  params["value"] = keysParam;
  params["id"] = m_private->m_elementId;
  m_private->execute(Command::SEND_KEYS_TO_ELEMENT, params);
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
	params["propertyName"] = propertyName;
	return m_private->execute(Command::GET_ELEMENT_VALUE_OF_CSS_PROPERTY, params);
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

namespace selenium {

WebElement::Private::Private(CommandExecutor& driver, const std::string& elementId)
 : m_driver(driver), m_elementId(elementId)
{
}
WebElement::Private::Private(const Private& other)
 : m_driver(other.m_driver), m_elementId(other.m_elementId)
{

}

WebElement::Private::~Private() {
}

WebElement& WebElement::operator=(WebElement other)
{
        std::swap(m_private, other.m_private);
        return *this;
}

bool WebElement::operator==(const WebElement& other) const
{
  return other.m_private->m_elementId == m_private->m_elementId;
}



} /* namespace selenium */
