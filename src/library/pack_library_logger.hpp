#pragma once

#ifndef _PACK_LIBRARY_LOGGER_
#define _PACK_LIBRARY_LOGGER_

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
  static void msf_init() noexcept;
  static void msf_destroy() noexcept;

  static bool msf_is_initialized() noexcept;

  static void msf_profile(const std::string_view pc_Data) noexcept;
  static void msf_log(const std::string_view pc_Data) noexcept;
  static void msf_async_log(const std::string_view pc_Data) noexcept;

  static void msf_set_log_directory(
      const std::string_view pc_LogDirectory) noexcept;

  static std::string msf_get_pid() noexcept;

 private:
  static std::atomic<bool> msv_IsInitialized;

  static std::string msv_LogDirectory;

 private:
  static std::unique_ptr<std::ofstream> msp_ProfileStream;
  static std::unique_ptr<std::ofstream> msp_LogStream;
  static std::unique_ptr<std::ofstream> msp_AsyncLogStream;

  static std::unique_ptr<std::mutex> msp_ProfileStreamMutex;
  static std::unique_ptr<std::mutex> msp_LogStreamMutex;
  static std::unique_ptr<std::mutex> msp_AsyncLogStreamMutex;

 private:
  static constexpr std::string_view msc_ProfileFilenamePostfix{"_profile"};
  static constexpr std::string_view msc_LogFilenamePostfix{"_log"};
  static constexpr std::string_view msc_AsyncLogFilenamePostfix{"_async"};

 public:
  explicit logger() noexcept = delete;
  /* virtual */ ~logger() noexcept = delete;

 public:
  explicit logger(const logger& pcl_Other) noexcept = delete;
  explicit logger(logger&& pr_Other) noexcept = delete;

 public:
  logger& operator=(const logger& pcl_Other) noexcept = delete;
  logger& operator=(logger&& pr_Other) noexcept = delete;
};

}  // namespace library
}  // namespace pack

#endif  // !_PACK_LIBRARY_LOGGER_
