/*
 * webelement_private.h
 *
 *  Created on: Sep 8, 2014
 *      Author: speedpat
 */

#ifndef WEBELEMENT_PRIVATE_H_
#define WEBELEMENT_PRIVATE_H_

#include <functional>
#include <tr1/functional>
#include <selenium/webelement.hpp>

#include "types_internal.hpp"
#include "webdriver_private.hpp"

namespace selenium {

struct WebElement::Private {
	Private(WebDriver::Private& driver, const std::string& elementId);
	Private(const Private& other);
	virtual ~Private();

	WebDriver::Private& m_driver;
	std::string m_elementId;

	template <typename RES = std::string, typename value_handler = response_value_handler<RES> >
	RES execute(const Command& command, const CommandParameters& params)
	{
		CommandParameters _params = params;
		_params.add(std::string("id"), m_elementId);
		return m_driver.execute<RES, value_handler>(command, params);
	}


	template <typename RES = std::string, typename value_handler = response_value_handler<RES> >
	RES execute(const Command& command)
	{
		CommandParameters params;
    params.add(std::string("id"), m_elementId);
		return execute<RES, value_handler>(command, params);
	}

};

} /* namespace selenium */

#endif /* WEBELEMENT_PRIVATE_H_ */
