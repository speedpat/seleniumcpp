/*
 * action.hpp
 *
 *  Created on: Sep 12, 2014
 *      Author: speedpat
 */

#ifndef ACTION_HPP_
#define ACTION_HPP_

namespace selenium
{

class CommandExecutor;

namespace interactions
{

class Actions;

class Action
{
public:
  Action(const Action& other);
  ~Action();

  void perform();

private:
  Action(CommandExecutor& driver);
  friend class Actions;
  struct Private;

  Private* m_private;

};

} /* namespace interactions */
} /* namespace selenium */

#endif /* ACTION_HPP_ */
