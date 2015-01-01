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
