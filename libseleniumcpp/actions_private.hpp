/*
 * actions_private.hpp
 *
 *  Created on: Sep 13, 2014
 *      Author: speedpat
 */

#ifndef ACTIONS_PRIVATE_HPP_
#define ACTIONS_PRIVATE_HPP_

#include <memory>
#include <vector>
#include "selenium/interactions/actions.hpp"

namespace selenium
{
namespace interactions
{

struct Actions::Private
{
  void add(ActionFunction function);
  std::vector<ActionFunction> m_actions;
};

} /* namespace interactions */
} /* namespace selenium */



#endif /* ACTIONS_PRIVATE_HPP_ */
