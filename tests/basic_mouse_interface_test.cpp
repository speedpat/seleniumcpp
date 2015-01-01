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

#include <list>

#include <boost/regex.hpp>

#include <gmock/gmock.h>

#include "selenium/selenium.hpp"
#include "support/selenium_testcase.hpp"
#include "support/expected_test_conditions.hpp"

using namespace selenium;
using namespace interactions;
using namespace testing;

class FinalAction
{
public:
  FinalAction(std::function<void()> action)
   : m_action(action) {};
  ~FinalAction()
  {
    m_action();
  }

private:
  std::function<void()> m_action;
};

class BasicMouseInterfaceTest : public SeleniumTestCase
{
public:

  virtual void SetUp()
  {
    SeleniumTestCase::SetUp();

  }

  virtual void TearDown()
  {
    SeleniumTestCase::TearDown();
  }

  Actions getBuilder(WebDriver& driver)
  {
    return Actions(webDriver());
  }

 void performDragAndDropWithMouse()
  {
    webDriver().get(pages().draggableLists);

    WebElement dragReporter = webDriver().findElement(By::id("dragging_reports"));

    WebElement toDrag = webDriver().findElement(By::id("rightitem-3"));
    WebElement dragInto = webDriver().findElement(By::id("sortable1"));

    interactions::Action holdItem = getBuilder(webDriver()).clickAndHold(toDrag).build();

    interactions::Action moveToSpecificItem = getBuilder(webDriver())
    .moveToElement(webDriver().findElement(By::id("leftitem-4")))
    .build();

    interactions::Action moveToOtherList = getBuilder(webDriver()).moveToElement(dragInto).build();

    interactions::Action drop = getBuilder(webDriver()).release(dragInto).build();

    ASSERT_THAT(dragReporter.text(), Eq("Nothing happened."));

    {
      FinalAction([&drop]() { drop.perform(); });
      holdItem.perform();
      moveToSpecificItem.perform();
      moveToOtherList.perform();

      std::string text = dragReporter.text();
      boost::regex regex("Nothing happened. (?:DragOut *)+", boost::regex_constants::ECMAScript);
      ASSERT_TRUE(boost::regex_match(text, regex));
    }
  }

  bool isElementAvailable(WebDriver& driver, const Locator& locator)
 {
   try
   {
     webDriver().findElement(locator);
     return true;
   }
   catch (NoSuchElementException& e)
   {
     return false;
   }
 }

  //@SuppressWarnings("unchecked")
  ScriptResult getElementSize(WebElement& element)
  {
    return webDriver().executeScript(
        "return arguments[0].getBoundingClientRect()", {element});
  }

  int getHeight(const ScriptResult& sizeRect)
  {
    if (sizeRect.isMember("height"))
    {
      return getFieldValue(sizeRect, "height");
    }
    else
    {
      return getFieldValue(sizeRect, "bottom") - getFieldValue(sizeRect, "top");
    }
  }

  int getFieldValue(const ScriptResult& sizeRect, std::string fieldName)
  {
    if (sizeRect.isMember(fieldName) && sizeRect[fieldName].isConvertibleTo(Json::realValue))
    {
      return (int) sizeRect[fieldName].asDouble();
    }
    return 0;
  }

};

//@JavascriptEnabled
//@Ignore({ANDROID, IPHONE})
//@Test
TEST_F(BasicMouseInterfaceTest, testDraggingElementWithMouseMovesItToAnotherList)
{
  performDragAndDropWithMouse();
  WebElement dragInto = webDriver().findElement(By::id("sortable1"));
  ASSERT_THAT(dragInto.findElements(By::tagName("li")).size(), Eq(6));
}

//@JavascriptEnabled
//@Ignore(
//value =
//{ HTMLUNIT, ANDROID, IPHONE},
//    reason = "Advanced mouse actions only implemented in rendered browsers")
// This test is very similar to testDraggingElementWithMouse. The only
// difference is that this test also verifies the correct events were fired.
//@Test
TEST_F(BasicMouseInterfaceTest, testDraggingElementWithMouseFiresEvents)
{
  performDragAndDropWithMouse();
  WebElement dragReporter = webDriver().findElement(By::id("dragging_reports"));
  // This is failing under HtmlUnit. A bug was filed.
  std::string text = dragReporter.text();
  boost::regex regex("Nothing happened. (?:DragOut *)+DropIn RightItem 3", boost::regex_constants::ECMAScript);
  ASSERT_TRUE(boost::regex_match(text, regex));
}



