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

#include "selenium/by.hpp"


namespace selenium {

By::By(const std::string& selector) :
		m_selector(selector) {
}

By::operator Json::Value() const
{
  return Json::Value(m_selector);
}

const By& By::ID = By("id");
const By& By::NAME = By("name");
const By& By::LINK_TEXT = By("link text");
const By& By::PARTIAL_LINK_TEXT = By("partial link text");
const By& By::TAG_NAME = By("tag name");
const By& By::XPATH = By("xpath");
const By& By::CLASS_NAME = By("class name");
const By& By::CSS_SELECTOR = By("css selector");

Locator By::id(const std::string& id)
{
  return Locator(By::ID, id);
}

Locator By::name(const std::string& name)
{
  return Locator(By::NAME, name);
}

Locator By::linkText(const std::string& linkText)
{
  return Locator(By::LINK_TEXT, linkText);
}

Locator By::partialLinkText(const std::string& linkText)
{
  return Locator(By::PARTIAL_LINK_TEXT, linkText);
}

Locator By::tagName(const std::string& tagName)
{
  return Locator(By::TAG_NAME, tagName);
}

Locator By::xpath(const std::string& xpath)
{
  return Locator(By::XPATH, xpath);
}

Locator By::className(const std::string& className)
{
  return Locator(By::CLASS_NAME, className);
}

Locator By::cssSelector(const std::string& selector)
{
  return Locator(By::CSS_SELECTOR, selector);
}

Locator::Locator(const By& by, const std::string& value)
 : m_by(by), m_value(value)
{
}


const By& Locator::getClause() const
{
  return m_by;
}

const std::string& Locator::getValue() const
{
  return m_value;
}

} /* namespace selenium */
