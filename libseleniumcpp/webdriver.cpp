/*
 * WebDriver.cpp
 *
 *  Created on: Sep 4, 2014
 *      Author: speedpat
 */

#include <boost/optional.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/stream_translator.hpp>

#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/archive/iterators/insert_linebreaks.hpp>

#include "webdriver_private.hpp"
#include "command.hpp"
#include "selenium/webelement.hpp"
#include "selenium/by.hpp"
#include "selenium/switch_to.hpp"

namespace selenium {


WebDriver::WebDriver(const std::string& uri, const Capabilities& capabilitites)
 : m_private(new Private(uri, capabilitites))
{
	Response status = m_private->execute(Command::STATUS, {});

	CommandParameters params;
	CommandParameters desiredCapabilities;
	for (auto capability: capabilitites)
	{
		desiredCapabilities.add(capability.first, capability.second);
	}
	params.add_child("desiredCapabilities", desiredCapabilities);
	Response response = m_private->execute(Command::NEW_SESSION, params);

	std::string sessionId = response.get<std::string>("sessionId");
	m_private->m_sessionId = sessionId;

	Response caps = response.get_child("value");
	for (Response::const_iterator pos = caps.begin(); pos != caps.end(); ++pos)
	{
		m_capabilitites[pos->first] = pos->second.data();
	}

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
	params.add("url", uri);

	m_private->execute(Command::GET, params);
}

std::string WebDriver::title()
{
	Response response = m_private->execute(Command::GET_TITLE, {});

	return response.get<std::string>("value");
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
	params.add("using", by);
	params.add("value", value);

	Response response = m_private->execute(Command::FIND_ELEMENT, params);

	Response child = response.get_child("value");

	std::string elementId = child.get<std::string>("ELEMENT");

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
	params.add("using", by);
	params.add("value", value);

	Response response = m_private->execute(Command::FIND_ELEMENTS, params);
	Response elements = response.get_child("value");
	WebElements webElements;
	for (Response::const_iterator pos = elements.begin(); pos != elements.end(); ++pos)
	{
		std::string elementId = pos->second.get<std::string>("ELEMENT");
		webElements.push_back(WebElement(*m_private, elementId));
	}

	return webElements;
}

WebElements WebDriver::findElements(const Locator& locator)
{
  return findElements(locator.getClause(), locator.getValue());
}

WebDriver::ScriptResult WebDriver::executeScript(const std::string& script, std::vector<ScriptArg> args)
{
  return m_private->executeScript(Command::EXECUTE_SCRIPT, script, args);
}

WebDriver::ScriptResult WebDriver::executeAsyncSript(const std::string& script, std::vector<ScriptArg> args)
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


std::string WebDriver::currentWindowHandle()
{
	return m_private->execute<std::string>(Command::GET_CURRENT_WINDOW_HANDLE);
}

template<>
struct response_value_handler<std::vector<std::string>>
{

