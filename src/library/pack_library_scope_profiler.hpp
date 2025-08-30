#pragma once

#ifndef PACK_LIBRARY_SCOPE_PROFILER
#define PACK_LIBRARY_SCOPE_PROFILER

#include <atomic>
#include <boost/core/noncopyable.hpp>
#include <cstdint>
#include <string>
#include <string_view>

namespace pack {
namespace library {

class scope_profiler final : private boost::noncopyable {
 public:
  explicit scope_profiler(const std::string_view c_funcsig) noexcept;
  /* virtual */ ~scope_profiler() noexcept;

 public:
  explicit scope_profiler(scope_profiler&& otherRLink) noexcept = delete;
  scope_profiler& operator=(scope_profiler&& otherRLink) noexcept = delete;

 public:
  static void init() noexcept;
  static void destroy() noexcept;

  static bool is_initialized() noexcept;

 private:
  std::string record(const std::uint64_t& c_dur) const noexcept;

 private:
  const std::string mc_name;

 private:
  std::uint64_t m_ts;
  std::string m_pid;

 private:
  static std::atomic<bool> ms_isInitialized;
};

}  // namespace library
}  // namespace pack

#endif  // !PACK_LIBRARY_SCOPE_PROFILER