//@JavascriptEnabled
//@Ignore({ANDROID, IPHONE})
//@Test
TEST_F(BasicMouseInterfaceTest, testDoubleClickThenGet)
{
  // Fails in ff3 if WebLoadingListener removes browser listener
  webDriver().get(pages().javascriptPage);

  WebElement toClick = webDriver().findElement(By::id("clickField"));

  interactions::Action dblClick = getBuilder(webDriver()).doubleClick(toClick).build();
  dblClick.perform();

  webDriver().get(pages().droppableItems);
}

//@JavascriptEnabled
//@Ignore({ANDROID, IPHONE})
//@Test
TEST_F(BasicMouseInterfaceTest, testDragAndDrop)
{
  webDriver().get(pages().droppableItems);

  std::chrono::system_clock::time_point waitEndTime = std::chrono::system_clock::now() + std::chrono::seconds(15);

  while (!isElementAvailable(webDriver(), By::id("draggable")) &&
      (std::chrono::system_clock::now() < waitEndTime))
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
  }

  if (!isElementAvailable(webDriver(), By::id("draggable")))
  {
    FAIL() << "Could not find draggable element after 15 seconds.";
    return;
  }

  WebElement toDrag = webDriver().findElement(By::id("draggable"));
  WebElement dropInto = webDriver().findElement(By::id("droppable"));

  interactions::Action holdDrag = getBuilder(webDriver()).clickAndHold(toDrag).build();

  interactions::Action move = getBuilder(webDriver())
  .moveToElement(dropInto).build();

  interactions::Action drop = getBuilder(webDriver()).release(dropInto).build();

  holdDrag.perform();
  move.perform();
  drop.perform();

  dropInto = webDriver().findElement(By::id("droppable"));
  std::string text = dropInto.findElement(By::tagName("p")).text();

  ASSERT_THAT(text, Eq("Dropped!"));
}

//@JavascriptEnabled
//@Ignore({ANDROID, IPHONE, OPERA})
//@Test
TEST_F(BasicMouseInterfaceTest, testDoubleClick)
{
  webDriver().get(pages().javascriptPage);

  WebElement toDoubleClick = webDriver().findElement(
      By::id("doubleClickField"));

  interactions::Action dblClick = getBuilder(webDriver()).doubleClick(toDoubleClick).build();

  dblClick.perform();
  std::string testFieldContent = wait().until(
      ElementValueToBeEqual(toDoubleClick, "DoubleClicked"));
  ASSERT_THAT(testFieldContent, Eq("DoubleClicked")) << "Value should change to DoubleClicked.";
}

//@JavascriptEnabled
//@Ignore({ANDROID, HTMLUNIT, IPHONE})
//@Test
TEST_F(BasicMouseInterfaceTest, testContextClick)
{
  webDriver().get(pages().javascriptPage);

  WebElement toContextClick = webDriver().findElement(
      By::id("doubleClickField"));

  interactions::Action contextClick = getBuilder(webDriver()).contextClick(toContextClick).build();

  contextClick.perform();
  ASSERT_THAT(toContextClick.getAttribute("value"), Eq("ContextClicked")) << "Value should change to ContextClicked.";
}

//@JavascriptEnabled
//@Ignore({ANDROID, IPHONE})
//@Test
TEST_F(BasicMouseInterfaceTest, testMoveAndClick)
{
  webDriver().get(pages().javascriptPage);

  WebElement toClick = webDriver().findElement(By::id("clickField"));

  interactions::Action contextClick =
      getBuilder(webDriver()).moveToElement(toClick).click().build();

  contextClick.perform();

  wait().until(ElementValueToBeEqual(toClick, "Clicked"));

  ASSERT_THAT(toClick.getAttribute("value"), Eq("Clicked")) << "Value should change to Clicked.";
}

