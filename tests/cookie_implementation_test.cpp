/*
 * alerts_test.cpp
 *
 *  Created on: Sep 20, 2014
 *      Author: speedpat
 */

#include <list>

#include "selenium/selenium.hpp"
#include "support/selenium_testcase.hpp"
#include "support/expected_test_conditions.hpp"

using namespace selenium;

class CookieImplementationTest : public SeleniumTestCase
{
public:

  virtual void SetUp()
  {
    SeleniumTestCase::SetUp();
    cookiePage = whereIs("cookie");
    deleteAllCookiesOnServerSide();
    webDriver().deleteAllCookies();
    assertNoCookiesArePresent();

  }

  virtual void TearDown()
  {
    SeleniumTestCase::TearDown();
  }

  void openAnotherPage()
  {
    webDriver().get(whereIs("simpleTest.html"));
  }

  void deleteAllCookiesOnServerSide()
  {
    webDriver().get(cookiePage + "?action=deleteAll");
  }

  void assertNoCookiesArePresent()
  {
    Cookies cookies = webDriver().getCookies();
    EXPECT_TRUE(cookies.empty()) << "Cookies were not empty, present: "
        << cookies.size();
    ::boost::optional<std::string> documentCookie = getDocumentCookieOrNull();
    if (documentCookie.is_initialized() && !documentCookie->empty())
    {
      FAIL()<< "Cookies were not empty " << documentCookie.get();
    }
  }

  void assertCookieIsNotPresentWithName(std::string key)
  {
    Cookie cookie = webDriver().getCookie(key);
    EXPECT_TRUE(cookie.empty()) << "Cookie was present with name " << key;
    ::boost::optional<std::string> documentCookie = getDocumentCookieOrNull();
    if (documentCookie && !documentCookie->empty())
    {
      EXPECT_TRUE(documentCookie->find(key + "=") == std::string::npos) << "Cookie was present with name " << key;
    }
  }

  class UnsupportedOperationException
  {

  };

  ::boost::optional<std::string> getDocumentCookieOrNull()
  {
    try
    {
      return ::boost::optional<std::string>(webDriver().executeScript("return document.cookie"));
    }
    catch (UnsupportedOperationException& e)
    {
      return ::boost::optional<std::string>(::boost::none);
    }
  }

  void assertSomeCookiesArePresent()
  {
    EXPECT_FALSE(webDriver().getCookies().empty()) << "Cookies were empty";
    ::boost::optional<std::string> documentCookie = getDocumentCookieOrNull();
    if (documentCookie && !documentCookie->empty())
    {
      EXPECT_STRNE("", documentCookie.get().data()) << "Cookies were empty";
    }
  }

  std::string generateUniqueKey()
  {
    char buffer[32];
    std::snprintf(buffer, sizeof(buffer)/sizeof(char), "key_%d", std::rand());
    return buffer;
  }

  void addCookieOnServerSide(Cookie cookie)
  {
    std::string url = cookiePage;
    url.append("?action=add");
    url.append("&name=").append(cookie["name"]);
    url.append("&value=").append(cookie["value"]);
    if (cookie.find("domain")!= cookie.end())
    {
      url.append("&domain=").append(cookie["domain"]);
    }
    if (cookie.find("path") != cookie.end())
    {
      url.append("&path=").append(cookie["path"]);
    }
    if (cookie.find("expiry") != cookie.end())
    {
      url.append("&expiry=").append(cookie["expiry"]);
    }
    if (cookie.find("secure") != cookie.end())
    {
      url.append("&secure=").append(cookie["secure"]);
    }
    if (cookie.find("httpOnly") != cookie.end())
    {
      url.append("&httpOnly=").append(cookie["httpOnly"]);
    }
    webDriver().get(url);
  }

  void assertCookieHasValue(std::string key, std::string value)
  {
    Cookie cookie = webDriver().getCookie(key);
    EXPECT_STREQ(
        value.data(),
        cookie.getValue().data()) << "Cookie had wrong value";
    ::boost::optional<std::string> documentCookie = getDocumentCookieOrNull();
    if (documentCookie && !documentCookie->empty())
    {
      EXPECT_TRUE(
          documentCookie->find(key + "=" + value) != std::string::npos) << "Cookie was present with name " + key;
    }
  }

  void assertCookieIsPresentWithName(std::string key)
  {
    EXPECT_TRUE(webDriver().getCookie(key).empty()) << "Cookie was not present with name " + key;
    ::boost::optional<std::string> documentCookie = getDocumentCookieOrNull();
    if (documentCookie && !documentCookie->empty())
    {
      EXPECT_TRUE(documentCookie->find(key + "=") != std::string::npos) << "Cookie was not present with name " << key << ", got: " << documentCookie;
    }
  }

