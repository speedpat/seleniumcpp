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

#include "selenium/interactions/action.hpp"
#include "action_private.hpp"

namespace selenium
{
namespace interactions {

Action::Private::Private(CommandExecutor& driver)
 : m_driver(driver)
{

}

Action::Private::Private(const Private& other)
 : m_driver(other.m_driver), m_actions(other.m_actions)
{

}

void Action::Private::perform()
{
  for (ActionFunction action: m_actions)
  {
    action(m_driver);
  }
}

Action::Action(const Action& other)
 : m_private(new Private(*other.m_private))
{

}

Action::Action(CommandExecutor& driver)
 : m_private(new Private(driver))
{

}

Action::~Action(){
}

void Action::perform(){
  m_private->perform();
}

} /* namespace interactions */
} /* namespace selenium */
