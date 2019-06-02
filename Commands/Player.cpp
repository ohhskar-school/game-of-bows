#include "Player.hpp"
#include <iostream>
struct MovePlayer {
  // Variable Declerations
  sf::Vector2f velocity;

  // Creating Constructor
  MovePlayer(float vx, float vy) : velocity(vx, vy) {}

  // Making the operator
  void operator()(Character& player, sf::Time) const { player.control(velocity); }
};

struct Halt {
  // Creating Constructor
  Halt() {}

  // Making the operator
  void operator()(Character& player, sf::Time) const { player.halt(); }
};

struct Aim {
  // Variable Declerations
  unsigned int _vert;
  unsigned int _hori;
  CommandQueue& passed;
  // Creating Constructor
  Aim(unsigned int v, unsigned int h, CommandQueue& commands) : _vert(v), _hori(h), passed(commands) {}

  // Making the operator
  void operator()(Character& player, sf::Time) const { player.aim(_vert, _hori, passed); }
};

Player::Player() : _vertical(0), _horizontal(0) {
  _keyBinding[sf::Keyboard::A] = MoveLeft;
  _keyBinding[sf::Keyboard::D] = MoveRight;
  _keyBinding[sf::Keyboard::W] = Jump;

  initializeActions();
  for (auto& pair : _actionBindingPress) {
    pair.second.category = Category::PlayerOne;
  }
  for (auto& pair : _actionBindingRelease) {
    pair.second.category = Category::PlayerOne;
  }
}

void Player::initializeActions() {
  _actionBindingPress[MoveLeft].action = derivedAction<Character>(MovePlayer(-250.f, 0.f));
  _actionBindingPress[MoveRight].action = derivedAction<Character>(MovePlayer(250.f, 0.f));
  _actionBindingPress[Jump].action = derivedAction<Character>(MovePlayer(0.f, -250.f));
  _actionBindingRelease[MoveLeft].action = derivedAction<Character>(Halt());
  _actionBindingRelease[MoveRight].action = derivedAction<Character>(Halt());
  _actionBindingRelease[Jump].action = derivedAction<Character>(MovePlayer(0.f, 0.f));
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands) {
  if (event.type == sf::Event::KeyPressed) {
    // Check if Aiming Keys are Pressed
    if (event.key.code == sf::Keyboard::Up) {
      _vertical = 1;
    } else if (event.key.code == sf::Keyboard::Down) {
      _vertical = 2;
    }

    if (event.key.code == sf::Keyboard::Left) {
      _horizontal = 1;
    } else if (event.key.code == sf::Keyboard::Right) {
      _horizontal = 2;
    }

    // Check if pressed key appears in key binding, trigger command if so
    auto found = _keyBinding.find(event.key.code);
    if (found != _keyBinding.end() && !isRealtimeAction(found->second)) {
      commands.push(_actionBindingPress[found->second]);
    }
  }

  if (event.type == sf::Event::KeyReleased) {
    if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down) {
      _vertical = 0;
    } else if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right) {
      _horizontal = 0;
    } else {
      auto found = _keyBinding.find(event.key.code);
      if (found != _keyBinding.end() && !isRealtimeAction(found->second)) {
        commands.push(_actionBindingRelease[found->second]);
      }
    }
  }

  // Handle Aiming
  Command aim;
  aim.category = Category::PlayerOne;
  aim.action = derivedAction<Character>(Aim(_vertical, _horizontal, commands));
  commands.push(aim);
}

void Player::handleRealtimeInput(CommandQueue& commands) {
  for (auto& pair : _keyBinding) {
    if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second)) {
      commands.push(_actionBindingPress[pair.second]);
    }
  }
}

bool Player::isRealtimeAction(Action action) {
  switch (action) {
      // case MoveLeft:
      // case MoveRight:
      // case Jump:
      // return true;

    default:
      return false;
  }
}
