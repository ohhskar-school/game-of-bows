#include "MovableEntity.hpp"

// Setters and Getters
void MovableEntity::setVelocity(sf::Vector2f velocity) { _velocity = velocity; }

void MovableEntity::setVelocity(float vx, float vy) {
  _velocity.x = vx;
  _velocity.y = vy;
}

void MovableEntity::setVelocity(float v, bool direction) {
  // True = x; False = y
  if (direction) {
    _velocity.x = v;
  } else {
    _velocity.y = v;
  }
}

sf::Vector2f MovableEntity::getVelocity() const { return _velocity; }

unsigned int MovableEntity::getCategory() const { return Category::Collidable; }

sf::FloatRect MovableEntity::getBoundRect() const { return sf::FloatRect(); }

void MovableEntity::updateCurrent(sf::Time dt) {
  move(_velocity * dt.asSeconds());
  _velocity.y += 98.f * dt.asSeconds();
}