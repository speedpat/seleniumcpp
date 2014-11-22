/*
 * keys.cpp
 *
 *  Created on: Oct 20, 2014
 *      Author: speedpat
 */

#include "selenium/interactions/keys.hpp"

namespace selenium
{
namespace interactions
{

const Keys Keys::NULL_KEY = Keys(u8"\ue000");
const Keys Keys::CANCEL = Keys(u8"\ue001");
const Keys Keys::HELP = Keys(u8"\ue002");
const Keys Keys::BACK_SPACE = Keys(u8"\ue003");
const Keys Keys::TAB = Keys(u8"\ue004");
const Keys Keys::CLEAR = Keys(u8"\ue005");
const Keys Keys::RETURN = Keys(u8"\ue006");
const Keys Keys::ENTER = Keys(u8"\ue007");
const Keys Keys::SHIFT = Keys(u8"\ue008");
const Keys Keys::LEFT_SHIFT = Keys(u8"\ue008");
const Keys Keys::CONTROL = Keys(u8"\ue009");
const Keys Keys::LEFT_CONTROL = Keys(u8"\ue009");
const Keys Keys::ALT = Keys(u8"\ue00a");
const Keys Keys::LEFT_ALT = Keys(u8"\ue00a");
const Keys Keys::PAUSE = Keys(u8"\ue00b");
const Keys Keys::ESCAPE = Keys(u8"\ue00c");
const Keys Keys::SPACE = Keys(u8"\ue00d");
const Keys Keys::PAGE_UP = Keys(u8"\ue00e");
const Keys Keys::PAGE_DOWN = Keys(u8"\ue00f");
const Keys Keys::END = Keys(u8"\ue010");
const Keys Keys::HOME = Keys(u8"\ue011");
const Keys Keys::LEFT = Keys(u8"\ue012");
const Keys Keys::ARROW_LEFT = Keys(u8"\ue012");
const Keys Keys::UP = Keys(u8"\ue013");
const Keys Keys::ARROW_UP = Keys(u8"\ue013");
const Keys Keys::RIGHT = Keys(u8"\ue014");
const Keys Keys::ARROW_RIGHT = Keys(u8"\ue014");
const Keys Keys::DOWN = Keys(u8"\ue015");
const Keys Keys::ARROW_DOWN = Keys(u8"\ue015");
const Keys Keys::INSERT = Keys(u8"\ue016");
const Keys Keys::DELETE = Keys(u8"\ue017");
const Keys Keys::SEMICOLON = Keys(u8"\ue018");
const Keys Keys::EQUALS = Keys(u8"\ue019");

const Keys Keys::NUMPAD0 = Keys(u8"\ue01a");
const Keys Keys::NUMPAD1 = Keys(u8"\ue01b");
const Keys Keys::NUMPAD2 = Keys(u8"\ue01c");
const Keys Keys::NUMPAD3 = Keys(u8"\ue01d");
const Keys Keys::NUMPAD4 = Keys(u8"\ue01e");
const Keys Keys::NUMPAD5 = Keys(u8"\ue01f");
const Keys Keys::NUMPAD6 = Keys(u8"\ue020");
const Keys Keys::NUMPAD7 = Keys(u8"\ue021");
const Keys Keys::NUMPAD8 = Keys(u8"\ue022");
const Keys Keys::NUMPAD9 = Keys(u8"\ue023");
const Keys Keys::MULTIPLY = Keys(u8"\ue024");
const Keys Keys::ADD = Keys(u8"\ue025");
const Keys Keys::SEPARATOR = Keys(u8"\ue026");
const Keys Keys::SUBTRACT = Keys(u8"\ue027");
const Keys Keys::DECIMAL = Keys(u8"\ue028");
const Keys Keys::DIVIDE = Keys(u8"\ue029");

const Keys Keys::F1 = Keys(u8"\ue031");
const Keys Keys::F2 = Keys(u8"\ue032");
const Keys Keys::F3 = Keys(u8"\ue033");
const Keys Keys::F4 = Keys(u8"\ue034");
const Keys Keys::F5 = Keys(u8"\ue035");
const Keys Keys::F6 = Keys(u8"\ue036");
const Keys Keys::F7 = Keys(u8"\ue037");
const Keys Keys::F8 = Keys(u8"\ue038");
const Keys Keys::F9 = Keys(u8"\ue039");
const Keys Keys::F10 = Keys(u8"\ue03a");
const Keys Keys::F11 = Keys(u8"\ue03b");
const Keys Keys::F12 = Keys(u8"\ue03c");

const Keys Keys::META = Keys(u8"\ue03d");
const Keys Keys::COMMAND = Keys(u8"\ue03d");

Keys::Keys(const std::string& key)
 : std::string(key)
{

}
}
}