  bool findCookie(Cookies& cookies, Cookie& cookie)
  {
    return std::find_if(cookies.begin(), cookies.end(), [&cookie](const Cookie& elem)
        {
          return elem.getName() == cookie.getName();
        })
      != cookies.end();
  }

  std::chrono::system_clock::time_point someTimeInTheFuture() {
    return std::chrono::system_clock::now() + std::chrono::seconds(100000);
  }

  std::string cookiePage;

};

TEST_F(CookieImplementationTest, testShouldGetCookieByName)
{
  std::string key = generateUniqueKey();
  std::string value = "set";
  assertCookieIsNotPresentWithName(key);

  addCookieOnServerSide(Cookie(key, value));

  Cookie cookie = webDriver().getCookie(key);
  EXPECT_STREQ(value.data(), cookie.getValue().data());
}

TEST_F(CookieImplementationTest, testShouldBeAbleToAddCookie)
{
  std::string key = generateUniqueKey();
  std::string value = "foo";
  Cookie cookie = Cookie(key, value);
  cookie.setDomain("testhost.test.ch");
  assertCookieIsNotPresentWithName(key);

  webDriver().addCookie(cookie);

  assertCookieHasValue(key, value);

  webDriver().getCookies();

  openAnotherPage();
  assertCookieHasValue(key, value);
}

TEST_F(CookieImplementationTest, testGetAllCookies)
{
  std::string key1 = generateUniqueKey();
  std::string key2 = generateUniqueKey();

  assertCookieIsNotPresentWithName(key1);
  assertCookieIsNotPresentWithName(key2);

  Cookies cookies = webDriver().getCookies();
  int countBefore = cookies.size();

  Cookie one = Cookie(key1, "value");
  Cookie two = Cookie(key2, "value");

  webDriver().addCookie(one);
  webDriver().addCookie(two);

  openAnotherPage();
  cookies = webDriver().getCookies();
  EXPECT_EQ(countBefore + 2, cookies.size());

  EXPECT_TRUE(findCookie(cookies, one));
  EXPECT_TRUE(findCookie(cookies, two));
}

TEST_F(CookieImplementationTest, testDeleteAllCookies)
{
  addCookieOnServerSide(Cookie("foo", "set"));
  assertSomeCookiesArePresent();

  webDriver().deleteAllCookies();

  assertNoCookiesArePresent();

  openAnotherPage();
  assertNoCookiesArePresent();
}

TEST_F(CookieImplementationTest, testDeleteCookieWithName)
{
  std::string key1 = generateUniqueKey();
  std::string key2 = generateUniqueKey();

  addCookieOnServerSide(Cookie(key1, "set"));
  addCookieOnServerSide(Cookie(key2, "set"));

  assertCookieIsPresentWithName(key1);
  assertCookieIsPresentWithName(key2);

  webDriver().deleteCookie(key1);

  assertCookieIsNotPresentWithName(key1);
  assertCookieIsPresentWithName(key2);

  openAnotherPage();
  assertCookieIsNotPresentWithName(key1);
  assertCookieIsPresentWithName(key2);
}

TEST_F(CookieImplementationTest, testShouldNotDeleteCookiesWithASimilarName)
{
  std::string cookieOneName = "fish";
  Cookie cookie1 = Cookie(cookieOneName, "cod");
  Cookie cookie2 = Cookie(cookieOneName + "x", "earth");
  assertCookieIsNotPresentWithName(cookie1.getName());

  webDriver().addCookie(cookie1);
  webDriver().addCookie(cookie2);

  assertCookieIsPresentWithName(cookie1.getName());

  webDriver().deleteCookie(cookieOneName);
  Cookies cookies = webDriver().getCookies();

  EXPECT_TRUE(findCookie(cookies, cookie2));
  EXPECT_FALSE(findCookie(cookies, cookie1));
}

TEST_F(CookieImplementationTest, testAddCookiesWithDifferentPathsThatAreRelatedToOurs)
{
  webDriver().get(whereIs("/common/animals"));
  Cookie cookie1 = Cookie("fish", "cod", "/common/animals");
  Cookie cookie2 = Cookie("planet", "earth", "/common/");
  webDriver().addCookie(cookie1);
  webDriver().addCookie(cookie2);

  webDriver().get(whereIs("/common/animals"));

  assertCookieIsPresentWithName(cookie1.getName());
  assertCookieIsPresentWithName(cookie2.getName());

  webDriver().get(whereIs("/common/simplePage.html"));
  assertCookieIsNotPresentWithName(cookie1.getName());
}

