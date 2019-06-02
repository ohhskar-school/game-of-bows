#include "MovableEntity.hpp"
#include <iostream>

MovableEntity::MovableEntity() : _collidable(true) {}
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
  addGravity(dt);
}

void MovableEntity::addGravity(sf::Time dt) {
  if (_collidable) {
    _velocity.y += 500.f * dt.asSeconds();
  }
}

void MovableEntity::setCollidable(bool update) { _collidable = update; }

bool MovableEntity::getCollidable() const { return _collidable; }

// Actions

void MovableEntity::control(sf::Vector2f change) {
  _velocity += change;
  if (_velocity.x > 240.f) {
    _velocity.x = 240.f;
  }
  if (_velocity.x < -240.f) {
    _velocity.x = -240.f;
  }
  if (_velocity.y <= -250.f) {
    _velocity.y = -250.f;
  }
  _collidable = true;
}

void MovableEntity::halt() {
  _velocity.x = 0.f;
  _collidable = true;
}