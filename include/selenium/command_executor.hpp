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
    return response["value"].asString();
  }

};

template <>
struct response_value_handler<Response>
{
  Response get_value(CommandExecutor& driver, const CommandParameters& params, Response& response)
  {
    return response["value"];
  }

};

template <>
struct response_value_handler<int>
{
  int get_value(CommandExecutor& driver, const CommandParameters& params, Response& response)
  {
    return response["value"].asInt();
  }
};

template <>
struct response_value_handler<bool>
{
  bool get_value(CommandExecutor& driver, const CommandParameters& params, Response& response)
  {
    return response["value"].asBool();
  }
};

template<>
struct response_value_handler<WebElement>
{

  WebElement get_value(CommandExecutor& driver, const CommandParameters& params, Response& response)
  {
    Response element = response["value"];
    std::string elementId = element["ELEMENT"].asString();

    return WebElement(driver, elementId);
  }
};

template<>
struct response_value_handler<WebElements>
{

  WebElements get_value(CommandExecutor& driver, const CommandParameters& params, Response& response)
  {
    Response elements = response["value"];
    WebElements webElements;
    for (Response::iterator pos = elements.begin();
        pos != elements.end(); ++pos) {
      std::string elementId = (*pos)["ELEMENT"].asString();
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
    Response value = response["value"];
    return {value["height"].asInt(), value["width"].asInt()};
  }
};


class CommandExecutor
{
public:
  CommandExecutor() = default;
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

  virtual const ScriptResult executeScript(const Command& command, const std::string& script, const std::vector<ScriptArg>& args) = 0;

};

} /* namespace selenium */

#endif /* COMMAND_EXECUTOR_HPP_ */
