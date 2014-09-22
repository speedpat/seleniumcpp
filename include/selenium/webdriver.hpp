/*
 * WebDriver.h
 *
 *  Created on: Sep 4, 2014
 *      Author: speedpat
 */

#ifndef WEBDRIVER_H_
#define WEBDRIVER_H_

#include <string>
#include <vector>
#include <selenium/types.hpp>

namespace selenium {
namespace interactions {
class Actions;
class Action;
}
class By;
class Locator;
class WebElement;
class Mobile;
class ApplicationCache;

class WebDriver {
public:
  struct Private;
  class ScriptArg
  {
  public:
    enum ArgType
    {
      _INT,
      _DOUBLE,
      _STRING,
      _WEBELEMENT,
    };
    ScriptArg(const char* val);
    ScriptArg(std::string val);
    ScriptArg(int val);
    ScriptArg(long val);
    ScriptArg(double val);
    ScriptArg(float val);
    ScriptArg(bool val);
    ScriptArg(const WebElement& val);
    ScriptArg(const ScriptArg& other);

    ArgType type() const;
    operator int() const;
    operator long() const;
    operator float() const;
    operator double() const;
    operator bool() const;
    operator std::string() const;

  private:
    ArgType m_type;
    std::string m_stringvalue;
    long m_int_value;
    double m_double_value;
  };

  class ScriptResult
  {
  public:
    ScriptResult(WebDriver::Private& driver, std::string val);
    ScriptResult(const ScriptResult& other);

    operator int() const throw (std::invalid_argument, std::out_of_range);
    operator long() const throw (std::invalid_argument, std::out_of_range);
    operator float() const;
    operator double() const;
    operator bool() const;
    operator WebElement() const;
    operator std::string() const;

  private:
    std::string m_value;
    WebDriver::Private& m_driver;
  };

public:
	WebDriver(const std::string& uri, const Capabilities& capabilities);
	virtual ~WebDriver();

	void get(std::string uri);
	std::string title();
	void close();
	void quit();

	WebElement findElementByID(const std::string& id);
	WebElement findElementByName(const std::string& name);
	WebElement findElementByLinkText(const std::string& linkText);
	WebElement findElementByPartialLinkText(const std::string& linkText);
	WebElement findElementByTagName(const std::string& name);
	WebElement findElementByXPath(const std::string& xpath);
	WebElement findElementByClassName(const std::string& className);
	WebElement findElementByCssSelector(const std::string& css_selector);

	WebElement findElement(const By& by, const std::string& value);
	WebElement findElement(const Locator& locator);

	WebElements findElementsByID(const std::string& id);
	WebElements findElementsByName(const std::string& name);
	WebElements findElementsByLinkText(const std::string& linkText);
	WebElements findElementsByPartialLinkText(const std::string& linkText);
	WebElements findElementsByTagName(const std::string& name);
	WebElements findElementsByXPath(const std::string& xpath);
	WebElements findElementsByClassName(const std::string& className);
	WebElements findElementsByCssSelector(const std::string& css_selector);

	WebElements findElements(const By& by, const std::string& value);
  WebElements findElements(const Locator& locator);

	ScriptResult executeScript(const std::string& script, std::vector<ScriptArg> args = {});
	ScriptResult executeAsyncSript(const std::string& script, std::vector<ScriptArg> args = {});

	std::string currentUrl();
	std::string pageSource();

	std::string currentWindowHandle();
	std::vector<std::string> windowHandles();

	void maximizeWindow();

	SwitchTo switchTo();
	Mobile mobile();

	void back();
	void forward();
	void refresh();

	Cookies getCookies();
	Cookie getCookie(const std::string& name);
	void deleteCookie(const std::string& name);
	void deleteAllCookies();
	void addCookie(Cookie cookie);

	void implicitlyWait(const unsigned int timeToWait);
	void setScriptTimeout(const unsigned int timeToWait);
	void setPageLoadTimeout(const unsigned int timeToWait);

	Capabilities getCapabilities();
	bool getScreenshotAsFile(const std::string& filename);
	std::string getScreenshotAsBase64();
	std::vector<char> getScreenshotAsPMG();

	void setWindowSize(const unsigned int width, const unsigned int height, const std::string& windowHandle = "current");
	Dimension getWindowSize(const std::string& windowHandle = "current");

	void setWindowPosition(const unsigned int x, const unsigned int y, const std::string& windowHandle = "current");
	Rect getWindowPosition(const std::string& windowHandle = "current");

	ScreenOrientation getOrientiation();
	void setOrientation(ScreenOrientation orientation);

	ApplicationCache getApplicationCache();

	std::vector<std::string> getLogTypes();
	std::vector<std::string> getLog(const std::string& logType);

private:
	friend class interactions::Actions;
	friend class interactions::Action;
	Private* m_private;
	Capabilities m_capabilitites;
};

} /* namespace selenium */

#endif /* WEBDRIVER_H_ */
