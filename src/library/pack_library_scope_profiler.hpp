#pragma once

#ifndef _PACK_LIBRARY_SCOPE_PROFILER_
#define _PACK_LIBRARY_SCOPE_PROFILER_

#include <atomic>
#include <cstdint>
#include <string>
#include <string_view>

namespace pack {
namespace library {

class scope_profiler final {
 public:
  explicit scope_profiler(const std::string_view pc_FuncSig) noexcept;
  /* virtual */ ~scope_profiler() noexcept;

 public:
  static void msf_init() noexcept;
  static void msf_destroy() noexcept;

  static bool msf_is_initialized() noexcept;

 private:
  std::string mf_create_record() const noexcept;

 private:
  const std::string mc_Name;
  const std::string mc_Cat{};
  const std::string mc_Ph{"X"};
  const std::string mc_Tid{"0"};

 private:
  std::string mv_Pid{};

  std::uint64_t mv_Ts{};
  std::uint64_t mv_Dur{};

 private:
  static std::atomic<bool> msv_IsInitialized;

 public:
  explicit scope_profiler(const scope_profiler& pcl_Other) noexcept = delete;
  explicit scope_profiler(scope_profiler&& pr_Other) noexcept = delete;

 public:
  scope_profiler& operator=(const scope_profiler& pcl_Other) noexcept = delete;
  scope_profiler& operator=(scope_profiler&& pr_Other) noexcept = delete;
};

}  // namespace library
}  // namespace pack

#endif  // !_PACK_LIBRARY_SCOPE_PROFILER_
