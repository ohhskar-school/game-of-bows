#ifndef RC_SPRITEENTITY
#define RC_SPRITEENTITY

#include <SFML/Graphics/Sprite.hpp>
#include "../SceneNode.hpp"
#include "Categories.hpp"

class SpriteEntity : public SceneNode {
 public:
  //Draws
  
  // For Collision
  unsigned int getCategory() const;
  virtual sf::FloatRect getBoundRect() const;

 private:
  sf::Sprite _sprite;
};

#endif