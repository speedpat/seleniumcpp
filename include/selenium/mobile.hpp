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

#ifndef MOBILE_HPP_
#define MOBILE_HPP_


namespace selenium
{

class CommandExecutor;

class Mobile
{
public:
  enum ConnectionType
  {
    ALL_NETWORK = 6,
    WIFI_NETWORK = 2,
    DATA_NETWORK = 4,
    AIRPLANE_MODE = 1,
  };

  Mobile(CommandExecutor& driver);
  ~Mobile() = default;

  ConnectionType getNetworkConnection();
  void setNetworkConnection(ConnectionType type);

private:
  CommandExecutor& m_driver;
};

} /* namespace selenium */

#endif /* MOBILE_HPP_ */
