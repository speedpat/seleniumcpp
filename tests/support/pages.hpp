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

#ifndef PAGES_HPP_
#define PAGES_HPP_

#include <string>

#include "app_server.hpp"

namespace selenium
{
class Pages : public AppServer
{
public:
  Pages(const std::string& baseUrl);
  virtual ~Pages() = default;

  virtual const std::string whereIs(const std::string& relativeUrl) const;

  std::string ajaxyPage;
  std::string alertsPage;
  std::string blankPage;
  std::string bodyTypingPage;
  std::string booleanAttributes;
  std::string childPage;
  std::string chinesePage;
  std::string clickEventPage;
  std::string clickJacker;
  std::string clicksPage;
  std::string colorPage;
  std::string documentWrite;
  std::string dragDropOverflow;
  std::string draggableLists;
  std::string dragAndDropPage;
  std::string droppableItems;
  std::string dynamicallyModifiedPage;
  std::string dynamicPage;
  std::string errorsPage;
  std::string formPage;
  std::string formSelectionPage;
  std::string framesetPage;
  std::string grandchildPage;
  std::string html5Page;
  std::string iframePage;
  std::string javascriptEnhancedForm;
  std::string javascriptPage;
  std::string linkedImage;
  std::string longContentPage;
  std::string macbethPage;
  std::string mapVisibilityPage;
  std::string metaRedirectPage;
  std::string missedJsReferencePage;
  std::string mouseOverPage;
  std::string mouseTrackerPage;
  std::string nestedPage;
  std::string readOnlyPage;
  std::string rectanglesPage;
  std::string redirectPage;
  std::string richTextPage;
  std::string selectableItemsPage;
  std::string selectPage;
  std::string simpleTestPage;
  std::string simpleXmlDocument;
  std::string sleepingPage;
  std::string slowIframes;
  std::string slowLoadingAlertPage;
  std::string svgPage;
  std::string svgTestPage;
  std::string tables;
  std::string underscorePage;
  std::string unicodeLtrPage;
  std::string uploadPage;
  std::string userDefinedProperty;
  std::string veryLargeCanvas;
  std::string xhtmlFormPage;
  std::string xhtmlTestPage;
private:
  std::string m_baseUrl;
};

} /* namespace selenium */

#endif /* PAGES_HPP_ */
