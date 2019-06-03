#ifndef RC_PLAYER
#define RC_PLAYER

// SFML Modules
#include <SFML/Window/Event.hpp>

// User Defined
#include "../Entities/Character.hpp"
#include "Command.hpp"
#include "CommandQueue.hpp"

class CommandQueue;

// Player Class
class Player {
 public:
  enum Action { MoveLeft, MoveRight, Jump, Fire, ActionCount };

  Player();
  void handleEvent(const sf::Event& event, CommandQueue& commands);
  void handleRealtimeInput(CommandQueue& commands);

  void assignKey(Action action, sf::Keyboard::Key key);
  sf::Keyboard::Key getAssignedKey(Action action) const;

 private:
  std::map<sf::Keyboard::Key, Action> _keyBinding;
  std::map<Action, Command> _actionBindingPress;
  std::map<Action, Command> _actionBindingRelease;

  unsigned int _vertical;
  unsigned int _horizontal;

  void initializeActions();
  static bool isRealtimeAction(Action action);
};

// Action Functors

#endif