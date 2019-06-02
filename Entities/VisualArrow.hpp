#ifndef RC_VISUALARROW
#define RC_VISUALARROW

#include "../ResourceManager.hpp"
#include "SpriteEntity.hpp"

class VisualArrow : public SpriteEntity {
 public:
  enum Set { Standard };
  explicit VisualArrow(const sf::Texture& texture, const sf::IntRect& textureRect);

  // Draws
  void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

  // For Actions
  unsigned int getCategory() const;
  void aim(sf::Vector2f newPos, float newRotation);

 private:
  sf::Sprite _sprite;
  sf::Vector2f _position;
  float _rotation;
};
#endif