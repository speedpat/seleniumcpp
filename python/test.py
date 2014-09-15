# coding: utf8

from selenium.webdriver.common.keys import Keys
from selenium.webdriver.remote.webdriver import WebDriver
from selenium.webdriver.common.desired_capabilities import DesiredCapabilities
from selenium.webdriver.common.action_chains import ActionChains
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.common.by import By
import sys
import time
from selenium.common.exceptions import TimeoutException

if __name__ == '__main__':
	driver = WebDriver(command_executor='http://localhost:9515', desired_capabilities=DesiredCapabilities.CHROME, browser_profile=None)
	driver.get('http://www.google.ch')
	chains = ActionChains(driver)
	chains.send_keys('hallo')
	chains.key_down(Keys.CONTROL)
	chains.key_down('A')
	chains.key_up('A')
	chains.key_up(Keys.CONTROL)
	chains.perform()