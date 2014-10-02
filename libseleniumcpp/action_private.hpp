/*
 * action_private.hpp
 *
 *  Created on: Sep 13, 2014
 *      Author: speedpat
 */

#ifndef ACTION_PRIVATE_HPP_
#define ACTION_PRIVATE_HPP_

#include <vector>

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
