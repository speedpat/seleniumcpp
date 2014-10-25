/*
 * keys.hpp
 *
 *  Created on: Sep 13, 2014
 *      Author: speedpat
 */

#ifndef KEYS_HPP_
#define KEYS_HPP_

#include <string>

namespace selenium
{
namespace interactions
{
class Keys
{
public:
  static const Keys NULL_KEY;
   static const Keys CANCEL      ;
   static const Keys HELP        ;
   static const Keys BACK_SPACE  ;
   static const Keys TAB         ;
   static const Keys CLEAR       ;
   static const Keys RETURN      ;
   static const Keys ENTER       ;
   static const Keys SHIFT       ;
   static const Keys LEFT_SHIFT  ;
   static const Keys CONTROL     ;
   static const Keys LEFT_CONTROL;
   static const Keys ALT         ;
   static const Keys LEFT_ALT    ;
   static const Keys PAUSE       ;
   static const Keys ESCAPE      ;
   static const Keys SPACE       ;
   static const Keys PAGE_UP     ;
   static const Keys PAGE_DOWN   ;
   static const Keys END         ;
   static const Keys HOME        ;
   static const Keys LEFT        ;
   static const Keys ARROW_LEFT  ;
   static const Keys UP          ;
   static const Keys ARROW_UP    ;
   static const Keys RIGHT       ;
   static const Keys ARROW_RIGHT ;
   static const Keys DOWN        ;
   static const Keys ARROW_DOWN  ;
   static const Keys INSERT      ;
   static const Keys DELETE      ;
   static const Keys SEMICOLON   ;
   static const Keys EQUALS      ;

   static const Keys NUMPAD0     ;
   static const Keys NUMPAD1     ;
   static const Keys NUMPAD2     ;
   static const Keys NUMPAD3     ;
   static const Keys NUMPAD4     ;
   static const Keys NUMPAD5     ;
   static const Keys NUMPAD6     ;
   static const Keys NUMPAD7     ;
   static const Keys NUMPAD8     ;
   static const Keys NUMPAD9     ;
   static const Keys MULTIPLY    ;
   static const Keys ADD         ;
   static const Keys SEPARATOR   ;
   static const Keys SUBTRACT    ;
   static const Keys DECIMAL     ;
   static const Keys DIVIDE      ;

   static const Keys F1          ;
   static const Keys F2          ;
   static const Keys F3          ;
   static const Keys F4          ;
   static const Keys F5          ;
   static const Keys F6          ;
   static const Keys F7          ;
   static const Keys F8          ;
   static const Keys F9          ;
   static const Keys F10         ;
   static const Keys F11         ;
   static const Keys F12         ;

   static const Keys META        ;
   static const Keys COMMAND     ;

   const std::string& key() const { return m_key; };

private:
   Keys(std::string key);
   std::string m_key;
};
} /* namespace interactions*/
} /* namespace selenium */


#endif /* KEYS_HPP_ */
