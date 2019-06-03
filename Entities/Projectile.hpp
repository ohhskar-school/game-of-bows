#ifndef RC_PROJECTILES
#define RC_PROJECTILES

#include "../ResourceManager.hpp"
#include "MovableEntity.hpp"
#include <cmath>

class Projectile : public MovableEntity {
 public:
  Projectile(const TextureHolder& textures, float rotation, sf::Vector2f position);

  // For Collision
  virtual sf::FloatRect getBoundRect() const;
  virtual unsigned int getCategory() const;
  void handleWallCollision(sf::FloatRect wallBounds);
  void handlePlayerCollision();
  bool isDestroyed() const;

 private:
  sf::Sprite _sprite;
  sf::Vector2f _targetDirection;
  float _rotation;
  float _initx;
  bool _grabbed;

  // Draws and Updates
  virtual void updateCurrent(sf::Time dt, CommandQueue& commands);
  virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif