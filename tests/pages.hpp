/*
 * pages.hpp
 *
 *  Created on: Sep 20, 2014
 *      Author: speedpat
 */

#ifndef PAGES_HPP_
#define PAGES_HPP_

#include <string>

namespace selenium
{
class AppServer;
class Pages
{
public:
  Pages(const AppServer& appServer);
  virtual ~Pages() = default;

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
};

} /* namespace selenium */

#endif /* PAGES_HPP_ */
