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
