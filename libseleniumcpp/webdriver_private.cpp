/*
 * WebDriver_Private.cpp
 *
 *  Created on: Sep 8, 2014
 *      Author: speedpat
 */

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/xpressive/xpressive.hpp>

#include <selenium/exceptions.hpp>

#include "webdriver_private.hpp"
#include "command.hpp"

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
            "/session/${sessionId}/frame/parent" } },
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
        { Command::TOUCH_ELEMENT_SCROLL, { POST,
            "session/:sessionId/touch/scroll" } },
        { Command::TOUCH_ELEMENT_DOUBLETAP, { POST,
            "session/:sessionId/touch/doubleclick" } },
        { Command::TOUCH_ELEMENT_LONGTAP, { POST,
            "session/:sessionId/touch/longclick" } },
        { Command::TOUCH_ELEMENT_FLICK,
            { POST, "session/:sessionId/touch/flick" } },
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
  _params.add(std::string("sessionId"), m_sessionId);

  boost::network::uri::uri request_uri(m_uri);
  std::string path = pos->second.second;
  boost::xpressive::sregex envar = "$(" >> (boost::xpressive::s1 =
      +boost::xpressive::_w) >> ')';
  std::string output = boost::xpressive::regex_replace(path, envar,
      [&_params](boost::xpressive::smatch const &what)
      {
        std::cout << what[1].str() << std::endl;
        std::string value = _params.get<std::string>(what[1].str());
        _params.erase(what[1].str());
        return value;
      });

  request_uri.append(output);

  std::cout << request_uri.string() << std::endl;

  httpclient::request request(request_uri);
  request << boost::network::header("Content-Type",
      "application/x-www-form-urlencoded");
  request << boost::network::header("Accept", "application/json");

  std::stringstream bs;
  boost::property_tree::json_parser::write_json(bs, _params, false);
  std::string body = bs.str();
  std::stringstream length;
  length << body.length();
  request << boost::network::header("Content-Length", length.str());

  std::cout << "request: " << body << std::endl;
  request.body(body);

  httpclient::response response;
  switch (pos->second.first)
  {
    case GET:
      {
      std::cout << "GET" << std::endl;
      response = m_client.get(request);
      break;
    }
    case POST:
      {
      std::cout << "POST" << std::endl;
      response = m_client.post(request);
      break;
    }
    case DELETE:
      {
      std::cout << "DELETE" << std::endl;
      response = m_client.delete_(request);
      break;
    }
    default:
      {
      throw WebDriverException("unknown request method");
    }
  }

  if (response.status() == 200)
  {
    boost::property_tree::iptree res;
    std::stringstream str(response.body());
    std::cout << "response: " << response.body() << std::endl;
    try
    {
      boost::property_tree::json_parser::read_json(str, res);
    }
    catch (boost::property_tree::json_parser::json_parser_error& e)
    {
      throw ErrorInResponseException("failed to parse response", e);
    }

    ResponseStatusCode status = static_cast<ResponseStatusCode>(res.get<int>(
        "status"));
    std::string value = res.get<std::string>("value");
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
        throw NoSuchElementException(value);
        break;
      }
      case NoSuchFrame:
        {
        throw NoSuchFrameException(value);
        break;
      }
      case UnknownCommand:
        {
        break;
      }
      case StaleElementReference:
        {
        break;
      }
      case ElementNotVisible:
        {
        break;
      }
      case InvalidElementState:
        {
        break;
      }
      case UnknownError:
        {
        break;
      }
      case ElementIsNotSelectable:
        {
        break;
      }
      case JavaScriptError:
        {
        break;
      }
      case XPathLookupError:
        {
        break;
      }
      case Timeout:
        {
        break;
      }
      case NoSuchWindow:
        {
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
        break;
      }
      case NoAlertOpenError:
        {
        break;
      }
      case ScriptTimeout:
        {
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
        break;
      }
      case SessionNotCreatedException:
        {
        break;
      }
      case MoveTargetOutOfBounds:
        {
        break;
      }
      default:
        throw ErrorInResponseException(value);
    }
  }
  else
  {
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
  cookie["name"] = element.get<std::string>("name");
  cookie["value"] = element.get<std::string>("value");

  boost::optional<std::string> path = element.get_optional<std::string>("path");
  if (path)
  {
    cookie["path"] = path.get();
  }

  boost::optional<std::string> domain = element.get_optional<std::string>(
      "domain");
  if (domain)
  {
    cookie["domain"] = domain.get();
  }

  boost::optional< bool > secure = element.get_optional< bool >("secure");
  if (secure)
  {
    cookie["secure"] = secure.get() ? "true" : "false";
  }

  boost::optional< bool > httpOnly = element.get_optional< bool >("httpOnly");
  if (httpOnly)
  {
    cookie["httpOnly"] = httpOnly.get() ? "true" : "false";
  }

  boost::optional<unsigned int> expiry = element.get_optional<unsigned int>(
      "expiry");
  if (expiry)
  {
    std::stringstream str;
    str << expiry.get();
    cookie["expiry"] = str.str();
  }
  return cookie;
}

WebDriver::ScriptResult WebDriver::Private::executeScript(
    const Command& command,
    const std::string& script, std::vector<WebDriver::ScriptArg> args)
{
  CommandParameters params;
  params.add("script", script);
  CommandParameters argsParam;
  CommandParameters argParam;
  CommandParameters elementParam;

  for (ScriptArg arg : args)
  {
    switch (arg.type())
    {
      case ScriptArg::ArgType::_INT:
        {
        argParam.put("", (int) arg);
        break;
      }
      case ScriptArg::ArgType::_DOUBLE:
        {
        argParam.put("", (double) arg);
        break;
      }
      case ScriptArg::ArgType::_STRING:
        {
        argParam.put("", (std::string) arg);
        break;
      }
      case ScriptArg::ArgType::_WEBELEMENT:
        {
        argParam.put("ELEMENT", (std::string) arg);
        break;
      }
    }
    argsParam.push_back(CommandParameters::value_type("", argParam));
    argParam.clear();
  }
  params.put_child("args", argsParam);
  Response response = execute(command, params);
  Response value = response.get_child("value");
  if (value.find("ELEMENT") != value.not_found())
  {
    std::string elementId = value.get<std::string>("ELEMENT");
    return ScriptResult(*this, elementId);
  }

  return ScriptResult(*this, value.data());

}
} /* namespace selenium */
