#ifndef RC_APPLICATION
#define RC_APPLICATION

#include "Commands/Player.hpp"
#include "ResourceManager.hpp"
#include "States/StateStack.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>

class Application {
 public:
  Application();
  void run();

 private:
  void processInput();
  void update(sf::Time dt);
  void render();

  void updateStatistics(sf::Time dt);
  void registerStates();

 private:
  static const sf::Time TimePerFrame;

  sf::RenderWindow _Window;
  TextureHolder _Textures;
  FontHolder _Fonts;
  Player _Player;

  StateStack _StateStack;

  sf::Text _StatisticsText;
  sf::Time _StatisticsUpdateTime;
  std::size_t _StatisticsNumFrames;
};

#endif
