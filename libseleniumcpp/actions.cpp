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

#include <thread>
#include <chrono>

#include <utf8.h>

#include <boost/algorithm/string.hpp>
#include <boost/optional.hpp>

#include "log.hpp"

#include "selenium/interactions/actions.hpp"
#include "selenium/interactions/action.hpp"
#include "selenium/webdriver.hpp"
#include "selenium/command_executor.hpp"
#include "action_private.hpp"
#include "actions_private.hpp"

namespace selenium
{
namespace interactions
{

void Actions::Private::add(ActionFunction function)
{
  m_actions.push_back(function);
}

Actions::Actions(WebDriver& driver)
    : m_private(new Private()), m_driver(driver)
{

}

Action Actions::build()
{
  Action action(*((CommandExecutor*)m_driver.m_private));
  std::vector<ActionFunction> actions = m_private->m_actions;
  for (auto actionFunction: actions) {
    action.m_private->m_actions.push_back(actionFunction);
  }

  m_private->m_actions.clear();

  return action;
}

Actions& Actions::click(MouseButton button)
{
  m_private->add([button](CommandExecutor& driver){
    CommandParameters params;
    params["button"] = button;
    driver.execute(Command::CLICK, params);
  });
  return *this;
}
/**
 Clicks in the middle of the given element.
 */
Actions& Actions::click(const WebElement& onElement, MouseButton button)
{
  m_private->add([onElement, button](CommandExecutor& driver){
    CommandParameters moveParams;
    moveParams["element"] = onElement.id();
    driver.execute(Command::MOVE_TO, moveParams);
    CommandParameters params;
    params["button"] = button;
    driver.execute(Command::CLICK, params);
  });
  return *this;
}
/**
 Clicks (without releasing) at the current mouse location.
 */
Actions& Actions::clickAndHold(MouseButton button)
{
  m_private->add([button](CommandExecutor& driver){
    CommandParameters params;
    params["button"] = button;
    driver.execute(Command::MOUSE_DOWN, params);
  });
  return *this;
}
/**
 Clicks (without releasing) in the middle of the given element.
 */
Actions& Actions::clickAndHold(const WebElement& onElement, MouseButton button)
{
  m_private->add([onElement, button](CommandExecutor& driver){
    CommandParameters moveParams;
    moveParams["element"] = onElement.id();
    driver.execute(Command::MOVE_TO, moveParams);
    CommandParameters params;
    params["button"] = button;
    driver.execute(Command::MOUSE_DOWN, params);
  });
  return *this;
}
/**
 Performs a context-click at the current mouse location.
 */
Actions& Actions::contextClick()
{
  return click(Right);
}
/**
 Performs a context-click at middle of the given element.
 */
Actions& Actions::contextClick(const WebElement& onElement)
{
  return click(onElement, Right);
}
/**
 Performs a double-click at the current mouse location.
 */
Actions& Actions::doubleClick()
{
  m_private->add([](CommandExecutor& driver){
    driver.execute(Command::DOUBLE_CLICK);
  });
  return *this;
}
/**
 Performs a double-click at middle of the given element.
 */
Actions& Actions::doubleClick(const WebElement& onElement)
{
  m_private->add([onElement](CommandExecutor& driver){
    CommandParameters moveParams;
    moveParams["element"] = onElement.id();
    driver.execute(Command::MOVE_TO, moveParams);
    CommandParameters params;
    driver.execute(Command::DOUBLE_CLICK, params);
  });
  return *this;
}
/**
 A convenience method that performs click-and-hold at the location of the source element, moves to the location of the target element, then releases the mouse.
 */
Actions& Actions::dragAndDrop(const WebElement& source,
    const WebElement& target)
{
  m_private->add([source, target](CommandExecutor& driver){
    CommandParameters moveParams;
    moveParams["element"] = source.id();
    driver.execute(Command::MOVE_TO, moveParams);
    driver.execute(Command::MOUSE_DOWN);
    moveParams["element"] = target.id();
    driver.execute(Command::MOVE_TO, moveParams);
    driver.execute(Command::MOUSE_UP);
  });
  return *this;
}
/**
 A convenience method that performs click-and-hold at the location of the source element, moves by a given offset, then releases the mouse.
 */
Actions& Actions::dragAndDropBy(const WebElement& source, int xOffset,
    int yOffset)
{
  m_private->add([source, xOffset, yOffset](CommandExecutor& driver){
    CommandParameters moveParams;
    moveParams["element"] = source.id();
    driver.execute(Command::MOVE_TO, moveParams);
    driver.execute(Command::MOUSE_DOWN);
    CommandParameters moveToParams;
    moveToParams["xoffset"] = xOffset;
    moveToParams["yoffset"] = yOffset;
    driver.execute(Command::MOVE_TO, moveToParams);
    driver.execute(Command::MOUSE_UP);
  });
  return *this;
}
/**
 Performs a modifier key press.
 */
Actions& Actions::keyDown(const Keys& key)
{
  m_private->add([key](CommandExecutor& driver){
    CommandParameters params;
    CommandParameters keysParam;
    keysParam.append(key);
    params["value"] = keysParam;
    driver.execute(Command::SEND_KEYS_TO_ACTIVE_ELEMENT, params);
  });
  return *this;
}
/**
 Performs a modifier key press after focusing on an element.
 */
Actions& Actions::keyDown(const WebElement& element, const Keys& keys)
{
  click(element);
  keyDown(keys);
  return *this;
}
/**
 Performs a modifier key release.
 */
Actions& Actions::keyUp(const Keys& keys)
{
  m_private->add([keys](CommandExecutor& driver){
    CommandParameters params;
    CommandParameters keysParam;
    keysParam.append(keys);
    params["value"] = keysParam;
    driver.execute(Command::SEND_KEYS_TO_ACTIVE_ELEMENT, params);
  });
  return *this;
}
/**
 Performs a modifier key release after focusing on an element.
 */
Actions& Actions::keyUp(const WebElement& element, const Keys& keys)
{
  click(element);
  keyUp(keys);

  return *this;
}
/**
 Moves the mouse from its current position (or 0,0) by the given offset.
 */
Actions& Actions::moveByOffset(int xOffset, int yOffset)
{
  m_private->add([xOffset, yOffset](CommandExecutor& driver){
    CommandParameters params;
    params["xoffset"] = xOffset;
    params["yOffset"] = yOffset;
    driver.execute(Command::MOVE_TO, params);
  });
  return *this;
}
/**
 Moves the mouse to the middle of the element.
 */
Actions& Actions::moveToElement(const WebElement& toElement)
{
  m_private->add([toElement](CommandExecutor& driver){
    CommandParameters params;
    params["element"] = toElement.id();
    driver.execute(Command::MOVE_TO, params);
  });
  return *this;
}
/**
 Moves the mouse to an offset from the top-left corner of the element.
 */
Actions& Actions::moveToElement(const WebElement& toElement, int xOffset,
    int yOffset)
{
  m_private->add([toElement, xOffset, yOffset](CommandExecutor& driver){
    CommandParameters params;
    params["element"] = toElement.id();
    params["xoffset"] = xOffset;
    params["yOffset"] = yOffset;
    driver.execute(Command::MOVE_TO, params);
  });
  return *this;
}
/**libutfcpp-dev
 Deprecated.
 'Pause' is considered to be a bad design practice.
 */
Actions& Actions::pause(long pause)
{
  m_private->add([pause](CommandExecutor& driver){
    std::this_thread::sleep_for(std::chrono::milliseconds(pause));
  });
  return *this;
}
/**
 A convenience method for performing the actions without calling build() first.
 */
void Actions::perform()
{
  for (ActionFunction action: m_private->m_actions)
  {
    action(*((CommandExecutor*)m_driver.m_private));
  }
 // m_private->m_actions.clear();
}
/**
 Releases the depressed left mouse button at the current mouse location.
 */
Actions& Actions::release(MouseButton button)
{
  m_private->add([button](CommandExecutor& driver){
    CommandParameters params;
    params["button"] = button;
    driver.execute(Command::MOUSE_UP, params);
  });
  return *this;
}
/**
 Releases the depressed left mouse button, in the middle of the given element.
 */
Actions& Actions::release(const WebElement& onElement, MouseButton button)
{
  m_private->add([onElement, button](CommandExecutor& driver){
    CommandParameters moveParams;
    moveParams["element"] = onElement.id();
    driver.execute(Command::MOVE_TO, moveParams);
    CommandParameters params;
    params["button"] = button;
    driver.execute(Command::MOUSE_DOWN, params);
  });
  return *this;
}
/**
 Sends keys to the active element.
 */
Actions& Actions::sendKeys(const std::string& keysToSend)
{
  m_private->add([keysToSend](CommandExecutor& driver){
    CommandParameters params;
    CommandParameters keysParam;
    for (char key: keysToSend)
    {
      std::string keyString;
      keyString += key;
      keysParam.append(keyString);

    }
    params["value"] = keysParam;
    driver.execute(Command::SEND_KEYS_TO_ACTIVE_ELEMENT, params);
  });
  return *this;
}
/**
 Equivalent to calling: Actions.click(element).sendKeys(keysToSend). This method is different from const WebElement&.sendKeys(CharSequence...) - see sendKeys(CharSequence...) for details how.
 */
Actions& Actions::sendKeys(const WebElement& element,
    const std::string& keysToSend)
{
  m_private->add([keysToSend, element](CommandExecutor& driver){
    CommandParameters params;
    CommandParameters keysParam;
    keysParam.append(keysToSend);
    params["value"] = keysParam;
    params["id"] = element.id();
    driver.execute(Command::SEND_KEYS_TO_ELEMENT, params);
  });
  return *this;
}


} /* namespace interactions */
} /* namespace selenium */




