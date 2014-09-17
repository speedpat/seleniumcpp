/*
 * By.cpp
 *
 *  Created on: Sep 7, 2014
 *      Author: speedpat
 */

#include "selenium/by.hpp"

namespace selenium {

By::By(const std::string& selector) :
		m_selector(selector) {
}

std::ostream& operator<<(std::ostream& stream, const By& by) {
	stream << by.m_selector;
	return stream;
}

const By& By::ID = By("id");
const By& By::NAME = By("name");
const By& By::LINK_TEXT = By("link text");
const By& By::PARTIAL_LINK_TEXT = By("partial link text");
const By& By::TAG_NAME = By("tag name");
const By& By::XPATH = By("xpath");
const By& By::CLASS_NAME = By("class name");
const By& By::CSS_SELECTOR = By("css selector");


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
