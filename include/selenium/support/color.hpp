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

#ifndef COLOR_HPP_
#define COLOR_HPP_

#include <string>

namespace selenium
{
namespace support
{
class Colors;

class Color
{
public:
  Color(int red, int green, int blue, double alpha);
  ~Color() = default;

  /*
   * Guesses what format the input color is in.
   */
  static Color fromString(std::string value);

  void setOpacity(double alpha);

  std::string asRgb() const;

  std::string asRgba() const;

  std::string asHex() const;

  std::string toString() const;

  bool operator==(const Color& other) const;

  class Converter;


private:

  int red;
  int green;
  int blue;
  double alpha;

};

} /* namespace support */
} /* namespace selenium */

#endif /* COLOR_HPP_ */
