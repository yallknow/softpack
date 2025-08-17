#include "pack_library_logger.hpp"

#include <filesystem>
#include <system_error>
#include <thread>

#include "pack_library_time.hpp"

std::atomic<bool> pack::library::logger::msv_IsInitialized{false};

std::string pack::library::logger::msv_LogDirectory{"log/"};

std::unique_ptr<std::ofstream> pack::library::logger::msp_ProfileStream{
    nullptr};
std::unique_ptr<std::ofstream> pack::library::logger::msp_LogStream{nullptr};
std::unique_ptr<std::ofstream> pack::library::logger::msp_AsyncLogStream{
    nullptr};

std::unique_ptr<std::mutex> pack::library::logger::msp_ProfileStreamMutex{
    nullptr};
std::unique_ptr<std::mutex> pack::library::logger::msp_LogStreamMutex{nullptr};
std::unique_ptr<std::mutex> pack::library::logger::msp_AsyncLogStreamMutex{
    nullptr};

void pack::library::logger::msf_init() noexcept {
  if (msv_IsInitialized) {
    return;
  }

  std::error_code lv_ErrorCode{};

  if (!std::filesystem::exists(msv_LogDirectory, lv_ErrorCode)) {
    std::filesystem::create_directories(msv_LogDirectory, lv_ErrorCode);

    if (lv_ErrorCode) {
      return;
    }
  }

  const std::string lc_Extension{".json"};
  const std::string lc_TimeNow{time::msf_now_underscore()};

  msp_ProfileStream.reset(new (std::nothrow) std::ofstream{
      std::string{msv_LogDirectory + '/' + lc_TimeNow +
                  msc_ProfileFilenamePostfix.data() + lc_Extension},
      std::ofstream::trunc});

  msp_LogStream.reset(new (std::nothrow) std::ofstream{
      std::string{msv_LogDirectory + '/' + lc_TimeNow +
                  msc_LogFilenamePostfix.data() + lc_Extension},
      std::ofstream::trunc});

  msp_AsyncLogStream.reset(new (std::nothrow) std::ofstream{
      std::string{msv_LogDirectory + '/' + lc_TimeNow +
                  msc_AsyncLogFilenamePostfix.data() + lc_Extension},
      std::ofstream::trunc});

  msp_ProfileStreamMutex.reset(new (std::nothrow) std::mutex{});
  msp_LogStreamMutex.reset(new (std::nothrow) std::mutex{});
  msp_AsyncLogStreamMutex.reset(new (std::nothrow) std::mutex{});

  if (!msp_ProfileStream || !msp_ProfileStream->is_open() || !msp_LogStream ||
      !msp_LogStream->is_open() || !msp_AsyncLogStream ||
      !msp_AsyncLogStream->is_open() || !msp_ProfileStreamMutex ||
      !msp_LogStreamMutex || !msp_AsyncLogStreamMutex) {
    return;
  }

  msv_IsInitialized = true;
}

void pack::library::logger::msf_destroy() noexcept {
  if (!msv_IsInitialized) {
    return;
  }

  msp_ProfileStream->close();
  msp_ProfileStream.reset();

  msp_LogStream->close();
  msp_LogStream.reset();

  msp_AsyncLogStream->close();
  msp_AsyncLogStream.reset();

  msp_ProfileStreamMutex.reset();
  msp_LogStreamMutex.reset();
  msp_AsyncLogStreamMutex.reset();

  msv_IsInitialized = false;
}

bool pack::library::logger::msf_is_initialized() noexcept {
  return msv_IsInitialized;
}

void pack::library::logger::msf_profile(
    const std::string_view pc_Data) noexcept {
  if (!msv_IsInitialized) {
    return;
  }

  const std::lock_guard<std::mutex> lc_ProfileStreamLock{
      *msp_ProfileStreamMutex};
  *msp_ProfileStream << pc_Data;
}

void pack::library::logger::msf_log(const std::string_view pc_Data) noexcept {
  if (!msv_IsInitialized) {
    return;
  }

  const std::lock_guard<std::mutex> lc_LogStreamLock{*msp_LogStreamMutex};
  *msp_LogStream << pc_Data;
}

void pack::library::logger::msf_async_log(
    const std::string_view pc_Data) noexcept {
  if (!msv_IsInitialized) {
    return;
  }

  const std::lock_guard<std::mutex> lc_AsyncLogStreamLock{
      *msp_AsyncLogStreamMutex};
  *msp_AsyncLogStream << pc_Data;
}

void pack::library::logger::msf_set_log_directory(
    const std::string_view pc_LogDirectory) noexcept {
  msv_LogDirectory = pc_LogDirectory;
}

std::string pack::library::logger::msf_get_pid() noexcept {
  return std::to_string(
      std::hash<std::thread::id>{}(std::this_thread::get_id()));
}
