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
  _velocity.x += 400.f * dt.asSeconds();
}

void MovableEntity::addGravity(sf::Time dt) {
  if (true){
    _velocity.y += 350.f * dt.asSeconds();
  }
}

void MovableEntity::setCollidable(bool update) { _collidable = update; }

bool MovableEntity::getCollidable() const { return _collidable; }
