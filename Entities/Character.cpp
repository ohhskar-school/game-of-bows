#include "Character.hpp"
#include <iostream>
Character::Character(Arch arch, unsigned int playerNumber, const TextureHolder& textures)
    : _archetype(arch), _sprite(textures.get(toTextureId(arch))), _hitbox(sf::Vector2f(32.f, 48.f)) {}

void Character::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const { target.draw(_sprite, states); }

unsigned int Character::getCategory() const {
  unsigned int collidable = true ? Category::Collidable : Category::Collidable | Category::IgnoreWallCollide;
  switch (_playerNumber) {
    case 1:
      return (Category::PlayerOne | collidable);
    case 2:
      return (Category::PlayerTwo | collidable);
    default:
      return (Category::PlayerOne | collidable);
  }
}

sf::FloatRect Character::getBoundRect() const { return getWorldTransform().transformRect(_hitbox.getGlobalBounds()); }

// Texture Maps
Textures::ID Character::toTextureId(Character::Arch arch) {
  switch (arch) {
    case Character::Arch::Archer:
      return Textures::Player;
    default:
      return Textures::Player;
  }
}

// Collision Handling

void Character::handleWallCollision(sf::FloatRect wallBounds) {
  sf::FloatRect ownBounds = getBoundRect();

  float ownBottom = ownBounds.top + ownBounds.height;
  float wallBottom = wallBounds.top + wallBounds.height;
  float ownRight = ownBounds.left + ownBounds.width;
  float wallRight = wallBounds.left + wallBounds.width;

  float bot = wallBottom - ownBounds.top;
  float top = ownBottom - wallBounds.top;
  float left = ownRight - wallBounds.left;
  float right = wallRight - ownBounds.left;
  setVelocity(0.f, 0.f);
  if (top < bot && top < left && top < right) {
    move(sf::Vector2f(0.f, -top));
  } else if (bot < top && bot < left && bot < right) {
    move(sf::Vector2f(0.f, bot));
    // disables wall collisions;
  } else if (left < right && left < top && left < bot) {
    move(sf::Vector2f(-left, 0.f));
  } else if (right < left && right < top && right < bot) {
    move(sf::Vector2f(right, 0.f));
  }
  setCollidable(false);

  // https://stackoverflow.com/questions/5062833/detecting-the-direction-of-a-collision
}