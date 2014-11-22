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

#ifndef TYPES_H_
#define TYPES_H_

#include <map>
#include <list>
#include <vector>
#include <string>

#include <json/json.h>

#include <selenium/cookie.hpp>

namespace selenium {
struct Dimension
{
	int height;
	int width;
};

struct Rect
{
	int x;
	int y;
};

enum ScreenOrientation
{
  UNDEFINED,
	LANDSCAPE,
	PORTRAIT
};

typedef std::list<Cookie> Cookies;

typedef Json::Value Capabilities;

class WebDriver;
class Alert;
class SwitchTo;
class By;
class Locator;

class WebElement;
typedef std::vector<WebElement> WebElements;

/*typedef boost::property_tree::iptree CommandParameters;
typedef boost::property_tree::iptree Response;*/

typedef Json::Value CommandParameters;
typedef Json::Value Response;
typedef Json::Value Attribute;

class ScriptArg;
typedef std::vector<ScriptArg> ScriptArgs;


class WindowHandle : public std::string
{
public:
   using std::string::string;
   WindowHandle(const std::string& str)
    : std::string(str)
   {

   }
};

typedef std::vector<WindowHandle> WindowHandles;

} /* namespace selenium */


#endif /* TYPES_H_ */
