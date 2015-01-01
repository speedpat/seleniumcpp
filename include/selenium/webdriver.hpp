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

#ifndef WEBDRIVER_H_
#define WEBDRIVER_H_

#include <string>
#include <vector>
#include <selenium/types.hpp>
#include <selenium/script_result.hpp>
#include <selenium/script_arg.hpp>

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
class ScriptArg;
class ScriptResult;

class WebDriver {
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

	const ScriptResult executeScript(const std::string& script, const ScriptArgs& args = {});

	template <typename T>
	const ScriptResult executeScript(const std::string& script, const std::vector<T>& args)
	{
	  ScriptArgs scriptArgs;
	  for (auto element: args)
	  {
	     scriptArgs.push_back(element);
	  }
	  ScriptArgs arg;
	  arg.push_back(scriptArgs);
	  return executeScript(script, arg);
	}

	const ScriptResult executeScript(const std::string& script, const std::map<std::string, ScriptArg>& args)
	{
	  ScriptArg arg(Json::objectValue);
	  for (std::pair<std::string, ScriptArg> entry: args)
	  {
	    arg[entry.first] = entry.second;
	  }
	  return executeScript(script, { arg });
	}

	const ScriptResult executeAsyncScript(const std::string& script, const ScriptArgs& args = {});

	std::string currentUrl();
	std::string pageSource();

	WindowHandle currentWindowHandle();
	WindowHandles windowHandles();

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
	void addCookie(const Cookie& cookie);

	void implicitlyWait(const unsigned int timeToWait);
	template <class Rep, class period>
  void setScriptTimeout(std::chrono::duration<Rep, period> timeout)
	{
	  std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(timeout);
	  setScriptTimeoutMs(ms.count());
	}

	void setScriptTimeoutMs(double timeToWait);
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

  struct Private;

private:
	friend class interactions::Actions;
	friend class interactions::Action;
	Private* m_private;
	Capabilities m_capabilitites;
};

} /* namespace selenium */

#endif /* WEBDRIVER_H_ */
