#pragma once
// STL
#include <memory>
#include <mutex>
#include <vector>

class Logger;

class LogManagerImplementation final {
public:
  LogManagerImplementation() noexcept;

  // Must be implemented because std::mutex is non-copyable, see
  // http://stackoverflow.com/questions/14263836/why-does-stdmutex-create-a-c2248-when-used-in-a-struct-with-windows-socket
  // for more details
  LogManagerImplementation(const LogManagerImplementation& other);

  void operator=(const LogManagerImplementation& other);

  ~LogManagerImplementation() noexcept;

  void addLogger(std::shared_ptr<Logger> logger);

  void removeLogger(std::shared_ptr<Logger> logger);

  void removeLoggersByType(const std::string& type);

  void clearLoggers();

  int getLoggerCount() const;

  Logger* getLogger(std::shared_ptr<Logger> logger);

  Logger* getLoggerByType(const std::string& type);

  void logInfo(const std::wstring& message,
               const std::string& file,
               const std::string& function,
               const unsigned int line);

  void logWarning(const std::wstring& message,
                  const std::string& file,
                  const std::string& function,
                  const unsigned int line);

  void logError(const std::wstring& message,
                const std::string& file,
                const std::string& function,
                const unsigned int line);

  std::vector<std::shared_ptr<Logger>> m_loggers;

  mutable std::mutex m_loggerMutex;
};