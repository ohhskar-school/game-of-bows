#include "Projectile.hpp"
#include <iostream>
Projectile::Projectile(const TextureHolder& textures, float rotation, sf::Vector2f position)
    : _sprite(textures.get(Textures::ID::Arrow)), _targetDirection(position), _rotation(rotation), _grabbed(false) {
  sf::Vector2f velocity;
  switch (static_cast<int>(rotation)) {
    case 0:
      velocity.x = 300.f;
      velocity.y = 250.f;
      break;
    case 45:
      velocity.x = 300.f;
      velocity.y = 250.f;
      break;
    case -45:
      velocity.x = 300.f;
      velocity.y = -250.f;
      break;
    case 90:
      velocity.x = 0.f;
      velocity.y = 300.f;
      break;
    case -90:
      velocity.x = 0.f;
      velocity.y = -300.f;
      break;
    case 135:
      velocity.x = -300.f;
      velocity.y = 250.f;
      break;
    case 180:
      velocity.x = -300.f;
      velocity.y = 250.f;
      break;
    case 225:
      velocity.x = -300.f;
      velocity.y = 250.f;
      break;
    default:
      velocity.x = 0.f;
      velocity.y = 250.f;
      break;
  };

  setVelocity(velocity.x, velocity.y);
  setRotation(rotation);
  _initx = velocity.x;
}

// For Collision
sf::FloatRect Projectile::getBoundRect() const { return getWorldTransform().transformRect(_sprite.getGlobalBounds()); };
unsigned int Projectile::getCategory() const {
  unsigned int collidable =
      getCollidable() == true ? Category::Collidable : Category::Collidable | Category::IgnoreWallCollide;
  return Category::Arrow | collidable;
}

void Projectile::updateCurrent(sf::Time dt, CommandQueue& commands) {
  if (getCollidable()) {
    sf::Vector2f velocity = getVelocity();
    velocity.x += _initx / 8;
    float angle = _rotation * -velocity.y / 20000;

    if (_rotation == 45 || _rotation == 135 || _rotation == 90)
      setRotation((angle * 180.0 / M_PI) * -1);
    else
      setRotation(angle * 180.0 / M_PI);

    setVelocity(velocity);
    MovableEntity::updateCurrent(dt, commands);
  }
}
void Projectile::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const { target.draw(_sprite, states); }

// Collision Handling

void Projectile::handleWallCollision(sf::FloatRect wallBounds) {
  setVelocity(sf::Vector2f(0.f, 0.f));
  setCollidable(false);

  sf::FloatRect ownBounds = getBoundRect();

  float ownBottom = ownBounds.top + ownBounds.height;
  float wallBottom = wallBounds.top + wallBounds.height;
  float ownRight = ownBounds.left + ownBounds.width;
  float wallRight = wallBounds.left + wallBounds.width;

  float bot = wallBottom - ownBounds.top;
  float top = ownBottom - wallBounds.top;
  float left = ownRight - wallBounds.left;
  float right = wallRight - ownBounds.left;

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
}

void Projectile::handlePlayerCollision() {
  if (!getCollidable()) {
    _grabbed = true;
  }
}

bool Projectile::isDestroyed() const { return _grabbed; }