//@JavascriptEnabled
//@Ignore({ANDROID, CHROME, IE, IPHONE})
//@Test
/*TEST_F(BasicMouseInterfaceTest, testCannotMoveToANullLocator)
{
  webDriver().get(pages().javascriptPage);

  try
  {
    interactions::Action contextClick = getBuilder(webDriver()).moveToElement(null).build();

    contextClick.perform();
    fail("Shouldn't be allowed to click on null element.");
  }
  catch (IllegalArgumentException expected)
  {
    // Expected.
  }
}*/

//@JavascriptEnabled
//@Ignore({ANDROID, CHROME, IE, IPHONE, FIREFOX, OPERA, HTMLUNIT, OPERA_MOBILE})
//@Test
TEST_F(BasicMouseInterfaceTest, testMousePositionIsNotPreservedInActionsChain)
{
  webDriver().get(pages().javascriptPage);
  WebElement toMoveTo = webDriver().findElement(By::id("clickField"));

  getBuilder(webDriver()).moveToElement(toMoveTo).build().perform();

  // TODO(andreastt): Is this correct behaviour?  Should the last known mouse position be
  // disregarded if calling click() from a an Actions chain?
  EXPECT_ANY_THROW(getBuilder(webDriver()).click().build().perform()) << "Shouldn't be allowed to click without a context.";
}

//@Ignore(value = {ANDROID, IE, HTMLUNIT, IPHONE, REMOTE, OPERA},
//        reason = "Behaviour not finalized yet regarding linked images.")
//@Test
TEST_F(BasicMouseInterfaceTest, testMovingIntoAnImageEnclosedInALink)
{
/*  assumeFalse(
      "No way to compensate for accessibility-provided offsets on Firefox 3.0 or 3.5",
      isFirefox30(driver) || isFirefox35(driver));
  assumeFalse(isFirefox(driver) && isNativeEventsEnabled(driver));*/

  webDriver().get(pages().linkedImage);

  // Note: For some reason, the Accessibility API in Firefox will not be available before we
  // click on something. As a work-around, click on a different element just to get going.
  webDriver().findElement(By::id("linkToAnchorOnThisPage")).click();

  WebElement linkElement = webDriver().findElement(
      By::id("linkWithEnclosedImage"));

  // Image is 644 x 41 - move towards the end.
  // Note: The width of the link element itself is correct - 644 pixels. However,
  // the height is 17 pixels and the rectangle containing it is *below* the image.
  // For this reason, this action will fail.
  Actions(webDriver())
  .moveToElement(linkElement, 500, 30).click().perform();

  wait().until(TitleIs("We Arrive Here"));
}



//@Ignore(value = {ANDROID, IE, HTMLUNIT, IPHONE, CHROME},
//        reason = "Not implemented yet.")
//@Test
TEST_F(BasicMouseInterfaceTest, testMovingMousePastViewPort)
{
 // assumeTrue (isNativeEventsEnabled(driver));

webDriver  ().get(pages().javascriptPage);

  WebElement keyUpArea = webDriver().findElement(By::id("keyPressArea"));
  Actions(webDriver()).moveToElement(keyUpArea).click().perform();

  ScriptResult keyUpSize = getElementSize(keyUpArea);

  // When moving to an element using the interactions API, the element is not scrolled
  // using scrollElementIntoView so the top of the element may not end at 0.
  // Estimate the mouse position based on the distance of the element from the top plus
  // half its size (the mouse is moved to the middle of the element by default).
  int assumedMouseY = getHeight(keyUpSize) / 2 + getFieldValue(keyUpSize, "top");

  // Calculate the scroll offset by figuring out the distance of the 'parent' element from
  // the top (adding half it's height), then substracting the current mouse position.
  // Regarding width, the event attached to this element will only be triggered if the mouse
  // hovers over the text in this element. Use a simple negative offset for this.
  WebElement parent = webDriver().findElement(By::id("parent"));
  ScriptResult parentSize = getElementSize(parent);

  int verticalMove = getFieldValue(parentSize, "top") + getHeight(parentSize) / 2 -
  assumedMouseY;

  // Move by verticalMove pixels down and -50 pixels left:
  // we should be hitting the element with id 'parent'
  Actions(webDriver()).moveByOffset(-50, verticalMove).perform();

  WebElement resultArea = webDriver().findElement(By::id("result"));
  wait().until(ElementTextToContain(resultArea, "parent matches"));
}

