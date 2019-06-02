#include "Projectile.hpp"

Projectile::Projectile(const TextureHolder& textures, float rotation, sf::Vector2f position)
    : _sprite(textures.get(Textures::ID::Arrow)), _rotation(rotation), _targetDirection(position) {
  sf::Vector2f velocity;

  switch (static_cast<int>(rotation)) {
    case 0:
    case 45:
    case -45:
      velocity.x = 300.f;
      break;
    case 90:
    case 180:
      velocity.x = 0.f;
      break;
    case 135:
    case 225:
      velocity.x = -300.f;
      break;
    default:
      velocity.x = 0.f;
      break;
  };

  setVelocity(velocity.x, -250.f);
  setRotation(rotation);
  _initx = velocity.x;
}

// For Collision
sf::FloatRect Projectile::getBoundRect() const { return getWorldTransform().transformRect(_sprite.getGlobalBounds()); };
unsigned int Projectile::getCategory() const { return Category::Arrow | Category::Collidable; }

void Projectile::updateCurrent(sf::Time dt) {
  sf::Vector2f velocity = getVelocity();
  velocity.x += _initx / 5;
  float angle = _rotation * -velocity.y / 20000;

  setRotation(angle * 180.0 / M_PI);
  setVelocity(velocity);
  MovableEntity::updateCurrent(dt);
}
void Projectile::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const { target.draw(_sprite, states); }
