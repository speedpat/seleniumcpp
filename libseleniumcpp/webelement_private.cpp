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

/*Response WebElement::Private::execute(const std::string& command, const CommandParameters& params)
{
	CommandParameters _params = params;
	_params.add(std::string("id"), m_elementId);
	return m_driver.execute(command, _params);
}

Response WebElement::Private::execute(const std::string& command)
{
	return execute(command, {});
}*/

} /* namespace selenium */
