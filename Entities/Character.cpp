#include "Character.hpp"
#include <iostream>
Character::Character(Arch arch, unsigned int playerNumber, const TextureHolder& textures)
    : setArrowAim(),
      fireArrow(),
      _playerNumber(playerNumber),
      _archetype(arch),
      _sprite(textures.get(toTextureId(arch)), sf::IntRect(0, 0, 32, 32)),
      _hitbox(sf::Vector2f(40.f, 32.f)),
      _idleLeft(textures.get(toTextureIdAnim(Character::_animationState::IdleLeft))),
      _runLeft(textures.get(toTextureIdAnim(Character::_animationState::RunLeft))),
      _idleRight(textures.get(toTextureIdAnim(Character::_animationState::IdleRight))),
      _runRight(textures.get(toTextureIdAnim(Character::_animationState::RunRight))),
      _arrowRotation(0.f),
      _arrowPosition(sf::Vector2f(0.f, 0.f)),
      _arrowQuantity(4),
      _aiming(false),
      _firing(false),
      _countdown(sf::Time::Zero),
      _dead(false),
      _right(true) {
  setCollidable(true);
  sf::FloatRect bounds = _hitbox.getLocalBounds();

  // Creating Actions

  switch (_playerNumber) {
    case 1:
      setArrowAim.category = Category::VisualArrowOne;
      break;
    case 2:
      setArrowAim.category = Category::VisualArrowTwo;
      break;
    default:
      setArrowAim.category = Category::VisualArrowOne;
      break;
  }
  setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
  fireArrow.category = Category::ArrowHolder;
  fireArrow.action = [this, &textures](SceneNode& node, sf::Time) { createProjectile(node, textures); };

  // Creating Animations
  _idleRight.setFrameSize(sf::Vector2i(48, 32));
  _idleRight.setNumFrames(8);
  _idleRight.setDuration(sf::seconds(1));
  _idleRight.setRepeating(true);

  _runRight.setFrameSize(sf::Vector2i(48, 32));
  _runRight.setNumFrames(8);
  _runRight.setDuration(sf::seconds(0.5));
  _runRight.setRepeating(true);

  _idleLeft.setFrameSize(sf::Vector2i(48, 32));
  _idleLeft.setNumFrames(8);
  _idleLeft.setDuration(sf::seconds(1));
  _idleLeft.setRepeating(true);

  _runLeft.setFrameSize(sf::Vector2i(48, 32));
  _runLeft.setNumFrames(8);
  _runLeft.setDuration(sf::seconds(0.5));
  _runLeft.setRepeating(true);
}

// Draws and Updates

void Character::updateDirection() {
  if (getMoving() == 1) {
    setCollidable(true);
    _right = false;
    _running = true;
  } else if (getMoving() == 2) {
    setCollidable(true);
    _right = true;
    _running = true;
  } else {
    _running = false;
  }
  
  if (getJumping()) {
    _jumping = true;
  }
}

void Character::updateCurrent(sf::Time dt, CommandQueue& commands) {
  updateDirection();
  if (_right) {
    if (_running) {
      _runRight.update(dt);
    } else {
      _idleRight.update(dt);
    }
  } else {
    if (_running) {
      _runLeft.update(dt);
    } else {
      _idleLeft.update(dt);
    }
  }
  checkProjectileLaunch(dt, commands);
  MovableEntity::updateCurrent(dt, commands);
}

void Character::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
  if (_right) {
    if (_running) {
      target.draw(_runRight, states);
    } else {
      target.draw(_idleRight, states);
    }
  } else {
    if (_running) {
      target.draw(_runLeft, states);
    } else {
      target.draw(_idleLeft, states);
    }
  }

  // target.draw(_hitbox, states);
}

unsigned int Character::getCategory() const {
  unsigned int collidable =
      getCollidable() == true ? Category::Collidable : Category::Collidable | Category::IgnoreWallCollide;

  unsigned int dead = _dead ? Category::Dead : Category::None;
  switch (_playerNumber) {
    case 1:
      return (Category::PlayerOne | collidable | dead);
    case 2:
      return (Category::PlayerTwo | collidable | dead);
    default:
      return (Category::PlayerOne | collidable | dead);
  }
}

sf::FloatRect Character::getBoundRect() const { return getWorldTransform().transformRect(_hitbox.getGlobalBounds()); }

// Texture Maps
Textures::ID Character::toTextureId(Character::Arch arch) {
  switch (arch) {
    case Character::Arch::Archer:
      return Textures::BlueIdleRight;
    default:
      return Textures::BlueIdleRight;
  }
}

Textures::ID Character::toTextureIdAnim(Character::_animationState state) {
  switch (_playerNumber) {
    case 1:
      switch (state) {
        case IdleRight:
          return Textures::ID::BlueIdleRight;
        case RunRight:
          return Textures::ID::BlueRunRight;
        case IdleLeft:
          return Textures::ID::BlueIdleLeft;
        case RunLeft:
          return Textures::ID::BlueRunLeft;
        default:
          return Textures::ID::BlueIdleRight;
      }
    case 2:
    default:
      switch (state) {
        case IdleRight:
          return Textures::ID::PinkIdleRight;
        case RunRight:
          return Textures::ID::PinkRunRight;
        case IdleLeft:
          return Textures::ID::PinkIdleLeft;
        case RunLeft:
          return Textures::ID::PinkRunLeft;
        default:
          return Textures::ID::PinkIdleRight;
      }
  }
}

