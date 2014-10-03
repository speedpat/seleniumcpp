/*
 * Actions.cpp
 *
 *  Created on: Sep 11, 2014
 *      Author: speedpat
 */

#include <thread>
#include <chrono>

#include <utf8.h>

#include <boost/algorithm/string.hpp>

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
    params.put("button", button);
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
    moveParams.put("element", onElement.id());
    driver.execute(Command::MOVE_TO, moveParams);
    CommandParameters params;
    params.put("button", button);
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
    params.put("button", button);
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
    moveParams.put("element", onElement.id());
    driver.execute(Command::MOVE_TO, moveParams);
    CommandParameters params;
    params.put("button", button);
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
    moveParams.put("element", onElement.id());
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
    moveParams.put("element", source.id());
    driver.execute(Command::MOVE_TO, moveParams);
    driver.execute(Command::MOUSE_DOWN);
    moveParams.put("element", target.id());
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
    moveParams.put("element", source.id());
    driver.execute(Command::MOVE_TO, moveParams);
    driver.execute(Command::MOUSE_DOWN);
    CommandParameters moveToParams;
    moveToParams.put("xoffset", xOffset);
    moveToParams.put("yoffset", yOffset);
    driver.execute(Command::MOVE_TO, moveToParams);
    driver.execute(Command::MOUSE_UP);
  });
  return *this;
}
/**
 Performs a modifier key press.
 */
/*Actions& Actions::keyDown(std::vector<Keys> keys)
{
  m_private->add([keys](CommandExecutor& driver){
    CommandParameters params;
    CommandParameters keysParam;
    CommandParameters keyParam;
    for (Keys key: keys)
    {
      keyParam.put("", key);
      keysParam.push_back(CommandParameters::value_type("", keyParam));

    }
    params.put_child("value", keysParam);
    driver.execute(Command::SEND_KEYS_TO_ACTIVE_ELEMENT, params);
  });
  return *this;
}*/
/**
 Performs a modifier key press after focusing on an element.
 */
/*Actions& Actions::keyDown(const WebElement& element, std::vector<Keys> keys)
{
  m_private->add([element](CommandExecutor& driver){
    CommandParameters params;
    params.put("element", element.id());
    driver.execute(Command::CLICK_ELEMENT, params);
  });
  keyDown(keys);
  return *this;
}*/
/**
 Performs a modifier key release.
 */
/*Actions& Actions::keyUp(std::vector<Keys> keys)
{
  m_private->add([keys](CommandExecutor& driver){
    CommandParameters params;
    CommandParameters keysParam;
    CommandParameters keyParam;
    for (Keys key: keys)
    {
      keyParam.put("", key);
      keysParam.push_back(CommandParameters::value_type("", keyParam));

    }
    params.put_child("value", keysParam);
    driver.execute(Command::SEND_KEYS_TO_ACTIVE_ELEMENT, params);
  });
  return *this;
}*/
/**
 Performs a modifier key release after focusing on an element.
 */
/*Actions& Actions::keyUp(const WebElement& element, std::vector<Keys> keys)
{
  m_private->add([element](CommandExecutor& driver){
    CommandParameters params;
    params.put("element", element.id());
    driver.execute(Command::CLICK_ELEMENT, params);
  });
  keyUp(keys);
  return *this;
}*/
/**
 Moves the mouse from its current position (or 0,0) by the given offset.
 */
Actions& Actions::moveByOffset(int xOffset, int yOffset)
{
  m_private->add([xOffset, yOffset](CommandExecutor& driver){
    CommandParameters params;
    params.put("xoffset", xOffset);
    params.put("yOffset", yOffset);
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
    params.put("element", toElement.id());
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
    params.put("element", toElement.id());
    params.put("xoffset", xOffset);
    params.put("yOffset", yOffset);
    driver.execute(Command::MOVE_TO, params);
  });
  return *this;
}
/**libutfcpp-dev
 Deprecated.
 'Pause' is considered to be a bad design practice.
 /**
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
    params.put("button", button);
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
    moveParams.put("element", onElement.id());
    driver.execute(Command::MOVE_TO, moveParams);
    CommandParameters params;
    params.put("button", button);
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
    CommandParameters keyParam;
    for (char key: keysToSend)
    {
      keyParam.put("", key);
      keysParam.push_back(CommandParameters::value_type("", keyParam));

    }
    params.put_child("value", keysParam);
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
    CommandParameters keyParam;
    for (char key: keysToSend)
    {
      keyParam.put("", key);
      keysParam.push_back(CommandParameters::value_type("", keyParam));

    }
    params.put_child("value", keysParam);
    params.put("id", element.id());
    driver.execute(Command::SEND_KEYS_TO_ELEMENT, params);
  });
  return *this;
}


struct KeyTranslator
{
    typedef std::string            internal_type;
    typedef interactions::Keys     external_type;



    // Converts a string to ScreenOrientation
    ::boost::optional<external_type> get_value(const internal_type& str)
    {
         LOG("get value: " << str);
        std::string value = ::boost::to_upper_copy(str);
        if (value == "PORTRAIT")
        {
          return ::boost::optional<external_type>(NULL_KEY);
        }
        else if (value == "LANDSCAPE")
        {
          return ::boost::optional<external_type>(F1);
        }
        return ::boost::optional<external_type>(boost::none);
    }

    // Converts a bool to string
    ::boost::optional<internal_type> put_value(const external_type& e)
    {

      switch (e)
      {
      case CONTROL: {
        LOG("put value: " << "CONTROL");
        std::string ustr = u8"\00dc";
        std::string str;
        utf8::utf16to8(ustr.begin(), ustr.end(), std::back_inserter(str));
        return ::boost::optional<internal_type>(str);
      }
      case F1: {
        LOG("put value: " << "F1");
        std::string ustr = u8"\ue0dc";
        std::string str;
        utf8::utf16to8(ustr.begin(), ustr.end(), std::back_inserter(str));
        str = "\xe0\x31";
        return ::boost::optional<internal_type>(str);
        break;
      }
      default: {
        LOG("NONE");
        return ::boost::optional<internal_type>(boost::none);
      }
      }

    }
};

} /* namespace interactions */
} /* namespace selenium */

/*
  Specialize translator_between so that it uses our custom translator for
    bool value types. Specialization must be in boost::property_tree
    namespace.*/



namespace boost {
namespace property_tree {

template<typename Ch, typename Traits, typename Alloc>
struct translator_between<std::basic_string< Ch, Traits, Alloc >,  selenium::interactions::Keys>
{
    typedef selenium::interactions::KeyTranslator type;
};



} // namespace property_tree
} // namespace boost


