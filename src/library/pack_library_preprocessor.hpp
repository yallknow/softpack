#pragma once

#ifndef PACK_LIBRARY_PREPROCESSOR
#define PACK_LIBRARY_PREPROCESSOR

#ifndef PACK_LIBRARY_PROFILING_ENABLED
#define PACK_LIBRARY_PROFILING_ENABLED 1
#endif  // !PACK_LIBRARY_PROFILING_ENABLED

#ifndef PACK_LIBRARY_LOGGING_ENABLED
#define PACK_LIBRARY_LOGGING_ENABLED 1
#endif  // !PACK_LIBRARY_LOGGING_ENABLED

#ifndef PACK_LIBRARY_ASYNC_LOGGING_ENABLED
#define PACK_LIBRARY_ASYNC_LOGGING_ENABLED 1
#endif  // !PACK_LIBRARY_ASYNC_LOGGING_ENABLED

#if PACK_LIBRARY_PROFILING_ENABLED || PACK_LIBRARY_LOGGING_ENABLED || \
    PACK_LIBRARY_ASYNC_LOGGING_ENABLED

#ifndef __FUNCSIG__
#define __FUNCSIG__ __PRETTY_FUNCTION__
#endif  //!__FUNCSIG__

#endif  // PACK_LIBRARY_PROFILING_ENABLED || PACK_LIBRARY_LOGGING_ENABLED || \
        // PACK_LIBRARY_ASYNC_LOGGING_ENABLED

#if PACK_LIBRARY_PROFILING_ENABLED

#include "pack_library_scope_profiler.hpp"

#define PACK_LIBRARY_PROFILE_FUNCTION() \
  const pack::library::scope_profiler c_profiler(__FUNCSIG__)

#else

#define PACK_LIBRARY_PROFILE_FUNCTION()

#endif  // PACK_LIBRARY_PROFILING_ENABLED

#if PACK_LIBRARY_LOGGING_ENABLED || PACK_LIBRARY_ASYNC_LOGGING_ENABLED

#include <boost/system/error_code.hpp>

#include <string_view>

#include "pack_library_log_builder.hpp"

static constexpr std::string_view gsc_errorTag{"ERROR"};
static constexpr std::string_view gsc_infoTag{"INFO"};
static constexpr std::string_view gsc_warningTag{"WARNING"};

#endif  // PACK_LIBRARY_LOGGING_ENABLED || PACK_LIBRARY_ASYNC_LOGGING_ENABLED

#if PACK_LIBRARY_LOGGING_ENABLED

#if PACK_LIBRARY_PROFILING_ENABLED

#define PACK_LIBRARY_LOG_FUNCTION_CALL()                   \
  const pack::library::log_builder c_builder(__FUNCSIG__); \
  PACK_LIBRARY_PROFILE_FUNCTION()

#else

#define PACK_LIBRARY_LOG_FUNCTION_CALL() \
  const pack::library::log_builder c_builder(__FUNCSIG__)

#endif  // PACK_LIBRARY_PROFILING_ENABLED

#define PACK_LIBRARY_LOG_ERROR(c_message)                  \
  pack::library::log_builder::log(gsc_errorTag, c_message, \
                                  boost::system::error_code{})

#define _PACK_LIBRARY_LOG_ERROR_CODE(c_message, c_errorCode) \
  pack::library::log_builder::log(gsc_errorTag, c_message, c_errorCode)

#define PACK_LIBRARY_LOG_INFO(c_message)                  \
  pack::library::log_builder::log(gsc_infoTag, c_message, \
                                  boost::system::error_code{})

#define PACK_LIBRARY_LOG_WARNING(c_message)                  \
  pack::library::log_builder::log(gsc_warningTag, c_message, \
                                  boost::system::error_code{})

#else

#if PACK_LIBRARY_PROFILING_ENABLED

#define PACK_LIBRARY_LOG_FUNCTION_CALL() PACK_LIBRARY_PROFILE_FUNCTION()

#else

#define PACK_LIBRARY_LOG_FUNCTION_CALL()

#endif  // PACK_LIBRARY_PROFILING_ENABLED

#define PACK_LIBRARY_LOG_ERROR(c_message)
#define PACK_LIBRARY_LOG_ERROR_CODE(c_message, c_errorCode)
#define PACK_LIBRARY_LOG_INFO(c_message)
#define PACK_LIBRARY_LOG_WARNING(c_message)

#endif  // PACK_LIBRARY_LOGGING_ENABLED

#if PACK_LIBRARY_ASYNC_LOGGING_ENABLED

#if PACK_LIBRARY_PROFILING_ENABLED

#define PACK_LIBRARY_ASYNC_LOG_FUNCTION_CALL()                    \
  pack::library::log_builder::async(gsc_infoTag, __FUNCSIG__,     \
                                    boost::system::error_code{}); \
  PACK_LIBRARY_PROFILE_FUNCTION()

#else

#define PACK_LIBRARY_ASYNC_LOG_FUNCTION_CALL()                \
  pack::library::log_builder::async(gsc_infoTag, __FUNCSIG__, \
                                    boost::system::error_code{})

#endif  // PACK_LIBRARY_PROFILING_ENABLED

#define PACK_LIBRARY_ASYNC_LOG_ERROR(c_message)                   \
  pack::library::log_builder::async(                              \
      gsc_ErrorTag, std::string{__FUNCSIG__} + " : " + c_message, \
      boost::system::error_code{})

#define PACK_LIBRARY_ASYNC_LOG_ERROR_CODE(c_message, c_errorCode) \
  pack::library::log_builder::async(                              \
      gsc_ErrorTag, std::string{__FUNCSIG__} + " : " + c_message, c_errorCode)

#define PACK_LIBRARY_ASYNC_LOG_INFO(c_message)                   \
  pack::library::log_builder::async(                             \
      gsc_InfoTag, std::string{__FUNCSIG__} + " : " + c_message, \
      boost::system::error_code{})

#define PACK_LIBRARY_ASYNC_LOG_WARNING(c_message)                   \
  pack::library::log_builder::async(                                \
      gsc_WarningTag, std::string{__FUNCSIG__} + " : " + c_message, \
      boost::system::error_code{})

#else

#if PACK_LIBRARY_PROFILING_ENABLED

#define PACK_LIBRARY_ASYNC_LOG_FUNCTION_CALL() PACK_LIBRARY_PROFILE_FUNCTION()

#else

#define PACK_LIBRARY_ASYNC_LOG_FUNCTION_CALL()

#endif  // PACK_LIBRARY_PROFILING_ENABLED

#define PACK_LIBRARY_ASYNC_LOG_ERROR(c_message)
#define PACK_LIBRARY_ASYNC_LOG_ERROR_CODE(c_message, c_errorCode)
#define PACK_LIBRARY_ASYNC_LOG_INFO(c_message)
#define PACK_LIBRARY_ASYNC_LOG_WARNING(c_message)

#endif  // PACK_LIBRARY_ASYNC_LOGGING_ENABLED

#endif  // !PACK_LIBRARY_PREPROCESSOR
