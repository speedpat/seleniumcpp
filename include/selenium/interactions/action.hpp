/*
 * action.hpp
 *
 *  Created on: Sep 12, 2014
 *      Author: speedpat
 */

#ifndef ACTION_HPP_
#define ACTION_HPP_

#include <selenium/webdriver.hpp>

namespace selenium
{
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
  Action(WebDriver::Private& driver);
  friend class Actions;
  struct Private;

  Private* m_private;

};

} /* namespace interactions */
} /* namespace selenium */

#endif /* ACTION_HPP_ */