// Collision Handling

void Character::handleWallCollision(sf::FloatRect wallBounds) {
  sf::FloatRect ownBounds = getBoundRect();

  float ownBottom = ownBounds.top + ownBounds.height;
  float wallBottom = wallBounds.top + wallBounds.height;
  float ownRight = ownBounds.left + ownBounds.width;
  float wallRight = wallBounds.left + wallBounds.width;

  float bot = wallBottom - ownBounds.top;
  float top = ownBottom - wallBounds.top;
  float left = ownRight - wallBounds.left;
  float right = wallRight - ownBounds.left;
  if (top < bot && top < left && top < right) {
    move(sf::Vector2f(0.f, -top));
    setCollidable(false);
    setJumping(false);
    setVelocity(0.f, false);
  } else if (bot < top && bot < left && bot < right) {
    move(sf::Vector2f(0.f, bot));
    setVelocity(0.f, false);
  } else if (left < right && left < top && left < bot) {
    move(sf::Vector2f(-left, 0.f));

  } else if (right < left && right < top && right < bot) {
    move(sf::Vector2f(right, 0.f));
  }

  // https://stackoverflow.com/questions/5062833/detecting-the-direction-of-a-collision
}

void Character::handleArrowCollision(bool grabbable) {
  if (grabbable) {
    _arrowQuantity++;
  } else {
    _dead = true;
  }
}

// Actions

struct AimArrow {
  // Variable Declerations
  sf::Vector2f position;
  float rotation;

  // Creating Constructor
  AimArrow(sf::Vector2f newPos, float newRot) : position(newPos), rotation(newRot) {}

  // Making the operator
  void operator()(VisualArrow& arrow, sf::Time) const { arrow.aim(position, rotation); }
};

void Character::aim(unsigned int y, unsigned int x, CommandQueue& commands) {
  _aiming = true;
  _arrowRotation = 0.f;
  if (_arrowQuantity > 0) {
    if (x == 1) {
      if (y == 2) {
        _arrowRotation = 135.f;
        _arrowPosition.x = -1.f;
        _arrowPosition.y = 43.f;
      } else if (y == 1) {
        _aiming = true;
        _arrowRotation = 225.f;
        _arrowPosition.x = -8.f;
        _arrowPosition.y = 0.f;
      } else {
        _arrowRotation = 180.f;
        _arrowPosition.x = -5.f;
        _arrowPosition.y = 25.f;
      }
    } else if (x == 2) {
      if (y == 2) {
        _arrowRotation = 45.f;
        _arrowPosition.x = 50.f;
        _arrowPosition.y = 35.f;
      } else if (y == 1) {
        _arrowRotation = -45.f;
        _arrowPosition.x = 40.f;
        _arrowPosition.y = -12.f;
      } else {
        _arrowPosition.x = 55.f;
        _arrowPosition.y = 13.f;
      }
    } else if (x == 0) {
      if (y == 2) {
        _arrowRotation = 90.f;
        _arrowPosition.x = 29.f;
        _arrowPosition.y = 45.f;

      } else if (y == 1) {
        _arrowRotation = -90.f;
        _arrowPosition.x = 15.f;
        _arrowPosition.y = -7.f;
      } else {
        _aiming = false;
        _arrowPosition.x = -1000.f;
        _arrowPosition.y = -1000.f;
      }
    }
  } else {
    _aiming = false;
    _arrowPosition.x = -1000.f;
    _arrowPosition.y = -1000.f;
  }
  // Creating the command
  setArrowAim.action = derivedAction<VisualArrow>(AimArrow(_arrowPosition, _arrowRotation));
  commands.push(setArrowAim);
}

void Character::createProjectile(SceneNode& node, const TextureHolder& textures) const {
  std::unique_ptr<Projectile> projectile(new Projectile(textures, _arrowRotation, _arrowPosition));

  sf::Vector2f finalOffset(getBoundRect().left + _arrowPosition.x, getBoundRect().top + _arrowPosition.y);

  projectile->setPosition(finalOffset);
  node.attachChild(std::move(projectile));
}

void Character::fire() {
  if (_aiming && _arrowQuantity > 0) {
    _firing = true;
  } else {
    _firing = false;
  }
}

void Character::checkProjectileLaunch(sf::Time dt, CommandQueue& commands) {
  if (_firing && _countdown <= sf::Time::Zero) {
    commands.push(fireArrow);
    _countdown += sf::seconds(1.f / 10.f);
    _firing = false;
    _arrowQuantity--;
  } else if (_countdown > sf::Time::Zero) {
    _countdown -= dt;
  }
}