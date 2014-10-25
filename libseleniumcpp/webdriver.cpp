/*
 * WebDriver.cpp
 *
 *  Created on: Sep 4, 2014
 *      Author: speedpat
 */

#include <string>
#include <fstream>

#include <boost/optional.hpp>

#include <boost/xpressive/xpressive.hpp>

#include <boost/network/protocol/http/client.hpp>
#include <boost/network/uri.hpp>

#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/archive/iterators/insert_linebreaks.hpp>

#include "log.hpp"
#include "command.hpp"
#include "types_internal.hpp"
#include <selenium/exceptions.hpp>
#include "selenium/script_arg.hpp"
#include "selenium/script_result.hpp"
#include "selenium/command_executor.hpp"
#include "selenium/webdriver.hpp"
#include "selenium/types.hpp"
#include "selenium/webelement.hpp"
#include "selenium/by.hpp"
#include "selenium/switch_to.hpp"
#include "selenium/script_result.hpp"
#include "selenium/script_arg.hpp"

namespace selenium {

typedef boost::network::http::basic_client<boost::network::http::tags::http_keepalive_8bit_udp_resolve, 1, 1> httpclient;

struct WebDriver::Private : public CommandExecutor
{
  Private(const std::string& uri, const Capabilities& capabilities);
  Private(const Private& other);
  virtual ~Private();

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
    return CommandExecutor::execute<RES, value_handler>(command, params);
  }


  template <typename RES, typename value_handler = response_value_handler<RES> >
  RES execute(const Command& command)
  {
    return CommandExecutor::execute<RES, value_handler>(command);
  }


  virtual Response execute(const Command& command, const CommandParameters& params) override;
  virtual Response execute(const Command& command) override;

  virtual const ScriptResult executeScript(const Command& command, const std::string& script, const ScriptArgs& args);

  static Cookie createCookie(const Response& cookie );

  boost::network::uri::uri m_uri;
  httpclient m_client;
  std::string m_sessionId;

  static Commands s_commands;
};

} /* namespace selenium */

