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

#ifndef KEYS_HPP_
#define KEYS_HPP_

#include <string>

namespace selenium
{
namespace interactions
{
class Keys : public std::string
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

private:
   using std::string::string;
   Keys(const std::string& key);
};
} /* namespace interactions*/
} /* namespace selenium */


#endif /* KEYS_HPP_ */
