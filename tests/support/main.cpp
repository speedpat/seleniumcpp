/*
 * main.cpp
 *
 *  Created on: Sep 6, 2014
 *      Author: speedpat
 */

#include <gtest/gtest.h>
#include "selenium/selenium.hpp"

#include "test_environment.hpp"


int main(int argc, char **argv) {
  ::testing::AddGlobalTestEnvironment(selenium::TestEnvironment::s_testEnvironment);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

