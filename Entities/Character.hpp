#ifndef RC_CHARACTER
#define RC_CHARACTER

// User Created
#include "../Animation.hpp"
#include "../Commands/CommandQueue.hpp"
#include "../ResourceManager.hpp"
#include "MovableEntity.hpp"
#include "Projectile.hpp"
#include "VisualArrow.hpp"

class Character : public MovableEntity {
 public:
  // Variable Declarations and Constructor
  enum Arch { Archer };
  explicit Character(Arch arch, unsigned int playerNumber, const TextureHolder& textures);

  // Actions
  Command setArrowAim;
  Command fireArrow;

  // Updates
  void updateCurrent(sf::Time dt, CommandQueue& commands);

  // Draws
  virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

  // For Collisions and Actions
  unsigned int getCategory() const;
  virtual sf::FloatRect getBoundRect() const;

  void aim(unsigned int y, unsigned int x, CommandQueue& commands);
  void fire();
  void createProjectile(SceneNode& node, const TextureHolder& textures) const;

  // Collision Handling
  void handleWallCollision(sf::FloatRect wallBounds);
  void handleArrowCollision(bool grabbable);

 private:
  // Variable Declarations
  enum _animationState {
    IdleRight,
    RunRight,
    JumpRight,
    DeathRight,
    IdleLeft,
    RunLeft,
    JumpLeft,
    DeathLeft,
  };
  unsigned int _playerNumber;
  Arch _archetype;
  sf::Sprite _sprite;
  sf::RectangleShape _hitbox;
  Animation _idleLeft;
  Animation _runLeft;
  Animation _jumpLeft;
  Animation _deathLeft;
  Animation _idleRight;
  Animation _runRight;
  Animation _jumpRight;
  Animation _deathRight;
  // Aiming & Arrow Values
  float _arrowRotation;
  sf::Vector2f _arrowPosition;
  unsigned int _arrowQuantity;
  bool _aiming;
  bool _firing;
  sf::Time _countdown;
  bool _dead;
  bool _right;

  void checkProjectileLaunch(sf::Time dt, CommandQueue& commands);
  void updateDirection();
  Textures::ID toTextureId(Character::Arch);
  Textures::ID toTextureIdAnim(_animationState state);
};
#endif