//@Ignore(value = {ANDROID, IE, HTMLUNIT, IPHONE, CHROME, OPERA, OPERA_MOBILE},
//        reason = "Not implemented yet.")
//@Test
TEST_F(BasicMouseInterfaceTest, testMovingMouseBackAndForthPastViewPort)
{
//  assumeTrue(!isFirefox(driver) || isNativeEventsEnabled(driver));

  webDriver().get(pages().veryLargeCanvas);

  WebElement firstTarget = webDriver().findElement(By::id("r1"));
  Actions(webDriver())
  .moveToElement(firstTarget).click().perform();

  WebElement resultArea = webDriver().findElement(By::id("result"));
  std::string expectedEvents = "First";
  wait().until(ElementTextToBeEqual(resultArea, expectedEvents));

  // Move to element with id 'r2', at (2500, 50) to (2580, 100)
  Actions(webDriver())
  .moveByOffset(2540 - 150, 75 - 125).click().perform();
  expectedEvents += " Second";
  wait().until(ElementTextToBeEqual(resultArea, expectedEvents));

  // Move to element with id 'r3' at (60, 1500) to (140, 1550)
  Actions(webDriver())
  .moveByOffset(100 - 2540, 1525 - 75).click().perform();
  expectedEvents += " Third";
  wait().until(ElementTextToBeEqual(resultArea, expectedEvents));

  // Move to element with id 'r4' at (220,180) to (320, 230)
  Actions(webDriver())
  .moveByOffset(270 - 100, 205 - 1525).click().perform();
  expectedEvents += " Fourth";
  wait().until(ElementTextToBeEqual(resultArea, expectedEvents));
}

//@Ignore({ANDROID, IPHONE, OPERA, OPERA_MOBILE})
//@Test
TEST_F(BasicMouseInterfaceTest, testShouldClickElementInIFrame)
{
  webDriver().get(pages().clicksPage);
  {
    FinalAction([]()
    { webDriver().switchTo().defaultContent();});
    webDriver().switchTo().frame("source");
    WebElement element = webDriver().findElement(By::id("otherframe"));
    Actions(webDriver()).moveToElement(element).click().perform();
    webDriver().switchTo().defaultContent().frame("target");
    wait().until(ElementTextToBeEqualLocated(By::id("span"), "An inline element"));
  }
}

//@JavascriptEnabled
//@Ignore(
// value =
// {HTMLUNIT, IPHONE, OPERA, SAFARI, MARIONETTE},
//    reason = "HtmlUnit: Advanced mouse actions only implemented in rendered browsers.",
//    issues = {4136})
//@Test
TEST_F(BasicMouseInterfaceTest, testShouldAllowUsersToHoverOverElements)
{
  webDriver().get(pages().javascriptPage);

  WebElement element = webDriver().findElement(By::id("menu1"));

  WebElement item = webDriver().findElement(By::id("item1"));
  ASSERT_THAT(item.text(), Eq(""));

  webDriver().executeScript(
      "arguments[0].style.background = 'green'", {element});
  Actions(webDriver())
  .moveToElement(element).build().perform();

  wait().until(::selenium::Not<ElementTextToBeEqual> (ElementTextToBeEqual(item, "")));
  ASSERT_THAT(item.text(), Eq("Item 1"));
}

