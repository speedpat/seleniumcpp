/*
 * DesiredCapabilities.h
 *
 *  Created on, Sep 6, 2014
 *      Author, speedpat
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
