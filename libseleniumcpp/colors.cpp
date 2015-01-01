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

#include "selenium/support/colors.hpp"
#include "selenium/support/color.hpp"

namespace selenium
{
namespace support
{


const Color Colors::TRANSPARENT(0, 0, 0, 0.0);
const Color Colors::ALICEBLUE(240, 248, 255, 1.0);
const Color Colors::ANTIQUEWHITE(250, 235, 215, 1.0);
const Color Colors::AQUA(0, 255, 255, 1.0);
const Color Colors::AQUAMARINE(127, 255, 212, 1.0);
const Color Colors::AZURE(240, 255, 255, 1.0);
const Color Colors::BEIGE(245, 245, 220, 1.0);
const Color Colors::BISQUE(255, 228, 196, 1.0);
const Color Colors::BLACK(0, 0, 0, 1.0);
const Color Colors::BLANCHEDALMOND(255, 235, 205, 1.0);
const Color Colors::BLUE(0, 0, 255, 1.0);
const Color Colors::BLUEVIOLET(138, 43, 226, 1.0);
const Color Colors::BROWN(165, 42, 42, 1.0);
const Color Colors::BURLYWOOD(222, 184, 135, 1.0);
const Color Colors::CADETBLUE(95, 158, 160, 1.0);
const Color Colors::CHARTREUSE(127, 255, 0, 1.0);
const Color Colors::CHOCOLATE(210, 105, 30, 1.0);
const Color Colors::CORAL(255, 127, 80, 1.0);
const Color Colors::CORNFLOWERBLUE(100, 149, 237, 1.0);
const Color Colors::CORNSILK(255, 248, 220, 1.0);
const Color Colors::CRIMSON(220, 20, 60, 1.0);
const Color Colors::CYAN(0, 255, 255, 1.0);
const Color Colors::DARKBLUE(0, 0, 139, 1.0);
const Color Colors::DARKCYAN(0, 139, 139, 1.0);
const Color Colors::DARKGOLDENROD(184, 134, 11, 1.0);
const Color Colors::DARKGRAY(169, 169, 169, 1.0);
const Color Colors::DARKGREEN(0, 100, 0, 1.0);
const Color Colors::DARKGREY(169, 169, 169, 1.0);
const Color Colors::DARKKHAKI(189, 183, 107, 1.0);
const Color Colors::DARKMAGENTA(139, 0, 139, 1.0);
const Color Colors::DARKOLIVEGREEN(85, 107, 47, 1.0);
const Color Colors::DARKORANGE(255, 140, 0, 1.0);
const Color Colors::DARKORCHID(153, 50, 204, 1.0);
const Color Colors::DARKRED(139, 0, 0, 1.0);
const Color Colors::DARKSALMON(233, 150, 122, 1.0);
const Color Colors::DARKSEAGREEN(143, 188, 143, 1.0);
const Color Colors::DARKSLATEBLUE(72, 61, 139, 1.0);
const Color Colors::DARKSLATEGRAY(47, 79, 79, 1.0);
const Color Colors::DARKSLATEGREY(47, 79, 79, 1.0);
const Color Colors::DARKTURQUOISE(0, 206, 209, 1.0);
const Color Colors::DARKVIOLET(148, 0, 211, 1.0);
const Color Colors::DEEPPINK(255, 20, 147, 1.0);
const Color Colors::DEEPSKYBLUE(0, 191, 255, 1.0);
const Color Colors::DIMGRAY(105, 105, 105, 1.0);
const Color Colors::DIMGREY(105, 105, 105, 1.0);
const Color Colors::DODGERBLUE(30, 144, 255, 1.0);
const Color Colors::FIREBRICK(178, 34, 34, 1.0);
const Color Colors::FLORALWHITE(255, 250, 240, 1.0);
const Color Colors::FORESTGREEN(34, 139, 34, 1.0);
const Color Colors::FUCHSIA(255, 0, 255, 1.0);
const Color Colors::GAINSBORO(220, 220, 220, 1.0);
const Color Colors::GHOSTWHITE(248, 248, 255, 1.0);
const Color Colors::GOLD(255, 215, 0, 1.0);
const Color Colors::GOLDENROD(218, 165, 32, 1.0);
const Color Colors::GRAY(128, 128, 128, 1.0);
const Color Colors::GREY(128, 128, 128, 1.0);
const Color Colors::GREEN(0, 128, 0, 1.0);
const Color Colors::GREENYELLOW(173, 255, 47, 1.0);
const Color Colors::HONEYDEW(240, 255, 240, 1.0);
const Color Colors::HOTPINK(255, 105, 180, 1.0);
const Color Colors::INDIANRED(205, 92, 92, 1.0);
const Color Colors::INDIGO(75, 0, 130, 1.0);
const Color Colors::IVORY(255, 255, 240, 1.0);
const Color Colors::KHAKI(240, 230, 140, 1.0);
const Color Colors::LAVENDER(230, 230, 250, 1.0);
const Color Colors::LAVENDERBLUSH(255, 240, 245, 1.0);
const Color Colors::LAWNGREEN(124, 252, 0, 1.0);
const Color Colors::LEMONCHIFFON(255, 250, 205, 1.0);
const Color Colors::LIGHTBLUE(173, 216, 230, 1.0);
const Color Colors::LIGHTCORAL(240, 128, 128, 1.0);
const Color Colors::LIGHTCYAN(224, 255, 255, 1.0);
const Color Colors::LIGHTGOLDENRODYELLOW(250, 250, 210, 1.0);
const Color Colors::LIGHTGRAY(211, 211, 211, 1.0);
const Color Colors::LIGHTGREEN(144, 238, 144, 1.0);
const Color Colors::LIGHTGREY(211, 211, 211, 1.0);
const Color Colors::LIGHTPINK(255, 182, 193, 1.0);
const Color Colors::LIGHTSALMON(255, 160, 122, 1.0);
const Color Colors::LIGHTSEAGREEN(32, 178, 170, 1.0);
const Color Colors::LIGHTSKYBLUE(135, 206, 250, 1.0);
const Color Colors::LIGHTSLATEGRAY(119, 136, 153, 1.0);
const Color Colors::LIGHTSLATEGREY(119, 136, 153, 1.0);
const Color Colors::LIGHTSTEELBLUE(176, 196, 222, 1.0);
const Color Colors::LIGHTYELLOW(255, 255, 224, 1.0);
const Color Colors::LIME(0, 255, 0, 1.0);
const Color Colors::LIMEGREEN(50, 205, 50, 1.0);
const Color Colors::LINEN(250, 240, 230, 1.0);
const Color Colors::MAGENTA(255, 0, 255, 1.0);
const Color Colors::MAROON(128, 0, 0, 1.0);
const Color Colors::MEDIUMAQUAMARINE(102, 205, 170, 1.0);
const Color Colors::MEDIUMBLUE(0, 0, 205, 1.0);
const Color Colors::MEDIUMORCHID(186, 85, 211, 1.0);
const Color Colors::MEDIUMPURPLE(147, 112, 219, 1.0);
const Color Colors::MEDIUMSEAGREEN(60, 179, 113, 1.0);
const Color Colors::MEDIUMSLATEBLUE(123, 104, 238, 1.0);
const Color Colors::MEDIUMSPRINGGREEN(0, 250, 154, 1.0);
const Color Colors::MEDIUMTURQUOISE(72, 209, 204, 1.0);
const Color Colors::MEDIUMVIOLETRED(199, 21, 133, 1.0);
const Color Colors::MIDNIGHTBLUE(25, 25, 112, 1.0);
const Color Colors::MINTCREAM(245, 255, 250, 1.0);
const Color Colors::MISTYROSE(255, 228, 225, 1.0);
const Color Colors::MOCCASIN(255, 228, 181, 1.0);
const Color Colors::NAVAJOWHITE(255, 222, 173, 1.0);
const Color Colors::NAVY(0, 0, 128, 1.0);
const Color Colors::OLDLACE(253, 245, 230, 1.0);
const Color Colors::OLIVE(128, 128, 0, 1.0);
const Color Colors::OLIVEDRAB(107, 142, 35, 1.0);
const Color Colors::ORANGE(255, 165, 0, 1.0);
const Color Colors::ORANGERED(255, 69, 0, 1.0);
const Color Colors::ORCHID(218, 112, 214, 1.0);
const Color Colors::PALEGOLDENROD(238, 232, 170, 1.0);
const Color Colors::PALEGREEN(152, 251, 152, 1.0);
const Color Colors::PALETURQUOISE(175, 238, 238, 1.0);
const Color Colors::PALEVIOLETRED(219, 112, 147, 1.0);
const Color Colors::PAPAYAWHIP(255, 239, 213, 1.0);
const Color Colors::PEACHPUFF(255, 218, 185, 1.0);
const Color Colors::PERU(205, 133, 63, 1.0);
const Color Colors::PINK(255, 192, 203, 1.0);
const Color Colors::PLUM(221, 160, 221, 1.0);
const Color Colors::POWDERBLUE(176, 224, 230, 1.0);
const Color Colors::PURPLE(128, 0, 128, 1.0);
const Color Colors::RED(255, 0, 0, 1.0);
const Color Colors::ROSYBROWN(188, 143, 143, 1.0);
const Color Colors::ROYALBLUE(65, 105, 225, 1.0);
const Color Colors::SADDLEBROWN(139, 69, 19, 1.0);
const Color Colors::SALMON(250, 128, 114, 1.0);
const Color Colors::SANDYBROWN(244, 164, 96, 1.0);
const Color Colors::SEAGREEN(46, 139, 87, 1.0);
const Color Colors::SEASHELL(255, 245, 238, 1.0);
const Color Colors::SIENNA(160, 82, 45, 1.0);
const Color Colors::SILVER(192, 192, 192, 1.0);
const Color Colors::SKYBLUE(135, 206, 235, 1.0);
const Color Colors::SLATEBLUE(106, 90, 205, 1.0);
const Color Colors::SLATEGRAY(112, 128, 144, 1.0);
const Color Colors::SLATEGREY(112, 128, 144, 1.0);
const Color Colors::SNOW(255, 250, 250, 1.0);
const Color Colors::SPRINGGREEN(0, 255, 127, 1.0);
const Color Colors::STEELBLUE(70, 130, 180, 1.0);
const Color Colors::TAN(210, 180, 140, 1.0);
const Color Colors::TEAL(0, 128, 128, 1.0);
const Color Colors::THISTLE(216, 191, 216, 1.0);
const Color Colors::TOMATO(255, 99, 71, 1.0);
const Color Colors::TURQUOISE(64, 224, 208, 1.0);
const Color Colors::VIOLET(238, 130, 238, 1.0);
const Color Colors::WHEAT(245, 222, 179, 1.0);
const Color Colors::WHITE(255, 255, 255, 1.0);
const Color Colors::WHITESMOKE(245, 245, 245, 1.0);
const Color Colors::YELLOW(255, 255, 0, 1.0);
const Color Colors::YELLOWGREEN(154, 205, 50, 1.0);


} /* namespace support */
} /* namespace selenium */
