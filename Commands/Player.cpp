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

Player::Player() {
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
    // Check if pressed key appears in key binding, trigger command if so
    auto found = _keyBinding.find(event.key.code);
    if (found != _keyBinding.end() && !isRealtimeAction(found->second)) {
      commands.push(_actionBindingPress[found->second]);
    }
  }
  if (event.type == sf::Event::KeyReleased) {
    // Check if pressed key appears in key binding, trigger command if so
    auto found = _keyBinding.find(event.key.code);
    if (found != _keyBinding.end() && !isRealtimeAction(found->second)) {
      commands.push(_actionBindingRelease[found->second]);
    }
  }
}

void Player::handleRealtimeInput(CommandQueue& commands) {
  for (auto& pair : _keyBinding) {
    if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
      commands.push(_actionBindingPress[pair.second]);
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
