#include "Character.hpp"

Character::Character(Arch arch, unsigned int playerNumber, const TextureHolder& textures)
    : _archetype(arch), _sprite(textures.get(toTextureId(arch))), _hitbox(sf::Vector2f(32.f, 48.f)) {}

void Character::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const { target.draw(_sprite, states); }

unsigned int Character::getCategory() const {
  switch (_playerNumber) {
    case 1:
      return Category::PlayerOne | Category::Collidable;
    case 2:
      return Category::PlayerTwo | Category::Collidable;
    default:
      return Category::Collidable;
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