//@JavascriptEnabled
//@Ignore(
//value =
//{HTMLUNIT, IPHONE, OPERA, SAFARI, MARIONETTE},
//    reason = "HtmlUnit: Advanced mouse actions only implemented in rendered browsers",
//    issues = {4136})
//@Test
TEST_F(BasicMouseInterfaceTest, testHoverPersists)
{
// This test passes on IE. When running in Firefox on Windows, the test
// will fail if the mouse cursor is not in the window. Solution: Maximize.
/*  if ((TestUtilities.getEffectivePlatform().is(Platform.WINDOWS)) &&
      TestUtilities.isFirefox(driver)
      && TestUtilities.isNativeEventsEnabled(driver))*/
  {
    webDriver().maximizeWindow();
  }

  webDriver().get(pages().javascriptPage);
// Move to a different element to make sure the mouse is not over the
// element with id 'item1' (from a previous test).
  Actions(webDriver())
  .moveToElement(webDriver().findElement(By::id("dynamo"))).build().perform();

  WebElement element = webDriver().findElement(By::id("menu1"));

  WebElement
  item = webDriver().findElement(By::id("item1"));
  ASSERT_THAT(item.text(), Eq(""));

  webDriver().executeScript("arguments[0].style.background = 'green'", {element});
  Actions(webDriver())
  .moveToElement(element).build().perform();

// Intentionally wait to make sure hover persists.
  std::this_thread::sleep_for(std::chrono::seconds(2));

  wait().until(selenium::Not<ElementTextToBeEqual> (ElementTextToBeEqual(item, "")));

  ASSERT_THAT(item.text(), Eq("Item 1"));
}

//@JavascriptEnabled
//@Ignore(
//value =
//{HTMLUNIT, IPHONE, OPERA, FIREFOX},
//    reason = "This is an IE only tests")
//@NoDriverAfterTest
//@NeedsLocalEnvironment
//@Test
/*TEST_F(BasicMouseInterfaceTest, testPersistentHoverCanBeTurnedOff)
{
  assumeTrue(TestUtilities.isInternetExplorer(driver));
// Destroy the previous driver to make sure the hovering thread is
// stopped.
  webDriver().quit();

  DesiredCapabilities caps = new DesiredCapabilities();
  caps.setCapability(ENABLE_PERSISTENT_HOVERING, false);
  WebDriverBuilder builder = new WebDriverBuilder()
  .setDesiredCapabilities(caps);
  driver = builder.get();

try
{
  webDriver().get(pages().javascriptPage);
  // Move to a different element to make sure the mouse is not over the
  // element with id 'item1' (from a previous test).
  Actions(webDriver()).moveToElement(webDriver().findElement(By::id("keyUp"))).build().perform();
  WebElement element = webDriver().findElement(By::id("menu1"));

  final WebElement item = webDriver().findElement(By::id("item1"));
  assertEquals("", item.text());

  webDriver().executeScript("arguments[0].style.background = 'green'", element);
  Actions(webDriver()).moveToElement(element).build().perform();

  // Move the mouse somewhere - to make sure that the thread firing the events making
  // hover persistent is not active.
  Robot robot = new Robot();
  robot.mouseMove(50, 50);

  // Intentionally wait to make sure hover DOES NOT persist.
  Thread.sleep(1000);

  wait().until(elementTextToEqual(item, ""));

  assertEquals("", item.text());

}finally
{
  webDriver().quit();
}
}*/