	std::vector<std::string> get_value(WebDriver::Private& driver, const CommandParameters& params, Response& response)
	{
		Response elements = response.get_child("value");
		std::vector<std::string> handles;
		for (Response::const_iterator pos = elements.begin();
				pos != elements.end(); ++pos) {
			std::string handle = pos->second.get_value<std::string>();
			handles.push_back(handle);
		}

		return handles;
	}
};

std::vector<std::string> WebDriver::windowHandles()
{
	return m_private->execute<std::vector<std::string> >(Command::GET_WINDOW_HANDLES);
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

	Cookies get_value(WebDriver::Private& driver, const CommandParameters& params, Response& response)
	{
		Response elements = response.get_child("value");
		Cookies cookies;
		for (Response::const_iterator pos = elements.begin(); pos != elements.end(); ++pos)
		{
			cookies.push_back(WebDriver::Private::createCookie(pos->second));
		}

		return cookies;
	}
};

template<>
struct response_value_handler<Cookie>
{
	Cookie get_value(WebDriver::Private& driver, const CommandParameters& params, Response& response)
	{
		std::string name = params.get<std::string>("name");
		Response elements = response.get_child("value");
		for (Response::const_iterator pos = elements.begin();
				pos != elements.end(); ++pos) {
			if (name == pos->second.get<std::string>("name")) {
				return WebDriver::Private::createCookie(pos->second);
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
	params.put("name", name);
	return m_private->execute<Cookie>(Command::GET_ALL_COOKIES);
}

void WebDriver::deleteCookie(const std::string& name)
{
	CommandParameters params;
	params.add("name", name);

	m_private->execute(Command::DELETE_COOKIE, params);
}

void WebDriver::deleteAllCookies()
{
	m_private->execute(Command::DELETE_ALL_COOKIES);
}

void WebDriver::addCookie(Cookie cookie)
{
	CommandParameters params;
	for (auto prop: cookie)
	{
		params.add(prop.first, prop.second);
	}

	m_private->execute(Command::ADD_COOKIE, params);
}


void WebDriver::implicitlyWait(const unsigned int timeToWait)
{
	CommandParameters params;
	params.add("ms", timeToWait*1000);

	m_private->execute(Command::IMPLICIT_WAIT, params);
}

void WebDriver::setScriptTimeout(const unsigned int timeToWait)
{
	CommandParameters params;
	params.add("ms", timeToWait*1000);

	m_private->execute(Command::SET_SCRIPT_TIMEOUT, params);
}

void WebDriver::setPageLoadTimeout(const unsigned int timeToWait)
{
	CommandParameters params;
	params.add("ms", timeToWait*1000);
	params.add("type", "page load");

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
	params.put("width", width);
	params.put("height", height);
	params.put("windowHandle", windowHandle);

	m_private->execute(Command::SET_WINDOW_SIZE, params);
}

Dimension WebDriver::getWindowSize(const std::string& windowHandle)
{
	CommandParameters params;
	params.put("windowHandle", windowHandle);
	return m_private->execute<Dimension>(Command::GET_WINDOW_SIZE, params);
}


void WebDriver::setWindowPosition(const unsigned int x, const unsigned int y, const std::string& windowHandle)
{
	CommandParameters params;
	params.put("x", x);
	params.put("y", y);
	params.put("windowHandle", windowHandle);

	m_private->execute(Command::SET_WINDOW_POSITION, params);
}

template<>
struct response_value_handler<Rect>
{
	Rect get_value(WebDriver::Private& driver, const CommandParameters& params, Response& response)
	{
		return {response.get<int>("x"), response.get<int>("y")};
	}
};

Rect WebDriver::getWindowPosition(const std::string& windowHandle)
{
	CommandParameters params;
	params.put("windowHandle", windowHandle);
	return m_private->execute<Rect>(Command::GET_WINDOW_POSITION, params);
}


ScreenOrientation WebDriver::getOrientiation()
{
	return m_private->execute<ScreenOrientation>(Command::GET_SCREEN_ORIENTATION);
}


struct ScreenOrientationTranslator
{
    typedef std::string            internal_type;
    typedef ScreenOrientation      external_type;

    // Converts a string to ScreenOrientation
    ::boost::optional<external_type> get_value(const internal_type& str)
    {
    	std::cout << "get value: " << str << std::endl;
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

    // Converts a ScreenOrientation to string
    ::boost::optional<internal_type> put_value(const external_type& e)
    {
    	std::cout << "put value: ";
    	switch (e)
    	{
    	case PORTRAIT: {
    		std::cout << "PORTRAIT" << std::endl;
    		return ::boost::optional<internal_type>("PORTRAIT");
    	}
    	case LANDSCAPE: {
    		std::cout << "LANDSCAPE" << std::endl;
    		return ::boost::optional<internal_type>("LANDSCAPE");
    		break;
    	}
    	default: {
    		std::cout << "NONE" << std::endl;
    		return ::boost::optional<internal_type>(boost::none);
    	}
    	}

    }
};


void WebDriver::setOrientation(ScreenOrientation orientation)
{
	CommandParameters params;
	params.put("orientation", orientation);

	m_private->execute(Command::SET_SCREEN_ORIENTATION, params);
}


WebDriver::ScriptArg::ScriptArg(const char* val)
    : m_type(_STRING), m_int_value(0), m_stringvalue(val), m_double_value(0)
{
  std::cout << "create char*" << std::endl;
}

WebDriver::ScriptArg::ScriptArg(std::string val)
    : m_type(_STRING), m_int_value(0), m_stringvalue(val), m_double_value(0)
{
  std::cout << "create string" << std::endl;
}

WebDriver::ScriptArg::ScriptArg(int val)
    : m_type(_INT), m_int_value(val), m_double_value(0)
{
  std::cout << "create int" << std::endl;
}

WebDriver::ScriptArg::ScriptArg(double val)
    : m_type(_DOUBLE), m_int_value(0), m_double_value(val)
{
  std::cout << "create double" << std::endl;
}

WebDriver::ScriptArg::ScriptArg(float val)
    : m_type(_DOUBLE), m_int_value(0), m_double_value(val)
{
  std::cout << "create float" << std::endl;
}

WebDriver::ScriptArg::ScriptArg(bool val)
    : m_type(_STRING), m_int_value(val), m_stringvalue(val ? "true" : "false"),
        m_double_value(0)
{
  std::cout << "create bool" << std::endl;
}

WebDriver::ScriptArg::ScriptArg(const WebElement& val)
    : m_type(_WEBELEMENT), m_int_value(0), m_stringvalue(val.id()),
        m_double_value(0)
{
  std::cout << "create WebElement" << std::endl;
}

WebDriver::ScriptArg::ScriptArg(const ScriptArg& other)
    : m_type(other.m_type), m_int_value(other.m_int_value),
        m_stringvalue(other.m_stringvalue), m_double_value(other.m_double_value)
{
  std::cout << "copy element " << m_type << std::endl;
}

WebDriver::ScriptArg::ArgType  WebDriver::ScriptArg::type() const
{
  return m_type;
}

WebDriver::ScriptArg::operator int() const
{
  return m_int_value;
}

WebDriver::ScriptArg::operator float() const
{
  return m_double_value;
}

WebDriver::ScriptArg::operator double() const
{
  return m_double_value;
}

WebDriver::ScriptArg::operator bool() const
{
  return m_int_value;
}

WebDriver::ScriptArg::operator std::string() const
{
  return m_stringvalue;
}

WebDriver::ScriptResult::ScriptResult(WebDriver::Private& driver, std::string val)
: m_value(val), m_driver(driver)
{

}

WebDriver::ScriptResult::operator int() const throw (std::invalid_argument, std::out_of_range)
{
  return std::stoi(m_value);
}
WebDriver::ScriptResult::operator float() const
{
  return std::stof(m_value);
}
WebDriver::ScriptResult::operator double() const
{
  return std::stod(m_value);
}

WebDriver::ScriptResult::operator bool() const
{
  std::string lower = m_value;
  std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
  if (lower == "true")
  {
    return true;
  }
  else if (lower == "false")
  {
    return false;
  }

  int res = this->operator int();

  return res != 0;
}

WebDriver::ScriptResult::operator WebElement() const
{
  return WebElement(m_driver, m_value);
}

WebDriver::ScriptResult::operator std::string() const
{
  return m_value;
}
/*
struct ScriptArgTranslator
{
    typedef std::string            internal_type;
    typedef ScriptArg              external_type;

    // Converts a string to ScreenOrientation
    ::boost::optional<external_type> get_value(const internal_type& str)
    {
      std::cout << "get value: " << str << std::endl;
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
      std::cout << "put value: ";
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
          argParam.put("ELEMENT", s);

          std::stringstream str;
          boost::property_tree::json_parser::write_json(str, argParam, false);
          return ::boost::optional<internal_type>(str.str());
          break;
        }
        default: {
          std::cout << "NONE" << std::endl;
          return ::boost::optional<internal_type>(boost::none);
        }
      }
    }
};
*/

} /* namespace selenium */

/*  Specialize translator_between so that it uses our custom translator for
    bool value types. Specialization must be in boost::property_tree
    namespace. */
namespace boost {
namespace property_tree {

template<typename Ch, typename Traits, typename Alloc>
struct translator_between<std::basic_string< Ch, Traits, Alloc >,  selenium::ScreenOrientation>
{
    typedef selenium::ScreenOrientationTranslator type;
};

/*template<typename Ch, typename Traits, typename Alloc>
struct translator_between<std::basic_string< Ch, Traits, Alloc >,  selenium::ScriptArg>
{
    typedef selenium::ScriptArgTranslator type;
};*/


} // namespace property_tree
} // namespace boost
