#pragma once

#ifndef _PACK_CLIENT_APP_
#define _PACK_CLIENT_APP_

namespace pack {
namespace client {

class app {
 public:
  explicit app() noexcept;
  virtual ~app() noexcept;

 public:
  bool mf_start() noexcept;
};

}  // namespace client
}  // namespace pack

#endif  // !_PACK_CLIENT_APP_
