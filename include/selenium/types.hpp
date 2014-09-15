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

typedef std::map<std::string, std::string> Cookie;
typedef std::list<Cookie> Cookies;

typedef std::map<std::string, std::string> Capabilities;

class WebDriver;

class WebElement;
typedef std::list<WebElement> WebElements;


} /* namespace selenium */


#endif /* TYPES_H_ */
