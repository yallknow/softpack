#include "pack_library_logger.hpp"

#include <filesystem>
#include <system_error>
#include <thread>

#include "pack_library_time.hpp"

namespace pack {
namespace library {

namespace {

constexpr std::string_view gsc_extension{".json"};

constexpr std::string_view gsc_profilePostfix{"_profile"};
constexpr std::string_view gsc_logPostfix{"_log"};
constexpr std::string_view gsc_asyncPostfix{"_async"};

}  // namespace

std::atomic<bool> logger::ms_isInitialized{false};

std::unique_ptr<std::ofstream> logger::ms_profileStreamUPtr{nullptr};
std::unique_ptr<std::ofstream> logger::ms_logStreamUPtr{nullptr};
std::unique_ptr<std::ofstream> logger::ms_asyncStreamUPtr{nullptr};

std::unique_ptr<std::mutex> logger::ms_profileMutexUPtr{nullptr};
std::unique_ptr<std::mutex> logger::ms_logMutexUPtr{nullptr};
std::unique_ptr<std::mutex> logger::ms_asyncMutexUPtr{nullptr};

std::string logger::get_pid() noexcept {
  return std::to_string(
      std::hash<std::thread::id>{}(std::this_thread::get_id()));
}

void logger::init(const std::string_view c_logDirectory) noexcept {
  if (ms_isInitialized) {
    return;
  }

  std::error_code errorCode{};

  if (!std::filesystem::exists(c_logDirectory, errorCode)) {
    std::filesystem::create_directories(c_logDirectory, errorCode);

    if (errorCode) {
      return;
    }
  }

  const std::string c_currentTime{time::now_underscore()};

  ms_profileStreamUPtr.reset(new (std::nothrow) std::ofstream{
      std::string{c_logDirectory} + '/' + c_currentTime +
          gsc_profilePostfix.data() + gsc_extension.data(),
      std::ofstream::trunc});

  ms_logStreamUPtr.reset(new (std::nothrow) std::ofstream{
      std::string{c_logDirectory} + '/' + c_currentTime +
          gsc_logPostfix.data() + gsc_extension.data(),
      std::ofstream::trunc});

  ms_asyncStreamUPtr.reset(new (std::nothrow) std::ofstream{
      std::string{c_logDirectory} + '/' + c_currentTime +
          gsc_asyncPostfix.data() + gsc_extension.data(),
      std::ofstream::trunc});

  ms_profileMutexUPtr.reset(new (std::nothrow) std::mutex{});
  ms_logMutexUPtr.reset(new (std::nothrow) std::mutex{});
  ms_asyncMutexUPtr.reset(new (std::nothrow) std::mutex{});

  if (!ms_profileStreamUPtr || !ms_profileStreamUPtr->is_open() ||
      !ms_logStreamUPtr || !ms_logStreamUPtr->is_open() ||
      !ms_asyncStreamUPtr || !ms_asyncStreamUPtr->is_open() ||
      !ms_profileMutexUPtr || !ms_logStreamUPtr || !ms_asyncStreamUPtr) {
    return;
  }

  ms_isInitialized = true;
}

void logger::destroy() noexcept {
  if (!ms_isInitialized) {
    return;
  }

  ms_profileStreamUPtr->close();
  ms_profileStreamUPtr.reset();

  ms_logStreamUPtr->close();
  ms_logStreamUPtr.reset();

  ms_asyncStreamUPtr->close();
  ms_asyncStreamUPtr.reset();

  ms_profileMutexUPtr.reset();
  ms_logMutexUPtr.reset();
  ms_asyncMutexUPtr.reset();

  ms_isInitialized = false;
}

bool logger::is_initialized() noexcept { return ms_isInitialized; }

void logger::profile(const std::string_view c_data) noexcept {
  if (!ms_isInitialized || !ms_profileMutexUPtr) {
    return;
  }

  const std::lock_guard<std::mutex> c_lock{*ms_profileMutexUPtr};
  *ms_profileStreamUPtr << c_data;
}

void logger::log(const std::string_view c_data) noexcept {
  if (!ms_isInitialized || !ms_logMutexUPtr) {
    return;
  }

  const std::lock_guard<std::mutex> c_lock{*ms_logMutexUPtr};
  *ms_logStreamUPtr << c_data;
}

void logger::async(const std::string_view c_data) noexcept {
  if (!ms_isInitialized || !ms_asyncMutexUPtr) {
    return;
  }

  const std::lock_guard<std::mutex> c_lock{*ms_asyncMutexUPtr};
  *ms_asyncStreamUPtr << c_data;
}

}  // namespace library
}  // namespace pack
