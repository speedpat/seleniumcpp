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

#include "pages.hpp"
#include "app_server.hpp"

namespace selenium
{

Pages::Pages(const std::string& baseUrl)
 : m_baseUrl(baseUrl)
{
  ajaxyPage = whereIs("ajaxy_page.html");
  alertsPage = whereIs("alerts.html");
  blankPage = whereIs("blank.html");
  bodyTypingPage = whereIs("bodyTypingTest.html");
  booleanAttributes = whereIs("booleanAttributes.html");
  childPage = whereIs("child/childPage.html");
  chinesePage = whereIs("cn-test.html");
  clickJacker = whereIs("click_jacker.html");
  clickEventPage = whereIs("clickEventPage.html");
  clicksPage = whereIs("clicks.html");
  colorPage = whereIs("colorPage.html");
  dragDropOverflow = whereIs("dragDropOverflow.html");
  draggableLists = whereIs("draggableLists.html");
  dragAndDropPage = whereIs("dragAndDropTest.html");
  droppableItems = whereIs("droppableItems.html");
  documentWrite = whereIs("document_write_in_onload.html");
  dynamicallyModifiedPage = whereIs("dynamicallyModifiedPage.html");
  dynamicPage = whereIs("dynamic.html");
  errorsPage = whereIs("errors.html");
  xhtmlFormPage = whereIs("xhtmlFormPage.xhtml");
  formPage = whereIs("formPage.html");
  formSelectionPage = whereIs("formSelectionPage.html");
  framesetPage = whereIs("frameset.html");
  grandchildPage = whereIs("child/grandchild/grandchildPage.html");
  html5Page = whereIs("html5Page.html");
  iframePage = whereIs("iframes.html");
  javascriptEnhancedForm = whereIs("javascriptEnhancedForm.html");
  javascriptPage = whereIs("javascriptPage.html");
  linkedImage = whereIs("linked_image.html");
  longContentPage = whereIs("longContentPage.html");
  macbethPage = whereIs("macbeth.html");
  mapVisibilityPage = whereIs("map_visibility.html");
  metaRedirectPage = whereIs("meta-redirect.html");
  missedJsReferencePage = whereIs("missedJsReference.html");
  mouseOverPage = whereIs("mouseOver.html");
  mouseTrackerPage = whereIs("mousePositionTracker.html");
  nestedPage = whereIs("nestedElements.html");
  readOnlyPage = whereIs("readOnlyPage.html");
  rectanglesPage = whereIs("rectangles.html");
  redirectPage = whereIs("redirect");
  richTextPage = whereIs("rich_text.html");
  selectableItemsPage = whereIs("selectableItems.html");
  selectPage = whereIs("selectPage.html");
  simpleTestPage = whereIs("simpleTest.html");
  simpleXmlDocument = whereIs("simple.xml");
  sleepingPage = whereIs("sleep");
  slowIframes = whereIs("slow_loading_iframes.html");
  slowLoadingAlertPage = whereIs("slowLoadingAlert.html");
  svgPage = whereIs("svgPiechart.xhtml");
  svgTestPage = whereIs("svgTest.svg");
  tables = whereIs("tables.html");
  underscorePage = whereIs("underscore.html");
  unicodeLtrPage = whereIs("utf8/unicode_ltr.html");
  uploadPage = whereIs("upload.html");
  userDefinedProperty = whereIs("userDefinedProperty.html");
  veryLargeCanvas = whereIs("veryLargeCanvas.html");
  xhtmlTestPage = whereIs("xhtmlTest.html");
}

const std::string Pages::whereIs(const std::string& relativeUrl) const
{
	std::string slash = "/";
	return m_baseUrl
			+ (relativeUrl.size() > 0
					&& std::equal(slash.begin(), slash.end(),
							relativeUrl.begin()) ? "" : "/") + relativeUrl;

}

} /* namespace selenium */
