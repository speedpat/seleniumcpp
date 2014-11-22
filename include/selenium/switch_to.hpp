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

#ifndef SWITCH_TO_HPP_
#define SWITCH_TO_HPP_

#include <string>

namespace selenium
{
class Alert;
class CommandExecutor;
class WebElement;

class SwitchTo
{
public:
  SwitchTo(CommandExecutor& driver);
  //virtual ~SwitchTo() = default;

  Alert alert();
  SwitchTo& defaultContent();
  SwitchTo& frame(const std::string& reference);
  SwitchTo& frame(int index);
  SwitchTo& frame(const WebElement& element);
  SwitchTo& parentFrame();
  SwitchTo& window(const std::string& windowName);
  WebElement activeElement();


private:
  CommandExecutor& m_driver;
};

} /* namespace selenium */

#endif /* SWITCH_TO_HPP_ */
