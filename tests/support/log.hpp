/*
 * log.hpp
 *
 *  Created on: Sep 22, 2014
 *      Author: speedpat
 */

#ifndef LOG_HPP_
#define LOG_HPP_

#define DEBUG 1

#if DEBUG
#define LOG(x) \
  { std::cerr << x << std::endl; }
#else
#define LOG(x)
#endif


#endif /* LOG_HPP_ */
