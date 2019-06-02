#ifndef RC_ARROWHOLDER
#define RC_ARROWHOLDER

#include <SFML/Graphics/Sprite.hpp>
#include "../SceneNode.hpp"
#include "Categories.hpp"

class ArrowHolder : public SceneNode {
 public:
  // For Collision
  unsigned int getCategory() const;
};

#endif