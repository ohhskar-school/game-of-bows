#include "VisualArrow.hpp"
#include <iostream>

VisualArrow::VisualArrow(const sf::Texture& texture, unsigned int playerNumber)
    : _sprite(texture), _position(), _rotation(), _playerNumber(playerNumber) {}

// Draws
void VisualArrow::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const { target.draw(_sprite, states); }

void VisualArrow::aim(sf::Vector2f newPos, float newRotation) {
  _position = newPos;
  _rotation = newRotation;
  setPosition(_position);
  setRotation(_rotation);
}

// Getters
unsigned int VisualArrow::getCategory() const {
  unsigned int category = Category::VisualArrow;
  switch (_playerNumber) {
    case 1:
      category = Category::VisualArrowOne;
      break;
    case 2:
      category = Category::VisualArrowTwo;
      break;
    default:
      category = Category::VisualArrowOne;
      break;
  }
  return category;
}