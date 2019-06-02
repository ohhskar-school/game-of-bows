#ifndef RC_CHARACTER
#define RC_CHARACTER

// User Created
#include "../ResourceManager.hpp"
#include "MovableEntity.hpp"

class Character : public MovableEntity {
 public:
  // Variable Declarations and Constructor
  enum Arch { Archer };
  explicit Character(Arch arch, unsigned int playerNumber, const TextureHolder& textures);

  // Draws
  virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

  // For Collisions and Actions
  unsigned int getCategory() const;
  virtual sf::FloatRect getBoundRect() const;

  //Collision Handling
  void handleWallCollision(sf::FloatRect wallBounds);

 private:
  // Variable Declarations
  unsigned int _playerNumber;
  Arch _archetype;
  sf::Sprite _sprite;
  sf::RectangleShape _hitbox;

  Textures::ID toTextureId(Character::Arch);
};
#endif