TEST_F(CookieImplementationTest, testGetCookiesInAFrame)
{
  webDriver().get(whereIs("/common/animals"));
  Cookie cookie1 = Cookie("fish", "cod", "/common/animals");
  webDriver().addCookie(cookie1);

  webDriver().get(whereIs("frameWithAnimals.html"));
  assertCookieIsNotPresentWithName(cookie1.getName());

  webDriver().switchTo().frame("iframe1");
  assertCookieIsPresentWithName(cookie1.getName());
}

TEST_F(CookieImplementationTest, testCannotGetCookiesWithPathDifferingOnlyInCase)
{
  std::string cookieName = "fish";
  Cookie cookie = Cookie(cookieName, "cod", "/Common/animals");
  webDriver().addCookie(cookie);

  webDriver().get(whereIs("/common/animals"));
  EXPECT_TRUE(webDriver().getCookie(cookieName).empty());
}

/*TEST_F(CookieImplementationTest, testShouldNotGetCookieOnDifferentDomain) {

 std::string cookieName = "fish";
 webDriver().addCookie(Cookie.Builder(cookieName, "cod").build());
 assertCookieIsPresentWithName(cookieName);

 webDriver().get(domainHelper.getUrlForSecondValidHostname("simpleTest.html"));

 assertCookieIsNotPresentWithName(cookieName);
 }*/

/*TEST_F(CookieImplementationTest, testShouldBeAbleToAddToADomainWhichIsRelatedToTheCurrentDomain) {
 std::string cookieName = "name";
 assertCookieIsNotPresentWithName(cookieName);

 std::string shorter = domainHelper.getHostName().replaceFirst(".*?\\.", ".");
 Cookie cookie = Cookie.Builder(cookieName, "value").domain(shorter).build();
 webDriver().addCookie(cookie);

 assertCookieIsPresentWithName(cookieName);
 }*/

/*
 TEST_F(CookieImplementationTest, testsShouldNotGetCookiesRelatedToCurrentDomainWithoutLeadingPeriod) {
 std::string cookieName = "name";
 assertCookieIsNotPresentWithName(cookieName);

 std::string shorter = domainHelper.getHostName().replaceFirst(".*?\\.", "");
 Cookie cookie = Cookie.Builder(cookieName, "value").domain(shorter).build();
 webDriver().addCookie(cookie);
 assertCookieIsNotPresentWithName(cookieName);
 }*/

/*
 TEST_F(CookieImplementationTest, testShouldBeAbleToIncludeLeadingPeriodInDomainName){
 std::string cookieName = "name";
 assertCookieIsNotPresentWithName(cookieName);

 std::string shorter = domainHelper.getHostName().replaceFirst(".*?\\.", ".");
 Cookie cookie = Cookie.Builder("name", "value").domain(shorter).build();

 webDriver().addCookie(cookie);

 assertCookieIsPresentWithName(cookieName);
 }
 */

/*TEST_F(CookieImplementationTest, testShouldBeAbleToSetDomainToTheCurrentDomain) {
 URI url = new URI(webDriver().getCurrentUrl());
 std::string host = url.getHost() + ":" + url.getPort();

 Cookie cookie = Cookie.Builder("fish", "cod").domain(host).build();
 webDriver().addCookie(cookie);

 webDriver().get(whereIs("javascriptPage.html"));
 Set<Cookie> cookies = webDriver().getCookies();
 assertTrue(cookies.contains(cookie));
 }*/

TEST_F(CookieImplementationTest, testShouldWalkThePathToDeleteACookie)
{
  Cookie cookie1 = Cookie(
  "fish", "cod"
  );
  webDriver().addCookie(cookie1);

  webDriver().get(whereIs("child/childPage.html"));
  Cookie cookie2 = Cookie("rodent", "hamster", "/common/child");
  webDriver().addCookie(cookie2);

  webDriver().get(whereIs("child/grandchild/grandchildPage.html"));
  Cookie cookie3 = Cookie("dog", "dalmation", "/common/child/grandchild/");
  webDriver().addCookie(cookie3);

  webDriver().get(whereIs("child/grandchild/grandchildPage.html"));
  webDriver().deleteCookie("rodent");

  EXPECT_TRUE(webDriver().getCookie("rodent").empty());

  Cookies cookies = webDriver().getCookies();
  EXPECT_EQ(2, cookies.size());
  EXPECT_TRUE(findCookie(cookies, cookie1));
  EXPECT_TRUE(findCookie(cookies, cookie3));

  webDriver().deleteAllCookies();
  webDriver().get(whereIs("child/grandchild/grandchildPage.html"));
  assertNoCookiesArePresent();
}
/*
TEST_F(CookieImplementationTest, testShouldIgnoreThePortNumberOfTheHostWhenSettingTheCookie)
{
  std::string uri = new URI(webDriver().currentUrl());
  std::string host = std::string.format("%s:%d", uri.getHost(), uri.getPort());

  std::string cookieName = "name";
  assertCookieIsNotPresentWithName(cookieName);

  Cookie cookie = Cookie.Builder(cookieName, "value").domain(host).build();
  webDriver().addCookie(cookie);

  assertCookieIsPresentWithName(cookieName);
}*/

