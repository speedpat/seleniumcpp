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

  void sendKeys(const char* keys);
	void sendKeys(const std::string& keys);
	void sendKeys(const selenium::interactions::Keys& key);

	template <class ... CharSeq>
  void sendKeys(CharSeq ... keys)
	{
	  CommandParameters param;
	  sendSequence(param, keys...);
  }

	bool isDisplayed();

	Dimension size();

	std::string valueOfCssProperty(const std::string& propertyName);
	std::string location();

	std::string id() const;

  WebElement& operator=(WebElement other);

  bool operator==(const WebElement& other) const;

private:

  template <class T, class ... CharSeq>
  void sendSequence(CommandParameters& param, T& key, CharSeq ... keys)
  {
    appendKeys(param, key);
    sendSequence(param, keys...);
  }

  void sendSequence(CommandParameters& result);

  void appendKeys(CommandParameters& param, const char* keys);
  void appendKeys(CommandParameters& param, const std::string& keys);
  void appendKeys(CommandParameters& param, const selenium::interactions::Keys& keys);

	struct Private;
	Private* m_private;
};

} /* namespace selenium */

#endif /* WEBELEMENT_H_ */
