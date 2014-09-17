/*
 * webelement_private.cpp
 *
 *  Created on: Sep 8, 2014
 *      Author: speedpat
 */


#include <boost/property_tree/json_parser.hpp>

#include "types_internal.hpp"
#include "webelement_private.hpp"
#include "command.hpp"

namespace selenium {

WebElement::Private::Private(WebDriver::Private& driver, const std::string& elementId)
 : m_driver(driver), m_elementId(elementId)
{
}
WebElement::Private::Private(const Private& other)
 : m_driver(other.m_driver), m_elementId(other.m_elementId)
{

}

WebElement::Private::~Private() {
}

std::ostream& operator<<(std::ostream& stream, const WebElement& element) {
  stream << element.m_private->m_elementId;
  return stream;
}



} /* namespace selenium */
