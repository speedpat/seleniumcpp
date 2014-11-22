/*
 * color.hpp
 *
 *  Created on: Oct 27, 2014
 *      Author: speedpat
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
