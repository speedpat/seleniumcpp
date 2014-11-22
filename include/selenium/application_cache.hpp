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

#ifndef APPLICATION_CACHE_HPP_
#define APPLICATION_CACHE_HPP_


namespace selenium
{

class CommandExecutor;

class ApplicationCache
{
public:
  enum Status
  {
    UNCACHED = 0,
    IDLE = 1,
    CHECKING = 2,
    DOWNLOADING = 3,
    UPDATE_READY = 4,
    OBSOLETE = 5,
  };
  ApplicationCache(CommandExecutor& driver);
  ~ApplicationCache() = default;

  void get();
  Status getStatus();
  void clear();

private:
  CommandExecutor& m_driver;

};

} /* namespace selenium */

#endif /* APPLICATION_CACHE_HPP_ */
