#ifndef RC_GAME
#define RC_GAME

// SFML Modules
#include <SFML/Graphics.hpp>

#include "World.hpp"

class Game {
 public:
  Game();
  void run();

 private:
  void processInput();
  void update(sf::Time);
  void render();

  sf::RenderWindow _window;
  World _world;
  static const sf::Time TimePerFrame;
};

#endif