#include "SpriteEntity.hpp"

SpriteEntity::SpriteEntity(){};

SpriteEntity::SpriteEntity(const sf::Texture& texture) : _sprite(texture){};

SpriteEntity::SpriteEntity(const sf::Texture& texture, const sf::IntRect& textureRect)
    : _sprite(texture, textureRect) {}

unsigned int SpriteEntity::getCategory() const {
  // By default, sprite entities are not collidable
  return Category::None;
}

sf::FloatRect SpriteEntity::getBoundRect() const { return sf::FloatRect(); }

void SpriteEntity::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(_sprite, states);
}