namespace selenium {


WebDriver::WebDriver(const std::string& uri, const Capabilities& capabilitites)
 : m_private(new Private(uri, capabilitites))
{
	Response status = m_private->execute(Command::STATUS, {});

	CommandParameters params;
	params["desiredCapabilities"] = capabilitites;
	Response response = m_private->execute(Command::NEW_SESSION, params);

	std::string sessionId = response["sessionId"].asString();
	m_private->m_sessionId = sessionId;

	m_capabilitites = response["value"];


}

WebDriver::~WebDriver()
{
	delete m_private;
}

void WebDriver::close()
{
  m_private->execute(Command::CLOSE, {});
}

void WebDriver::quit()
{
	m_private->execute(Command::QUIT, {});
}

void WebDriver::get(std::string uri)
{
	CommandParameters params;
	params["url"] = uri;

	m_private->execute(Command::GET, params);
}

std::string WebDriver::title()
{
	Response response = m_private->execute(Command::GET_TITLE, {});

	return response["value"].asString();
}

WebElement WebDriver::findElementByID(const std::string& id)
{
	return findElement(By::ID, id);
}

WebElement WebDriver::findElementByName(const std::string& name)
{
	return findElement(By::NAME, name);
}

WebElement WebDriver::findElementByLinkText(const std::string& linkText)
{
	return findElement(By::LINK_TEXT, linkText);
}

WebElement WebDriver::findElementByPartialLinkText(const std::string& linkText)
{
	return findElement(By::PARTIAL_LINK_TEXT, linkText);
}

WebElement WebDriver::findElementByTagName(const std::string& name)
{
	return findElement(By::TAG_NAME, name);
}

WebElement WebDriver::findElementByXPath(const std::string& xpath)
{
	return findElement(By::XPATH, xpath);
}

WebElement WebDriver::findElementByClassName(const std::string& className)
{
	return findElement(By::CLASS_NAME, className);
}

WebElement WebDriver::findElementByCssSelector(const std::string& css_selector)
{
	return findElement(By::CSS_SELECTOR, css_selector);
}

WebElement WebDriver::findElement(const By& by, const std::string& value)
{
	CommandParameters params;
	params["using"] = by;
	params["value"] = value;

	Response response = m_private->execute(Command::FIND_ELEMENT, params);

	Response child = response["value"];

	std::string elementId = child["ELEMENT"].asString();

	return WebElement(*m_private, elementId);
}

WebElement WebDriver::findElement(const Locator& locator)
{
  return findElement(locator.getClause(), locator.getValue());
}


WebElements WebDriver::findElementsByID(const std::string& id)
{
	return findElements(By::ID, id);
}

WebElements WebDriver::findElementsByName(const std::string& name)
{
	return findElements(By::NAME, name);
}

WebElements WebDriver::findElementsByLinkText(const std::string& linkText)
{
	return findElements(By::LINK_TEXT, linkText);
}

WebElements WebDriver::findElementsByPartialLinkText(const std::string& linkText)
{
	return findElements(By::PARTIAL_LINK_TEXT, linkText);
}

WebElements WebDriver::findElementsByTagName(const std::string& name)
{
	return findElements(By::TAG_NAME, name);
}

WebElements WebDriver::findElementsByXPath(const std::string& xpath)
{
	return findElements(By::XPATH, xpath);
}

WebElements WebDriver::findElementsByClassName(const std::string& className)
{
	return findElements(By::CLASS_NAME, className);
}

WebElements WebDriver::findElementsByCssSelector(const std::string& css_selector)
{
	return findElements(By::CSS_SELECTOR, css_selector);
}

WebElements WebDriver::findElements(const By& by, const std::string& value)
{
	CommandParameters params;
	params["using"] = by;
	params["value"] = value;

	Response response = m_private->execute(Command::FIND_ELEMENTS, params);
	Response elements = response["value"];
	WebElements webElements;
	for (Response::iterator pos = elements.begin(); pos != elements.end(); ++pos)
	{
		std::string elementId = (*pos)["ELEMENT"].asString();
		webElements.push_back(WebElement(*m_private, elementId));
	}

	return webElements;
}

WebElements WebDriver::findElements(const Locator& locator)
{
  return findElements(locator.getClause(), locator.getValue());
}

const ScriptResult WebDriver::executeScript(const std::string& script, const ScriptArgs& args)
{
  return m_private->executeScript(Command::EXECUTE_SCRIPT, script, args);
}

const ScriptResult WebDriver::executeAsyncScript(const std::string& script, const ScriptArgs& args)
{
  return m_private->executeScript(Command::EXECUTE_ASYNC_SCRIPT, script, args);
}


std::string WebDriver::currentUrl()
{
	return m_private->execute<std::string>(Command::GET_CURRENT_URL);
}

std::string WebDriver::pageSource()
{
	return m_private->execute<std::string>(Command::GET_PAGE_SOURCE);
}


WindowHandle WebDriver::currentWindowHandle()
{
	return m_private->execute<WindowHandle>(Command::GET_CURRENT_WINDOW_HANDLE);
}

template<>
struct response_value_handler<WindowHandles>
{

	WindowHandles get_value(CommandExecutor& driver, const CommandParameters& params, Response& response)
	{
		Response elements = response["value"];
		WindowHandles handles;
		for (Response::iterator pos = elements.begin();
				pos != elements.end(); ++pos) {
			WindowHandle handle = WindowHandle((*pos).asString());
			handles.push_back(handle);
		}

		return handles;
	}
};

WindowHandles WebDriver::windowHandles()
{
	return m_private->execute<WindowHandles>(Command::GET_WINDOW_HANDLES);
}


void WebDriver::maximizeWindow()
{
	m_private->execute(Command::MAXIMIZE_WINDOW);
}


SwitchTo WebDriver::switchTo()
{
	return SwitchTo(*m_private);
}

void WebDriver::back()
{
	m_private->execute(Command::GO_BACK);
}

void WebDriver::forward()
{
	m_private->execute(Command::GO_FORWARD);
}

void WebDriver::refresh()
{
	m_private->execute(Command::REFRESH);
}

template<>
struct response_value_handler<Cookies>
{

