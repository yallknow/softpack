#include "pack_library_scope_profiler.hpp"

#include "pack_library_logger.hpp"
#include "pack_library_time.hpp"

namespace pack {
namespace library {

namespace {

constexpr std::string_view gsc_cat{};
constexpr std::string_view gsc_ph{"X"};
constexpr std::string_view gsc_tid{"0"};

}  // namespace

std::atomic<bool> scope_profiler::ms_isInitialized{false};

scope_profiler::scope_profiler(const std::string_view c_funcsig) noexcept
    : mc_name{c_funcsig}, m_ts{time::since_epoch()}, m_pid{logger::get_pid()} {}

scope_profiler::~scope_profiler() noexcept {
  logger::profile(this->record(time::since_epoch() - this->m_ts));
}

void scope_profiler::init() noexcept {
  if (is_initialized() || !logger::is_initialized()) {
    return;
  }

  logger::profile("[ {} ");
  const scope_profiler c_profiler{__FUNCSIG__};

  ms_isInitialized = true;
}

void scope_profiler::destroy() noexcept {
  if (!is_initialized() || !logger::is_initialized()) {
    return;
  }

  logger::profile(" ]");

  ms_isInitialized = false;
}

bool scope_profiler::is_initialized() noexcept { return ms_isInitialized; }

std::string scope_profiler::record(const std::uint64_t& c_dur) const noexcept {
  std::string record{};

  record += ", { \"cat\": \"";
  record += gsc_cat;

  record += "\", \"dur\": ";
  record += std::to_string(c_dur);

  record += ", \"name\": \"";
  record += this->mc_name;

  record += "\", \"ph\": \"";
  record += gsc_ph;

  record += "\", \"pid\": ";
  record += this->m_pid;

  record += ", \"tid\": ";
  record += gsc_tid;

  record += ", \"ts\": ";
  record += std::to_string(this->m_ts) + "}";

  return record;
}

}  // namespace library
}  // namespace pack
