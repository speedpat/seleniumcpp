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

#ifndef __COMMAND_H_
#define __COMMAND_H_

#include <string>

namespace selenium
{

  enum Command
  {
    /**
     http://code.google.com/p/selenium/wiki/JsonWireProtocol

     # Keep in sync with org.openqa.selenium.remote.DriverCommand
     **/
    STATUS,
    NEW_SESSION,
    GET_SESSIONS,
    GET_SESSION,
    DELETE_SESSION,
    CLOSE,
    QUIT,
    GET,
    GO_BACK,
    GO_FORWARD,
    REFRESH,
    ADD_COOKIE,
    GET_COOKIE,
    GET_ALL_COOKIES,
    DELETE_COOKIE,
    DELETE_ALL_COOKIES,
    FIND_ELEMENT,
    FIND_ELEMENTS,
    FIND_CHILD_ELEMENT,
    FIND_CHILD_ELEMENTS,
    CLEAR_ELEMENT,
    CLICK_ELEMENT,
    HOVER_OVER_ELEMENT,
    SEND_KEYS_TO_ELEMENT,
    SEND_KEYS_TO_ACTIVE_ELEMENT,
    SUBMIT_ELEMENT,
    UPLOAD_FILE,
    TOGGLE_ELEMENT,
    GET_CURRENT_WINDOW_HANDLE,
    GET_WINDOW_HANDLES,
    GET_WINDOW_SIZE,
    GET_WINDOW_POSITION,
    SET_WINDOW_SIZE,
    SET_WINDOW_POSITION,
    SWITCH_TO_WINDOW,
    SWITCH_TO_FRAME,
    SWITCH_TO_PARENT_FRAME,
    GET_ACTIVE_ELEMENT,
    GET_ELEMENT,
    GET_CURRENT_URL,
    GET_PAGE_SOURCE,
    GET_TITLE,
    EXECUTE_SCRIPT,
    GET_SPEED,
    SET_SPEED,
    SET_BROWSER_VISIBLE,
    IS_BROWSER_VISIBLE,
    GET_ELEMENT_TEXT,
    GET_ELEMENT_VALUE,
    GET_ELEMENT_TAG_NAME,
    SET_ELEMENT_SELECTED,
    DRAG_ELEMENT,
    IS_ELEMENT_SELECTED,
    IS_ELEMENT_ENABLED,
    IS_ELEMENT_DISPLAYED,
    GET_ELEMENT_LOCATION,
    GET_ELEMENT_LOCATION_ONCE_SCROLLED_INTO_VIEW,
    GET_ELEMENT_SIZE,
    GET_ELEMENT_ATTRIBUTE,
    GET_ELEMENT_VALUE_OF_CSS_PROPERTY,
    ELEMENT_EQUALS,
    SCREENSHOT,
    IMPLICIT_WAIT,
    EXECUTE_ASYNC_SCRIPT,
    SET_SCRIPT_TIMEOUT,
    SET_TIMEOUTS,
    MAXIMIZE_WINDOW,
    GET_LOG,
    GET_LOG_TYPES,

// Alerts
    DISMISS_ALERT,
    ACCEPT_ALERT,
    SET_ALERT_VALUE,
    GET_ALERT_TEXT,

// Advanced user interactions
    CLICK,
    DOUBLE_CLICK,
    MOUSE_DOWN,
    MOUSE_UP,
    MOVE_TO,

// Screen Orientation
    SET_SCREEN_ORIENTATION,
    GET_SCREEN_ORIENTATION,

// IME
    GET_IME_ENGINES,
    GET_ACTIVE_IME_ENGINE,
    IS_IME_ACTIVATED,
    DEACTIVATE_IME,
    ACTIVATE_IME,

// Touch
    SINGLE_TAP,
    TOUCH_DOWN,
    TOUCH_UP,
    TOUCH_MOVE,
    TOUCH_SCROLL,
    TOUCH_FLICK,
    TOUCH_DOUBLE_TAP,
    TOUCH_LONG_PRESS,

//  HTML 5
    EXECUTE_SQL,

//  GEO Location
    GET_GEO_LOCATION,
    SET_GEO_LOCATION,

// Application Cache
    GET_APP_CACHE,
    GET_APP_CACHE_STATUS,
    CLEAR_APP_CACHE,

// Network Connection
    GET_NETWORK_CONNECTION,
    SET_NETWORK_CONNECTION,

// Local Storage
    GET_LOCAL_STORAGE_KEYS,
    SET_LOCAL_STORAGE_ITEM,
    CLEAR_LOCAL_STORAGE,
    GET_LOCAL_STORAGE_ITEM,
    DELETE_LOCAL_STORAGE_ITEM,
    GET_LOCAL_STORAGE_SIZE,

// Session Storage
    GET_SESSION_STORAGE_KEYS,
    SET_SESSION_STORAGE_ITEM,
    CLEAR_SESSION_STORAGE,
    GET_SESSION_STORAGE_ITEM,
    DELETE_SESSION_STORAGE_ITEM,
    GET_SESSION_STORAGE_SIZE,



  };

} /* namespace selenium */

#endif /* COMMAND_H_ */
