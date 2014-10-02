/*
 * action.cpp
 *
 *  Created on: Sep 12, 2014
 *      Author: speedpat
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