/*TEST_F(CookieImplementationTest, testCookieEqualityAfterSetAndGet)
{
  webDriver().get(whereIs("animals"));

  webDriver().deleteAllCookies();

  Cookie addedCookie =
      Cookie.Builder("fish", "cod")
          .path("/common/animals")
          .expiresOn(someTimeInTheFuture())
          .build();
  webDriver().addCookie(addedCookie);

  Set<Cookie> cookies = webDriver().getCookies();
  Cookie retrievedCookie = null;
  for (Cookie temp : cookies)
  {
    if (addedCookie.equals(temp))
    {
      retrievedCookie = temp;
      break;
    }
  }

  assertNotNull("Cookie was null", retrievedCookie);
  // Cookie.equals only compares name, domain and path
  assertEquals(addedCookie, retrievedCookie);
}*/

TEST_F(CookieImplementationTest, testRetainsCookieExpiry)
{
  Cookie addedCookie =
      Cookie("fish", "cod", "/common/animals", someTimeInTheFuture());
  webDriver().addCookie(addedCookie);

  Cookie retrieved = webDriver().getCookie("fish");
  EXPECT_FALSE(retrieved.empty());
  EXPECT_EQ(addedCookie.getExpiry(), retrieved.getExpiry());
}

/*TEST_F(CookieImplementationTest, testRetainsCookieSecure)
{
  webDriver().get(domainHelper.getSecureUrlForFirstValidHostname("animals"));

  Cookie addedCookie =
      Cookie.Builder("fish", "cod")
          .path("/common/animals")
          .isSecure(true)
          .build();
  webDriver().addCookie(addedCookie);

  webDriver().navigate().refresh();

  Cookie retrieved = webDriver().getCookieNamed("fish");
  assertNotNull(retrieved);
  assertTrue(retrieved.isSecure());
}*/
/*
TEST_F(CookieImplementationTest, testRetainsHttpOnlyFlag)
{
  Cookie addedCookie =
      Cookie.Builder("fish", "cod")
          .path("/common/animals")
          .isHttpOnly(true)
          .build();

  addCookieOnServerSide(addedCookie);

  Cookie retrieved = webDriver().getCookieNamed("fish");
  assertNotNull(retrieved);
  assertTrue(retrieved.isHttpOnly());
}*/

/*TEST_F(CookieImplementationTest, testSettingACookieThatExpiredInThePast)
{
  long expires = System.currentTimeMillis() - 1000;
  Cookie cookie =
      Cookie.Builder("expired", "yes").expiresOn(new Date(expires)).build();
  webDriver().addCookie(cookie);

  cookie = webDriver().getCookieNamed("fish");
  assertNull(
      "Cookie expired before it was set, so nothing should be returned: "
          + cookie, cookie);
}*/

TEST_F(CookieImplementationTest, testCanSetCookieWithoutOptionalFieldsSet)
{
  std::string key = generateUniqueKey();
  std::string value = "foo";
  Cookie cookie = Cookie(key, value);
  assertCookieIsNotPresentWithName(key);

  webDriver().addCookie(cookie);

  assertCookieHasValue(key, value);
}

TEST_F(CookieImplementationTest, testDeleteNotExistedCookie)
{
  std::string key = generateUniqueKey();
  assertCookieIsNotPresentWithName(key);

  webDriver().deleteCookie(key);
}
/*
TEST_F(CookieImplementationTest, testShouldDeleteOneOfTheCookiesWithTheSameName)
{
  webDriver().get(whereIs("/common/animals"));
  Cookie cookie1 = Cookie.Builder("fish", "cod")
      .domain(domainHelper.getHostName()).path("/common/animals").build();
  Cookie cookie2 = Cookie.Builder("fish", "tune")
      .domain(domainHelper.getHostName()).path("/common/").build();
  WebDriver.Options
  options = webDriver().manage();
  webDriver().addCookie(cookie1);
  webDriver().addCookie(cookie2);
  assertEquals(webDriver().getCookies().size(), 2);

  webDriver().deleteCookie(cookie1);

  assertEquals(webDriver().getCookies().size(), 1);
  Cookie retrieved = webDriver().getCookieNamed("fish");
  assertNotNull("Cookie was null", retrieved);
  assertEquals(cookie2, retrieved);
}*/

