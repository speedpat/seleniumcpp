/*
 * pages.cpp
 *
 *  Created on: Sep 20, 2014
 *      Author: speedpat
 */

#include "pages.hpp"
#include "app_server.hpp"

namespace selenium
{

Pages::Pages(const AppServer& appServer)
{
  ajaxyPage = appServer.whereIs("ajaxy_page.html");
  alertsPage = appServer.whereIs("alerts.html");
  blankPage = appServer.whereIs("blank.html");
  bodyTypingPage = appServer.whereIs("bodyTypingTest.html");
  booleanAttributes = appServer.whereIs("booleanAttributes.html");
  childPage = appServer.whereIs("child/childPage.html");
  chinesePage = appServer.whereIs("cn-test.html");
  clickJacker = appServer.whereIs("click_jacker.html");
  clickEventPage = appServer.whereIs("clickEventPage.html");
  clicksPage = appServer.whereIs("clicks.html");
  colorPage = appServer.whereIs("colorPage.html");
  dragDropOverflow = appServer.whereIs("dragDropOverflow.html");
  draggableLists = appServer.whereIs("draggableLists.html");
  dragAndDropPage = appServer.whereIs("dragAndDropTest.html");
  droppableItems = appServer.whereIs("droppableItems.html");
  documentWrite = appServer.whereIs("document_write_in_onload.html");
  dynamicallyModifiedPage = appServer.whereIs("dynamicallyModifiedPage.html");
  dynamicPage = appServer.whereIs("dynamic.html");
  errorsPage = appServer.whereIs("errors.html");
  xhtmlFormPage = appServer.whereIs("xhtmlFormPage.xhtml");
  formPage = appServer.whereIs("formPage.html");
  formSelectionPage = appServer.whereIs("formSelectionPage.html");
  framesetPage = appServer.whereIs("frameset.html");
  grandchildPage = appServer.whereIs("child/grandchild/grandchildPage.html");
  html5Page = appServer.whereIs("html5Page.html");
  iframePage = appServer.whereIs("iframes.html");
  javascriptEnhancedForm = appServer.whereIs("javascriptEnhancedForm.html");
  javascriptPage = appServer.whereIs("javascriptPage.html");
  linkedImage = appServer.whereIs("linked_image.html");
  longContentPage = appServer.whereIs("longContentPage.html");
  macbethPage = appServer.whereIs("macbeth.html");
  mapVisibilityPage = appServer.whereIs("map_visibility.html");
  metaRedirectPage = appServer.whereIs("meta-redirect.html");
  missedJsReferencePage = appServer.whereIs("missedJsReference.html");
  mouseOverPage = appServer.whereIs("mouseOver.html");
  mouseTrackerPage = appServer.whereIs("mousePositionTracker.html");
  nestedPage = appServer.whereIs("nestedElements.html");
  readOnlyPage = appServer.whereIs("readOnlyPage.html");
  rectanglesPage = appServer.whereIs("rectangles.html");
  redirectPage = appServer.whereIs("redirect");
  richTextPage = appServer.whereIs("rich_text.html");
  selectableItemsPage = appServer.whereIs("selectableItems.html");
  selectPage = appServer.whereIs("selectPage.html");
  simpleTestPage = appServer.whereIs("simpleTest.html");
  simpleXmlDocument = appServer.whereIs("simple.xml");
  sleepingPage = appServer.whereIs("sleep");
  slowIframes = appServer.whereIs("slow_loading_iframes.html");
  slowLoadingAlertPage = appServer.whereIs("slowLoadingAlert.html");
  svgPage = appServer.whereIs("svgPiechart.xhtml");
  svgTestPage = appServer.whereIs("svgTest.svg");
  tables = appServer.whereIs("tables.html");
  underscorePage = appServer.whereIs("underscore.html");
  unicodeLtrPage = appServer.whereIs("utf8/unicode_ltr.html");
  uploadPage = appServer.whereIs("upload.html");
  userDefinedProperty = appServer.whereIs("userDefinedProperty.html");
  veryLargeCanvas = appServer.whereIs("veryLargeCanvas.html");
  xhtmlTestPage = appServer.whereIs("xhtmlTest.html");
}


} /* namespace selenium */