	Cookies get_value(CommandExecutor& driver, const CommandParameters& params, Response& response)
	{
		Response elements = response["value"];
		Cookies cookies;
		for (Response::iterator pos = elements.begin(); pos != elements.end(); ++pos)
		{
			cookies.push_back(WebDriver::Private::createCookie(*pos));
		}

		return cookies;
	}
};

template<>
struct response_value_handler<Cookie>
{
	Cookie get_value(CommandExecutor& driver, const CommandParameters& params, Response& response)
	{
	  if (!params["name"].isNull())
	  {
      std::string name = params["name"].asString();
      LOG("cookie: " << name);
      Response elements = response["value"];
      for (Response::iterator pos = elements.begin();
          pos != elements.end(); ++pos) {
        LOG("have: " << (*pos)["name"].toStyledString());
        LOG(!((*pos)["name"].isNull()));
        LOG((name == (*pos)["name"].asString()));
        if ((!((*pos)["name"].isNull())) && name == (*pos)["name"].asString()) {
          LOG("found");
          return WebDriver::Private::createCookie(*pos);
        }
      }
	  }

		return Cookie();
	}
};


Cookies WebDriver::getCookies()
{
	return m_private->execute<Cookies>(Command::GET_ALL_COOKIES);
}

Cookie WebDriver::getCookie(const std::string& name)
{
	CommandParameters params;
	params["name"] = name;

  for (CommandParameters::iterator entry = params.begin(); entry != params.end(); ++entry)
  {
    std::string key = entry.key().asString();
    std::string val = (*entry).asString();
    LOG(key << ": " << val);
  }
	return m_private->execute<Cookie>(Command::GET_ALL_COOKIES, params);
}

void WebDriver::deleteCookie(const std::string& name)
{
	CommandParameters params;
	params["name"] = name;

	m_private->execute(Command::DELETE_COOKIE, params);
}

void WebDriver::deleteAllCookies()
{
	m_private->execute(Command::DELETE_ALL_COOKIES);
}

void WebDriver::addCookie(const Cookie& cookie)
{
	CommandParameters params;
	CommandParameters cookieParam;
	for (auto prop: cookie)
	{
		cookieParam[prop.first] = prop.second;
	}
	params["cookie"]= cookieParam;

	m_private->execute(Command::ADD_COOKIE, params);
}


void WebDriver::implicitlyWait(const unsigned int timeToWait)
{
	CommandParameters params;
	params["ms"] = timeToWait*1000;

	m_private->execute(Command::IMPLICIT_WAIT, params);
}

void WebDriver::setScriptTimeout(double timeoutInMs)
{
	CommandParameters params;
	params["ms"] = timeoutInMs;

	m_private->execute(Command::SET_SCRIPT_TIMEOUT, params);
}

void WebDriver::setPageLoadTimeout(const unsigned int timeToWait)
{
	CommandParameters params;
	params["ms"] = timeToWait*1000;
	params["type"] = "page load";

	m_private->execute(Command::SET_TIMEOUTS, params);
}


Capabilities WebDriver::getCapabilities()
{
	return m_capabilitites;
}

bool WebDriver::getScreenshotAsFile(const std::string& filename)
{
	typedef boost::archive::iterators::transform_width<
			boost::archive::iterators::binary_from_base64<
			std::string::const_iterator
	        >, 8, 6 > base64_to_binary_t;
	std::string screenshot = getScreenshotAsBase64();
	std::ofstream file(filename, std::ios::binary | std::ios::trunc);
	if (file)
	{
		std::ostream_iterator<char> f_iter(file);
		std::copy(base64_to_binary_t(screenshot.begin()), base64_to_binary_t(screenshot.end()), f_iter);
		file.close();
		return true;
	}
	return false;
}

std::string WebDriver::getScreenshotAsBase64()
{
	return m_private->execute<std::string>(Command::SCREENSHOT);
}


void WebDriver::setWindowSize(const unsigned int width, const unsigned int height, const std::string& windowHandle)
{
	CommandParameters params;
	params["width"] = width;
	params["height"] = height;
	params["windowHandle"] = windowHandle;

	m_private->execute(Command::SET_WINDOW_SIZE, params);
}

Dimension WebDriver::getWindowSize(const std::string& windowHandle)
{
	CommandParameters params;
	params["windowHandle"] = windowHandle;
	return m_private->execute<Dimension>(Command::GET_WINDOW_SIZE, params);
}


void WebDriver::setWindowPosition(const unsigned int x, const unsigned int y, const std::string& windowHandle)
{
	CommandParameters params;
	params["x"] = x;
	params["y"] = y;
	params["windowHandle"] = windowHandle;

	m_private->execute(Command::SET_WINDOW_POSITION, params);
}

template<>
struct response_value_handler<Rect>
{
	Rect get_value(CommandExecutor& driver, const CommandParameters& params, Response& response)
	{
		return {response["x"].asInt(), response["y"].asInt()};
	}
};

Rect WebDriver::getWindowPosition(const std::string& windowHandle)
{
	CommandParameters params;
	params["windowHandle"] = windowHandle;
	return m_private->execute<Rect>(Command::GET_WINDOW_POSITION, params);
}

template<>
struct response_value_handler<ScreenOrientation>
{
  ScreenOrientation get_value(CommandExecutor& driver, const CommandParameters& params, Response& response)
  {
    std::string value = ::boost::to_upper_copy(response["value"].asString());
    LOG("get value: " << value);
    if (value == "PORTRAIT")
    {
      return PORTRAIT;
    }
    else if (value == "LANDSCAPE")
    {
      return LANDSCAPE;
    }

    return UNDEFINED;
  }
};

ScreenOrientation WebDriver::getOrientiation()
{
	return m_private->execute<ScreenOrientation>(Command::GET_SCREEN_ORIENTATION);
}


void WebDriver::setOrientation(ScreenOrientation orientation)
{
	CommandParameters params;
	params["orientation"] = orientation;

	m_private->execute(Command::SET_SCREEN_ORIENTATION, params);
}

/*
struct ScriptArgTranslator
{
    typedef std::string            internal_type;
    typedef ScriptArg              external_type;

    // Converts a string to ScreenOrientation
    ::boost::optional<external_type> get_value(const internal_type& str)
    {
      LOG("get value: " << str);
        std::string value = ::boost::to_upper_copy(str);
        if (value == "PORTRAIT")
        {
          return ::boost::optional<external_type>(PORTRAIT);
        }
        else if (value == "LANDSCAPE")
        {
          return ::boost::optional<external_type>(LANDSCAPE);
        }
        return ::boost::optional<external_type>(boost::none);
    }

    // Converts a bool to string
    ::boost::optional<internal_type> put_value(const external_type& e)
    {
      switch (e.type())
      {
        case ScriptArg::ArgType::_INT:
        {
          std::stringstream str;
          str << (int)e;
          return ::boost::optional<internal_type>(str.str());
          break;
        }
        case ScriptArg::ArgType::_STRING:
        {
          std::string s;
          s = (std::string)e;
          return ::boost::optional<internal_type>(s);
          break;
        }
        case ScriptArg::ArgType::_DOUBLE:
        {
          std::stringstream str;
          str << (double)e;
          return ::boost::optional<internal_type>(str.str());
          break;
        }

        case ScriptArg::ArgType::_WEBELEMENT:
        {
          CommandParameters argParam;
          std::string s;
          s = (std::string)e;
          argParam["ELEMENT"] = s;

          std::stringstream str;
          boost::property_tree::json_parser::write_json(str, argParam, false);
          return ::boost::optional<internal_type>(str.str());
          break;
        }
        default: {
          LOG("NONE");
          return ::boost::optional<internal_type>(boost::none);
        }
      }
    }
};
*/

} /* namespace selenium */




