#ifndef RC_CHARACTER
#define RC_CHARACTER

// User Created
#include "../ResourceManager.hpp"
#include "MovableEntity.hpp"
#include "VisualArrow.hpp"
#include "../Commands/CommandQueue.hpp"

class Character : public MovableEntity {
 public:
  // Variable Declarations and Constructor
  enum Arch { Archer };
  explicit Character(Arch arch, unsigned int playerNumber, const TextureHolder& textures);

  // Actions
  Command setArrowAim;
  Command fireArrow;

  // Draws
  virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

  // For Collisions and Actions
  unsigned int getCategory() const;
  virtual sf::FloatRect getBoundRect() const;

  void aim(unsigned int y, unsigned int x, CommandQueue& commands);
  // Collision Handling
  void handleWallCollision(sf::FloatRect wallBounds);

 private:
  // Variable Declarations
  unsigned int _playerNumber;
  Arch _archetype;
  sf::Sprite _sprite;
  sf::RectangleShape _hitbox;

  // Aiming & Arrow Values
  float _arrowRotation;
  sf::Vector2f _arrowPosition;
  unsigned int _arrowQuantity;
  bool _aiming;

  Textures::ID toTextureId(Character::Arch);
};
#endif