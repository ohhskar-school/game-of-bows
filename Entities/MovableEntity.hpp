#ifndef RC_MOVABLEENTITY
#define RC_MOVABLEENTITY

#include "../SceneNode.hpp"

class MovableEntity : public SceneNode {
 public:
  // Velocity Setter and Getter
  MovableEntity();
  void setVelocity(sf::Vector2f velocity);
  void setVelocity(float vx, float vy);
  void setVelocity(float v, bool direction);
  void addGravity(sf::Time dt);
  void changeVelocity(sf::Vector2f change);
  sf::Vector2f getVelocity() const;

  // Updates
  void updateCurrent(sf::Time dt, CommandQueue& commands);

  // For Collision
  unsigned int getCategory() const;
  virtual sf::FloatRect getBoundRect() const;
  void setCollidable(bool update);
  bool getCollidable() const;

  // Actions
  void setJumping(bool update);
  bool getJumping() const;
  unsigned int getMoving() const;
  void control(sf::Vector2f change);
  void halt();

 private:
  sf::Vector2f _velocity;
  bool _collidable;
  bool _jumping;
  unsigned int _moving;
};

#endif
