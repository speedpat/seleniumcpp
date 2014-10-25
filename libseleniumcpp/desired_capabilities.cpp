/*
 * DesiredCapabilities.cpp
 *
 *  Created on, Sep 6, 2014
 *      Author, speedpat
 */


#include "selenium/types.hpp"
#include "selenium/desired_capabilities.hpp"

namespace selenium {

const Capabilities DesiredCapabilities::FIREFOX = Json::Value(Json::objectValue);
const Capabilities DesiredCapabilities::CHROME = Json::Value(Json::objectValue);

const DesiredCapabilities::Initializer DesiredCapabilities::INITIALIZER = DesiredCapabilities::Initializer();

DesiredCapabilities::Initializer::Initializer()
{
  Json::Value firefox(Json::objectValue);
  firefox["browserName"] = "firefox";
  firefox["version"] = "";
  firefox["platform"] = "ANY";
  firefox["javascriptEnabled"] = "True";

  const_cast<Capabilities&>(FIREFOX) = firefox;

  Json::Value chrome(Json::objectValue);
  chrome["browserName"] = "chrome";
  chrome["version"] = "";
  chrome["platform"] = "ANY";
  chrome["javascriptEnabled"] = "True";

  const_cast<Capabilities&>(CHROME) = chrome;
}

DesiredCapabilities::Initializer::~Initializer()
{

}
/*
    struct Initializer
    {
      Initializer();
      ~Initializer();
    };
    static const Initializer INITIALIZER;*/

/*
{ { "browserName", "firefox" }, { "version",
    "" }, { "platform", "ANY" }, { "javascriptEnabled", "True" } };
*/

/*
{ { "browserName", "chrome" }, { "version",
    "" }, { "platform", "ANY" }, { "javascriptEnabled", "True" } };
*/

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
} /* namespace selenium */

