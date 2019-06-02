#include "VisualArrow.hpp"
#include <iostream>

VisualArrow::VisualArrow(const sf::Texture& texture, const sf::IntRect& textureRect)
    : _sprite(texture, textureRect), _position(), _rotation() {}

// Draws
void VisualArrow::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const { target.draw(_sprite, states); }

void VisualArrow::aim(sf::Vector2f newPos, float newRotation) {
  _position = newPos;
  _rotation = newRotation;
  setPosition(_position);
  setRotation(_rotation);
}

// Getters
unsigned int VisualArrow::getCategory() const { return Category::VisualArrow; }