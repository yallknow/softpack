//#include "pack_library_eternal_actor.hpp"
//
//#include "pack_library_preprocessor.hpp"
//
//namespace pack {
//namespace library {
//
//eternal_actor::eternal_actor(
//    const std::shared_ptr<sf::RenderTarget>& c_renderSPtr,
//    const std::shared_ptr<sf::Shape>& c_shapeSPtr,
//    const sf::Vector2f& c_velocity) noexcept
//    : abstract::actor{c_renderSPtr, c_shapeSPtr, c_velocity} {
//  PACK_LIBRARY_LOG_FUNCTION_CALL();
//}
//
//eternal_actor::~eternal_actor() noexcept { PACK_LIBRARY_LOG_FUNCTION_CALL(); }
//
//eternal_actor::eternal_actor(eternal_actor&& otherRLink) noexcept
//    : abstract::actor(std::move(otherRLink)) {
//  PACK_LIBRARY_LOG_FUNCTION_CALL();
//}
//
//eternal_actor& eternal_actor::operator=(eternal_actor&& otherRLink) noexcept {
//  PACK_LIBRARY_LOG_FUNCTION_CALL();
//
//  abstract::actor::operator=(std::move(otherRLink));
//  return *this;
//}
//
//void eternal_actor::inner_tick(const float c_dt) const noexcept {
//  PACK_LIBRARY_LOG_FUNCTION_CALL();
//
//  const sf::Vector2f c_old{this->m_shapeSPtr->getPosition()};
//  const sf::Vector2 c_size{this->m_shapeSPtr->getGlobalBounds().getSize()};
//
//  if (c_old.x < ms_minPosition.x - c_size.x) {
//    this->m_shapeSPtr->setPosition(ms_maxPosition.x, c_old.y);
//  } else if (c_old.x > ms_maxPosition.x + c_size.x) {
//    this->m_shapeSPtr->setPosition(ms_minPosition.x, c_old.y);
//  } else if (c_old.y < ms_minPosition.y - c_size.y) {
//    this->m_shapeSPtr->setPosition(c_old.x, ms_maxPosition.y);
//  } else if (c_old.y > ms_maxPosition.y + c_size.y) {
//    this->m_shapeSPtr->setPosition(c_old.x, ms_minPosition.y);
//  }
//}
//
//}  // namespace library
//}  // namespace pack
