#include "SpriteEntity.hpp"

unsigned int SpriteEntity::getCategory() const {
  // By default, sprite entities are not collidable
  return Category::None;
}

sf::FloatRect SpriteEntity::getBoundRect() const { return sf::FloatRect(); }
