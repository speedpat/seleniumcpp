/*
 * Types.h
 *
 *  Created on: Sep 8, 2014
 *      Author: speedpat
 */

#ifndef TYPES_H_
#define TYPES_H_

#include <map>
#include <list>
#include <vector>

#include <boost/property_tree/ptree.hpp>


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
	LANDSCAPE,
	PORTRAIT
};

typedef std::list<Cookie> Cookies;

typedef std::map<std::string, std::string> Capabilities;

class WebDriver;
class Alert;
class SwitchTo;
class By;
class Locator;

class WebElement;
typedef std::vector<WebElement> WebElements;

typedef boost::property_tree::iptree CommandParameters;
typedef boost::property_tree::iptree Response;


} /* namespace selenium */


#endif /* TYPES_H_ */
