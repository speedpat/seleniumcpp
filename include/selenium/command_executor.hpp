/*
 * command_executor.hpp
 *
 *  Created on: Sep 24, 2014
 *      Author: speedpat
 */

#ifndef COMMAND_EXECUTOR_HPP_
#define COMMAND_EXECUTOR_HPP_

#include "selenium/webelement.hpp"
#include "command.hpp"

namespace selenium
{

class CommandExecutor;
class ScriptArg;
class ScriptResult;

template <typename RES>
struct response_value_handler
{
  RES get_value(CommandExecutor& driver, const CommandParameters& params, Response& response)
  {
    return response.get<RES>("value");
  }

};

template<>
struct response_value_handler<WebElement>
{

  WebElement get_value(CommandExecutor& driver, const CommandParameters& params, Response& response)
  {
    Response element = response.get_child("value");
    std::string elementId = element.get<std::string>("ELEMENT");

    return WebElement(driver, elementId);
  }
};

template<>
struct response_value_handler<WebElements>
{

  WebElements get_value(CommandExecutor& driver, const CommandParameters& params, Response& response)
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
  Dimension get_value(CommandExecutor& driver, const CommandParameters& params, Response& response)
  {
    Response value = response.get_child("value");
    return {value.get<int>("height"), value.get<int>("width")};
  }
};


class CommandExecutor
{
public:
  inline CommandExecutor() {};
  virtual ~CommandExecutor() = default;

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

  virtual Response execute(const Command& command, const CommandParameters& params) = 0;
  virtual Response execute(const Command& command) = 0;

  virtual ScriptResult executeScript(const Command& command, const std::string& script, std::vector<ScriptArg> args) = 0;

};

} /* namespace selenium */

#endif /* COMMAND_EXECUTOR_HPP_ */
