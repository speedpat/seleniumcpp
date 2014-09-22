/*
 * test_environment.cpp
 *
 *  Created on: Sep 18, 2014
 *      Author: speedpat
 */

#include <iostream>

#include "test_environment.hpp"
#include "in_process_web_server.hpp"
#include "pages.hpp"

namespace selenium
{

TestEnvironment* TestEnvironment::s_testEnvironment = new TestEnvironment();

TestEnvironment::TestEnvironment()
 : m_webserver(nullptr), m_driver(-1), m_pages(nullptr)
{

}

TestEnvironment::~TestEnvironment()
{
  delete m_webserver;
  m_webserver = nullptr;
  delete m_pages;
}

void TestEnvironment::SetUp()
{
  std::cout << "TestEnvironment::SetUp" << std::endl;
  m_webserver = new InProcessWebServer(8686, "/home/speedpat/development/selenium/common/src/web/");
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  EXPECT_TRUE(m_webserver->isRunning());

  ::boost::process::context ctx;
  ctx.stdout_behavior = ::boost::process::inherit_stream();
  ctx.stderr_behavior = ::boost::process::inherit_stream();
  ctx.environment = ::boost::process::self::get_environment();

  m_pages = new Pages(*m_webserver);

  std::string command = "/home/speedpat/tools/chromedriver/chromedriver";
  std::vector<std::string> args({command});
  m_driver = ::boost::process::launch(command, args, ctx);
  std::cout << "chromedriver started, pid: " << m_driver.get_id() << std::endl;
  m_driverUrl = "http://localhost:9515";

  std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

void TestEnvironment::TearDown()
{
  std::cout << "TestEnvironment::TearDown" << std::endl;
  m_driver.terminate();
  m_webserver->stop();
  delete m_webserver;
  m_webserver = nullptr;

}

Pages& TestEnvironment::pages()
{
  return *m_pages;
}

std::string& TestEnvironment::driverUrl()
{
  return m_driverUrl;
}

std::string TestEnvironment::whereIs(const std::string& page)
{
  return m_webserver->whereIs(page);
}

} /* namespace selenium */
