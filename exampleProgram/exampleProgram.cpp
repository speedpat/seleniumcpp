/*
 ============================================================================
 Name        : exampleProgram.c
 Author      : SpeedPat
 Version     :
 Copyright   : (C) 2014 by SpeedPat
 Description : Uses shared library to print greeting
 To run the resulting executable the LD_LIBRARY_PATH must be
 set to ${project_loc}/libseleniumcpp/.libs
 Alternatively, libtool creates a wrapper shell script in the
 build directory of this program which can be used to run it.
 Here the script will be called exampleProgram.
 ============================================================================
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

		interactions::Actions actions(driver);
/*		actions.click();

		interactions::Action a = actions.build();

		a.perform();*/

		actions.sendKeys("hallo");
		WebElement element = driver.findElementByID("gbqfq");
		actions.sendKeys(element, "gugus");

		interactions::Action a = actions.build();
		a.perform();

		WebDriver::ScriptResult res = driver.executeScript("return arguments[4]", { 42, true, false, "hallo", element, "gugus", 1.1f, 1.1 });
		std::cout << "foooo" << std::endl;
		WebElement foo = res;
    std::cout << "bar" << std::endl;

		foo.clear();
    std::cout << "foooobar" << std::endl;

    WebDriver::ScriptResult res2 = driver.executeScript("return arguments[1]", { 42, true, false, "hallo", element, "gugus", 1.1f, 1.1 });
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

	} catch (std::string& e) {
		std::cout << e << std::endl;
	} catch (WebDriverException& e) {
		std::cout << e.what() << std::endl;
	}

	return 0;
}
