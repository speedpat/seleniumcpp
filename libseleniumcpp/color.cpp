/*
 * color.cpp
 *
 *  Created on: Oct 27, 2014
 *      Author: speedpat
 */

#include <memory>

#include <boost/format.hpp>
#include <boost/regex.hpp>

#include "selenium/support/color.hpp"
#include "selenium/exceptions.hpp"
#include "log.hpp"

namespace selenium
{
namespace support
{

class Color::Converter
{
public:
  virtual ~Converter() = default;

  virtual bool getColor(const std::string& value, Color& color)
  {
    boost::smatch matcher;
    LOG("checking color: '" << value << "'");
    if (boost::regex_match(value, matcher, getPattern()))
    {
      LOG("found something");
      double a = 1.0;
      if (matcher.size() == 4)
      {
        a = std::stod(matcher[4]);
      }
      color = createColor(matcher, a);
      return true;
    }
    LOG("found nothing");
    return false;
  }

protected:
  virtual Color createColor(const boost::smatch& matcher, double a)
  {
    return Color(
        fromMatchGroup(matcher, 1),
        fromMatchGroup(matcher, 2),
        fromMatchGroup(matcher, 3),
        a);
  }

  virtual short fromMatchGroup(const boost::smatch& matcher, int index)
  {
    return std::stoi(matcher[index]);
  }

