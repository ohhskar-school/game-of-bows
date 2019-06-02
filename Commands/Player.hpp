#ifndef RC_PLAYER
#define RC_PLAYER

//SFML Modules
#include <SFML/Window/Event.hpp>

//User Defined
#include "../Entities/Character.hpp"
#include "Command.hpp"
#include "CommandQueue.hpp"


//Player Class
class Player {
 public:
  void handleEvent(const sf::Event& event, CommandQueue& commands);
  void handleRealtimeInput(CommandQueue& commands);
};

//Action Functors

#endif