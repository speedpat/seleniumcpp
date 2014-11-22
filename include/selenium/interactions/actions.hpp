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

#ifndef ACTIONS_H_
#define ACTIONS_H_

#include <string>

#include <selenium/interactions/action.hpp>
#include <selenium/interactions/keys.hpp>

namespace selenium
{
class WebElement;
class CommandExecutor;
class WebDriver;

namespace interactions
{


enum MouseButton
{
  Left,
  Middle,
  Right
};

class Actions
{
public:
  Actions(WebDriver& driver);
  ~Actions() = default;

  /**
   Generates a composite action containing all actions so far, ready to be performed (and resets the internal builder state, so subsequent calls to build() will contain fresh sequences).
   */
  Action build();
  /**
   Clicks at the current mouse location.
   */
  Actions& click(MouseButton button = Left);
  /**
   Clicks in the middle of the given element.
   */
  Actions& click(const WebElement& onElement, MouseButton button = Left);
  /**
   Clicks (without releasing) at the current mouse location.
   */
  Actions& clickAndHold(MouseButton button = Left);
  /**
   Clicks (without releasing) in the middle of the given element.
   */
  Actions& clickAndHold(const WebElement& onElement, MouseButton button = Left);
  /**
   Performs a context-click at the current mouse location.
   */
  Actions& contextClick();
  /**
   Performs a context-click at middle of the given element.
   */
  Actions& contextClick(const WebElement& onElement);
  /**
   Performs a double-click at the current mouse location.
   */
  Actions& doubleClick();
  /**
   Performs a double-click at middle of the given element.
   */
  Actions& doubleClick(const WebElement& onElement);
  /**
   A convenience method that performs click-and-hold at the location of the source element, moves to the location of the target element, then releases the mouse.
   */
  Actions& dragAndDrop(const WebElement& source, const WebElement& target);
  /**
   A convenience method that performs click-and-hold at the location of the source element, moves by a given offset, then releases the mouse.
   */
  Actions& dragAndDropBy(const WebElement& source, int xOffset, int yOffset);
  /**
   Performs a modifier key press.
   */
  Actions& keyDown(const Keys& key);
  /**
   Performs a modifier key press after focusing on an element.
   */
  Actions& keyDown(const WebElement& element, const Keys& key);
  /**
   Performs a modifier key release.
   */
  Actions& keyUp(const Keys& key);
  /**
   Performs a modifier key release after focusing on an element.
   */
  Actions& keyUp(const WebElement& element, const Keys& key);
  /**
   Moves the mouse from its current position (or 0,0) by the given offset.
   */
  Actions& moveByOffset(int xOffset, int yOffset);
  /**
   Moves the mouse to the middle of the element.
   */
  Actions& moveToElement(const WebElement& toElement);
  /**
   Moves the mouse to an offset from the top-left corner of the element.
   */
  Actions& moveToElement(const WebElement& toElement, int xOffset, int yOffset);
  /**
   Deprecated.
   'Pause' is considered to be a bad design practice.
   /**
   */
  Actions& pause(long pause);
  /**
   A convenience method for performing the actions without calling build() first.
   */
  void perform();
  /**
   Releases the depressed left mouse button at the current mouse location.
   */
  Actions& release(MouseButton button);
  /**
   Releases the depressed left mouse button, in the middle of the given element.
   */
  Actions& release(const WebElement& onElement, MouseButton button = Left);
  /**
   Sends keys to the active element.
   */
  Actions& sendKeys(const std::string& keysToSend);
  /**
   Equivalent to calling: Actions.click(element).sendKeys(keysToSend). This method is different from const WebElement&.sendKeys(CharSequence...) - see sendKeys(CharSequence...) for details how.
   */
  Actions& sendKeys(const WebElement& element, const std::string& keysToSend);
private:
  struct Private;
  Private* m_private;
  WebDriver& m_driver;

};
} /* namespace interactions*/
} /* namespace selenium */

#endif /* ACTIONS_H_ */