  virtual boost::regex getPattern()
  {
    return boost::regex("");
  }

};

Color::Color(int red, int green, int blue, double alpha)
    : red(red), green(green), blue(blue), alpha(alpha)
{
}

void Color::setOpacity(double alpha)
{
  this->alpha = alpha;
}

std::string Color::asRgb() const
{
  return (::boost::format("rgb(%d, %d, %d)") % red % green % blue).str();
}

std::string Color::asRgba() const
{
  std::string alphaString;
  if (alpha == 1)
  {
    alphaString = "1";
  }
  else if (alpha == 0)
  {
    alphaString = "0";
  }
  else
  {
    alphaString = std::to_string(alpha);
  }
  return (::boost::format("rgba(%d, %d, %d, %s)") % red % green % blue
      % alphaString).str();
}

std::string Color::asHex() const
{
  return (::boost::format("#%02x%02x%02x") % red % green % blue).str();
}

std::string Color::toString() const
{
  return "Color: " + asRgba();
}

bool Color::operator ==(const Color& other) const
    {
  return asRgba() == other.asRgba();
}

class RgbConverter : public Color::Converter
{
public:
  virtual ~RgbConverter() = default;
private:
  const boost::regex RGB_PATTERN = boost::regex("^[[:space:]]*rgb\\([[:space:]]*"
      "([[:digit:]]{1,3})[[:space:]]*,[[:space:]]*"
      "([[:digit:]]d{1,3})[[:space:]]*,[[:space:]]*"
      "([[:digit:]]{1,3})[[:space:]]*\\)[[:space:]]*$", boost::regex::basic);

protected:
  virtual boost::regex getPattern()
  {
    LOG("using pattern: '" << RGB_PATTERN << "'");
    return RGB_PATTERN;
  }
};

class RgbPctConverter : public Color::Converter
{
public:
  virtual ~RgbPctConverter() = default;
private:
  const boost::regex RGBPCT_PATTERN = boost::regex("^[[:space:]]*rgb\\([[:space:]]*"
      "([[:digit:]]{1,3}|[[:digit:]]{1,2}\\.[[:digit:]]+)%[[:space:]]*,[[:space:]]*"
      "([[:digit:]]{1,3}|[[:digit:]]{1,2}\\.[[:digit:]]+)%[[:space:]]*,[[:space:]]*"
      "([[:digit:]]{1,3}|[[:digit:]]{1,2}\\.[[:digit:]]+)%[[:space:]]*\\)[[:space:]]*$");

protected:
  virtual boost::regex getPattern()
  {
    return RGBPCT_PATTERN;
  }

protected:
  virtual short fromMatchGroup(boost::smatch matcher, int index)
  {
    double n = std::stod(matcher[index]) / 100 * 255;
    return (short) n;
  }
};

class RgbaConverter : public RgbConverter
{
public:
  virtual ~RgbaConverter() = default;
private:
  const boost::regex RGBA_PATTERN = boost::regex("^[[:space:]]*rgba\\([[:space:]]*"
      "([[:digit:]]{1,3})[[:space:]]*,[[:space:]]*([[:digit:]]{1,3})[[:space:]]*,[[:space:]]*"
      "([[:digit:]]{1,3})[[:space:]]*,[[:space:]]*(0|1|0\\.[[:digit:]]+)[[:space:]]*\\)[[:space:]]*$", boost::regex_constants::extended);

protected:
  virtual boost::regex getPattern()
  {
    LOG("using pattern: '" << RGBA_PATTERN << "'");
    return RGBA_PATTERN;
  }
};
/*
 class RgbaPctConverter : public  RgbPctConverter {
 private:
 const boost::regex RGBAPCT_PATTERN = boost::regex("^\\s*rgba\\(\\s*"
 "(\\d{1,3}|\\d{1,2}\\.\\d+)%\\s*,\\s*"
 "(\\d{1,3}|\\d{1,2}\\.\\d+)%\\s*,\\s*"
 "(\\d{1,3}|\\d{1,2}\\.\\d+)%\\s*,\\s*"
 "(0|1|0\\.\\d+)\\s*\\)\\s*$");

 protected: virtual boost::regex getPattern() {
 return RGBAPCT_PATTERN;
 }
 };

 class HexConverter : public Color::Converter {
 private:
 const boost::regex HEX_PATTERN = boost::regex(
 "#(\\p{XDigit}{2})(\\p{XDigit}{2})(\\p{XDigit}{2})");

 protected: virtual boost::regex getPattern() {
 return HEX_PATTERN;
 }

 protected:
 virtual short fromMatchGroup(boost::smatch matcher, int index) {
 return std::stoi(matcher[index], nullptr, 16);
 }
 };

 class Hex3Converter : public Color::Converter {
 private:
 const boost::regex HEX3_PATTERN = boost::regex(
 "#(\\p{XDigit}{1})(\\p{XDigit}{1})(\\p{XDigit}{1})");

 protected: virtual boost::regex getPattern() {
 return HEX3_PATTERN;
 }

 protected:
 virtual short fromMatchGroup(boost::smatch matcher, int index) {
 return std::stoi(matcher[index].str() + matcher[index].str(), nullptr, 16);
 }

 };

 class HslConverter : public Color::Converter {
 private:
 const boost::regex HSL_PATTERN = boost::regex("^\\s*hsl\\(\\s*"
 "(\\d{1,3})\\s*,\\s*"
 "(\\d{1,3})\\%\\s*,\\s*"
 "(\\d{1,3})\\%\\s*\\)\\s*$");

 protected: virtual boost::regex getPattern() {
 return HSL_PATTERN;
 }

 protected:
 virtual Color createColor(boost::smatch matcher, double a) {
 double h = std::stod(matcher[0]) / 360;
 double s = std::stod(matcher[1]) / 100;
 double l = std::stod(matcher[2]) / 100;
 double r, g, b;

 if (s == 0) {
 r = l;
 g = r;
 b = r;
 } else {
 double luminocity2 = (l < 0.5) ? l * (1 + s) : l + s - l * s;
 double luminocity1 = 2 * l - luminocity2;
 r = hueToRgb(luminocity1, luminocity2, h + 1.0 / 3.0);
 g = hueToRgb(luminocity1, luminocity2, h);
 b = hueToRgb(luminocity1, luminocity2, h - 1.0 / 3.0);
 }

 return Color((short) (r * 256),
 (short) (g * 256),
 (short) (b * 256),
 a);
 }

 private:
 double hueToRgb(double luminocity1, double luminocity2, double hue) {
 if (hue < 0.0) hue += 1;
 if (hue > 1.0) hue -= 1;
 if (hue < 1.0 / 6.0) return (luminocity1 + (luminocity2 - luminocity1) * 6.0 * hue);
 if (hue < 1.0 / 2.0) return luminocity2;
 if (hue < 2.0 / 3.0) return (luminocity1 + (luminocity2 - luminocity1) * ((2.0 / 3.0) - hue) * 6.0);
 return luminocity1;
 }

 };

 class HslaConverter : public  HslConverter {
 private:
 const boost::regex HSLA_PATTERN = boost::regex("^\\s*hsla\\(\\s*"
 "(\\d{1,3})\\s*,\\s*"
 "(\\d{1,3})\\%\\s*,\\s*"
 "(\\d{1,3})\\%\\s*,\\s*"
 "(0|1|0\\.\\d+)\\s*\\)\\s*$");

 protected: virtual boost::regex getPattern() {
 return HSLA_PATTERN;
 }

 };

 /*
 class NamedColorConverter : public Color::Converter {
 public:
 virtual Color getColor(std::string value) {
 return Colors.valueOf(value.toUpperCase()).getColorValue();
 }

 virtual boost::regex getPattern() {
 throw std::runtime_error("getPattern is unsupported");
 }
 };
 */

typedef std::shared_ptr<Color::Converter> ConverterPtr;
static std::vector<ConverterPtr> CONVERTERS = {
    ConverterPtr(new RgbConverter()),
//    RgbPctConverter(),
    ConverterPtr(new RgbaConverter()),
//    RgbaPctConverter(),
//    HexConverter(),
//    Hex3Converter(),
//    HslConverter(),
//    HslaConverter(),
    //   new NamedColorConverter(),
    };

/*
 * Guesses what format the input color is in.
 */
Color Color::fromString(std::string value)
{
  using boost::format;
  for (ConverterPtr converter : CONVERTERS)
  {
    Color color(0, 0, 0, 0.0);
    if (converter->getColor(value, color))
    {
      return color;
    }
  }

  format fmt = format("Did not know how to convert %s into color") % value;

  throw WebDriverException(
      fmt.str());
}

} /* namespace support */
} /* namespace selenium */
