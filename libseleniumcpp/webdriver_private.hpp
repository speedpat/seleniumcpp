/*
 * WebDriver_Private.h#include <string>
#include <iostream>
 *
 *  Created on: Sep 6, 2014
 *      Author: speedpat
 */

#ifndef WEBDRIVER_PRIVATE_H_
#define WEBDRIVER_PRIVATE_H_

#include <string>
#include <map>

#include <selenium/webelement.hpp>
#include "selenium/webdriver.hpp"

#include "types_internal.hpp"
#include "command.hpp"

namespace selenium {

template <typename RES>
struct response_value_handler
{
	RES get_value(WebDriver::Private& driver, const CommandParameters& params, Response& response)
	{
		return response.get<RES>("value");
	}

};

template<>
struct response_value_handler<WebElement>
{

	WebElement get_value(WebDriver::Private& driver, const CommandParameters& params, Response& response)
	{
		std::string elementId = response.get<std::string>("ELEMENT");

		return WebElement(driver, elementId);
	}
};

template<>
struct response_value_handler<WebElements>
{

	WebElements get_value(WebDriver::Private& driver, const CommandParameters& params, Response& response)
	{
		Response elements = response.get_child("value");
		WebElements webElements;
		for (Response::const_iterator pos = elements.begin();
				pos != elements.end(); ++pos) {
			std::string elementId = pos->second.get<std::string>("ELEMENT");
			webElements.push_back(WebElement(driver, elementId));
		}

		return webElements;
	}
};

template<>
struct response_value_handler<Dimension>
{
  Dimension get_value(WebDriver::Private& driver, const CommandParameters& params, Response& response)
  {
    return {response.get<int>("height"), response.get<int>("width")};
  }
};


struct WebDriver::Private
{
	Private(const std::string& uri, const Capabilities& capabilities);
	Private(const Private& other);
	~Private();

	enum HttpRequestType
	{
		GET,
		POST,
		DELETE
	};

	typedef std::pair<HttpRequestType, std::string> CommandMap;
	typedef std::map<Command, CommandMap> Commands;


	template <typename RES, typename value_handler = response_value_handler<RES> >
	RES execute(const Command& command, const CommandParameters& params)
	{
		Response response = execute(command, params);
		value_handler handler;
		return handler.get_value(*this, params, response);
	}


	template <typename RES, typename value_handler = response_value_handler<RES> >
	RES execute(const Command& command)
	{
		Response response = execute(command);
		value_handler handler;
		CommandParameters params;
		return handler.get_value(*this, params, response);
	}

	Response execute(const Command& command, const CommandParameters& params);
	Response execute(const Command& command);

	WebDriver::ScriptResult executeScript(const Command& command, const std::string& script, std::vector<WebDriver::ScriptArg> args);

	static Cookie createCookie(const Response& cookie );

	boost::network::uri::uri m_uri;
	httpclient m_client;
	std::string m_sessionId;

	static Commands s_commands;
};

} /* namespace selenium */


#endif /* WEBDRIVER_PRIVATE_H_ */
