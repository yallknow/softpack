#pragma once

#ifndef PACK_LIBRARY_LOG_BUILDER
#define PACK_LIBRARY_LOG_BUILDER

#include <atomic>
#include <boost/core/noncopyable.hpp>
#include <boost/system/error_code.hpp>
#include <chrono>
#include <string>
#include <string_view>

namespace pack {
namespace library {

class log_builder final : private boost::noncopyable {
 public:
  explicit log_builder(const std::string_view c_funcsig) noexcept;
  /* virtual */ ~log_builder() noexcept;

 public:
  explicit log_builder(log_builder&& otherRLink) noexcept = delete;
  log_builder& operator=(log_builder&& otherRLink) noexcept = delete;

 public:
  static void init() noexcept;
  static void destroy() noexcept;

  static bool is_initialized() noexcept;

  static void log(const std::string_view c_tag,
                  const std::string_view c_message,
                  const boost::system::error_code c_errorCode) noexcept;
  static void async(const std::string_view c_tag,
                    const std::string_view c_message,
                    const boost::system::error_code c_errorCode) noexcept;

 private:
  static std::string create_body(
      const std::string_view c_tag, const std::string_view c_message,
      const boost::system::error_code c_errorCode) noexcept;

 private:
  const std::chrono::steady_clock::time_point mc_startTime;

 private:
  static std::atomic<bool> ms_isInitialized;
  static std::atomic<bool> ms_isNextSectionClosed;
};

}  // namespace library
}  // namespace pack

#endif  // !PACK_LIBRARY_LOG_BUILDER
