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

#include <iostream>
#include <boost/exception/all.hpp>
#include <selenium/selenium.hpp>

using namespace selenium;
int main(void) {
	try {
		WebDriver driver("http://localhost:9515",
				DesiredCapabilities::CHROME);
//    driver.get("file:///tmp/test.html");
    driver.get("http://www.google.ch");
    //driver.addCookie(Cookie("test", "foo"));

    //driver.getCookies();
/*
		driver.title();
		WebElement element = driver.findElementByID("viewport");
		std::string tagName = element.tagName();
		std::cout << tagName << std::endl;
		WebElements elements = driver.findElementsByID("viewport");
		for (auto element: elements) {
			std::cout << element.tagName() << std::endl;
		}

//		elements = driver.findElementsByTagName("div");
//		for (auto element: elements) {
//			std::cout << element.getAttribute("class") << std::endl;
//		}

		for(auto handle: driver.windowHandles())
		{
			std::cout << handle << std::endl;
		}
*/

		//std::cout << driver.getScreenshotAsFile("/tmp/foo.png") << std::endl;
		//std::cout << driver.getOrientiation() << std::endl;

//		interactions::Actions actions(driver);
/*		actions.click();

		interactions::Action a = actions.build();

		a.perform();*/
/*
		actions.sendKeys("hallo");
		WebElement element = driver.findElementByID("gbqfq");
		actions.sendKeys(element, "gugus");

		interactions::Action a = actions.build();
		a.perform();

		ScriptResult res = driver.executeScript("return arguments[4]", { 42, true, false, "hallo", element, "gugus", 1.1f, 1.1 });
		std::cout << "foooo" << std::endl;
		WebElement foo = res;
    std::cout << "bar" << std::endl;

		foo.clear();
    std::cout << "foooobar" << std::endl;

    ScriptResult res2 = driver.executeScript("return arguments[1]", { 42, true, false, "hallo", element, "gugus", 1.1f, 1.1 });
    bool bRes2 = res2;
    std::cout << (bRes2 ? "yeah" : "boo") << std::endl;

    ExpectedConditions::VisibilityOfElement cond(element);

    Wait w(driver, 10, 100);
    WebElement bb = w.until(ExpectedConditions::VisibilityOfElement(element));
    std::string foos = "foo";
    bool ut = w.until(ExpectedConditions::TitleContains(foos));
    ut = w.until(ExpectedConditions::TitleContains("bar"));

    ut = w.until(ExpectedConditions::TitleIs(foos));
    ut = w.until(ExpectedConditions::TitleIs("bar"));

    bb = w.until(ExpectedConditions::PresenceOfElementLocated(By::id(foos)));
    bb = w.until(ExpectedConditions::PresenceOfElementLocated(By::id("bar")));
*/
	} catch (std::string& e) {
		std::cout << e << std::endl;
	} catch (WebDriverException& e) {
		std::cout << e.what() << std::endl;
	}

	return 0;
}
