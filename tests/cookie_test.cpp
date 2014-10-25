/*
 * cookie_test.cpp
 *
 *  Created on: Sep 20, 2014
 *      Author: speedpat
 */

#include <list>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "selenium/selenium.hpp"


using namespace selenium;
using namespace testing;

class CookieTest : public Test
{
public:
  Cookie::TimePoint someTimeInTheFuture() {
    //return std::chrono::system_clock::time_point();

    std::chrono::system_clock::time_point tp = std::chrono::system_clock::now() + std::chrono::seconds(10000);
    std::chrono::seconds secs = std::chrono::duration_cast<std::chrono::seconds>(tp.time_since_epoch());
    return Cookie::TimePoint(secs);
  }
};

TEST_F(CookieTest, testEmptyGetters)
{
  Cookie cookie;
  EXPECT_THAT(cookie.getDomain(), Eq(""));
  EXPECT_THAT(cookie.getPath(), Eq(""));
  EXPECT_THAT(cookie.getName(), Eq(""));
  EXPECT_THAT(cookie.getValue(), Eq(""));
  EXPECT_THAT(cookie.isSecure(), Eq(false));
  EXPECT_THAT(cookie.httpOnly(), Eq(false));
  EXPECT_THAT(cookie.getExpiry(), Eq(Cookie::TimePoint()));
  EXPECT_THAT(cookie.empty(), Eq(true));

}

TEST_F(CookieTest, testSetters)
{
  Cookie cookie;
  EXPECT_THAT(cookie.isSecure(), Eq(false));
  cookie.secure(true);
  EXPECT_THAT(cookie.isSecure(), Eq(true));
  cookie.secure(false);
  EXPECT_THAT(cookie.isSecure(), Eq(false));

  EXPECT_THAT(cookie.httpOnly(), Eq(false));
  cookie.httpOnly(true);
  EXPECT_THAT(cookie.httpOnly(), Eq(true));
  cookie.httpOnly(false);
  EXPECT_THAT(cookie.httpOnly(), Eq(false));

  EXPECT_THAT(cookie.getDomain(), Eq(""));
  cookie.setDomain(".domain");
  EXPECT_THAT(cookie.getDomain(), Eq(".domain"));
  cookie.setDomain("");
  EXPECT_THAT(cookie.getDomain(), Eq(""));

  EXPECT_THAT(cookie.getPath(), Eq(""));
  cookie.setPath("path");
  EXPECT_THAT(cookie.getPath(), Eq("path"));
  cookie.setPath("");
  EXPECT_THAT(cookie.getPath(), Eq("/"));

  EXPECT_THAT(cookie.getName(), Eq(""));
  cookie.setName("name");
  EXPECT_THAT(cookie.getName(), Eq("name"));
  cookie.setName("");
  EXPECT_THAT(cookie.getName(), Eq(""));

  EXPECT_THAT(cookie.getValue(), Eq(""));
  cookie.setValue("value");
  EXPECT_THAT(cookie.getValue(), Eq("value"));
  cookie.setValue("");
  EXPECT_THAT(cookie.getValue(), Eq(""));

  EXPECT_THAT(cookie.getExpiry(), Eq(Cookie::TimePoint()));
  Cookie::TimePoint expiry = someTimeInTheFuture();
  cookie.setExpiry(expiry);
  EXPECT_THAT(cookie.getExpiry(), Eq(expiry));
  cookie.setExpiry(Cookie::TimePoint());
  EXPECT_THAT(cookie.getExpiry(), Eq(Cookie::TimePoint()));
}

TEST_F(CookieTest, testConstructors)
{
  Cookie cookie = Cookie("key", "value");
  EXPECT_THAT(cookie.getName(), Eq("key"));
  EXPECT_THAT(cookie.getValue(), Eq("value"));
  EXPECT_THAT(cookie.getDomain(), Eq(""));
  EXPECT_THAT(cookie.getPath(), Eq("/"));
  EXPECT_THAT(cookie.isSecure(), Eq(false));
  EXPECT_THAT(cookie.httpOnly(), Eq(false));
  EXPECT_THAT(cookie.getExpiry(), Eq(Cookie::TimePoint()));


  cookie = Cookie("key", "value", "path");
  EXPECT_THAT(cookie.getName(), Eq("key"));
  EXPECT_THAT(cookie.getValue(), Eq("value"));
  EXPECT_THAT(cookie.getPath(), Eq("/path"));
  EXPECT_THAT(cookie.getDomain(), Eq(""));
  EXPECT_THAT(cookie.isSecure(), Eq(false));
  EXPECT_THAT(cookie.httpOnly(), Eq(false));
  EXPECT_THAT(cookie.getExpiry(), Eq(Cookie::TimePoint()));

  cookie = Cookie("key", "value", "path", Cookie::TimePoint(std::chrono::seconds(10)));
  EXPECT_THAT(cookie.getName(), Eq("key"));
  EXPECT_THAT(cookie.getValue(), Eq("value"));
  EXPECT_THAT(cookie.getPath(), Eq("/path"));
  EXPECT_THAT(cookie.getExpiry(), Eq(Cookie::TimePoint(std::chrono::seconds(10))));
  EXPECT_THAT(cookie.getDomain(), Eq(""));
  EXPECT_THAT(cookie.isSecure(), Eq(false));
  EXPECT_THAT(cookie.httpOnly(), Eq(false));


  cookie = Cookie("key", "value", "path", Cookie::TimePoint(std::chrono::seconds(10)));
  EXPECT_THAT(cookie.getName(), Eq("key"));
  EXPECT_THAT(cookie.getValue(), Eq("value"));
  EXPECT_THAT(cookie.getPath(), Eq("/path"));
  EXPECT_THAT(cookie.getExpiry(), Eq(Cookie::TimePoint(std::chrono::seconds(10))));
  EXPECT_THAT(cookie.getDomain(), Eq(""));
  EXPECT_THAT(cookie.isSecure(), Eq(false));
  EXPECT_THAT(cookie.httpOnly(), Eq(false));


  cookie = Cookie("key", "value", "domain", "path", Cookie::TimePoint(std::chrono::seconds(42)));
  EXPECT_THAT(cookie.getName(), Eq("key"));
  EXPECT_THAT(cookie.getValue(), Eq("value"));
  EXPECT_THAT(cookie.getDomain(), Eq("domain"));
  EXPECT_THAT(cookie.getPath(), Eq("/path"));
  EXPECT_THAT(cookie.getExpiry(), Eq(Cookie::TimePoint(std::chrono::seconds(42))));
  EXPECT_THAT(cookie.isSecure(), Eq(false));
  EXPECT_THAT(cookie.httpOnly(), Eq(false));




}
