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

#ifndef ACTION_PRIVATE_HPP_
#define ACTION_PRIVATE_HPP_

#include <vector>
#include <memory>

#include "selenium/interactions/action.hpp"
#include "selenium/command_executor.hpp"

namespace selenium
{
namespace interactions
{
typedef std::function<void(CommandExecutor&)> ActionFunction;

struct Action::Private
{
  Private(CommandExecutor& driver);
  Private(const Private& other);

  void perform();

private:
  friend class Actions;
  std::vector<ActionFunction> m_actions;
  CommandExecutor& m_driver;
};

} /* namespace interactions */
} /* namespace selenium */



#endif /* ACTION_PRIVATE_HPP_ */
