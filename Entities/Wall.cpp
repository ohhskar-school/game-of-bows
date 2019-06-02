#include "Wall.hpp"
#include <iostream>

Wall::Wall(Set spriteSet, Textures::WallSpecific& tile, sf::Vector2f position, const TextureHolder& textures)
    : _sprite(textures.get(getSpriteSheet(spriteSet)), getSpriteBounds(tile)), _position(position) {
  _sprite.setOrigin(sf::Vector2f(0.f, 0.f));
  _sprite.setPosition(position);
}

// Draws
void Wall::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(_sprite, states);
}

// Getters
unsigned int Wall::getCategory() const { return Category::Wall | Category::Collidable; }
sf::FloatRect Wall::getBoundRect() const { return getWorldTransform().transformRect(_sprite.getGlobalBounds()); }

// Texture Maps
Textures::ID Wall::getSpriteSheet(Wall::Set set) {
  switch (set) {
    case Wall::Set::Standard:
      return Textures::ID::WallStandard;
    default:
      return Textures::ID::WallStandard;
  }
}

unsigned int Wall::getCell() const {
  unsigned int cell = 0;
  if (_position.x <= 768 / 2) {
    cell = cell | 1 << 1;
  }

  if (_position.y <= 576 / 2) {
    cell = cell | 1 << 0;
  }

  return cell;
}

sf::IntRect Wall::getSpriteBounds(Textures::WallSpecific& id) {
  switch (id) {
    case Textures::WallSpecific::Floor:
      return sf::IntRect(0, 0, 32, 32);
    case Textures::WallSpecific::Cracked:
      return sf::IntRect(32, 0, 32, 32);
    case Textures::WallSpecific::Brick:
      return sf::IntRect(64, 0, 32, 32);
    case Textures::WallSpecific::Solid:
      return sf::IntRect(96, 0, 32, 32);
    case Textures::WallSpecific::ChunkOne:
      return sf::IntRect(0, 32, 32, 32);
    case Textures::WallSpecific::ChunkTwo:
      return sf::IntRect(32, 32, 32, 32);
    case Textures::WallSpecific::ChunkThree:
      return sf::IntRect(64, 32, 32, 32);
    case Textures::WallSpecific::ChunkFour:
      return sf::IntRect(96, 32, 32, 32);
    case Textures::WallSpecific::ChunkFive:
      return sf::IntRect(0, 64, 32, 32);
    case Textures::WallSpecific::ChunkSix:
      return sf::IntRect(32, 64, 32, 32);
    case Textures::WallSpecific::ChunkSeven:
      return sf::IntRect(64, 64, 32, 32);
    case Textures::WallSpecific::ChunkEight:
      return sf::IntRect(96, 64, 32, 32);
    case Textures::WallSpecific::ChunkNine:
      return sf::IntRect(0, 96, 32, 32);
    case Textures::WallSpecific::ChunkTen:
      return sf::IntRect(32, 96, 32, 32);
    case Textures::WallSpecific::ChunkEleven:
      return sf::IntRect(64, 96, 32, 32);
    case Textures::WallSpecific::ChunkTwelve:
      return sf::IntRect(96, 96, 32, 32);
    case Textures::WallSpecific::ChunkThirteen:
      return sf::IntRect(0, 128, 32, 32);
    case Textures::WallSpecific::ChunkFourteen:
      return sf::IntRect(32, 128, 32, 32);
    case Textures::WallSpecific::ChunkFifteen:
      return sf::IntRect(64, 128, 32, 32);
    case Textures::WallSpecific::ChunkSixteen:
      return sf::IntRect(96, 128, 32, 32);
    default:
      return sf::IntRect(0, 0, 32, 32);
  }
}