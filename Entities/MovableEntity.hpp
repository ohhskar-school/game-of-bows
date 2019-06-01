#ifndef RC_MOVABLEENTITY
#define RC_MOVABLEENTITY

#include "../SceneNode.hpp"

class MovableEntity : public SceneNode {
 public:
  // Velocity Setter and Getter
  void setVelocity(sf::Vector2f velocity);
  void setVelocity(float vx, float vy);
  void setVelocity(float v, bool direction);
  sf::Vector2f getVelocity() const;

  //Updates
  void updateCurrent(sf::Time dt);

  // For Collision
  unsigned int getCategory() const;
  virtual sf::FloatRect getBoundRect() const;

 private:
  sf::Vector2f _velocity;
};

#endif