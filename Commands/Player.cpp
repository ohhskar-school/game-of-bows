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

struct FireArrow {
  // Creating Constructor
  FireArrow() {}

  // Making the operator
  void operator()(Character& player, sf::Time) const { player.fire(); }
};

struct DoNothing {
  // Creating Constructor
  DoNothing() {}

  // Making the operator
  void operator()(Character& player, sf::Time) const {}
};

Player::Player() : _vertical(0), _horizontal(0) {
  _keyBinding[sf::Keyboard::A] = MoveLeft;
  _keyBinding[sf::Keyboard::D] = MoveRight;
  _keyBinding[sf::Keyboard::W] = Jump;
  _keyBinding[sf::Keyboard::Space] = Fire;

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
  _actionBindingPress[Fire].action = derivedAction<Character>(FireArrow());
  _actionBindingRelease[MoveLeft].action = derivedAction<Character>(Halt());
  _actionBindingRelease[MoveRight].action = derivedAction<Character>(Halt());
  _actionBindingRelease[Jump].action = derivedAction<Character>(MovePlayer(0.f, 0.f));
  _actionBindingRelease[Fire].action = derivedAction<Character>(DoNothing());
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

  if (event.type == sf::Event::JoystickButtonPressed) {
    if (event.joystickButton.button == 6) {
      Command jump;
      jump.category = Category::PlayerTwo;
      jump.action = derivedAction<Character>(MovePlayer(0.f, -250.f));
      commands.push(jump);
    }
    if (event.joystickButton.button == 7) {
      Command shoot;
      shoot.category = Category::PlayerTwo;
      shoot.action = derivedAction<Character>(FireArrow());
      commands.push(shoot);
    }
  }

  // Handle Aiming
  Command aim;
  aim.category = Category::PlayerOne;
  aim.action = derivedAction<Character>(Aim(_vertical, _horizontal, commands));
  commands.push(aim);
}

void Player::handleRealtimeInput(CommandQueue& commands) {
  sf::Joystick::update();

  for (auto& pair : _keyBinding) {
    if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second)) {
      commands.push(_actionBindingPress[pair.second]);
    }
  }
  if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 15.f) {
    Command moveRight;
    moveRight.category = Category::PlayerTwo;
    moveRight.action = derivedAction<Character>(MovePlayer(250.f, 0.f));
    commands.push(moveRight);
  }

  if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -15.f) {
    Command moveLeft;
    moveLeft.category = Category::PlayerTwo;
    moveLeft.action = derivedAction<Character>(MovePlayer(-250.f, 0.f));
    commands.push(moveLeft);
  }

  if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) > -15.f &&
      sf::Joystick::getAxisPosition(0, sf::Joystick::X) < 15.f) {
    Command halt;
    halt.category = Category::PlayerTwo;
    halt.action = derivedAction<Character>(Halt());
    commands.push(halt);
  }

  if (sf::Joystick::getAxisPosition(0, sf::Joystick::U) < -50.f) {
    Command aim;
    aim.category = Category::PlayerTwo;
    float y = sf::Joystick::getAxisPosition(0, sf::Joystick::V);
    if (y > 45.f) {
      aim.action = derivedAction<Character>(Aim(2, 1, commands));
    } else if (y < -45.f) {
      aim.action = derivedAction<Character>(Aim(1, 1, commands));
    } else {
      aim.action = derivedAction<Character>(Aim(0, 1, commands));
    }
    commands.push(aim);
  } else if (sf::Joystick::getAxisPosition(0, sf::Joystick::U) > 50.f) {
    Command aim;
    aim.category = Category::PlayerTwo;
    float y = sf::Joystick::getAxisPosition(0, sf::Joystick::V);
    if (y > 45.f) {
      aim.action = derivedAction<Character>(Aim(2, 2, commands));
    } else if (y < -45.f) {
      aim.action = derivedAction<Character>(Aim(1, 2, commands));
    } else {
      aim.action = derivedAction<Character>(Aim(0, 2, commands));
    }
    commands.push(aim);
  } else if (sf::Joystick::getAxisPosition(0, sf::Joystick::V) > 50.f) {
    Command aim;
    aim.category = Category::PlayerTwo;
    aim.action = derivedAction<Character>(Aim(2, 0, commands));
    commands.push(aim);
  } else if (sf::Joystick::getAxisPosition(0, sf::Joystick::V) < -50.f) {
    Command aim;
    aim.category = Category::PlayerTwo;
    aim.action = derivedAction<Character>(Aim(1, 0, commands));
    commands.push(aim);
  } else {
    Command aim;
    aim.category = Category::PlayerTwo;
    aim.action = derivedAction<Character>(Aim(0, 0, commands));
    commands.push(aim);
  }
}

bool Player::isRealtimeAction(Action action) {
  switch (action) {
      //   case MoveLeft:
      //   case MoveRight:
      //   case Jump:
      //     return true;

    default:
      return false;
  }
}
