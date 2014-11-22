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

#ifndef DESIREDCAPABILITIES_H_
#define DESIREDCAPABILITIES_H_

#include <map>
#include <string>

namespace selenium {

class DesiredCapabilities {
public:
static const Capabilities FIREFOX;
static const Capabilities CHROME;

private:
struct Initializer
{
  Initializer();
  ~Initializer();
};
static const Initializer INITIALIZER;

/*
 INTERNETEXPLORER = { "browserName", "internet explorer",
 "version", "",
 "platform", "WINDOWS",
 "javascriptEnabled", True }


 OPERA = {"browserName", "opera",
 "version", "",
 "platform", "ANY"}

 HTMLUNIT = {"browserName", "htmlunit",
 "version", "",
 "platform", "ANY" }

 HTMLUNITWITHJS = {"browserName", "htmlunit",
 "version", "firefox",
 "platform", "ANY",
 "javascriptEnabled", True }

 IPHONE = {"browserName", "iPhone",
 "version", "",
 "platform", "MAC",
 "javascriptEnabled", True }

 IPAD = {"browserName", "iPad",
 "version", "",
 "platform", "MAC",
 "javascriptEnabled", True }

 ANDROID = {"browserName", "android",
 "version", "",
 "platform", "ANDROID",
 "javascriptEnabled", True }

 */
};

} /* namespace selenium */

#endif /* DESIREDCAPABILITIES_H_ */