/*
//@JavascriptEnabled
//@Ignore(value = {HTMLUNIT, OPERA, SAFARI, MARIONETTE},
//        reason = "Advanced mouse actions only implemented in rendered browsers",
//        issues = {4136})
//@Test
TEST_F(BasicMouseInterfaceTest, testMovingMouseByRelativeOffset)
{
webDriver().get(pages().mouseTrackerPage);

WebElement trackerDiv = webDriver().findElement(By::id("mousetracker"));
Actions(webDriver())
.moveToElement(trackerDiv).build().perform();

WebElement reporter = webDriver().findElement(By::id("status"));

wait().until(fuzzyMatchingOfCoordinates(reporter, 50, 200));

Actions(webDriver())
.moveByOffset(10, 20).build().perform();

wait().until(fuzzyMatchingOfCoordinates(reporter, 60, 220));
}

//@JavascriptEnabled
//@Ignore(value = {HTMLUNIT, SAFARI, MARIONETTE},
//        reason = "Advanced mouse actions only implemented in rendered browsers",
//        issues = {4136})
//@Test
TEST_F(BasicMouseInterfaceTest, testMovingMouseToRelativeElementOffset)
{
webDriver().get(pages().mouseTrackerPage);

WebElement trackerDiv = webDriver().findElement(By::id("mousetracker"));
Actions(webDriver())
.moveToElement(trackerDiv, 95, 195).build()
.perform();

WebElement reporter = webDriver().findElement(By::id("status"));

wait().until(fuzzyMatchingOfCoordinates(reporter, 95, 195));
}

//@JavascriptEnabled
//@Ignore(value = {HTMLUNIT, SAFARI, MARIONETTE},
//        reason = "Advanced mouse actions only implemented in rendered browsers",
//        issues = {4136})
//@Test
TEST_F(BasicMouseInterfaceTest, testMovingMouseToRelativeZeroElementOffset)
{
webDriver().get(pages().mouseTrackerPage);

WebElement trackerDiv = webDriver().findElement(By::id("mousetracker"));
Actions(webDriver())
.moveToElement(trackerDiv, 0, 0).build()
.perform();

WebElement reporter = webDriver().findElement(By::id("status"));

wait().until(fuzzyMatchingOfCoordinates(reporter, 0, 0));
}

//@JavascriptEnabled
//@NeedsFreshDriver
//@Ignore(value = {HTMLUNIT, OPERA, SAFARI, MARIONETTE},
//        reason = "Advanced mouse actions only implemented in rendered browsers",
//        issues = {4136})
//@Test
TEST_F(BasicMouseInterfaceTest, testMoveRelativeToBody)
{
try
{
webDriver().get(pages().mouseTrackerPage);

Actions(webDriver()).moveByOffset(50, 100).build().perform();

WebElement reporter = webDriver().findElement(By::id("status"));

wait().until(fuzzyMatchingOfCoordinates(reporter, 40, 20));
}finally
{
Actions(webDriver()).moveByOffset(-50, -100).build().perform();
}
}

//@JavascriptEnabled
//@Test
//@Ignore(value = {HTMLUNIT, OPERA, SAFARI, MARIONETTE},
//        reason = "Advanced mouse actions only implemented in rendered browsers",
//        issues = {4136})
//@NoDriverAfterTest
TEST_F(BasicMouseInterfaceTest, canMouseOverAndOutOfAnElement)
{
webDriver().get(pages().mouseOverPage);

WebElement greenbox = webDriver().findElement(By::id("greenbox"));
WebElement redbox = webDriver().findElement(By::id("redbox"));
Dimension size = redbox.getSize();

Actions(webDriver())
.moveToElement(greenbox, 1, 1).perform();

assertEquals(
  Colors.GREEN.getColorValue(),
  Color.fromString(redbox.getCssValue("background-color")));

Actions(webDriver())
.moveToElement(redbox).perform();
assertEquals(
  Colors.RED.getColorValue(),
  Color.fromString(redbox.getCssValue("background-color")));

    // IE8 (and *only* IE8) requires a move of 2 pixels. All other browsers
    // would be happy with 1.
Actions(webDriver())
.moveToElement(redbox, size.getWidth() + 2, size.getHeight() + 2)
.perform();
assertEquals(
  Colors.GREEN.getColorValue(),
  Color.fromString(redbox.getCssValue("background-color")));
}

private boolean fuzzyPositionMatching(int expectedX, int expectedY, std::string locationTouple)
{
std::string[] splitString = locationTouple.split(",");
int gotX = Integer.parseInt(splitString[0].trim());
int gotY = Integer.parseInt(splitString[1].trim());

  // Everything within 5 pixels range is OK
final int ALLOWED_DEVIATION = 5;
return Math.abs(expectedX - gotX) < ALLOWED_DEVIATION &&
Math.abs(expectedY - gotY) < ALLOWED_DEVIATION;

}

private ExpectedCondition<Boolean> fuzzyMatchingOfCoordinates(
final WebElement element, final int x, final int y)
{
return new ExpectedCondition<Boolean>()
{
@Override
public Boolean apply(WebDriver ignored)
{
  return fuzzyPositionMatching(x, y, element.text());
}

@Override
public std::string toString()
{
  return "Coordinates: " + element.text() + " but expected: " +
  x + ", " + y;
}
};
}
*/