namespace selenium
{

enum ResponseStatusCode
{
  Success = 0,
  NoSuchDriver = 6,
  NoSuchElement = 7,
  NoSuchFrame = 8,
  UnknownCommand = 9,
  StaleElementReference = 10,
  ElementNotVisible = 11,
  InvalidElementState = 12,
  UnknownError = 13,
  ElementIsNotSelectable = 15,
  JavaScriptError = 17,
  XPathLookupError = 19,
  Timeout = 21,
  NoSuchWindow = 23,
  InvalidCookieDomain = 24,
  UnableToSetCookie = 25,
  UnexpectedAlertOpen = 26,
  NoAlertOpenError = 27,
  ScriptTimeout = 28,
  InvalidElementCoordinated = 29,
  IMENotAvailable = 30,
  IMEEngineActivationFailed = 31,
  InvalidSelector = 32,
  SessionNotCreatedException = 33,
  MoveTargetOutOfBounds = 34
};

WebDriver::Private::Commands WebDriver::Private::s_commands =
    {
        { Command::STATUS, { GET, "/status" } },
        { Command::NEW_SESSION, { POST, "/session" } },
        { Command::GET_SESSIONS, { GET, "/sessions" } },
        { Command::GET_SESSION, { GET, "/session/${sessionId}" } },
        { Command::QUIT, { DELETE, "/session/$(sessionId)" } },
        { Command::SET_TIMEOUTS, { POST, "/session/$(sessionId)/timeouts" } },
        { Command::IMPLICIT_WAIT, { POST,
            "/session/$(sessionId)/timeouts/implicit_wait" } },
        { Command::SET_SCRIPT_TIMEOUT, { POST,
            "/session/$(sessionId)/timeouts/async_script" } },
        { Command::GET_CURRENT_WINDOW_HANDLE, { GET,
            "/session/$(sessionId)/window_handle" } },
        { Command::GET_WINDOW_HANDLES, { GET,
            "/session/$(sessionId)/window_handles" } },
        { Command::GET_CURRENT_URL, { GET, "/session/$(sessionId)/url" } },
        { Command::GET, { POST, "/session/$(sessionId)/url" } },
        { Command::GO_FORWARD, { POST, "/session/$(sessionId)/forward" } },
        { Command::GO_BACK, { POST, "/session/$(sessionId)/back" } },
        { Command::REFRESH, { POST, "/session/$(sessionId)/refresh" } },
        { Command::EXECUTE_SCRIPT, { POST, "/session/$(sessionId)/execute" } },
        { Command::EXECUTE_ASYNC_SCRIPT, { POST,
            "/session/$(sessionId)/execute_async" } },
        { Command::SCREENSHOT, { GET, "/session/$(sessionId)/screenshot" } },
        { Command::GET_IME_ENGINES, { GET,
            "/session/${sessionId}/ime/available_engines" } },
        { Command::GET_ACTIVE_IME_ENGINE, { GET,
            "/session/${sessionId}/ime/active_engine" } },
        { Command::IS_IME_ACTIVATED, { GET,
            "/session/${sessionId}/ime/activated" } },
        { Command::DEACTIVATE_IME, { POST,
            "/session/${sessionId}/ime/deactivate" } },
        { Command::ACTIVATE_IME, { POST, "/session/${sessionId}/ime/activate" } },
        { Command::SWITCH_TO_FRAME, { POST, "/session/$(sessionId)/frame" } },
        { Command::SWITCH_TO_PARENT_FRAME, { POST,
            "/session/$(sessionId)/frame/parent" } },
        { Command::SWITCH_TO_WINDOW, { POST, "/session/$(sessionId)/window" } },
        { Command::CLOSE, { DELETE, "/session/$(sessionId)/window" } },
        { Command::GET_WINDOW_SIZE, { GET,
            "/session/$(sessionId)/window/$(windowHandle)/size" } },
        { Command::SET_WINDOW_SIZE, { POST,
            "/session/$(sessionId)/window/$(windowHandle)/size" } },
        { Command::GET_WINDOW_POSITION, { GET,
            "/session/$(sessionId)/window/$(windowHandle)/position" } },
        { Command::SET_WINDOW_POSITION, { POST,
            "/session/$(sessionId)/window/$(windowHandle)/position" } },
        { Command::MAXIMIZE_WINDOW, { POST,
            "/session/$(sessionId)/window/$(windowHandle)/maximize" } },
        { Command::GET_ALL_COOKIES, { GET, "/session/$(sessionId)/cookie" } },
        { Command::ADD_COOKIE, { POST, "/session/$(sessionId)/cookie" } },
        { Command::DELETE_ALL_COOKIES,
            { DELETE, "/session/$(sessionId)/cookie" } },
        { Command::DELETE_COOKIE, { DELETE,
            "/session/$(sessionId)/cookie/$(name)" } },
        { Command::GET_PAGE_SOURCE, { GET, "/session/$(sessionId)/source" } },
        { Command::GET_TITLE, { GET, "/session/$(sessionId)/title" } },
        { Command::FIND_ELEMENT, { POST, "/session/$(sessionId)/element" } },
        { Command::FIND_ELEMENTS, { POST, "/session/$(sessionId)/elements" } },
        { Command::GET_ACTIVE_ELEMENT, { POST,
            "/session/$(sessionId)/element/active" } },
        { Command::GET_ELEMENT, { GET, "/session/${sessionId}/element/${id}" } },
        { Command::FIND_CHILD_ELEMENT, { POST,
            "/session/$(sessionId)/element/$(id)/element" } },
        { Command::FIND_CHILD_ELEMENTS, { POST,
            "/session/$(sessionId)/element/$(id)/elements" } },
        { Command::CLICK_ELEMENT, { POST,
            "/session/$(sessionId)/element/$(id)/click" } },
        { Command::SUBMIT_ELEMENT, { POST,
            "/session/$(sessionId)/element/$(id)/submit" } },
        { Command::GET_ELEMENT_TEXT, { GET,
            "/session/$(sessionId)/element/$(id)/text" } },
        { Command::SEND_KEYS_TO_ELEMENT, { POST,
            "/session/$(sessionId)/element/$(id)/value" } },
        { Command::SEND_KEYS_TO_ACTIVE_ELEMENT, { POST,
            "/session/$(sessionId)/keys" } },
        { Command::GET_ELEMENT_TAG_NAME, { GET,
            "/session/$(sessionId)/element/$(id)/name" } },
        { Command::CLEAR_ELEMENT, { POST,
            "/session/$(sessionId)/element/$(id)/clear" } },
        { Command::IS_ELEMENT_SELECTED, { GET,
            "/session/$(sessionId)/element/$(id)/selected" } },
        { Command::IS_ELEMENT_ENABLED, { GET,
            "/session/$(sessionId)/element/$(id)/enabled" } },
        { Command::GET_ELEMENT_ATTRIBUTE, { GET,
            "/session/$(sessionId)/element/$(id)/attribute/$(name)" } },
        { Command::ELEMENT_EQUALS, { GET,
            "/session/$(sessionId)/element/$(id)/equals/$(other)" } },
        { Command::IS_ELEMENT_DISPLAYED, { GET,
            "/session/$(sessionId)/element/$(id)/displayed" } },
        { Command::GET_ELEMENT_LOCATION, { GET,
            "/session/$(sessionId)/element/$(id)/location" } },
        { Command::GET_ELEMENT_LOCATION_ONCE_SCROLLED_INTO_VIEW, { GET,
            "/session/$(sessionId)/element/$(id)/location_in_view" } },
        { Command::GET_ELEMENT_SIZE, { GET,
            "/session/$(sessionId)/element/$(id)/size" } },
        { Command::GET_ELEMENT_VALUE_OF_CSS_PROPERTY, { GET,
            "/session/$(sessionId)/element/$(id)/css/$(propertyName)" } },
        { Command::GET_ELEMENT_VALUE, { GET,
            "/session/$(sessionId)/element/$(id)/value" } },
        { Command::SET_ELEMENT_SELECTED, { POST,
            "/session/$(sessionId)/element/$(id)/selected" } },
        { Command::TOGGLE_ELEMENT, { POST,
            "/session/$(sessionId)/element/$(id)/toggle" } },
        { Command::HOVER_OVER_ELEMENT, { POST,
            "/session/$(sessionId)/element/$(id)/hover" } },
        { Command::DRAG_ELEMENT, { POST,
            "/session/$(sessionId)/element/$(id)/drag" } },
        { Command::SET_SCREEN_ORIENTATION, { POST,
            "/session/$(sessionId)/orientation" } },
        { Command::GET_SCREEN_ORIENTATION, { GET,
            "/session/$(sessionId)/orientation" } },
        { Command::SET_ALERT_VALUE, { POST, "/session/$(sessionId)/alert_text" } },
        { Command::GET_ALERT_TEXT, { GET, "/session/$(sessionId)/alert_text" } },
        { Command::DISMISS_ALERT,
            { POST, "/session/$(sessionId)/dismiss_alert" } },
        { Command::ACCEPT_ALERT, { POST, "/session/$(sessionId)/accept_alert" } },
        { Command::MOVE_TO, { POST, "/session/$(sessionId)/moveto" } },
        { Command::CLICK, { POST, "/session/$(sessionId)/click" } },
        { Command::MOUSE_DOWN, { POST, "/session/$(sessionId)/buttondown" } },
        { Command::MOUSE_UP, { POST, "/session/$(sessionId)/buttonup" } },
        { Command::DOUBLE_CLICK, { POST, "/session/$(sessionId)/doubleclick" } },
        { Command::SINGLE_TAP, { POST, "/session/:sessionId/touch/click" } },
        { Command::TOUCH_DOWN, { POST, "/session/:sessionId/touch/down" } },
        { Command::TOUCH_UP, { POST, "/session/:sessionId/touch/up" } },
        { Command::TOUCH_MOVE, { POST, "session/:sessionId/touch/move" } },
        { Command::TOUCH_SCROLL, { POST, "session/:sessionId/touch/scroll" } },
        { Command::TOUCH_DOUBLE_TAP, { POST,
            "session/:sessionId/touch/doubleclick" } },
        { Command::TOUCH_LONG_PRESS, { POST,
            "session/:sessionId/touch/longclick" } },
        { Command::TOUCH_FLICK, { POST, "session/:sessionId/touch/flick" } },
        { Command::GET_GEO_LOCATION, { GET, "/session/:sessionId/location" } }, //  Get the current geo location.
        { Command::SET_GEO_LOCATION, { POST, "/session/:sessionId/location" } }, // Set the current geo location.
        { Command::GET_LOCAL_STORAGE_KEYS, { GET,
            "/session/:sessionId/local_storage" } }, // Get all keys of the storage.
        { Command::SET_LOCAL_STORAGE_ITEM, { POST,
            "/session/:sessionId/local_storage" } }, // Set the storage item for the given key.
        { Command::CLEAR_LOCAL_STORAGE, { DELETE,
            "/session/:sessionId/local_storage" } }, // Clear the storage.
        { Command::GET_LOCAL_STORAGE_ITEM, { GET,
            "/session/:sessionId/local_storage/key/:key" } }, //  Get the storage item for the given key.
        { Command::DELETE_LOCAL_STORAGE_ITEM, { DELETE,
            "/session/:sessionId/local_storage/key/:key" } }, //  Remove the storage item for the given key.
        { Command::GET_LOCAL_STORAGE_SIZE, { GET,
            "/session/:sessionId/local_storage/size" } }, // Get the number of items in the storage.
        { Command::GET_SESSION_STORAGE_KEYS, { GET,
            "/session/:sessionId/session_storage" } }, // Get all keys of the storage.
        { Command::SET_SESSION_STORAGE_ITEM, { POST,
            "/session/:sessionId/session_storage" } }, // Set the storage item for the given key.
        { Command::CLEAR_SESSION_STORAGE, { DELETE,
            "/session/:sessionId/session_storage" } }, // Clear the storage.
        { Command::GET_SESSION_STORAGE_ITEM, { GET,
            "/session/:sessionId/session_storage/key/:key" } }, //  Get the storage item for the given key.
        { Command::DELETE_SESSION_STORAGE_ITEM, { DELETE,
            "/session/:sessionId/session_storage/key/:key" } }, //  Remove the storage item for the given key.
        { Command::GET_SESSION_STORAGE_SIZE, { GET,
            "/session/:sessionId/session_storage/size" } }, //  Get the number of items in the storage.
        { Command::GET_LOG, { POST, "/session/:sessionId/log" } }, //Get the log for a given log type.
        { Command::GET_LOG_TYPES, { GET, "/session/:sessionId/log/types" } }, // Get available log types.
        { Command::GET_APP_CACHE_STATUS, { GET,
            "/session/:sessionId/application_cache/status" } }, //  Get the status of the html5 application cache.
        { Command::SET_BROWSER_VISIBLE,
            { POST, "/session/$(sessionId)/visible" } },
        { Command::IS_BROWSER_VISIBLE, { GET, "/session/$(sessionId)/visible" } },
        { Command::UPLOAD_FILE, { POST, "/session/$(sessionId)/file" } },
        { Command::GET_SPEED, { GET, "/session/$(sessionId)/speed" } },
        { Command::SET_SPEED, { POST, "/session/$(sessionId)/speed" } },
        { Command::GET_NETWORK_CONNECTION,
            { GET, "/session/$(sessionId)/network_connection" } },
        { Command::SET_NETWORK_CONNECTION,
            {POST, "/session/$(sessionId)/network_connection" } },
    };

WebDriver::Private::Private(const std::string& uri,
    const Capabilities& capabilites)
    : m_uri(uri)
{
}

WebDriver::Private::Private(const Private& other)
    : m_uri(other.m_uri), m_sessionId(other.m_sessionId)
{

}

WebDriver::Private::~Private()
{

}

Response
WebDriver::Private::execute(const Command& command,
    const CommandParameters& params)
{
  Commands::const_iterator pos = s_commands.find(command);
  if (pos == s_commands.end())
  {
    throw WebDriverException("unknown command");
  }

  CommandParameters _params = params;
  _params["sessionId"] = m_sessionId;

  boost::network::uri::uri request_uri(m_uri);
  std::string path = pos->second.second;
  boost::xpressive::sregex envar = "$(" >> (boost::xpressive::s1 =
      +boost::xpressive::_w) >> ')';
  std::string output = boost::xpressive::regex_replace(path, envar,
      [&_params](boost::xpressive::smatch const &what)
      {
        LOG(what[1].str());
        std::string value = _params[what[1].str()].asString();
        _params.removeMember(what[1].str());
        return value;
      });

  _params.removeMember("sessionId");

  request_uri.append(output);

  LOG(request_uri.string());

  httpclient::request request(request_uri);
  request << boost::network::header("Content-Type",
      "application/x-www-form-urlencoded");
  request << boost::network::header("Accept", "application/json");

  Json::FastWriter writer;
  std::string body = writer.write(_params);
  std::string length = std::to_string(body.length());

  httpclient::response response;
  switch (pos->second.first)
  {
    case GET:
      {
      LOG("GET");
      response = m_client.get(request);
      request << boost::network::header("Content-Length", "0");
      break;
    }
    case POST:
      {
      LOG("POST");
      LOG("request: " << body);
      request << boost::network::header("Content-Length", length);
      request.body(body);
      response = m_client.post(request);
      break;
    }
    case DELETE:
      {
      LOG("DELETE");
      LOG("request: " << body);
      request << boost::network::header("Content-Length", length);
      request.body(body);
      response = m_client.delete_(request);
      break;
    }
    default:
      {
      throw WebDriverException("unknown request method");
    }
  }

  if (response.status() == 200 || response.status() == 500)
  {
    Response res;
    Json::Reader reader;
    LOG("response: " << response.body());
    if (!reader.parse(response.body(), res, false))
    {
      throw ErrorInResponseException(reader.getFormattedErrorMessages());
    }

    ResponseStatusCode status = static_cast<ResponseStatusCode>(res["status"].asInt());
    //std::string value = res["value"].asString();
    Response valueObj = res["value"];
    std::string message;
    if (valueObj.isObject() && !(valueObj["message"].isNull()))
    {
      message = valueObj["message"].asString();
    }
    switch (status)
    {
      case Success:
        {
        return res;
        break;
      }
      case NoSuchDriver:
        {

        break;
      }
      case NoSuchElement:
        {
        throw NoSuchElementException(message);
        break;
      }
      case NoSuchFrame:
        {
        throw NoSuchFrameException(message);
        break;
      }
      case UnknownCommand:
        {
        break;
      }
      case StaleElementReference:
        {
          throw StaleElementReferenceException(message);
        break;
      }
      case ElementNotVisible:
      {
        throw ElementNotVisibleException(message);
        break;
      }
      case InvalidElementState:
        {
          throw InvalidElementStateException(message);
        break;
      }
      case UnknownError:
        {
          throw UnknownErrorException(message);
        break;
      }
      case ElementIsNotSelectable:
        {
          throw ElementIsNotSelectableException(message);
        break;
      }
      case JavaScriptError:
        {
          throw JavaScriptErrorException(message);
        break;
      }
      case XPathLookupError:
        {
        break;
      }
      case Timeout:
        {
          throw TimeoutException(message);
        break;
      }
      case NoSuchWindow:
        {
          throw NoSuchWindowException(message);
        break;
      }
      case InvalidCookieDomain:
        {
        break;
      }
      case UnableToSetCookie:
        {
        break;
      }
      case UnexpectedAlertOpen:
        {
          throw UnexpectedAlertException(message);
        break;
      }
      case NoAlertOpenError:
        {
          throw NoAlertPresentException(message);
        break;
      }
      case ScriptTimeout:
        {
          throw TimeoutException(message);
        break;
      }
      case InvalidElementCoordinated:
        {
        break;
      }
      case IMENotAvailable:
        {
        break;
      }
      case IMEEngineActivationFailed:
        {
        break;
      }
      case InvalidSelector:
        {
          throw InvalidSelectorException(message);
        break;
      }
      case SessionNotCreatedException:
        {
        break;
      }
      case MoveTargetOutOfBounds:
        {
          throw MoveTargetOutOfBoundsException(message);
        break;
      }
      default:
        throw ErrorInResponseException(message);
    }
  }
  else
  {
    LOG("response status : " << response.status());
    throw ErrorInResponseException(response.body());
  }

  throw WebDriverException("internal error");
}

Response
WebDriver::Private::execute(const Command& command)
{
  return execute(command, { });
}

Cookie
WebDriver::Private::createCookie(const Response& element)
{
  Cookie cookie;
  cookie["name"] = element["name"];
  cookie["value"] = element["value"];

  Response path = element["path"];
  if (!path.isNull())
  {
    cookie["path"] = path;
  }

  Response domain = element["domain"];
  if (!domain.isNull())
  {
    cookie["domain"] = domain;
  }

  Response secure = element["secure"];
  if (!secure.isNull())
  {
    cookie["secure"] = secure;
  }

  Response httpOnly = element["httpOnly"];
  if (!httpOnly.isNull())
  {
    cookie["httpOnly"] = httpOnly;
  }

  Response expiry = element["expiry"];
  if (!expiry.isNull())
  {
    cookie["expiry"] = expiry;
  }
  return cookie;
}

const ScriptResult WebDriver::Private::executeScript(
    const Command& command,
    const std::string& script, const ScriptArgs& args)
{
  CommandParameters params;
  params["script"] = script;
  CommandParameters argsParam(Json::arrayValue);

  for (ScriptArg arg : args)
  {
    LOG("appending arg type: " << arg.type() );
     argsParam.append(arg);
  }

  params["args"] = argsParam;
  Response response = execute(command, params);
  Response value = response["value"];

  return ScriptResult::create(*this, value);

}
} /* namespace selenium */


