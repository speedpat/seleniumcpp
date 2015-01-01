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

#include "test_environment.hpp"
#include "in_process_web_server.hpp"
#include "pages.hpp"
#include "log.hpp"

namespace selenium
{

TestEnvironment* TestEnvironment::s_testEnvironment = new TestEnvironment();

TestEnvironment::TestEnvironment()
 : m_driver(-1), m_pages(nullptr)
{

}

TestEnvironment::~TestEnvironment()
{
	delete m_pages;
	m_pages = nullptr;
}

void TestEnvironment::SetUp()
{
	LOG("TestEnvironment::SetUp");

	std::string url;
	char* baseUrl = std::getenv("SELENIUMCPP_BASE_URL");
	if (!baseUrl) {
		url = "http://testhost.test.ch:8787/common";
	} else {
		url = baseUrl;
	}

	m_pages = new Pages(url);

	char* driverUrl = std::getenv("SELENIUMCPP_DRIVER_URL");
	if (!driverUrl) {

		std::string chromedriverPath;
		char* path = std::getenv("SELENIUMCPP_CHROMEDRIVER_PATH");
		if (!path) {
			chromedriverPath = "chromedriver";
		} else {
			chromedriverPath = path;
		}

		::boost::process::context ctx;
		ctx.stdout_behavior = ::boost::process::inherit_stream();
		ctx.stderr_behavior = ::boost::process::inherit_stream();
		ctx.environment = ::boost::process::self::get_environment();

		std::vector<std::string> args( { chromedriverPath });
		std::string exec = ::boost::process::find_executable_in_path(chromedriverPath);
		m_driver = ::boost::process::launch(exec, args, ctx);
		std::cout << "chromedriver started, pid: " << m_driver.get_id()
				<< std::endl;

		m_driverUrl = "http://localhost:9515";
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	} else {
		m_driverUrl = driverUrl;
	}

}

void TestEnvironment::TearDown()
{
  std::cout << "TestEnvironment::TearDown" << std::endl;
  m_driver.terminate();

  delete m_pages;
  m_pages = nullptr;

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
  return m_pages->whereIs(page);

}

} /* namespace selenium */
