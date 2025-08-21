#pragma once

#ifndef PACK_LIBRARY_LOGGER
#define PACK_LIBRARY_LOGGER

#include <atomic>
#include <fstream>
#include <memory>
#include <mutex>
#include <string>
#include <string_view>

namespace pack {
namespace library {

class logger final {
 public:
  explicit logger() noexcept = delete;
  /* virtual */ ~logger() noexcept = delete;

 public:
  explicit logger(const logger& c_other) noexcept = delete;
  explicit logger(logger&& otherRLink) noexcept = delete;

 public:
  logger& operator=(const logger& c_other) noexcept = delete;
  logger& operator=(logger&& otherRLink) noexcept = delete;

 public:
  static void init(const std::string_view c_logDirectory) noexcept;
  static void destroy() noexcept;

  static bool is_initialized() noexcept;

  static void profile(const std::string_view c_data) noexcept;
  static void log(const std::string_view c_data) noexcept;
  static void async(const std::string_view c_data) noexcept;

  static std::string get_pid() noexcept;

 private:
  static std::atomic<bool> ms_isInitialized;

  static std::unique_ptr<std::ofstream> ms_profileStreamUPtr;
  static std::unique_ptr<std::ofstream> ms_logStreamUPtr;
  static std::unique_ptr<std::ofstream> ms_asyncStreamUPtr;

  static std::unique_ptr<std::mutex> ms_profileMutexUPtr;
  static std::unique_ptr<std::mutex> ms_logMutexUPtr;
  static std::unique_ptr<std::mutex> ms_asyncMutexUPtr;
};

}  // namespace library
}  // namespace pack

#endif  // !PACK_LIBRARY_LOGGER
