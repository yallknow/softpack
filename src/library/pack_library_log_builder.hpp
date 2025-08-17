#pragma once

#ifndef _PACK_LIBRARY_LOG_BUILDER_
#define _PACK_LIBRARY_LOG_BUILDER_

#include <atomic>
#include <boost/system/error_code.hpp>
#include <chrono>
#include <string>
#include <string_view>

namespace pack {
namespace library {

class log_builder final {
 public:
  explicit log_builder(const std::string_view pc_FuncSig) noexcept;
  /* virtual */ ~log_builder() noexcept;

 public:
  static void msf_init() noexcept;
  static void msf_destroy() noexcept;

  static bool msf_is_initialized() noexcept;

  static void msf_log(const std::string_view pc_Tag,
                      const std::string_view pc_Message,
                      const boost::system::error_code pc_ErrorCode) noexcept;
  static void msf_async_log(
      const std::string_view pc_Tag, const std::string_view pc_Message,
      const boost::system::error_code pc_ErrorCode) noexcept;

 private:
  static std::string msf_create_body(
      const std::string_view pc_Tag, const std::string_view pc_Message,
      const boost::system::error_code pc_ErrorCode) noexcept;

 private:
  const std::chrono::steady_clock::time_point mc_StartTime;

 private:
  static std::atomic<bool> msv_IsInitialized;
  static std::atomic<bool> msv_IsNextSectionClosed;

 public:
  explicit log_builder(const log_builder& pcl_Other) noexcept = delete;
  explicit log_builder(log_builder&& pr_Other) noexcept = delete;

 public:
  log_builder& operator=(const log_builder& pcl_Other) noexcept = delete;
  log_builder& operator=(log_builder&& pr_Other) noexcept = delete;
};

}  // namespace library
}  // namespace pack

#endif  // !_PACK_LIBRARY_LOG_BUILDER_
