/*
 * types_internal.hpp
 *
 *  Created on: Sep 8, 2014
 *      Author: speedpat
 */

#ifndef TYPES_INTERNAL_HPP_
#define TYPES_INTERNAL_HPP_

#include <boost/network/protocol/http/client.hpp>
#include <boost/network/uri.hpp>

#include <boost/property_tree/ptree.hpp>

namespace selenium
{

typedef boost::network::http::basic_client<boost::network::http::tags::http_keepalive_8bit_udp_resolve, 1, 1> httpclient;
typedef boost::property_tree::iptree CommandParameters;
typedef boost::property_tree::iptree Response;



} /* namespace selenium */



#endif /* TYPES_INTERNAL_HPP_ */
