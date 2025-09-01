#pragma once

#ifndef PACK_LIBRARY_WANDER_BRAIN
#define PACK_LIBRARY_WANDER_BRAIN

#include "abstract/pack_library_abstract_brain.hpp"

namespace pack {
namespace library {

class wander_brain final : public abstract::brain {
 public:
  explicit wander_brain() noexcept;
  /*virtual*/ ~wander_brain() noexcept;

 public:
  explicit wander_brain(wander_brain&& otherRLink) noexcept;
  wander_brain& operator=(wander_brain&& otherRLink) noexcept;

 public:
  void tick() noexcept override;
};

}  // namespace library
}  // namespace pack

#endif  // !PACK_LIBRARY_WANDER_BRAIN
