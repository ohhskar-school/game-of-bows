#ifndef RC_SPRITEENTITY
#define RC_SPRITEENTITY

#include <SFML/Graphics/Sprite.hpp>
#include "../SceneNode.hpp"
#include "Categories.hpp"

class SpriteEntity : public SceneNode {
 public:
  // Constructor
  SpriteEntity();
  SpriteEntity(const sf::Texture& texture);
  SpriteEntity(const sf::Texture& texture, const sf::IntRect& textureRect);
  // Draws
  void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

  // For Collision
  unsigned int getCategory() const;
  virtual sf::FloatRect getBoundRect() const;

 private:
  sf::Sprite _sprite;
};

#endif